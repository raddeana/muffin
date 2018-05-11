#### RPC
RPC (Remote Procedure Call) 即远程过程调用, 允许一台计算机调用另一台计算机上的程序得到结果, 而代码中不需要做额外的编程, 就像在本地调用一样

#### 在RPC框架中主要有三个角色: 
- Provider
- Consumer
- Registry

#### 节点角色说明:
- * Server: 暴露服务的服务提供方
- * Client: 调用远程服务的服务消费方
- * Registry: 服务注册与发现的注册中心

#### RPC调用流程
- 服务消费方（client）调用以本地调用方式调用服务
- client stub接收到调用后负责将方法、参数等组装成能够进行网络传输的消息体
- client stub找到服务地址，并将消息发送到服务端
- server stub收到消息后进行解码
- server stub根据解码结果调用本地的服务
- 本地服务执行并将结果返回给server stub
- server stub将返回结果打包成消息并发送至消费方
- client stub接收到消息，并进行解码
- 服务消费方得到最终结果

#### 服务注册&发现
- 服务提供者启动后主动向注册中心注册机器ip、port以及提供的服务列表
- 服务消费者启动时向注册中心获取服务提供方地址列表，可实现软负载均衡和Failover

#### 使用到的技术
- 动态代理
生成 client stub和server stub需要用到 Java 动态代理技术, 我们可以使用JDK原生的动态代理机制, 可以使用一些开源字节码工具框架
- 序列化
为了能在网络上传输和接收 Java对象，我们需要对它进行 序列化和反序列化操作
- * 序列化：将Java对象转换成byte[]的过程，也就是编码的过程
- * 反序列化：将byte[]转换成Java对象的过程

Java原生的序列化机制, 但是效率非常低, 推荐使用一些开源的、成熟的序列化技术, 例如：protobuf、Thrift、hessian、Kryo、Msgpack

#### NIO 
RPC框架都直接基于netty这一IO通信框架, 比如阿里巴巴的HSF、dubbo，Hadoop Avro, 推荐使用 Netty 作为底层通信框架

#### 服务注册中心
- * Redis 
- * Zookeeper 
- * Consul 
- * Etcd

