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

#### 主要组件
- 服务提供者
- 服务调用者
- 地址服务器
- 配置服务器
- Diamond 服务器
  - 通过设置白名单（服务调用者所在服务节点 IP 地址）的方式设置某些服务或服务中的方法只能让特定 IP 地址的服务器调用
  - 通过用户认证的方式控制服务是否能够调用
  - 按照不同的服务器权重设置服务调用者对多个服务提供者服务节点的访问
  - 设置某些服务的 QPS 能力上限值, 一旦该服务的 QPS 达到该阀值, 则拒绝服务的继续调用, 这也是实现服务限流的技术实现, 在平台进行大促或秒杀场景时, 保障平台的稳定的重要屏障

#### HSF 服务框架工作原理
- 服务节点对配置服务器列表的获取
- 服务的注册发布
- 服务的订阅
- 服务规则的推送（如果需要）
- 服务交互

#### HSF 框架采用 Netty + Hession 数据序列化协议实现服务交互
#### HSF 框架的容错机制
#### HSF 框架的线性扩展支持

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
