#### ORM
对象关系映射（Object Relational Mapping，简称 ORM）模式是一种为了解决面向对象与关系数据库存在的互不匹配的现象技术

#### Mybaits
优点:
- SQL 被统一提取出来，便于统一管理和优化
- SQL 和代码解耦，将业务逻辑和数据访问逻辑分离，使系统的设计更清晰，更易维护，更易单元测试
- 提供映射标签，支持对象与数据库的 ORM 字段关系映射
- 提供对象关系映射标签，支持对象关系组件维护
- 灵活书写动态 SQL，支持各种条件来动态生成不同的 SQL
缺点:
- 编写 SQL 语句时工作量很大，尤其是字段多、关联表多时，更是如此
- SQL 语句依赖于数据库，导致数据库移植性差

#### MyBatis 重要的概念
- Mapper 配置: 
  - Mapper 配置可以使用基于 XML 的 Mapper 配置文件来实现
  - 也可以使用基于 Java 注解的 MyBatis 注解来实现
  - 甚至可以直接使用 MyBatis 提供的 API 来实现

- Mapper 接口: 
  - Mapper 接口是指自行定义的一个数据操做接口，类似于通常所说的 DAO 接口

- Executor
  - MyBatis 中所有的 Mapper 语句的执行都是通过 Executor 进行的，Executor 是 MyBatis 的一个核心接口

- SqlSession 
  - SqlSession 是 MyBatis 的关键对象，是执行持久化操作的独享
  - 类似于 JDBC 中的 Connection，SqlSession 对象完全包含以数据库为背景的所有执行 SQL 操作的方法，它的底层封装了 JDBC 连接
  - 可以用 SqlSession 实例来直接执行被映射的 SQL 语句
  
- SqlSessionFactory
  - SqlSessionFactory 是 MyBatis 的关键对象，它是单个数据库映射关系经过编译后的内存镜像
  
#### MyBatis 的工作流程
- 加载 Mapper 配置的 SQL 映射文件，或者是注解的相关 SQL 内容
- 创建会话工厂，MyBatis 通过读取配置文件的信息来构造出会话工厂 (SqlSessionFactory)
- 创建会话。根据会话工厂，MyBatis 就可以通过它来创建会话对象 (SqlSession) 
- 会话对象是一个接口，该接口中包含了对数据库操作的增删改查方法
- 创建执行器。因为会话对象本身不能直接操作数据库，所以它使用了一个叫做数据库执行器 (Executor) 的接口来帮它执行操作
- 封装 SQL 对象。在这一步，执行器将待处理的 SQL 信息封装到一个对象中 (MappedStatement)
- 该对象包括 SQL 语句、输入参数映射信息 (Java 简单类型、HashMap 或 POJO)
- 输出结果映射信息 (Java 简单类型、HashMap 或 POJO)
- 操作数据库。拥有了执行器和 SQL 信息封装对象就使用它们访问数据库了，最后再返回操作结果，结束流程

#### MyBatis-Spring-Boot-Starter
- 构建独立的应用
- 几乎可以零配置
- 需要很少的 XML 配置

#### XML 版本
```xml
<dependency>
  <groupId>org.mybatis.spring.boot</groupId>
  <artifactId>mybatis-spring-boot-starter</artifactId>
  <version>1.3.1</version>
</dependency>
```
```xml
<dependency>
  <groupId>org.apache.commons</groupId>
  <artifactId>commons-lang3</artifactId>
  <version>3.6</version>
</dependency>
```

#### application.properties
application.properties 添加相关配置:
```xml
properties
mybatis.config-locations=classpath:mybatis/mybatis-config.xml
mybatis.mapper-locations=classpath:mybatis/mapper/*.xml
mybatis.type-aliases-package=com.neo.entity

spring.datasource.driverClassName = com.mysql.jdbc.Driver
spring.datasource.url = jdbc:mysql://localhost:3306/test1?useUnicode=true&characterEncoding=utf-8
spring.datasource.username = root
spring.datasource.password = root
```

- mybatis.config-locations: 配置 mybatis-config.xml 路径，mybatis-config.xml 中配置 MyBatis 基础属性。
- mybatis.mapper-locations: 配置 Mapper 对应的 XML 文件路径
- mybatis.type-aliases-package: 配置项目中实体类包路径
- spring.datasource.*: 数据源配置

#### 启动类
```java
@Spring BootApplication
@MapperScan("com.neo.mapper")
public class Application {
  public static void main(String[] args) {
    SpringApplication.run(Application.class, args);
  }
}
```

#### 类型配置
```xml
<configuration>
  <typeAliases>
    <typeAlias alias="Integer" type="java.lang.Integer" />
    <typeAlias alias="Long" type="java.lang.Long" />
    <typeAlias alias="HashMap" type="java.util.HashMap" />
    <typeAlias alias="LinkedHashMap" type="java.util.LinkedHashMap" />
    <typeAlias alias="ArrayList" type="java.util.ArrayList" />
    <typeAlias alias="LinkedList" type="java.util.LinkedList" />
  </typeAliases>
</configuration>
```

#### 注解
```java
public interface UserMapper {
    @Select("SELECT * FROM users")
    @Results({
        @Result(property = "userSex",  column = "user_sex", javaType = UserSexEnum.class),
        @Result(property = "nickName", column = "nick_name")
    })
    List<UserEntity> getAll();

    @Select("SELECT * FROM users WHERE id = #{id}")
    @Results({
        @Result(property = "userSex",  column = "user_sex", javaType = UserSexEnum.class),
        @Result(property = "nickName", column = "nick_name")
    })
    UserEntity getOne(Long id);

    @Insert("INSERT INTO users(userName,passWord,user_sex) VALUES(#{userName}, #{passWord}, #{userSex})")
    void insert(UserEntity user);

    @Update("UPDATE users SET userName=#{userName},nick_name=#{nickName} WHERE id =#{id}")
    void update(UserEntity user);

    @Delete("DELETE FROM users WHERE id =#{id}")
    void delete(Long id);
}
```

- @Select 是查询类的注解，所有的查询均使用这个
- @Result 修饰返回的结果集，关联实体类属性和数据库字段一一对应，如果实体类属性和数据库属性名保持一致，就不需要这个属性来修饰
- @Insert 插入数据库使用，直接传入实体类会自动解析属性到对应的值
- @Update 负责修改，也可以直接传入对象
- @delete 负责删除

