### Zookeeper的功能以及工作原理
ZooKeeper是一个分布式的，开放源码的分布式应用程序协调服务，是Google的Chubby一个开源的实现，它是集群的管理者，监视着集群中各个节点的状态根据节点提交的反馈进行下一步合理操作
- 文件系统
- 通知机制

### Zookeeper文件系统
每个子目录项如 NameService 都被称作为znode，和文件系统一样，我们能够自由的增加、删除znode，在一个znode下增加、删除子znode，唯一的不同在于znode是可以存储数据的
#### 有四种类型的znode
- PERSISTENT-持久化目录节点
  - 客户端与zookeeper断开连接后，该节点依旧存在
- PERSISTENT_SEQUENTIAL-持久化顺序编号目录节点
  - 客户端与zookeeper断开连接后，该节点依旧存在，只是Zookeeper给该节点名称进行顺序编号
- EPHEMERAL-临时目录节点
  - 客户端与zookeeper断开连接后，该节点被删除
- EPHEMERAL_SEQUENTIAL-临时顺序编号目录节点
  - 客户端与zookeeper断开连接后，该节点被删除，只是Zookeeper给该节点名称进行顺序编号
  
### Zookeeper通知机制
客户端注册监听它关心的目录节点，当目录节点发生变化（数据改变、被删除、子目录节点增加删除）时，zookeeper会通知客户端

### Zookeeper功能
- 命名服务
- 配置管理
- 集群管理
- 分布式锁
- 队列管理

### Zookeeper命名服务
在zookeeper的文件系统里创建一个目录，即有唯一的path。在我们使用tborg无法确定上游程序的部署机器时即可与下游程序约定好path，通过path即能互相探索发现

### Zookeeper的配置管理
- 程序总是需要配置的，如果程序分散部署在多台机器上，要逐个改变配置就变得困难
- 把这些配置全部放到zookeeper上去，保存在 Zookeeper 的某个目录节点中，然后所有相关应用程序对这个目录节点进行监听，一旦配置信息发生变化，每个应用程序就会收到 Zookeeper 的通知，然后从 Zookeeper 获取新的配置信息应用到系统中就好

### Zookeeper集群管理
### Zookeeper分布式锁
....

FROM: https://www.cnblogs.com/felixzh/p/5869212.html


