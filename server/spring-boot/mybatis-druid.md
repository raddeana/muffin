### Druid
Druid 是阿里巴巴开源平台上的一个项目，整个项目由数据库连接池、插件框架和 SQL 解析器组成

- 密钥服务请求凭证
- 统计 SQL 信息
- SQL 性能收集
- SQL 注入检查
- SQL 翻译

#### Spring Boot 集成 Druid
非常令人高兴的是，阿里为 Druid 也提供了 Spring Boot Starter 的支持

```xml
<dependency>
  <groupId>com.alibaba</groupId>
  <artifactId>druid-spring-boot-starter</artifactId>
  <version>1.1.5</version>
</dependency
```

#### application 配置
```conf
# 初始化大小、最小、最大连接数
spring.datasource.druid.initial-size=3
spring.datasource.druid.min-idle=3
spring.datasource.druid.max-active=10

# 配置获取连接等待超时的时间
spring.datasource.druid.max-wait=60000

# 监控后台账号和密码
spring.datasource.druid.stat-view-servlet.login-username=admin
spring.datasource.druid.stat-view-servlet.login-password=admin

# 配置 StatFilter
spring.datasource.druid.filter.stat.log-slow-sql=true
spring.datasource.druid.filter.stat.slow-sql-millis=2000
```

#### 多数据源
```conf
spring.datasource.druid.one.driverClassName = com.mysql.jdbc.Driver
spring.datasource.druid.one.url = jdbc:mysql://localhost:3306/test1?useUnicode=true&characterEncoding=utf-8
spring.datasource.druid.one.username = root
spring.datasource.druid.one.password = root

spring.datasource.druid.two.driverClassName = com.mysql.jdbc.Driver
spring.datasource.druid.two.url = jdbc:mysql://localhost:3306/test2?useUnicode=true&characterEncoding=utf-8
spring.datasource.druid.two.username = root
spring.datasource.druid.two.password = root
```

#### 属性继承
``
# Druid 数据源配置，继承 spring.datasource.* 配置，相同则覆盖
spring.datasource.druid.initial-size = 3
spring.datasource.druid.min-idle = 3
spring.datasource.druid.max-active = 10
spring.datasource.druid.max-wait = 60000

# Druid 数据源 1 配置，继承 spring.datasource.druid.* 配置，相同则覆盖
spring.datasource.druid.one.max-active = 20
spring.datasource.druid.one.max-wait = 10000

# Druid 数据源 2 配置，继承spring.datasource.druid.* 配置，相同则覆盖
spring.datasource.druid.two.max-active = 30
spring.datasource.druid.two.max-wait = 20000
``

#### 注入多数据源
```java
@Configuration
public class MultiDataSourceConfig {
    @Primary
    @Bean(name = "oneDataSource")
    @ConfigurationProperties("spring.datasource.druid.one")
    public DataSource dataSourceOne(){
        return DruidDataSourceBuilder.create().build();
    }
    @Bean(name = "twoDataSource")
    @ConfigurationProperties("spring.datasource.druid.two")
    public DataSource dataSourceTwo(){
        return DruidDataSourceBuilder.create().build();
    }
}
```

#### SqlSessionFactory
```java
@Bean(name = "oneSqlSessionFactory")
@Primary
public SqlSessionFactory testSqlSessionFactory(@Qualifier("oneDataSource") DataSource dataSource) throws Exception {
    SqlSessionFactoryBean bean = new SqlSessionFactoryBean();
    bean.setDataSource(dataSource);
    return bean.getObject();
}
```

#### 将数据源添加到事务
```java
@Bean(name = "oneTransactionManager")
@Primary
public DataSourceTransactionManager testTransactionManager(@Qualifier("oneDataSource") DataSource dataSource) {
    return new DataSourceTransactionManager(dataSource);
}
```

#### SqlSessionTemplate
```java
@Bean(name = "oneSqlSessionTemplate")
@Primary
public SqlSessionTemplate testSqlSessionTemplate(@Qualifier("oneSqlSessionFactory") SqlSessionFactory sqlSessionFactory) throws Exception {
    return new SqlSessionTemplate(sqlSessionFactory);
}
```

#### SqlSessionTemplate
```java
@Configuration
@MapperScan(basePackages = "com.neo.mapper.one", sqlSessionTemplateRef  = "oneSqlSessionTemplate")
public class OneDataSourceConfig {}
```

#### TwoDataSourceConfig
```java
@Configuration
@MapperScan(basePackages = "com.neo.mapper.two", sqlSessionTemplateRef  = "twoSqlSessionTemplate")
public class TwoSourceConfig {
    @Bean(name = "twoSqlSessionFactory")
    public SqlSessionFactory testSqlSessionFactory(@Qualifier("twoDataSource") DataSource dataSource) throws Exception {
        SqlSessionFactoryBean bean = new SqlSessionFactoryBean();
        bean.setDataSource(dataSource);
        return bean.getObject();
    }
    @Bean(name = "twoTransactionManager")
    public DataSourceTransactionManager testTransactionManager(@Qualifier("twoDataSource") DataSource dataSource) {
        return new DataSourceTransactionManager(dataSource);
    }
    @Bean(name = "twoSqlSessionTemplate")
    public SqlSessionTemplate testSqlSessionTemplate(@Qualifier("twoSqlSessionFactory") SqlSessionFactory sqlSessionFactory) throws Exception {
        return new SqlSessionTemplate(sqlSessionFactory);
    }
}
```

#### 测试
- 入俩个不同的 Mapper
```java
@RunWith(SpringRunner.class)
@SpringBootTest
public class UserMapperTest {
  @Autowired
  private UserOneMapper userOneMapper;
  @Autowired
  private UserTwoMapper userTwoMapper;
}
```
- 两个 Mapper 插入数据
```java
@Test
public void testInsert() throws Exception {
  userOneMapper.insert(new UserEntity("aaa", "a123456", UserSexEnum.MAN));
  userOneMapper.insert(new UserEntity("bbb", "b123456", UserSexEnum.WOMAN));
  userTwoMapper.insert(new UserEntity("ccc", "b123456", UserSexEnum.WOMAN));

  Assert.assertEquals(2, userOneMapper.getAll().size());
  Assert.assertEquals(2, userOneMapper.getAll().size());
}
```
- 注入不同的 Mapper
```java
@RequestMapping("/getUsers")
public List<UserEntity> getUsers() {
  List<UserEntity> usersOne=userOneMapper.getAll();
  List<UserEntity> usersTwo=userTwoMapper.getAll();
  usersOne.addAll(usersTwo);
  return usersOne;
}
```
