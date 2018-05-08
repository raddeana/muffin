#### 数据缓存
##### 注解:
- @Cacheable
- @CacheEvict
- @CachePut

##### spring-boot-starter-cache
```java
<dependency>
  <groupId>org.springframework.boot</groupId>
  <artifactId>spring-boot-starter-cache</artifactId>
</dependency>
```

##### @Cacheable
是用来声明方法是可缓存的，将结果存储到缓存中以便后续使用相同参数调用时不需执行实际的方法，直接从缓存中取值
```java
@RequestMapping("/getUsers")
@Cacheable(value="usersCache",key="#nickname",condition="#nickname.length() >= 6")
public List<User> getUsers(String nickname) {
  List<User> users=userRepository.findByNickname(nickname);
  System.out.println("执行了数据库操作");
  return users;
}
```
参数:
- value: 缓存的名称
- key: 缓存的key, 可以为空, 如果指定要按照 SpEL 表达式编写, 如果不指定, 则缺省按照方法的所有参数进行组合
- condition: 触发条件, 只有满足条件的情况才会加入缓存, 默认为空，既表示全部都加入缓存, 支持 SpEL

##### @CachePut
项目运行中会对数据库的信息进行更新，如果仍然使用 @Cacheable 就会导致数据库的信息和缓存的信息不一致

```java
@RequestMapping("/getPutUsers")
@CachePut(value="usersCache",key="#nickname")
public List<User> getPutUsers(String nickname) {
  List<User> users = userRepository.findByNickname(nickname);
  System.out.println("执行了数据库操作");
  return users;
}
```

##### @CachePut 配置方法
- value 缓存的名称
- key 缓存的 key，可以为空，如果指定要按照 SpEL 表达式编写，如果不指定，则缺省按照方法的所有参数进行组合
- condition 缓存的条件，可以为空，使用 SpEL 编写，返回 true 或者 false，只有为 true 才进行缓存

##### @CacheEvict
@CacheEvict 是用来标注在需要清除缓存元素的方法或类上的
@CacheEvict 可以指定的属性有 value、key、condition、allEntries 和 beforeInvocation

- allEntries: allEntries 是 boolean 类型，表示是否需要清除缓存中的所有元素
```java
@RequestMapping("/allEntries")
@CacheEvict(value="usersCache", allEntries=true)
public List<User> allEntries(String nickname) {
  List<User> users=userRepository.findByNickname(nickname);
  System.out.println("执行了数据库操作");
  return users;
}
```
- beforeInvocation: 清除操作默认是在对应方法成功执行之后触发的，即方法如果因为抛出异常而未能成功返回时也不会触发清除操作
```java
@RequestMapping("/beforeInvocation")
@CacheEvict(value="usersCache", allEntries=true, beforeInvocation=true)
public void beforeInvocation() {
  throw new RuntimeException("test beforeInvocation");
}
```

#### Session
容易实现: 
- HTTP 协议是无状态的协议，所以服务端需要记录用户的状态时，就需要用某种机制来识具体的用户
- API和用于管理用户会话的实现
- HttpSession - 允许以应用程序容器（即 Tomcat）中性的方式替换 HttpSession
- 将 session 所保存的状态卸载到特定的外部 session 存储中，如 Redis 或 Apache Geode 中，它们能够以独立于应用服务器的方式提供高质量的集群
- 支持每个浏览器上使用多个 session，从而能够很容易地构建更加丰富的终端用户体验
- 控制 session id 如何在客户端和服务器之间进行交换，这样的话就能很容易地编写 Restful API，因为它可以从 HTTP 头信息中获取 session id，而不必再依赖于 cookie
- 当用户使用 WebSocket 发送请求的时候，能够保持 HttpSession 处于活跃状态

#### spring-session-data-redis
- 引入依赖包
```xml
<dependency>
  <groupId>org.springframework.session</groupId>
  <artifactId>spring-session-data-redis</artifactId>
</dependency>
```
- Session 配置
```xml
@Configuration
@EnableRedisHttpSession(maxInactiveIntervalInSeconds = 86400*30)
public class SessionConfig {}
```
maxInactiveIntervalInSeconds: 设置 Session 失效时间, 使用 Redis Session 之后, 原 Boot 的 server.session.timeout 属性不再生效

#### 登录
```java
@RequestMapping(value = "/login")
public String login (HttpServletRequest request,String userName,String password){
  String msg = "logon failure!";
  User user = userRepository.findByUserName(userName);

  if (user!=null && user.getPassword().equals(password)){
    request.getSession().setAttribute("user",user);
    msg = "login successful";
  }

  return msg;
}
```
