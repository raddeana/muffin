### HSF
HSF 提供的是分布式服务开发框架，taobao内部使用较多，总体来说其提供的功能及一些实现基础：
- 标准Service方式的RPC
  - Service定义：基于OSGI的Service定义方式
  - TCP/IP通信：
   - IO方式: nio, 采用mina框架
   - 连接方式: 长连接
   - 服务器端有限定大小的连接池
   - WebService 方式
  - 序列化：Hessian序列化机制
- 软件负载体系
- 模块化、动态化
- 服务治理

#### pom.xml
```xml
<dependency>  
  <groupId>com.taobao.hsf</groupId>
  <artifactId>hsf.connector.spring</artifactId>
  <version>xxx</version>
</dependency>  
```

#### 提供者方要做的工作包括
- 将interface的代码打成Jar包，放进maven仓库中，供使用者下载使用，而具体代码实现则不需要放进jar包中，使用者只能调用，无法看见具体实现
- 在对应的HSF的配置文件里，将提供的服务提供出来
```xml
<bean id="xxxServiceImpl" class="xxx.xxxServiceImpl" />  
<bean id="xxxServiceProvider" class="com.taobao.hsf.app.spring.util.HSFSpringProviderBean" init-method="init">  
  <property name="serviceInterface">
    <value>xxx.xxxService</value>
  </property>
  <property name="target">
    <ref bean="xxxServiceImpl" />
  </property>
  <property name="serviceName">
    <value>xxxService</value>
  </property>
  <property name="serviceVersion">
    <value>xxx</value>
  </property>
  <property name="serviceGroup">
    <value>HSF</value>
  </property>
</bean>
```

```xml
<bean name="xxxService" class="com.taobao.hsf.app.spring.util.HSFSpringConsumerBean" init-method="init">
  <property name="interfaceName" value="xxx.xxxService" />
  <property name="version" value="xxx" />
</bean>
```
