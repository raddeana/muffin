#### mongoDB spring-boot
MongoDB 有两种比较流行的使用方法, 一种是直接将 MongoTemplate 直接注入到 Dao 中使用, 一种是继承 MongoRepository

#### MongoTemplate
##### pom 包配置
```xml
<dependencies>
  <dependency> 
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-data-mongodb</artifactId>
  </dependency> 
</dependencies>
```

##### application.properties
```
spring.data.mongodb.uri=mongodb://name:pass@localhost:27017/test
```

##### 多个 IP 集群
```
spring.data.mongodb.uri=mongodb://user:pwd@ip1:port1,ip2:port2/database
```

##### 创建数据实体
```java
public class UserEntity implements Serializable {
  private static final long serialVersionUID = -3258839839160856613L;
  private Long id;
  private String userName;
  private String passWord;
}
```

##### 创建实体 Dao 的增删改查操作
```java
@Component
public class UserDaoImpl implements UserDao {

    @Autowired
    private MongoTemplate mongoTemplate;

    /**
     * 创建对象
     * @param {UserEntity} user
     */
    @Override
    public void saveUser(UserEntity user) {
        mongoTemplate.save(user);
    }

    /**
     * 根据用户名查询对象
     * @param {String} userName
     * @return
     */
    @Override
    public UserEntity findUserByUserName(String userName) {
        Query query=new Query(Criteria.where("userName").is(userName));
        UserEntity user =  mongoTemplate.findOne(query , UserEntity.class);
        return user;
    }

    /**
     * 更新对象
     * @param {UserEntity} user
     */
    @Override
    public void updateUser(UserEntity user) {
        Query query=new Query(Criteria.where("id").is(user.getId()));
        Update update= new Update().set("userName", user.getUserName()).set("passWord", user.getPassWord());
        //更新查询返回结果集的第一条
        mongoTemplate.updateFirst(query,update,UserEntity.class);
        //更新查询返回结果集的所有
        // mongoTemplate.updateMulti(query,update,UserEntity.class);
    }

    /**
     * 删除对象
     * @param {Long} id
     */
    @Override
    public void deleteUserById(Long id) {
        Query query=new Query(Criteria.where("id").is(id));
        mongoTemplate.remove(query,UserEntity.class);
    }
}
```

##### 测试方法
```java
@RunWith(SpringRunner.class)
@SpringBootTest
public class UserDaoTest {
  @Autowired
  private UserDao userDao;

  @Test
  public void testSaveUser() throws Exception {
    UserEntity user=new UserEntity();
    user.setId(2l);
    user.setUserName("小明");
    user.setPassWord("fffooo123");
    userDao.saveUser(user);
  }

  @Test
  public void findUserByUserName(){
   UserEntity user= userDao.findUserByUserName("小明");
   System.out.println("user is " + user);
  }

  @Test
  public void updateUser(){
    UserEntity user=new UserEntity();
    user.setId(2l);
    user.setUserName("天空");
    user.setPassWord("fffxxxx");
    userDao.updateUser(user);
  }
  @Test
  public void deleteUserById(){
    userDao.deleteUserById(1l);
  }
}
```

##### 登录服务器
- 登录 mongos：bin/mongo -host localhost -port 20000
- 切换到 test 库：use test
- 查询 userEntity 集合数据：db.userEntity.find()

#### MongoRepository
##### dao
```java
public interface UserRepository extends MongoRepository<UserEntity, Long> {
  UserEntity findByUserName(String userName);
}
```

##### UserRepository 进行增删改查
```java
@RunWith(SpringRunner.class)
@SpringBootTest
public class UserDaoTest {
  @Autowired
  private UserRepository userRepository;

  @Test
  public void testSaveUser() throws Exception {
    UserEntity user=new UserEntity();
    user.setId(2l);
    user.setUserName("小明");
    user.setPassWord("fffooo123");
    userRepository.save(user);
  }

  @Test
  public void findUserByUserName(){
    UserEntity user= userRepository.findByUserName("小明");
    System.out.println("user is " + user);
  }

  @Test
  public void updateUser(){
    UserEntity user=new UserEntity();
    user.setId(2l);
    user.setUserName("天空");
    user.setPassWord("fffxxxx");
    userRepository.save(user);
  }

  @Test
  public void deleteUserById(){
    userRepository.delete(1l);
  }
}
```

##### 多数据源 MongoDB
```conf
mongodb.primary.uri=mongodb://192.168.0.1:27017     // 192.168.0.1:27017
mongodb.primary.database=primary
mongodb.secondary.uri=mongodb://192.168.0.1:27017   // 192.168.0.1:27017
mongodb.secondary.database=secondary
```

MongoDB 集群
```conf
mongodb.xxx.uri=mongodb:  // 192.168.0.1:27017, 192.168.0.2:27017, 192.168.0.3:27017
mongodb.xxx.database=xxx
```

##### 两个库的数据源
```java
@Data
@ConfigurationProperties(prefix = "mongodb")
public class MultipleMongoProperties {
  private MongoProperties primary = new MongoProperties();
  private MongoProperties secondary = new MongoProperties();
}
```

##### 配置不同包路径下使用不同的数据源
```java
@Configuration
@EnableMongoRepositories(basePackages = "com.neo.model.repository.primary", mongoTemplateRef = PrimaryMongoConfig.MONGO_TEMPLATE)
public class PrimaryMongoConfig {
  protected static final String MONGO_TEMPLATE = "primaryMongoTemplate";
}
```

```java
@Configuration
@EnableMongoRepositories(basePackages = "com.neo.model.repository.secondary", mongoTemplateRef = SecondaryMongoConfig.MONGO_TEMPLATE)
public class SecondaryMongoConfig {
  protected static final String MONGO_TEMPLATE = "secondaryMongoTemplate";
}
```

```java
@Configuration
public class MultipleMongoConfig {
  @Autowired
  private MultipleMongoProperties mongoProperties;

  @Primary
  @Bean(name = PrimaryMongoConfig.MONGO_TEMPLATE)
  public MongoTemplate primaryMongoTemplate() throws Exception {
    return new MongoTemplate(primaryFactory(this.mongoProperties.getPrimary()));
  }

  @Bean
  @Qualifier(SecondaryMongoConfig.MONGO_TEMPLATE)
  public MongoTemplate secondaryMongoTemplate() throws Exception {
    return new MongoTemplate(secondaryFactory(this.mongoProperties.getSecondary()));
  }

  @Bean
  @Primary
  public MongoDbFactory primaryFactory(MongoProperties mongo) throws Exception {
    MongoClient client = new MongoClient(new MongoClientURI(mongoProperties.getPrimary().getUri()));
    return new SimpleMongoDbFactory(client, mongoProperties.getPrimary().getDatabase());
  }

  @Bean
  public MongoDbFactory secondaryFactory(MongoProperties mongo) throws Exception {
    MongoClient client = new MongoClient(new MongoClientURI(mongoProperties.getSecondary().getUri()));
    return new SimpleMongoDbFactory(client, mongoProperties.getSecondary().getDatabase());
  }
}
```
