#### RabbitMQ
消息队列中间件是分布式系统中重要的组件，主要解决应用耦合、异步消息、流量削锋等问题，
实现高性能、高可用、可伸缩和最终一致性架构，是大型分布式系统不可缺少的中间件

##### 常用消息队列: 
- ActiveMQ
- RabbitMQ
- ZeroMQ
- Kafka
- MetaMQ
- RocketMQ 

##### 特性:
- 异步性, 将耗时的同步操作通过以发送消息的方式进行了异步化处理, 减少了同步等待的时间
- 松耦合, 消息队列减少了服务之间的耦合性, 不同的服务可以通过消息队列进行通信，而不用关心彼此的实现细节, 只要定义好消息的格式就行
- 分布式, 通过对消费者的横向扩展, 降低了消息队列阻塞的风险, 以及单个消费者产生单点故障的可能性（当然消息队列本身也可以做成分布式集群）
- 可靠性, 消息队列一般会把接收到的消息存储到本地硬盘上（当消息被处理完之后，存储信息根据不同的消息队列实现，有可能将其删除）, 这样即使应用挂掉或者消息队列本身挂掉, 消息也能够重新加载

队列服务，会有三个概念：发消息者、队列、收消息者
RabbitMQ 在这个基本概念之上，多做了一层抽象，在发消息者和队列之间加入了交换器（Exchange）

##### 虚拟主机、交换机、队列和绑定
- 虚拟主机: 一个虚拟主机持有一组交换机、队列和绑定
- 交换机: Exchange 用于转发消息, 但是它不会做存储, 如果没有 Queue bind 到 Exchange 的话, 它会直接丢弃掉 Producer 发送过来的消息
- 路由键: 消息到交换机的时候, 交互机会转发到对应的队列中, 那么究竟转发到哪个队列, 就要根据该路由键的情况
- 绑定: 也就是交换机需要和队列相绑定，这其中如上图所示，是多对多的关系

##### Direct & Topic & Headers & Fanout
Direct: 该类型的行为是 "先匹配，再投送", 即在绑定时设定一个 routing_key, 消息的 routing_key 匹配时, 才会被交换器投送到绑定的队列中去
Topic: 按规则转发消息（最灵活）
Headers: 设置 header attribute 参数类型的交换机
Fanout: 转发消息到所有绑定队列

##### Direct Exchange
Direct Exchange 是 RabbitMQ 默认的交换机模式，也是最简单的模式，根据 key 全文匹配去寻找队列

##### Topic Exchange
Topic Exchange 转发消息主要是根据通配符
交换机模式:
- 路由键必须是一串字符，用句号（.）隔开
- 路由模式必须包含一个星号（*）

##### Headers Exchange
Headers 也是根据规则匹配，相较于 direct 和 topic 固定地使用 routing_key，Headers 则是一个自定义匹配规则的类型

##### Fanout Exchange
Fanout Exchange 消息广播的模式, 不管路由键或者是路由模式, 会把消息发给绑定给它的全部队列, 如果配置了routing_key会被忽略

##### Spring Boot 集成 RabbitMQ
- 配置 pom 包, 主要是添加 spring-boot-starter-amqp 的支持
```java
<dependency>
  <groupId>org.springframework.boot</groupId>
  <artifactId>spring-boot-starter-amqp</artifactId>
</dependency>
```

- 配置文件, 配置 rabbitmq 的安装地址、端口及账户信息
```
spring.application.name = spirng-boot-rabbitmq
spring.rabbitmq.host = 192.168.0.1
spring.rabbitmq.port = 5672
spring.rabbitmq.username = admin
spring.rabbitmq.password = 123456
```

- 定义队列
```java
@Configuration
public class RabbitConfig {
  @Bean
  public Queue Queue () {
    return new Queue("hello");
  }
}
```

- 发送者
```java
public class HelloSender {
  @Autowired
  private AmqpTemplate rabbitTemplate;
  public void send() {
    String context = "hello " + new Date();
    System.out.println("Sender : " + context);
    this.rabbitTemplate.convertAndSend("hello", context);
  }
}
```

- 接收者
```java
@Component
@RabbitListener(queues = "hello")
public class HelloReceiver {
  @RabbitHandler
  public void process(String hello) {
    System.out.println("Receiver  : " + hello);
  }
}
```

- 测试
```java
@RunWith(SpringRunner.class)
@Spring BootTest
public class RabbitMqHelloTest {
  @Autowired
  private HelloSender helloSender;
  @Test
  public void hello() throws Exception {
    helloSender.send();
    Thread.sleep(1000l);
  }
}
```

#### 多方测试
- 一对多发送
  - 发送者
```java
@Component
public class NeoSender {
    @Autowired
    private AmqpTemplate rabbitTemplate;
    public void send(int i) {
      String context = "spirng boot neo queue" + " ****** " + i;
      System.out.println("Sender1 : " + context);
      this.rabbitTemplate.convertAndSend("neo", context);
    }
}
```
  - 接收者
```
@Component
@RabbitListener(queues = "neo")
public class NeoReceiver1 {
  @RabbitHandler
  public void process(String neo) {
    System.out.println("Receiver 1: " + neo);
  }
}
```

#### 多对多发送
```java
public void send(int i) {
  String context = "spirng boot neo queue" + " ****** "+i;
  System.out.println("Sender2 : " + context);
  this.rabbitTemplate.convertAndSend("neo", context);
}
```

```java
@Test
public void manyToMany() throws Exception {
  for (int i=0;i<100;i++){
    neoSender.send(i);
    neoSender2.send(i);
  }

  Thread.sleep(10000l);
}
```

#### 高级使用
##### Topic Exchange
Topic 是 RabbitMQ 中最灵活的一种方式，可以根据 routing_key 自由的绑定不同的队列
```java
@Configuration
public class TopicRabbitConfig {
  final static String message = "topic.message";
  final static String messages = "topic.messages";

  // 定义队列
  @Bean
  public Queue queueMessage() {
    return new Queue(TopicRabbitConfig.message);
  }

  @Bean
  public Queue queueMessages() {
    return new Queue(TopicRabbitConfig.messages);
  }

  // 交换机
  @Bean
  TopicExchange exchange() {
      return new TopicExchange("exchange");
  }

  // 将队列和交换机绑定
  @Bean
  Binding bindingExchangeMessage(Queue queueMessage, TopicExchange exchange) {
    return BindingBuilder.bind(queueMessage).to(exchange).with("topic.message");
  }

  @Bean
  Binding bindingExchangeMessages(Queue queueMessages, TopicExchange exchange) {
    return BindingBuilder.bind(queueMessages).to(exchange).with("topic.#");
  }
}
```
```java
public void send1 () {
    String context = "hi, i am message 1";
    System.out.println("Sender : " + context);
    this.rabbitTemplate.convertAndSend("exchange", "topic.message", context);
}

public void send2 () {
    String context = "hi, i am messages 2";
    System.out.println("Sender : " + context);
    this.rabbitTemplate.convertAndSend("exchange", "topic.messages", context);
}
```

##### Fanout Exchange
```java
@Configuration
public class FanoutRabbitConfig {
  // 定义队列
  @Bean
  public Queue AMessage() {
    return new Queue("fanout.A");
  }
  @Bean
  public Queue BMessage() {
    return new Queue("fanout.B");
  }
  @Bean
  public Queue CMessage() {
    return new Queue("fanout.C");
  }
  // 定义交换机
  @Bean
  FanoutExchange fanoutExchange() {
    return new FanoutExchange("fanoutExchange");
  }
  // 分部进行绑定
  @Bean
  Binding bindingExchangeA(Queue AMessage,FanoutExchange fanoutExchange) {
    return BindingBuilder.bind(AMessage).to(fanoutExchange);
  }
  @Bean
  Binding bindingExchangeB(Queue BMessage, FanoutExchange fanoutExchange) {
    return BindingBuilder.bind(BMessage).to(fanoutExchange);
  }
  @Bean
  Binding bindingExchangeC(Queue CMessage, FanoutExchange fanoutExchange) {
    return BindingBuilder.bind(CMessage).to(fanoutExchange);
  }
}
```

