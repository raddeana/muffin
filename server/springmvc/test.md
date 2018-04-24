#### 编写测试基类
在单元测试中需要对SpringMVC中的service、dao层进行调用，需要引入配置文件进行上下文的初始化。
所以为了避免每次写一个测试类都要进行相关的配置操作，我们直接写一个父类，然后每个测试类继承该类就可以达到简化的目的了。

```java
@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration({"classpath:spring-mvc.xml","classpath:spring-mybatis.xml"})
public class BaseTest {
    @Before
    public void init () {
        //在运行测试之前的业务代码
    }
    
    @After
    public void after () {
        //在测试完成之后的业务代码
    }
}
```

```java
public class HelloTest extends BaseTest {
  @Test
  public void getTicketInfo () {
    System.out.println("hello");
  }
}
```
