#### spring-boot-starter-web
spring-boot-starter-web 是 Spring Boot 对 Web 开发的支持，主要包括 RESTful、参数校验、使用 Tomcat 作为内嵌容器

#### Json 的支持
```java
public class User {
  private String name;
  private int age;
  private String pass;
}
```
```java
@RestController
public class WebController {
  @RequestMapping("/getUser")
  public User getUser() {
    User user=new User();
    user.setName("小明");
    user.setAge(12);
    user.setPass("123456");
    return user;
  }
}
```

#### 自定义 Filter
```java
public class MyFilter implements Filter {
    @Override
    public void destroy() {
        // TODO Auto-generated method stub
    }

    @Override
    public void doFilter(ServletRequest srequest, ServletResponse sresponse, FilterChain filterChain)
            throws IOException, ServletException {
        // TODO Auto-generated method stub
        HttpServletRequest request = (HttpServletRequest) srequest;
        System.out.println("this is MyFilter,url :"+request.getRequestURI());
        filterChain.doFilter(srequest, sresponse);
    }

    @Override
    public void init(FilterConfig arg0) throws ServletException {
        // TODO Auto-generated method stub
    }
}
```

#### Filter 加入过滤链
实现 Filter 接口，实现 Filter 方法 添加@Configuration 注解，将自定义 Filter 加入过滤链
```java
public class MyFilter implements Filter {
    @Override
    public void destroy() {
      // TODO Auto-generated method stub
    }
    @Override
    public void doFilter(ServletRequest srequest, ServletResponse sresponse, FilterChain filterChain)
            throws IOException, ServletException {
      // TODO Auto-generated method stub
      HttpServletRequest request = (HttpServletRequest) srequest;
      System.out.println("this is MyFilter,url :"+request.getRequestURI());
      filterChain.doFilter(srequest, sresponse);
    }
    @Override
    public void init(FilterConfig arg0) throws ServletException {
      // TODO Auto-generated method stub
    }
}
```
```java
@Configuration
public class WebConfiguration {
  @Bean
  public RemoteIpFilter remoteIpFilter() {
    return new RemoteIpFilter();
  }

  @Bean
  public FilterRegistrationBean testFilterRegistration() {
    FilterRegistrationBean registration = new FilterRegistrationBean();
    registration.setFilter(new MyFilter());
    registration.addUrlPatterns("/*");
    registration.addInitParameter("paramName", "paramValue");
    registration.setName("MyFilter");
    registration.setOrder(1);
    return registration;
  }
}
```

#### 自定义 Property
- application.properties
```config
com.neo.title=纯洁的微笑
com.neo.description=分享生活和技术
```
- NeoProperties
```java
@Component
public class NeoProperties {
    @Value("${com.neo.title}")
    private String title;
    @Value("${com.neo.description}")
    private String description;
}
```
- 单元测试
```java
@RunWith(SpringRunner.class)
@SpringBootTest
public class PropertiesTest {
  @Resource
  private NeoProperties properties;
  @Test
  public void testProperties() throws Exception {
    System.out.println("title:"+properties.getTitle());
    System.out.println("description:"+properties.getDescription());
  }
}
```
