#### Zookeeper
Zookeeper 是 Apacahe Hadoop 的子项目，是一个树型的目录服务，支持变更推送，适合作为 Dubbo 服务的注册中心，工业强度较高

#### 层级
- Zookeeper 的树根 Root 是 Dubbo，说明建立的 Zookeeper 分组为 Dubbo
- Service 层用来表示具体的接口服务
- Type 层用来区分是服务提供者，还是服务消费者
- URL 是具体服务提供者或者消费者对应的机器列表或者具体的路由规则

#### zoo.cfg
- 设置配置项 dataDir 为一个存在的以 data 结尾的目录
- 设置 Zookeeper 的监听端口 clientPort = 2181
- 设置 Zookeeper 心跳检查间隔 tickTime = 2000
- 设置 Follower 服务器启动时候从 Leader 同步完毕数据能忍受多少个心跳时间间隔数 initLimit = 5

#### ZooKeeper
- 服务提供方和调用方需要引入 ZKClient 的 Jar 包
- 指定一个 Zookeeper 的 IP 作为服务注册中心
```xml
<dubbo:registry address="zookeeper://12.22.123.101:2181" />
<dubbo:registry protocol="zookeeper" address="12.22.123.101:2181" />
```
- 指定多个 IP 作为服务注册中心
```xml
<dubbo:registry address="zookeeper://11.10.13.10:2181?backup=11.20.153.111:2181,11.30.133.112:2181" />
<dubbo:registry protocol="zookeeper" address="11.10.13.10:2181,11.20.153.111:2181,11.30.133.112:2181" /> 
```
- 在同一个 Zookeeper 服务器上划分多个分组
```xml
<dubbo:registry id="dubbo-registry-1" protocol="zookeeper" address="10.20.153.10:2181" group="registry-1" />
<dubbo:registry id="dubbo-registry-2" protocol="zookeeper" address="10.20.153.10:2181" group="registry-2" />
```
