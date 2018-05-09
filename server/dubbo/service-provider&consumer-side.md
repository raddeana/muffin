### 基于 Spring 配置的服务
#### UserServiceBo
```java
public interface UserServiceBo {
    String sayHello(String name);  
    String testPojo(Person person);
}
```

```java
public interface Person {
}
```

#### UserServiceImpl
```java
public class UserServiceImpl implements UserServiceBo {
    @Override
    public String sayHello(String name) {
        //让当前当前线程休眠2s
        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        return name; 
    }

    @Override
    public String sayHello2 (String name) {
        //让当前当前线程休眠2s
        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        return name;
    }
        @Override
    public String testPojo (Person person) {
        return JSON.toJSONString(person);
    }  
}
```

#### provider.xml
```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:context="http://www.springframework.org/schema/context"
    xmlns:dubbo="http://code.alibabatech.com/schema/dubbo"
    xsi:schemaLocation="http://www.springframework.org/schema/beans
    http://www.springframework.org/schema/beans/spring-beans.xsd
    http://www.springframework.org/schema/context
    http://www.springframework.org/schema/context/spring-context-4.0.xsd 
    http://code.alibabatech.com/schema/dubbo
    http://code.alibabatech.com/schema/dubbo/dubbo.xsd">

    <!-- 提供方应用信息，用于计算依赖关系 -->
    <dubbo:application name="dubboProvider" />

    <!-- 使用zookeeper注册中心暴露服务地址 -->
    <dubbo:registry address="zookeeper://127.0.0.1:2181" />

    <!-- 用dubbo协议在20880端口暴露服务 -->
    <dubbo:protocol name="dubbo" port="20880" />
    
    <!-- 启用monitor模块 -->
    <dubbo:monitor protocol="registry" />
    <bean id="userService" class="com.test.UserServiceImpl" />
    
    <!-- 声明需要暴露的服务接口 -->
    <dubbo:service interface="com.test.UserServiceBo" ref="userService" group="dubbo"  version="1.0.0" timeout="3000"/>
</beans>
```

#### log4j.properties
```conf
log4j.rootLogger=INFO,A1
log4j.appender.A1=org.apache.log4j.ConsoleAppender
log4j.appender.A1.layout=org.apache.log4j.PatternLayout
```

#### TestProvider
```java
public class TestProvider {   
    public static void main(String[] arg) throws InterruptedException {
        ClassPathXmlApplicationContext context = new ClassPathXmlApplicationContext("classpath:provider.xml");
        //挂起当前线程，如果没有改行代码，服务提供者进程会消亡，服务消费者就发现不了提供者了
        Thread.currentThread().join();
    }
}
```

#### consumer.xml
```xml
<beans xmlns="http://www.springframework.org/schema/beans"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"    
     xmlns:context="http://www.springframework.org/schema/context"
     xmlns:dubbo="http://code.alibabatech.com/schema/dubbo"
    xsi:schemaLocation="http://www.springframework.org/schema/beans
    http://www.springframework.org/schema/beans/spring-beans.xsd
    http://www.springframework.org/schema/context
    http://www.springframework.org/schema/context/spring-context-4.0.xsd 
    http://code.alibabatech.com/schema/dubbo
    http://code.alibabatech.com/schema/dubbo/dubbo.xsd">
    <!-- 消费方应用名，用于计算依赖关系，不是匹配条件，不要与提供方一样 -->    
    <dubbo:application name="dubboConsumer" />  

    <!-- 使用multicast广播注册中心暴露发现服务地址 -->    
    <dubbo:registry  protocol="zookeeper" address="zookeeper://127.0.0.1:2181" />
    
    <!-- 启动monitor-->
    <dubbo:monitor protocol="registry" />
    
    <!-- 生成远程服务代理，可以和本地bean一样使用demoService -->    
    <dubbo:reference id="userService" interface="com.test.UserServiceBo" group="dubbo" version="1.0.0" timeout="3000"/>
</beans>
```
#### TestConsumer
```java
public class TestConsumer {
    public static void main(String[] args) {
        ClassPathXmlApplicationContext context = new ClassPathXmlApplicationContext(
                new String[] { "classpath:consumer.xml" });
        final UserServiceBo demoService = (UserServiceBo) context.getBean("userService");
        System.out.println(demoService.sayHello("哈哈哈"));
    }
}
```

### 基于Dubbo API 方式的服务提供方搭建
```java
public class TestProviderApi {

    public static void main(String[] arg) throws InterruptedException {

        // 4.3.1-1）等价于  <bean id="userService" class="com.test.UserServiceImpl" />
        UserServiceBo userService = new UserServiceImpl();
        // 4.3.1-2）等价于  <dubbo:application name="dubboProvider" />
        ApplicationConfig application = new ApplicationConfig();
        application.setName("dubboProvider");

        // 4.3.1-3）等价于  <dubbo:registry address="zookeeper://127.0.0.1:2181" />
        RegistryConfig registry = new RegistryConfig();
        registry.setAddress("127.0.0.1:2181");
        registry.setProtocol("zookeeper");

        // 4.3.1-4）等价于 <dubbo:protocol name="dubbo" port="20880" />
        ProtocolConfig protocol = new ProtocolConfig();
        protocol.setName("dubbo");
        protocol.setPort(20880);

        // 4.3.1-5）等价于     <dubbo:monitor protocol="registry" />
        MonitorConfig monitorConfig = new MonitorConfig();
        monitorConfig.setProtocol("registry");

        // 4.3.1-6）等价于 <dubbo:service interface="com.test.UserServiceBo" ref="userService"
        // group="dubbo"  version="1.0.0" timeout="3000"/>
        ServiceConfig<UserServiceBo> service = new ServiceConfig<UserServiceBo>(); // 此实例很重，封装了与注册中心的连接，请自行缓存，否则可能造成内存和连接泄漏
        service.setApplication(application);
        service.setMonitor(monitorConfig);
        service.setRegistry(registry); // 多个注册中心可以用setRegistries()
        service.setProtocol(protocol); // 多个协议可以用setProtocols()
        service.setInterface(UserServiceBo.class);
        service.setRef(userService);
        service.setVersion("1.0.0");
        service.setGroup("dubbo");
        service.setTimeout(3000);
        service.export();

        // 4.3.1-8） 挂起当前线程
        Thread.currentThread().join();
    }
}
```

### 基于 Dubbo API 方式的服务消费方搭建
```java
public class TestConsumerApi {
    public static void main(String[] args) throws InterruptedException {
        // 等价于  <dubbo:application name="dubboConsumer" />  
        ApplicationConfig application = new ApplicationConfig();
        application.setName("dubboConsumer");

        // 等价于     <dubbo:registry  protocol="zookeeper" address="zookeeper://127.0.0.1:2181" />  
        RegistryConfig registry = new RegistryConfig();
        registry.setAddress("127.0.0.1:2181");
        registry.setProtocol("zookeeper");

        // 等价于   <dubbo:monitor protocol="registry" />
        MonitorConfig monitorConfig = new MonitorConfig();
        monitorConfig.setProtocol("registry");

        // 等价于<dubbo:reference id="userService" interface="com.test.UserServiceBo"
        // group="dubbo" version="1.0.0" timeout="3000" />
        ReferenceConfig<UserServiceBo> reference = new ReferenceConfig<UserServiceBo>(); // 此实例很重，封装了与注册中心的连接以及与提供者的连接，请自行缓存，否则可能造成内存和连接泄漏
        reference.setApplication(application);
        reference.setRegistry(registry); // 多个注册中心可以用setRegistries()
        reference.setInterface(UserServiceBo.class);
        reference.setVersion("1.0.0");
        reference.setGroup("dubbo");
        reference.setTimeout(3000);
        reference.setInjvm(false);
        reference.setMonitor(monitorConfig);

        UserServiceBo userService = reference.get(); 
        System.out.println(userService.sayHello("哈哈哈"));
        Thread.currentThread().join();
    }
}
```

### 基于 dubbo-spring-boot-starter
```java
@SpringBootApplication
@EnableDubboConfiguration
@RestController 
@ComponentScan(basePackages = { "com.gitchat.demo.provider.service" })  
public class ProviderApp {
    @RequestMapping("/")
    String home() {
        return "Hello Demo!";
    }
    
    public static void main(String[] args) {   
        SpringApplication.run(ProviderApp.class, args);
    }
}
```

#### UserServiceBoImpl
```java
@Service(interfaceClass = UserServiceBo.class,group="dubbo",version="1.0.0")
@Component
public class UserServiceBoImpl implements UserServiceBo {
    @Override
    public String sayHello(String name) {
        return "hello:" + name;
    }

    @Override
    public String testPojo(Person person) {
        return person.toString();
    }
}
```

#### application.properties
```conf
server.port=7003
management.port=7004
spring.application.name=demo-provider

spring.dubbo.server=true
spring.dubbo.registry=zookeeper://127.0.0.1:2181
```

#### log4j.properties
```conf
log4j.rootLogger=INFO,A1
log4j.appender.A1=org.apache.log4j.ConsoleAppender
log4j.appender.A1.layout=org.apache.log4j.PatternLayout
```

#### pom.xml
```xml
<parent>
  <groupId>org.springframework.boot</groupId>
  <artifactId>spring-boot-starter-parent</artifactId>
  <version>2.0.1.RELEASE</version>
</parent>
<dependency>
  <groupId>org.springframework.boot</groupId>
  <artifactId>spring-boot-starter-web</artifactId>
</dependency>
```

#### dubbo-spring-boot-starter
```xml
<dependency>
  <groupId>com.alibaba.spring.boot</groupId>
  <artifactId>dubbo-spring-boot-starter</artifactId>
  <version>2.0.0</version>
</dependency>
```

#### 引入 ZooKeeper
```xml
<dependency>
  <groupId>com.101tec</groupId>
  <artifactId>zkclient</artifactId>
  <version>0.10</version>
  <exclusions>
    <exclusion>
      <artifactId>slf4j-log4j12</artifactId>
      <groupId>org.slf4j</groupId>
    </exclusion>
  </exclusions>
</dependency>
```

#### spring-boot-maven
```xml
<build>
  <finalName>demo-provider</finalName>

  <plugins>
    <plugin>
      <groupId>org.springframework.boot</groupId>
      <artifactId>spring-boot-maven-plugin</artifactId>
      <configuration>
        <executable>false</executable>
        <excludeDevtools>true</excludeDevtools>
      </configuration>
      <executions>
        <execution>
          <goals>
            <goal>repackage</goal>
          </goals>
        </execution>
      </executions>
    </plugin>
  </plugins>
</build>
```

#### 服务消费方搭建
```java
@SpringBootApplication
@EnableDubboConfiguration 
@RestController
@ComponentScan(basePackages = { "com.gitchat.demo.consumer.service" })
public class ConsumerApp {

  @Autowired 
  private ConsumerService  consumerService; 

  @RequestMapping(value = "/testSayHello", method = RequestMethod.GET)
  String testSayHello(@RequestParam(value = "name", required = true) String name) {
    return  consumerService.sayHello(name);
  }

  @RequestMapping("/")
  String home() {
    return "Hello Demo!";
  }

  public static void main(String[] args) {
    SpringApplication.run(ConsumerApp.class, args);
  }
}
```

#### ConsumerService
```java
@Component
public class ConsumerService {
  @Reference(group="dubbo",interfaceClass=UserServiceBo.class,version="1.0.0")
  private UserServiceBo userServiceBo;

  public String sayHello(String name){
    return userServiceBo.sayHello(name);
  }
}
```

#### application.properties
```conf
server.port=7001
management.port=7002
spring.application.name=demo-consumer

spring.dubbo.server=true
spring.dubbo.registry=zookeeper://127.0.0.1:2181
```

