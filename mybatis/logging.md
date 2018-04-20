#### 日志
- SLF4J
- Apache Commons Logging
- Log4j 2
- Log4j
- JDK logging

```xml
<configuration>
  <settings>
    <setting name="logImpl" value="LOG4J"/>
  </settings>
</configuration>
```
```java
org.apache.ibatis.logging.LogFactory.useSlf4jLogging()
org.apache.ibatis.logging.LogFactory.useLog4JLogging()
org.apache.ibatis.logging.LogFactory.useJdkLogging()
org.apache.ibatis.logging.LogFactory.useCommonsLogging()
org.apache.ibatis.logging.LogFactory.useStdOutLogging()
```

#### 日志配置
- 添加 Log4J 的 jar 包
对于 web 应用或企业级应用，则需要将 log4j.jar 添加到 WEB-INF/lib 目录下；对于独立应用，可以将它添加到JVM 的 -classpath 启动参数中

- 配置 Log4J
```java
package org.mybatis.example;
public interface BlogMapper {
  @Select("SELECT * FROM blog WHERE id = #{id}")
  Blog selectBlog(int id);
}
```

```configure
# Global logging configuration
log4j.rootLogger=ERROR, stdout
# MyBatis logging configuration...
log4j.logger.org.mybatis.example.BlogMapper=TRACE
# Console output...
log4j.appender.stdout=org.apache.log4j.ConsoleAppender
log4j.appender.stdout.layout=org.apache.log4j.PatternLayout
log4j.appender.stdout.layout.ConversionPattern=%5p [%t] - %m%n
```

```configure
log4j.logger.org.mybatis.example.BlogMapper.selectBlog=TRACE
```

```configure
log4j.logger.org.mybatis.example=TRACE
```

```configure
log4j.logger.org.mybatis.example=DEBUG
```

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper
  PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
  "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="org.mybatis.example.BlogMapper">
  <select id="selectBlog" resultType="Blog">
    select * from Blog where id = #{id}
  </select>
</mapper>
```

```configure
log4j.logger.org.mybatis.example.BlogMapper=TRACE
```

```configure
log4j.logger.org.mybatis.example.BlogMapper.selectBlog=TRACE
```
