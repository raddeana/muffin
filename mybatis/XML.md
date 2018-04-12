### XML 映射配置文件
文档的顶层结构如下：
- configuration 配置
  - properties 属性
  - settings 设置
  - typeAliases 类型别名
  - typeHandlers 类型处理器
  - objectFactory 对象工厂
  - plugins 插件
  - environments 环境
    - environment 环境变量
      - transactionManager 事务管理器
      - dataSource 数据源
  - databaseIdProvider 数据库厂商标识
  - mappers 映射器


#### properties
这些属性都是可外部配置且可动态替换的，既可以在典型的 Java 属性文件中配置，亦可通过 properties 元素的子元素来传递
```xml
<properties resource="org/mybatis/config.properties">
  <property name="username" value="dev_user"/>
  <property name="password" value="F2Fa3!33TYyg"/>
</properties>
```
其中的属性就可以在整个配置文件中被用来替换需要动态配置的属性值
```xml
<dataSource type="POOLED">
  <property name="driver" value="${driver}"/>
  <property name="url" value="${url}"/>
  <property name="username" value="${username}"/>
  <property name="password" value="${password}"/>
</dataSource>
```
属性也可以被传递到 SqlSessionFactoryBuilder.build()方法中
```java
SqlSessionFactory factory = new SqlSessionFactoryBuilder().build(reader, props)
SqlSessionFactory factory = new SqlSessionFactoryBuilder().build(reader, environment, props)
```

如果属性在不只一个地方进行了配置，那么 MyBatis 将按照下面的顺序来加载：
- 在 properties 元素体内指定的属性首先被读取
- 然后根据 properties 元素中的 resource 属性读取类路径下属性文件或根据 url 属性指定的路径读取属性文件，并覆盖已读取的同名属性
- 最后读取作为方法参数传递的属性，并覆盖已读取的同名属性

```xml
<dataSource type="POOLED">
  <property name="username" value="${username:ut_user}"/>
</dataSource>
```
```xml
<properties resource="org/mybatis/example/config.properties">
  <property name="org.apache.ibatis.parsing.PropertyParser.enable-default-value" value="true"/>
</properties>
```
```xml
<properties resource="org/mybatis/example/config.properties">
  <property name="org.apache.ibatis.parsing.PropertyParser.default-value-separator" value="?:"/>
</properties>
```
```xml
<dataSource type="POOLED">
  <property name="username" value="${db:username?:ut_user}"/>
</dataSource>
```

#### settings
这是 MyBatis 中极为重要的调整设置，它们会改变 MyBatis 的运行时行为

#### typeAliases
类型别名是为 Java 类型设置一个短的名字。它只和 XML 配置有关，存在的意义仅在于用来减少类完全限定名的冗余

#### typeHandlers
无论是 MyBatis 在预处理语句（PreparedStatement）中设置一个参数时，
还是从结果集中取出一个值时， 都会用类型处理器将获取的值以合适的方式转换成 Java 类型

#### 处理枚举类型
若想映射枚举类型 Enum，则需要从 EnumTypeHandler 或者 EnumOrdinalTypeHandler 中选一个来使用

#### 对象工厂（objectFactory）
MyBatis 每次创建结果对象的新实例时，它都会使用一个对象工厂（ObjectFactory）实例来完成
默认的对象工厂需要做的仅仅是实例化目标类，要么通过默认构造方法，要么在参数映射存在的时候通过参数构造方法来实例化

#### 插件（plugins）
MyBatis 允许使用插件来拦截的方法调用包括：
- Executor (update, query, flushStatements, commit, rollback, getTransaction, close, isClosed)
- ParameterHandler (getParameterObject, setParameters)
- ResultSetHandler (handleResultSets, handleOutputParameters)
- StatementHandler (prepare, parameterize, batch, update, query)

```java
@Intercepts({
  @Signature(
    type= Executor.class,
    method = "update",
    args = {MappedStatement.class,Object.class}
  )
})
public class ExamplePlugin implements Interceptor {
  public Object intercept(Invocation invocation) throws Throwable {
    return invocation.proceed();
  }
  
  public Object plugin(Object target) {
    return Plugin.wrap(target, this);
  }
  
  public void setProperties(Properties properties) {}
}
```
```xml
<plugins>
  <plugin interceptor="org.mybatis.ExamplePlugin">
    <property name="someProperty" value="100"/>
  </plugin>
</plugins>
```

#### 配置环境（environments）
MyBatis 可以配置成适应多种环境，这种机制有助于将 SQL 映射应用于多种数据库之中， 现实情况下有多种理由需要这么做

#### databaseIdProvider
MyBatis 可以根据不同的数据库厂商执行不同的语句，这种多厂商的支持是基于映射语句中的 databaseId 属性

#### 映射器（mappers）
```xml
<!-- 使用相对于类路径的资源引用 -->
<mappers>
  <mapper resource="org/mybatis/builder/AuthorMapper.xml"/>
  <mapper resource="org/mybatis/builder/BlogMapper.xml"/>
  <mapper resource="org/mybatis/builder/PostMapper.xml"/>
</mappers>
```

```xml
<!-- 使用完全限定资源定位符（URL） -->
<mappers>
  <mapper url="file:///var/mappers/AuthorMapper.xml"/>
  <mapper url="file:///var/mappers/BlogMapper.xml"/>
  <mapper url="file:///var/mappers/PostMapper.xml"/>
</mappers>
```

```xml
<!-- 使用映射器接口实现类的完全限定类名 -->
<mappers>
  <mapper class="org.mybatis.builder.AuthorMapper"/>
  <mapper class="org.mybatis.builder.BlogMapper"/>
  <mapper class="org.mybatis.builder.PostMapper"/>
</mappers>
```

```xml
<!-- 将包内的映射器接口实现全部注册为映射器 -->
<mappers>
  <package name="org.mybatis.builder"/>
</mappers>
```
