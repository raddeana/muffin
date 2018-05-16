#### Spark
Spark是一个快速的、通用的分布式计算系统，而分布式的特性就意味着，必然存在节点间的通信

##### Spark的RPC主要在两个模块中
- 在 Spark-core 中, 主要承载了更好的封装server和client的作用, 以及和scala语言的融合, 它依赖于模块org.apache.spark.spark-network-common
- 在 org.apache.spark.spark-network-common 中, 该模块是java语言编写的
- 最新版本是基于netty4开发的, 提供全双工、多路复用I/O模型的Socket I/O 能力Spark的传输协议结构（wire protocol）也是自定义的

#### 简单示例
##### 定义一个 HelloEndpoint 继承自 RpcEndpoint 表明可以并发的调用该服务, 如果继承自 ThreadSafeRpcEndpoint 则表明该 Endpoint 不允许并发

```java
class HelloEndpoint(override val rpcEnv: RpcEnv) extends RpcEndpoint {
  override def onStart(): Unit = {
    println("start hello endpoint")
  }

  override def receiveAndReply(context: RpcCallContext): PartialFunction[Any, Unit] = {
    case SayHi(msg) => {
      println(s"receive $msg")
      context.reply(s"hi, $msg")
    }
    case SayBye(msg) => {
      println(s"receive $msg")
      context.reply(s"bye, $msg")
    }
  }

  override def onStop(): Unit = {
    println("stop hello endpoint")
  }
}

case class SayHi(msg: String)
case class SayBye(msg: String)
```

##### 把刚刚开发好的 Endpoint 交给Spark RPC管理其生命周期, 用于响应外部请求
```java
val config = RpcEnvServerConfig(new RpcConf(), "hello-server", "localhost", 52345)
val rpcEnv: RpcEnv = NettyRpcEnvFactory.create(config)
val helloEndpoint: RpcEndpoint = new HelloEndpoint(rpcEnv)
rpcEnv.setupEndpoint("hello-service", helloEndpoint)
rpcEnv.awaitTermination()
```

##### 开发一个client调用刚刚启动的server, 首先RpcEnvClientConfig和RpcEnv都是必须的
```java
val rpcConf = new RpcConf()
val config = RpcEnvClientConfig(rpcConf, "hello-client")
val rpcEnv: RpcEnv = NettyRpcEnvFactory.create(config)
val endPointRef: RpcEndpointRef = rpcEnv.setupEndpointRef(RpcAddress("localhost", 52345), "hell-service")
val future: Future[String] = endPointRef.ask[String](SayHi("neo"))

future.onComplete {
  case scala.util.Success(value) => println(s"Got the result = $value")
  case scala.util.Failure(e) => println(s"Got error: $e")
}

Await.result(future, Duration.apply("30s"))
val result = endPointRef.askWithRetry[String](SayBye("neo"))
```
- 这就是Spark RPC的通信过程，使用起来易用性可想而知
- 非常简单，RPC框架屏蔽了Socket I/O模型、线程模型、序列化/反序列化过程、使用netty做了包识别
- 长连接，网络重连重试等机制

#### 实际应用
- 在 Spark 内部，很多的 Endpoint 以及 EndpointRef 与之通信都是通过这种形式的
- 举例来说比如 driver 和 executor 之间的交互用到了心跳机制，使用 HeartbeatReceiver 来实现，这也是一个 Endpoint
- 它的注册在 SparkContext 初始化的时候做的
```java
_heartbeatReceiver = env.rpcEnv.setupEndpoint(HeartbeatReceiver.ENDPOINT_NAME, new HeartbeatReceiver(this))
```

```java
val message = Heartbeat(executorId, accumUpdates.toArray, env.blockManager.blockManagerId)
val response = heartbeatReceiverRef.askWithRetry[HeartbeatResponse](message, RpcTimeout(conf, "spark.executor.heartbeatInterval", "10s"))
```

##### Spark RPC模块的设计原理
- 在Spark内部, 很多的Endpoint以及EndpointRef与之通信都是通过这种形式的
- 比如driver和executor之间的交互用到了心跳机制, 使用HeartbeatReceiver来实现, 这也是一个Endpoint

```java
_heartbeatReceiver = env.rpcEnv.setupEndpoint(HeartbeatReceiver.ENDPOINT_NAME, new HeartbeatReceiver(this))
```
```java
val message = Heartbeat(executorId, accumUpdates.toArray, env.blockManager.blockManagerId)
val response = heartbeatReceiverRef.askWithRetry[HeartbeatResponse](message, RpcTimeout(conf, "spark.executor.heartbeatInterval", "10s")) 
```

##### Spark RPC 模块的设计原理
Spark RPC 中有如下映射关系

```java
RpcEndpoint => Actor
RpcEndpointRef => ActorRef
RpcEnv => ActorSystem
```
底层通信全部使用netty进行了替换，使用的是org.apache.spark.spark-network-common这个内部lib

#### 类图分析
##### RpcEndpoint & RpcCallContext
- 先看最左侧的RpcEndpoint，RpcEndpoint是一个可以响应请求的服务，和Akka中的Actor类似，从它的提供的方法签名（如下）可以看出
- receive方法是单向方式的，可以比作UDP，而receiveAndReply是应答方式的，可以比作TCP

##### RpcEndpointRef
- RpcEndpointRef类似于Akka中ActorRef，顾名思义，它是RpcEndpoint的引用，提供的方法send等同于

##### RpcEnv & NettyRpcEnv
- 类库中最核心的就是RpcEnv，刚刚提到了这就是ActorSystem，服务端和客户端都可以使用它来做通信

##### Dispatcher & Inbox
- NettyRpcEnv中包含Dispatcher，主要针对服务端，帮助路由到正确的RpcEndpoint，并且调用其业务逻辑

##### Outbox
- NettyRpcEnv中包含一个ConcurrentHashMap[RpcAddress, Outbox], 每个远程Endpoint都对应一个Outbox
- 这和上面Inbox遥相呼应, 是一个mailbox似的实现方式

##### spark-network-common
#### Spark RPC 核心技术总结
- Spark RPC作为RPC传输层选择TCP协议，做可靠的、全双工的 binary stream 通道
- CPU 和 I / O 之前天然存在着差异, 网络传输的延时不可控, CPU资源宝贵, 系统进程 / 线程资源宝贵
- 为了尽可能避免 Socket I / O 阻塞服务端和客户端调用, 有一些模式（pattern）是可以应用的
- Spark RPC的 I / O Model 由于采用了 Netty, 因此使用的底层的 I / O 多路复用（I / O Multiplexing）机制
- 这里可以通过spark.rpc.io.mode参数设置, 不同的平台使用的技术不同, 例如linux使用epoll
- 线程模型采用Multi-Reactors + mailbox的异步方式来处理
- Schema Declaration和序列化方面, Spark RPC默认采用Java native serialization方案, 主要从兼容性和JVM平台内部组件通信
- 协议结构, Spark RPC采用私有的wire format如下, 采用headr+payload的组织方式, header中包括整个frame的长度, message的类型, 请求UUID
