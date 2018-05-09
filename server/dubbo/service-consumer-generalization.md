### 服务消费端泛化调用
```java
public class TestConsumerApiGeneric {
    public static void main(String[] args) throws IOException {

        // 当前应用配置
        ApplicationConfig application = new ApplicationConfig();
        application.setName("dubboConsumer");

        // 连接注册中心配置
        RegistryConfig registry = new RegistryConfig();
        registry.setAddress("127.0.0.1:2181");
        registry.setProtocol("zookeeper");

        // 泛型参数设置为GenericService
        ReferenceConfig<GenericService> reference = new ReferenceConfig<GenericService>(); 
        reference.setApplication(application);
        reference.setRegistry(registry); 
        reference.setVersion("1.0.0");
        reference.setGroup("dubbo");
        reference.setTimeout(3000);

        //设置为泛化
        reference.setInterface("com.test.UserServiceBo");
        reference.setGeneric(true);

        //用com.alibaba.dubbo.rpc.service.GenericService替代所有接口引用
        GenericService userService = reference.get(); // 

        // 基本类型以及Date,List,Map等不需要转换，直接调用,如果返回值为POJO也将自动转成Map
        Object result = userService.$invoke("sayHello", new String[] {"java.lang.String"},
        new Object[] {"哈哈哈"});

        System.out.println(JSON.json(result));

        // POJO参数转换为map
        Map<String, Object> map = new HashMap<String, Object>();
        map.put("class", "com.test.PersonImpl");
        map.put("name", "jiaduo");
        map.put("password", "password");

        result = userService.$invoke("testPojo", new String[] { "com.test.Person" }, new Object[] { map });
        System.out.println((result));
    }
}
```

```java
package com.test;

public class PersonImpl implements Person {
  private String name;
  private String password;
  
  public String getName() {
    return name;
  }
  
  public void setName(String name) {
    this.name = name;
  }
  
  public String getPassword() {
    return password;
  }
  
  public void setPassword(String password) {
    this.password = password;
  }
}
```

```java
Person person = new PersonImpl();
person.setName("jiaduo");
person.setPassword("password");
```

```java
servicePerson.testPojo(person);
```

```java
Map<String, Object> map = new HashMap<String, Object>();
// 注意：如果参数类型是接口，或者List等丢失泛型，可通过class属性指定类型。
map.put("class", "com.test.PersonImpl");
map.put("name", "jiaduo");
map.put("password", "password");
```

```java
 servicePerson.$invoke("testPojo", new String[]
{"com.test.Person"}, new Object[]{map});
```

### 服务消费端异步调用
无论前面我们讲解的正常调用还是泛化调用, 都是同步调用, 也就是服务消费方发起一个远程调用后, 调用线程要被阻塞挂起, 直到服务提供方返回
```java
public class TestConsumerAsync {
  public static void main(String[] args) throws InterruptedException, ExecutionException {
    // 当前应用配置
    ApplicationConfig application = new ApplicationConfig();
    application.setName("dubboConsumer");

    // 连接注册中心配置
    RegistryConfig registry = new RegistryConfig();
    registry.setAddress("127.0.0.1:2181");
    registry.setProtocol("zookeeper");

    // 引用远程服务
    ReferenceConfig<UserServiceBo> reference = new ReferenceConfig<UserServiceBo>();
    reference.setApplication(application);
    reference.setRegistry(registry);
    reference.setInterface(UserServiceBo.class);
    reference.setVersion("1.0.0");
    reference.setGroup("dubbo");
    reference.setTimeout(3000);

    // 设置为异步调用
    reference.setAsync(true);

    // 和本地bean一样使用xxxService
    UserServiceBo userService = reference.get();

    long startTime = System.currentTimeMillis() / 1000;

    // 因为异步调用，此处返回null
    System.out.println(userService.sayHello("哈哈哈"));
    
    // 拿到调用的Future引用，当结果返回后，会被通知和设置到此Future
    Future<String> userServiceFutureOne = RpcContext.getContext().getFuture();

    // 因为异步调用，此处返回null
    System.out.println(userService.sayHello2("哈哈哈2"));
    
    // 拿到调用的Future引用，当结果返回后，会被通知和设置到此Future
    Future<String> userServiceFutureTwo = RpcContext.getContext().getFuture();

    // 阻塞到get方法，等待结果返回
    System.out.println(userServiceFutureOne.get());
    System.out.println(userServiceFutureTwo.get());
    long endTime = System.currentTimeMillis() / 1000;
    
    System.out.println("costs:" + (endTime - startTime));
  }
}
```
