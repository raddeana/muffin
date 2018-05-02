#### 消息队列
消息（Message）是指在应用间传送的数据。消息可以非常简单，比如只包含文本字符串，也可以更复杂，可能包含嵌入对象
消息队列（Message Queue）是一种应用间的通信方式，消息发送后可以立即返回，由消息系统来确保消息的可靠传递
消息发布者只管把消息发布到 MQ 中而不用管谁来取，消息使用者只管从 MQ 中取消息而不管是谁发布的
这样发布者和使用者都不用知道对方的存在

#### RabbitMQ 特点
RabbitMQ 是一个由 Erlang 语言开发的 AMQP 的开源实现
- AMQP ：Advanced Message Queue，高级消息队列协议
- RabbitMQ 最初起源于金融系统，用于在分布式系统中存储转发消息

#### Benefits
- 可靠性（Reliability）
  - RabbitMQ 使用一些机制来保证可靠性，如持久化、传输确认、发布确认

- 灵活的路由（Flexible Routing）
  - 在消息进入队列之前，通过 Exchange 来路由消息的
  - 对于典型的路由功能，RabbitMQ 已经提供了一些内置的 Exchange 来实现
  - 针对更复杂的路由功能，可以将多个 Exchange 绑定在一起，也通过插件机制实现自己的 Exchange

- 消息集群（Clustering）
  - 多个 RabbitMQ 服务器可以组成一个集群，形成一个逻辑 Broker

- 高可用（Highly Available Queues）
  - 队列可以在集群中的机器上进行镜像，使得在部分节点出问题的情况下队列仍然可用

- 多种协议（Multi-protocol）
  - RabbitMQ 支持多种消息队列协议，比如 STOMP、MQTT 等等

- 多语言客户端（Many Clients）
  - RabbitMQ 几乎支持所有常用语言，比如 Java、.NET、Ruby 等等

- 管理界面（Management UI）
  - RabbitMQ 提供了一个易用的用户界面，使得用户可以监控和管理消息 Broker 的许多方面

- 跟踪机制（Tracing）
  - 如果消息异常，RabbitMQ 提供了消息跟踪机制，使用者可以找出发生了什么

- 插件机制（Plugin System）
  - RabbitMQ 提供了许多插件，来从多方面进行扩展，也可以编写自己的插件

#### 概念模型
消费者（consumer）订阅某个队列。生产者（producer）创建消息，然后发布到队列（queue）中，最后将消息发送到监听的消费者

#### 基本概念
- Message
  - 消息，消息是不具名的，它由消息头和消息体组成
- Publisher
  - 消息的生产者，也是一个向交换器发布消息的客户端应用程序
- Exchange
  - 交换器，用来接收生产者发送的消息并将这些消息路由给服务器中的队列
- Binding
 - 绑定，用于消息队列和交换器之间的关联
- Queue
  - 消息队列，用来保存消息直到发送给消费者
- Connection
  - 网络连接，比如一个TCP连接
- Channel
  - 信道，多路复用连接中的一条独立的双向数据流通道
- Consumer
 - 消息的消费者，表示一个从消息队列中取得消息的客户端应用程序
- Virtual Host
 - 虚拟主机，表示一批交换器、消息队列和相关对象
- Broker
 - 表示消息队列服务器实体

#### AMQP 中的消息路由
AMQP 中消息的路由过程和 Java 开发者熟悉的 JMS 存在一些差别，AMQP 中增加了 Exchange 和 Binding 的角色
生产者把消息发布到 Exchange 上，消息最终到达队列并被消费者接收，而 Binding 决定交换器的消息应该发送到那个队列

#### Exchange 类型
Exchange分发消息时根据类型的不同分发策略有区别，目前共四种类型：direct、fanout、topic、headers

- direct
  - 消息中的路由键（routing key）如果和 Binding 中的 binding key 一致， 交换器就将消息发到对应的队列中
- fanout
  - 每个发到 fanout 类型交换器的消息都会分到所有绑定的队列上去
- topic
  - topic 交换器通过模式匹配分配消息的路由键属性，将路由键和某个模式进行匹配，此时队列需要绑定到一个模式上

#### 安装
```cmd
brew install rabbitmq
```

#### 运行和管理
- 启动
```cmd
./sbin/rabbitmq-server
```
- 后台启动
```
./sbin/rabbitmq-server -detached
``
- 查询服务器状态
  - sbin 目录下有个特别重要的文件叫 rabbitmqctl ，它提供了 RabbitMQ 管理需要的几乎一站式解决方案，绝大部分的运维命令它都可以提供
```cmd
./sbin/rabbitmqctl status
```

- 关闭 RabbitMQ 节点
我们知道 RabbitMQ 是用 Erlang 语言写的，在Erlang 中有两个概念：节点和应用程序
```cmd
./sbin/rabbitmqctl stop
./sbin/rabbitmqctl -n rabbit@server.example.com stop 
```

- 关闭 RabbitMQ
```cmd
./sbin/rabbitmqctl stop_app
```

- 启动 RabbitMQ 应用程序
```cmd
./sbin/rabbitmqctl start_app
```

- 重置 RabbitMQ 节点
```cmd
./sbin/rabbitmqctl reset
```

- 查看已声明的队列
```cmd
./sbin/rabbitmqctl list_queues
```

- 查看交换器
```cmd
./sbin/rabbitmqctl list_exchanges
```

```cmd
./sbin/rabbitmqctl list_exchanges name type durable auto_delete
```

- 查看绑定
```cmd
./sbin/rabbitmqctl list_bindings
```

#### Java 客户端访问
- maven工程的pom文件中添加依赖
```xml
<dependency>
    <groupId>com.rabbitmq</groupId>
    <artifactId>amqp-client</artifactId>
    <version>4.1.0</version>
</dependency>
```

- 消息生产者
```java
package org.study.rabbitmq;
import com.rabbitmq.client.Channel;
import com.rabbitmq.client.Connection;
import com.rabbitmq.client.ConnectionFactory;
import java.io.IOException;
import java.util.concurrent.TimeoutException;

public class Producer {
  public static void main(String[] args) throws IOException, TimeoutException {
    // 创建连接工厂
    ConnectionFactory factory = new ConnectionFactory();
    factory.setUsername("guest");
    factory.setPassword("guest");
    
    // 设置 RabbitMQ 地址
    factory.setHost("localhost");
    
    // 建立到代理服务器到连接
    Connection conn = factory.newConnection();
    
    // 获得信道
    Channel channel = conn.createChannel();
    
    // 声明交换器
    String exchangeName = "hello-exchange";
    channel.exchangeDeclare(exchangeName, "direct", true);
    String routingKey = "hola";
    
    // 发布消息
    byte[] messageBodyBytes = "quit".getBytes();
    channel.basicPublish(exchangeName, routingKey, null, messageBodyBytes);

    channel.close();
    conn.close();
  }
}
```

#### 消息消费者
```java
package org.study.rabbitmq;
import com.rabbitmq.client.*;
import java.io.IOException;
import java.util.concurrent.TimeoutException;

public class Consumer {
  public static void main(String[] args) throws IOException, TimeoutException {
    ConnectionFactory factory = new ConnectionFactory();
    factory.setUsername("guest");
    factory.setPassword("guest");
    factory.setHost("localhost");
    
    // 建立到代理服务器到连接
    Connection conn = factory.newConnection();
    
    // 获得信道
    final Channel channel = conn.createChannel();
    
    // 声明交换器
    String exchangeName = "hello-exchange";
    channel.exchangeDeclare(exchangeName, "direct", true);
    
    // 声明队列
    String queueName = channel.queueDeclare().getQueue();
    String routingKey = "hola";
    
    // 绑定队列，通过键 hola 将队列和交换器绑定起来
    channel.queueBind(queueName, exchangeName, routingKey);

    while (true) {
      // 消费消息
      boolean autoAck = false;
      String consumerTag = "";
      channel.basicConsume(queueName, autoAck, consumerTag, new DefaultConsumer (channel) {
        @Override
        public void handleDelivery(String consumerTag, Envelope envelope, AMQP.BasicProperties properties, byte[] body) throws IOException {
          String routingKey = envelope.getRoutingKey();
          String contentType = properties.getContentType();
          
          System.out.println("消费的路由键：" + routingKey);
          System.out.println("消费的内容类型：" + contentType);
          long deliveryTag = envelope.getDeliveryTag();
          
          // 确认消息
          channel.basicAck(deliveryTag, false);
          System.out.println("消费的消息体内容：");
          String bodyStr = new String(body, "UTF-8");
          System.out.println(bodyStr);
        }
      });
    }
  }
}
```

> 作者：预流
> 链接：https://www.jianshu.com/p/79ca08116d57
> 來源：简书
> 著作权归作者所有，商业转载请联系作者获得授权，非商业转载请注明出处
