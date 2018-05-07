#### 搭建一个 Spring Web
- 配置 web.xml，加载 Spring 和 Spring MVC
- 配置数据库连接、配置 Spring 事务
- 加载配置文件的读取，开启注解
- 配置日志文件
- 配置完成之后部署 Tomcat 调试

#### Spring Boot 的基础结构
- src/main/java：程序开发以及主程序入口
- src/main/resources：配置文件
- src/test/java：测试程序

#### 例子
- Application.java：建议放到根目录下面，是项目的启动类，Spring Boot 项目只能有一个 main() 方法。
- comm：目录建议放置公共的类，如全局的配置文件、工具类等。
- domain：目录主要用于实体（Entity）与数据访问层（Repository）。
- repository：数据库访问层代码。
- service：该层主要是业务类代码。
- web：该层负责页面访问控制。

#### resources 目录下
- static: 目录存放 Web 访问的静态资源，如 JS、CSS、图片
- templates: 目录存放页面模板
- application.properties: 项目的配置信息

#### 样例
- pom.xml
```xml
<dependency>
  <groupId>org.springframework.boot</groupId>
  <artifactId>spring-boot-starter-web</artifactId>
</dependency>
```

- pom.xml 文件中默认有两个模块
  - spring-boot-starter：核心模块，包括自动配置支持、日志和 YAML
  - spring-boot-starter-test：测试模块，包括 JUnit、Hamcrest、Mockito
- controller
```java
@RestController
public class HelloWorldController {
    @RequestMapping("/hello")
    public String hello() {
        return "Hello World";
    }
}
```

- HelloWorldController
```java
@RestController
public class HelloWorldController {
  @RequestMapping("/hello")
  public String index(String name) {
    return "Hello World, " +name;
  }
}
```

#### 热部署
热启动就需要用到我们在一开始引入的另外一个组件：devtools
- 添加 optional 属性
```xml
 <dependencies>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-devtools</artifactId>
        <optional>true</optional>
    </dependency>
</dependencies>
```
- 配置另外一个属性 fork
```xml
<build>
  <plugins>
    <plugin>
      <groupId>org.springframework.boot</groupId>
      <artifactId>spring-boot-maven-plugin</artifactId>
      <configuration>
        <fork>true</fork>
      </configuration>
    </plugin>
  </plugins>
</build>
```

#### 单元测试
```java
public class HelloTest {
  @Test
  public void hello(){
    System.out.println("hello world");
  }
}
```

```java
@SpringBootTest
public class HelloTest {
  private MockMvc mockMvc;
  @Before
  public void setUp() throws Exception {
    mockMvc = MockMvcBuilders.standaloneSetup(new HelloWorldController()).build();
  }
  @Test
  public void getHello() throws Exception {
    mockMvc.perform(MockMvcRequestBuilders.post("/hello?name=小明").accept(MediaType.APPLICATION_JSON_UTF8)).andDo(print());
  }
}
```
