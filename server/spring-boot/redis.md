#### 数据模型
为了满足高性能，Redis 采用内存（in-memory）数据集（dataset）
- string（字符串）
- hash（哈希）
- list（列表）
- set（集合）
- zset（sorted set：有序集合）

#### 配置
```xml
<dependency>
  <groupId>org.springframework.boot</groupId>
  <artifactId>spring-boot-starter-data-redis</artifactId>
</dependency>
```

```
# Redis 数据库索引（默认为0）
spring.redis.database = 0
# Redis 服务器地址
spring.redis.host = 192.168.0.71
# Redis 服务器连接端口
spring.redis.port = 6379
# Redis 服务器连接密码（默认为空）
spring.redis.password =
# 连接池最大连接数（使用负值表示没有限制）
spring.redis.pool.max-active = 8
# 连接池最大阻塞等待时间（使用负值表示没有限制）
spring.redis.pool.max-wait = -1
# 连接池中的最大空闲连接
spring.redis.pool.max-idle = 8
# 连接池中的最小空闲连接
spring.redis.pool.min-idle = 0
# 连接超时时间（毫秒）
spring.redis.timeout = 10000
```

#### 缓存配置
```java
@Configuration
@EnableCaching
public class RedisConfig extends CachingConfigurerSupport {
  @Bean
  public KeyGenerator keyGenerator() {
    return new KeyGenerator() {
      @Override
      public Object generate(Object target, Method method, Object... params) {
        StringBuilder sb = new StringBuilder();
        sb.append(target.getClass().getName());
        sb.append(method.getName());
        for (Object obj : params) {
          sb.append(obj.toString());
        }
        return sb.toString();
      }
    };
  }

  @Bean
  public CacheManager cacheManager(RedisTemplate redisTemplate) {
    RedisCacheManager rcm = new RedisCacheManager(redisTemplate);
    //设置缓存过期时间
    //rcm.setDefaultExpiration(60);//秒
    return rcm;
  }
}
```

#### 测试
```java
@RunWith(SpringRunner.class)
@SpringBootTest
public class TestRedisTemplate {
  @Autowired
  private RedisTemplate redisTemplate;

  @Test
  public void testString () {
    redisTemplate.opsForValue().set("neo", "ityouknow");
    Assert.assertEquals("ityouknow", redisTemplate.opsForValue().get("neo"));
  }
}
```


#### 各类型实操
- 实体
```java
@Test
public void testObj(){
  User user = new User("ityouknow@126.com", "smile", "youknow", "know","2020");
  ValueOperations<String, User> operations = redisTemplate.opsForValue();
  operations.set("com.neo", user);
  User u = operations.get("com.neo");
  System.out.println("user: "+u.toString());
}
```
- 超时失效
#### 超时失效
```java
@Test
public void testExpire() throws InterruptedException {
  User user=new User("ityouknow@126.com", "expire", "youknow", "expire","2020");
  ValueOperations<String, User> operations=redisTemplate.opsForValue();
  operations.set("expire", user,100,TimeUnit.MILLISECONDS);
  Thread.sleep(1000);
  boolean exists=redisTemplate.hasKey("expire");

  if (exists) {
    System.out.println("exists is true");
  } else {
    System.out.println("exists is false");
  }
}
```
- 删除数据
```java
@Test
public void testDelete() {
  ValueOperations<String, User> operations=redisTemplate.opsForValue();
  redisTemplate.opsForValue().set("deletekey", "ityouknow");
  redisTemplate.delete("deletekey");
  boolean exists=redisTemplate.hasKey("deletekey");

  if (exists) {
    System.out.println("exists is true");
  } else {
    System.out.println("exists is false");
  }
}
```

- hash（哈希）
```java
@Test
public void testHash() {
  HashOperations<String, Object, Object> hash = redisTemplate.opsForHash();
  hash.put("hash", "you", "you");
  String value = (String) hash.get("hash","you");
  System.out.println("hash value:" + value);
}
```

- List
```java
@Test
public void testList() {
  ListOperations<String, String> list = redisTemplate.opsForList();
  list.leftPush("list", "it");
  list.leftPush("list", "you");
  list.leftPush("list", "know");
  String value = (String)list.leftPop("list");
  System.out.println("list value:" + value.toString());
}
```

- set
```java
@Test
public void testSet() {
  String key = "set";
  SetOperations<String, String> set = redisTemplate.opsForSet();
  set.add(key, "it");
  set.add(key, "you");
  set.add(key, "you");
  set.add(key, "know");
  Set<String> values = set.members(key);

  for (String v:values){
    System.out.println("set value :"+v);
  }
}
```

- 测试 difference
```java
SetOperations<String, String> set = redisTemplate.opsForSet();
String key1 = "setMore1";
String key2 = "setMore2";

set.add(key1, "it");
set.add(key1, "you");
set.add(key1, "you");
set.add(key1, "know");
set.add(key2, "xx");
set.add(key2, "know");
Set<String> diffs = set.difference(key1,key2);

for (String v: diffs) {
  System.out.println("diffs set value :"+v);
}
```

- 测试 unions
```java
SetOperations<String, String> set = redisTemplate.opsForSet();

String key3="setMore3";
String key4="setMore4";

set.add(key3, "it");
set.add(key3, "you");
set.add(key3, "xx");
set.add(key4, "aa");
set.add(key4, "bb");
set.add(key4, "know");
Set<String> unions = set.union(key3, key4);

for (String v:unions) {
  System.out.println("unions value :" + v);
}
```

- Zset
```java
@Test
public void testZset () {
  String key = "zset";
  redisTemplate.delete(key);
  ZSetOperations<String, String> zset = redisTemplate.opsForZSet();
  zset.add(key, "it", 1);
  zset.add(key, "you", 6);
  zset.add(key, "know", 4);
  zset.add(key, "neo", 3);

  Set<String> zsets = zset.range(key, 0, 3);
  for (String v:zsets) {
    System.out.println("zset value :" + v);
  }

  Set<String> zsetB = zset.rangeByScore(key, 0, 3);
  for (String v:zsetB) {
    System.out.println("zsetB value :" + v);
  }
}
```

- 封装
```java
@Service
public class RedisService {
  @Autowired
  private RedisTemplate redisTemplate;
}
```

```java
public boolean set(final String key, Object value) {
  boolean result = false;
  try {
    ValueOperations<Serializable, Object> operations = redisTemplate.opsForValue();
    operations.set(key, value);
    result = true;
  } catch (Exception e) {
    logger.error("set error: key {}, value {}",key,value,e);
  }

  return result;
}
```

```java
public void removePattern(final String pattern) {
  Set<Serializable> keys = redisTemplate.keys(pattern);

  if (keys.size() > 0) {
    redisTemplate.delete(keys);
  }
}
```

```java
@Autowired
private RedisService redisService;

@Test
public void testString() throws Exception {
  redisService.set("neo", "ityouknow");
  Assert.assertEquals("ityouknow", redisService.get("neo"));
}
```

