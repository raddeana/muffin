### 典型的应用目录
```folders
/my_application
  /bin
  /devlib
  /lib
  /src
    /org/myapp/
      /action
      /data
        /mybatis-config.xml
        /BlogMapper.java
        /BlogMapper.xml
      /model
      /service
      /view
    /properties
  /test
    /org/myapp/
      /action
      /data
      /model
      /service
      /view
    /properties
  /web
    /WEB-INF
      /web.xml
```

### SqlSessions
- 获取映射器和管理事务
- MyBatis 的主要 Java 接口就是 SqlSession
- 执行语句方法
- 批量立即
- 本地缓存
- 确保 SqlSession 被关闭

#### SqlSessionFactoryBuilder
SqlSessionFactoryBuilder 有五个build方法
```java
  SqlSessionFactory build(InputStream inputStream)
  SqlSessionFactory build(InputStream inputStream, String environment)
  SqlSessionFactory build(InputStream inputStream, Properties properties)
  SqlSessionFactory build(InputStream inputStream, String env, Properties props)
  SqlSessionFactory build(Configuration config)
```

```xml
<environments default="development">
  <environment id="development">
    <transactionManager type="JDBC">
    <dataSource type="POOLED">
  </environment>
  <environment id="production">
    <transactionManager type="MANAGED">
    <dataSource type="JNDI">
  </environment>
</environments>
```

#### 加载顺序
- 读取在 properties 元素体中指定的属性；
- 读取从 properties 元素的类路径 resource 或 url 指定的属性，且会覆盖已经指定了的重复属性
- 读取作为方法参数传递的属性，且会覆盖已经从 properties 元素体和 resource 或 url 属性中加载了的重复属性

#### SqlSessionFactory
事务处理：需要在 session 使用事务或者使用自动提交功能（auto-commit）
连接：需要依赖 MyBatis 获得来自数据源的配置吗？还是使用自己提供的配置
执行语句：需要 MyBatis 复用预处理语句和/或批量更新语句（包括插入和删除）

```java
SqlSession openSession()
SqlSession openSession(boolean autoCommit)
SqlSession openSession(Connection connection)
SqlSession openSession(TransactionIsolationLevel level)
SqlSession openSession(ExecutorType execType,TransactionIsolationLevel level)
SqlSession openSession(ExecutorType execType)
SqlSession openSession(ExecutorType execType, boolean autoCommit)
SqlSession openSession(ExecutorType execType, Connection connection)
Configuration getConfiguration()
```

将会创建有如下特性的 SqlSession：
- 会开启一个事务（也就是不自动提交）
- 将从由当前环境配置的 DataSource 实例中获取 Connection 对象
- 事务隔离级别将会使用驱动或数据源的默认设置
- 预处理语句不会被复用，也不会批量处理更新

枚举类型：
- ExecutorType.SIMPLE：这个执行器类型不做特殊的事情。它为每个语句的执行创建一个新的预处理语句
- ExecutorType.REUSE：这个执行器类型会复用预处理语句
- ExecutorType.BATCH：这个执行器会批量执行所有更新语句，如果 SELECT 在它们中间执行，必要时请把它们区分开来以保证行为的易读性

#### SqlSession
- 执行语句方法
方法被用来执行定义在 SQL 映射的 XML 文件中的 SELECT、INSERT、UPDATE 和 DELETE 语句
- 批量立即更新方法
方法可以刷新（执行）存储在 JDBC 驱动类中的批量更新语句
- 本地缓存
两种缓存：本地缓存（local cache）和二级缓存（second level cache）
- 使用映射器
映射器类就是一个仅需声明与 SqlSession 方法相匹配的方法的接口类
- 映射器注解
- 映射申明



