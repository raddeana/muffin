### JPA
JPA（Java Persistence API）是 Sun 官方提出的 Java 持久化规范
为 Java 开发人员提供了一种对象/关联映射工具来管理 Java 应用中的关系数据
出现主要是为了简化现有的持久化开发工作和整合 ORM 技术，结束现在 Hibernate、TopLink、JDO 等 ORM 框架各自为营的局面

#### 添加依赖
```xml
<dependency>
    <groupId>org.Springframework.boot</groupId>
    <artifactId>Spring-boot-starter-data-jpa</artifactId>
</dependency>
 <dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
</dependency>
```

#### 添加配置文件
```config
Spring.datasource.url = jdbc:mysql://localhost:3306/test
Spring.datasource.username = root
Spring.datasource.password = root
Spring.datasource.driver-class-name = com.mysql.jdbc.Driver

Spring.jpa.properties.hibernate.hbm2ddl.auto = update
Spring.jpa.properties.hibernate.dialect = org.hibernate.dialect.MySQL5InnoDBDialect
Spring.jpa.show-sql = true
```

#### 添加实体类和 Dao
```java
@Entity
public class User implements Serializable {
  private static final long serialVersionUID = 1L;
  @Id
  @GeneratedValue
  private Long id;
  @Column(nullable = false, unique = true)
  private String userName;
  @Column(nullable = false)
  private String passWord;
  @Column(nullable = false, unique = true)
  private String email;
  @Column(nullable = true, unique = true)
  private String nickName;
  @Column(nullable = false)
  private String regTime;
}
```

#### Entity 中不映射成列的字段得加 @Transient 注解，不加注解也会映射成列
```java
public interface UserRepository extends JpaRepository<User, Long> {
  User findByUserName(String userName);
  User findByUserNameOrEmail(String username, String email);
}
```

#### 测试
```java
@RunWith(SpringRunner.class)
@SpringBootTest
public class UserRepositoryTests {
  @Resource
  private UserRepository userRepository;
  @Test
  public void test() {
    Date date = new Date();
    DateFormat dateFormat = DateFormat.getDateTimeInstance(DateFormat.LONG, DateFormat.LONG);        
    String formattedDate = dateFormat.format(date);

    userRepository.save(new User("aa", "aa@126.com", "aa", "aa123456",formattedDate));
    userRepository.save(new User("bb", "bb@126.com", "bb", "bb123456",formattedDate));
    userRepository.save(new User("cc", "cc@126.com", "cc", "cc123456",formattedDate));

    Assert.assertEquals(9, userRepository.findAll().size());
    Assert.assertEquals("bb", userRepository.findByUserNameOrEmail("bb", "cc@126.com").getNickName());
    userRepository.delete(userRepository.findByUserName("aa1"));
  }
}
```

#### 基本查询
基本查询也分为两种，一种是 Spring Data 默认已经实现，一种是根据查询的方法来自动解析成 SQL
Spring Data JPA 默认预先生成了一些基本的 CURD 的方法，如增、删、改

#### 继承 JpaRepository
```java
public interface UserRepository extends JpaRepository<User, Long> {}
```
```java
@Test
public void testBaseQuery() {
  userRepository.findAll();
  userRepository.findOne(1l);
  userRepository.save(user);
  userRepository.delete(user);
  userRepository.count();
  userRepository.exists(1l);
}
```

#### 自定义简单查询
```java
User findByUserName(String userName);
User findByUserNameOrEmail(String username, String email);
```

#### 修改、删除、统计
```java
Long deleteById(Long id)
Long countByUserName(String userName)
```

#### SQL 体系中的关键词都可以使用
```java
List<User> findByEmailLike (String email);
User findByUserNameIgnoreCase (String userName);
List<User> findByUserNameOrderByEmailDesc (String email);
```

#### 复杂查询
- 分页查询
```java
@Query("select u from User u")
Page<User> findALL (Pageable pageable);
Page<User> findByNickName (String nickName, Pageable pageable);
```
- Pageable 是 Spring 封装的分页实现类
```java
@Test
public void testPageQuery () {
  int page=1,size=10;
  Sort sort = new Sort (Direction.DESC, "id");
  Pageable pageable = new PageRequest (page, size, sort);
  userRepository.findALL (pageable);
  userRepository.findByNickName ("testName", pageable);
}
```

#### 限制查询
```java
User findFirstByOrderByLastnameAsc();
User findTopByOrderByAgeDesc();
Page<User> queryFirst10ByLastname(String lastname, Pageable pageable);
List<User> findFirst10ByLastname(String lastname, Sort sort);
List<User> findTop10ByLastname(String lastname, Pageable pageable);
```

#### 自定义 SQL 查询
```java
@Transactional(timeout = 10)
@Modifying
@Query("update User set userName = ?1 where id = ?2")
int modifyById(String  userName, Long id);

@Transactional
@Modifying
@Query("delete from User where id = ?1")
void deleteById(Long id);

@Query("select u from User u where u.email = ?1")
User findByEmail(String email);
```

#### 多表查询
- 利用 hibernate 的级联查询来实现，
- 创建一个结果集的接口来接收连表查询后的结果
```java
@Entity
public class UserDetail implements Serializable {
    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue
    private Long id;
    @Column(nullable = false, unique = true)
    private String userId;
    @Column(nullable = true)
    private String address;
    @Column(nullable = true)
    private String hobby;
}
```

#### 结果集
```java
public interface UserInfo {
  String getUserName ();
  String getEmail ();
  String getAddress ();
  String getHobby ();
}

@Query("select u.userName as userName, u.email as email, d.address as address , d.hobby as hobby from User u , UserDetail d " + "where u.id=d.userId  and  d.hobby = ?1 ")
List<UserInfo> findUserInfo (String hobby);
```

#### SQL 是 HQL，需要写类的名和属性
```java
@Test
public void testUserInfo () {
  List<UserInfo> userInfos = userDetailRepository.findUserInfo("打球");
  for (UserInfo userInfo : userInfos) {
    System.out.println("addree "+userInfo.getAddress());
  }
}
```

#### 多数据源
```config
# primary
spring.primary.datasource.url = jdbc:mysql://localhost:3306/test1
spring.primary.datasource.username = root
spring.primary.datasource.password = root
spring.primary.datasource.driver-class-name = com.mysql.jdbc.Driver

# econdary
spring.secondary.datasource.url = jdbc:mysql://localhost:3306/test2
spring.secondary.datasource.username = root
spring.secondary.datasource.password = root
spring.secondary.datasource.driver-class-name = com.mysql.jdbc.Driver
```

#### 读取两个配置源，构建两个数据源
```java
@Configuration
public class DataSourceConfig {
  @Bean(name = "primaryDataSource")
  @Qualifier("primaryDataSource")
  @ConfigurationProperties(prefix = "spring.primary.datasource")
  public DataSource primaryDataSource() {
    return DataSourceBuilder.create().build();
  }

  @Bean(name = "secondaryDataSource")
  @Qualifier("secondaryDataSource")
  @Primary
  @ConfigurationProperties(prefix = "spring.secondary.datasource")
  public DataSource secondaryDataSource() {
    return DataSourceBuilder.create().build();
  }
}
```

#### 使用枚举
```java
@Enumerated(EnumType.STRING)
@Column(nullable = true)
private UserType type;
```
```java
@Transient
private String userName;
```
