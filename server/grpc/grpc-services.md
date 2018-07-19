### 集中式LB（Proxy Model）
在服务消费者和服务提供者之间有一个独立的LB，通常是专门的硬件设备如 F5，或者基于软件如 LVS，HAproxy等实现
| DNS | -> Discover -> | Consumer | -> Load Balancer -> | Invoke | -> Load Balancing & Invoke -> | Service Provider |
- 单点问题，所有服务调用流量都经过LB，当服务数量和调用量大的时候，LB容易成为瓶颈，且一旦LB发生故障影响整个系统；
- 服务消费方、提供方之间增加了一级，有一定性能开销。

### 进程内LB（Balancing-aware Client）
针对第一个方案的不足，此方案将LB的功能集成到服务消费方进程里，也被称为软负载或者客户端负载方案
- 开发成本，该方案将服务调用方集成到客户端的进程里头，如果有多种不同的语言栈，就要配合开发多种不同的客户端，有一定的研发和维护成本
- 另外生产环境中，后续如果要对客户库进行升级，势必要求服务调用方修改代码并重新发布，升级较复杂

### 独立 LB 进程（External Load Balancing Service）
该方案是针对第二种方案的不足而提出的一种折中方案，原理和第二种方案基本类似

### 服务发现负载均衡实现
gRPC开源组件官方并未直接提供服务注册与发现的功能实现，但其设计文档已提供实现的思路，并在不同语言的gRPC代码API中已提供了命名解析和负载均衡接口供扩展
其基本实现原理：
- 服务启动后gRPC客户端向命名服务器发出名称解析请求，名称将解析为一个或多个IP地址，每个IP地址标示它是服务器地址还是负载均衡器地址，以及标示要使用那个客户端负载均衡策略或服务配置。
- 客户端实例化负载均衡策略，如果解析返回的地址是负载均衡器地址，则客户端将使用grpclb策略，否则客户端使用服务配置请求的负载均衡策略
- 负载均衡策略为每个服务器地址创建一个子通道（channel）
- 当有rpc请求时，负载均衡策略决定那个子通道即grpc服务器将接收请求，当可用服务器为空时客户端的请求将被阻塞

根据gRPC官方提供的设计思路，基于进程内LB方案（即第2个案，阿里开源的服务框架 Dubbo 也是采用类似机制）
结合分布式一致的组件（如Zookeeper、Consul、Etcd），可找到gRPC服务发现和负载均衡的可行解决方案

- 命名解析实现：resolver.go
```go
package etcdv3

import (
    "errors"
    "fmt"
    "strings"
    etcd3 "github.com/coreos/etcd/clientv3"
    "google.golang.org/grpc/naming"
)

// resolver is the implementaion of grpc.naming.Resolver
type resolver struct {
    serviceName string // service name to resolve
}

// NewResolver return resolver with service name
func NewResolver(serviceName string) *resolver {
    return &resolver{serviceName: serviceName}
}

// Resolve to resolve the service from etcd, target is the dial address of etcd
// target example: "http://127.0.0.1:2379,http://127.0.0.1:12379,http://127.0.0.1:22379"
func (re *resolver) Resolve(target string) (naming.Watcher, error) {
    if re.serviceName == "" {
        return nil, errors.New("grpclb: no service name provided")
    }

    // generate etcd client
    client, err := etcd3.New(etcd3.Config{
        Endpoints: strings.Split(target, ","),
    })
    if err != nil {
        return nil, fmt.Errorf("grpclb: creat etcd3 client failed: %s", err.Error())
    }

    // Return watcher
    return &watcher{re: re, client: *client}, nil
}
```

- 服务发现实现：watcher.go
```go
package etcdv3

import (
    "fmt"
    etcd3 "github.com/coreos/etcd/clientv3"
    "golang.org/x/net/context"
    "google.golang.org/grpc/naming"
    "github.com/coreos/etcd/mvcc/mvccpb"
)

// watcher is the implementaion of grpc.naming.Watcher
type watcher struct {
    re            *resolver // re: Etcd Resolver
    client        etcd3.Client
    isInitialized bool
}

// Close do nothing
func (w *watcher) Close() {
}

// Next to return the updates
func (w *watcher) Next() ([]*naming.Update, error) {
    // prefix is the etcd prefix/value to watch
    prefix := fmt.Sprintf("/%s/%s/", Prefix, w.re.serviceName)

    // check if is initialized
    if !w.isInitialized {
        // query addresses from etcd
        resp, err := w.client.Get(context.Background(), prefix, etcd3.WithPrefix())
        w.isInitialized = true
        if err == nil {
            addrs := extractAddrs(resp)
            //if not empty, return the updates or watcher new dir
            if l := len(addrs); l != 0 {
                updates := make([]*naming.Update, l)
                for i := range addrs {
                    updates[i] = &naming.Update{Op: naming.Add, Addr: addrs[i]}
                }
                return updates, nil
            }
        }
    }

    // generate etcd Watcher
    rch := w.client.Watch(context.Background(), prefix, etcd3.WithPrefix())
    for wresp := range rch {
        for _, ev := range wresp.Events {
            switch ev.Type {
            case mvccpb.PUT:
                return []*naming.Update{{Op: naming.Add, Addr: string(ev.Kv.Value)}}, nil
            case mvccpb.DELETE:
                return []*naming.Update{{Op: naming.Delete, Addr: string(ev.Kv.Value)}}, nil
            }
        }
    }
    return nil, nil
}

func extractAddrs(resp *etcd3.GetResponse) []string {
    addrs := []string{}

    if resp == nil || resp.Kvs == nil {
        return addrs
    }

    for i := range resp.Kvs {
        if v := resp.Kvs[i].Value; v != nil {
            addrs = append(addrs, string(v))
        }
    }

    return addrs
}
```

- 服务注册实现：register.go
```go
package etcdv3

import (
    "fmt"
    "log"
    "strings"
    "time"

    etcd3 "github.com/coreos/etcd/clientv3"
    "golang.org/x/net/context"
    "github.com/coreos/etcd/etcdserver/api/v3rpc/rpctypes"
)

// Prefix should start and end with no slash
var Prefix = "etcd3_naming"
var client etcd3.Client
var serviceKey string

var stopSignal = make(chan bool, 1)

// Register
func Register(name string, host string, port int, target string, interval time.Duration, ttl int) error {
    serviceValue := fmt.Sprintf("%s:%d", host, port)
    serviceKey = fmt.Sprintf("/%s/%s/%s", Prefix, name, serviceValue)

    // get endpoints for register dial address
    var err error
    client, err := etcd3.New(etcd3.Config{
        Endpoints: strings.Split(target, ","),
    })
    if err != nil {
        return fmt.Errorf("grpclb: create etcd3 client failed: %v", err)
    }

    go func() {
        // invoke self-register with ticker
        ticker := time.NewTicker(interval)
        for {
            // minimum lease TTL is ttl-second
            resp, _ := client.Grant(context.TODO(), int64(ttl))
            // should get first, if not exist, set it
            _, err := client.Get(context.Background(), serviceKey)
            if err != nil {
                if err == rpctypes.ErrKeyNotFound {
                    if _, err := client.Put(context.TODO(), serviceKey, serviceValue, etcd3.WithLease(resp.ID)); err != nil {
                        log.Printf("grpclb: set service '%s' with ttl to etcd3 failed: %s", name, err.Error())
                    }
                } else {
                    log.Printf("grpclb: service '%s' connect to etcd3 failed: %s", name, err.Error())
                }
            } else {
                // refresh set to true for not notifying the watcher
                if _, err := client.Put(context.Background(), serviceKey, serviceValue, etcd3.WithLease(resp.ID)); err != nil {
                    log.Printf("grpclb: refresh service '%s' with ttl to etcd3 failed: %s", name, err.Error())
                }
            }
            select {
            case <-stopSignal:
                return
            case <-ticker.C:
            }
        }
    }()

    return nil
}

// UnRegister delete registered service from etcd
func UnRegister() error {
    stopSignal <- true
    stopSignal = make(chan bool, 1) // just a hack to avoid multi UnRegister deadlock
    var err error;
    if _, err := client.Delete(context.Background(), serviceKey); err != nil {
        log.Printf("grpclb: deregister '%s' failed: %s", serviceKey, err.Error())
    } else {
        log.Printf("grpclb: deregister '%s' ok.", serviceKey)
    }
    return err
}
```

- 接口描述文件：helloworld.proto
```go
syntax = "proto3";

option java_multiple_files = true;
option java_package = "com.midea.jr.test.grpc";
option java_outer_classname = "HelloWorldProto";
option objc_class_prefix = "HLW";

package helloworld;

// The greeting service definition.
service Greeter {
    //   Sends a greeting
    rpc SayHello (HelloRequest) returns (HelloReply) {
    }
}

// The request message containing the user's name.
message HelloRequest {
    string name = 1;
}

// The response message containing the greetings
message HelloReply {
    string message = 1;
}
```

- 实现服务端接口：helloworldserver.go
```go
package main

import (
    "flag"
    "fmt"
    "log"
    "net"
    "os"
    "os/signal"
    "syscall"
    "time"

    "golang.org/x/net/context"
    "google.golang.org/grpc"

    grpclb "com.midea/jr/grpclb/naming/etcd/v3"
    "com.midea/jr/grpclb/example/pb"
)

var (
    serv = flag.String("service", "hello_service", "service name")
    port = flag.Int("port", 50001, "listening port")
    reg = flag.String("reg", "http://127.0.0.1:2379", "register etcd address")
)

func main() {
    flag.Parse()

    lis, err := net.Listen("tcp", fmt.Sprintf("0.0.0.0:%d", *port))
    if err != nil {
        panic(err)
    }

    err = grpclb.Register(*serv, "127.0.0.1", *port, *reg, time.Second*10, 15)
    if err != nil {
        panic(err)
    }

    ch := make(chan os.Signal, 1)
    signal.Notify(ch, syscall.SIGTERM, syscall.SIGINT, syscall.SIGKILL, syscall.SIGHUP, syscall.SIGQUIT)
    go func() {
        s := <-ch
        log.Printf("receive signal '%v'", s)
        grpclb.UnRegister()
        os.Exit(1)
    }()

    log.Printf("starting hello service at %d", *port)
    s := grpc.NewServer()
    pb.RegisterGreeterServer(s, &server{})
    s.Serve(lis)
}

// server is used to implement helloworld.GreeterServer.
type server struct{}

// SayHello implements helloworld.GreeterServer
func (s *server) SayHello(ctx context.Context, in *pb.HelloRequest) (*pb.HelloReply, error) {
    fmt.Printf("%v: Receive is %s\n", time.Now(), in.Name)
    return &pb.HelloReply{Message: "Hello " + in.Name}, nil
}
```

- 实现客户端接口：helloworldclient.go
```go
package main

import (
    "flag"
    "fmt"
    "time"
    grpclb "com.midea/jr/grpclb/naming/etcd/v3"
    "com.midea/jr/grpclb/example/pb"
    "golang.org/x/net/context"
    "google.golang.org/grpc"
    "strconv"
)

var (
    serv = flag.String("service", "hello_service", "service name")
    reg = flag.String("reg", "http://127.0.0.1:2379", "register etcd address")
)

func main () {
    flag.Parse()
    r := grpclb.NewResolver(*serv)
    b := grpc.RoundRobin(r)

    ctx, _ := context.WithTimeout(context.Background(), 10*time.Second)
    conn, err := grpc.DialContext(ctx, *reg, grpc.WithInsecure(), grpc.WithBalancer(b))
    if err != nil {
        panic(err)
    }

    ticker := time.NewTicker(1 * time.Second)
    for t := range ticker.C {
        client := pb.NewGreeterClient(conn)
        resp, err := client.SayHello(context.Background(), &pb.HelloRequest{Name: "world " + strconv.Itoa(t.Second())})
        if err == nil {
            fmt.Printf("%v: Reply is %s\n", t, resp.Message)
        }
    }
}
```
