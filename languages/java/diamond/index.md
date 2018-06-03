### diamond
diamond是淘宝内部使用的一个管理持久配置的系统, 它的特点是简单、可靠、易用, 目前淘宝内部绝大多数系统的配置, 由diamond来进行统一管理
diamond为应用系统提供了获取配置的服务, 应用不仅可以在启动时从diamond获取相关的配置, 而且可以在运行中对配置数据的变化进行感知并获取变化后的配置数据

- 配置分散在多个业务子系统里，对同一配置的翻译在多个子系统里经常不一致
- 将配置收敛成一个公有服务，可以有效改善，但是又会带来其他问题
- 配置收敛后，配置中心成了应用中的单点，配置如果挂了，应用也会跟着产生异常甚至挂掉

```java
DiamondManager manager = new DefaultDiamondManager(group, dataId, new ManagerListener() {
  public void receiveConfigInfo(String configInfo) {
    // 客户端处理数据的逻辑
  }
});
```

```java
String configInfo = manager.getAvailableConfigInfomation(timeout);
```

#### Diamond有两个主要配置类型 –single 和 aggr
##### ConfigInfo
- dataId
- group
- content
- md5
- appName

##### ConfigInfoAggr
- dataId
- group
- content
- appName
- datumId

Aggr 和 single相比, 少md5多datumId
DatumId是aggr的逻辑主键, aggr下dataId和datumId是1对多的关系, 也就是说多条aggr会聚合成一条single, diamond通过merge任务对aggr合并最终生成一条single

#### Diamond主要有ops, sdk, client 和 server 4个组件
- Ops是运维用的配置工具，主要用于下发以及查询配置等；server则是Diamond的后台，处理配置的一些逻辑
- sdk则是提供给ops或者其他第三方应用的开发工具包；client则是编程api，它和sdk乍看有点像，其实差别很大，sdk是用于构建前台运维配置程序的，本质是对数据的维护，所有的访问和操作都是直接面向数据库的
- 而client则是这些数据的消费者，事实上准确的说是diamond的消费者们（各子系统）都是通过client组件对server访问

Diamond server是无中心节点的逻辑集群，读请求都是访问local file，而写请求则会先进入数据库，接着再更新各节点缓存
#### 内存缓存
- Client端使用的内存cache是一个AtomicReference
  - 它并不是通常理解的内存缓存，而只是一个事件源，只有被监听的配置才会有cache
  - 客户端的长轮询任务（下一节将会重点介绍）只轮询被监听的配置，也就是cache的数据
  - 没被监听的数据不需要轮询，因为diamond提供的读数据api默认会先从服务节点获取实时数据
- 在客户端发起长轮询或者服务节点做dump时，都需要对比md5信息以确定是否要推送或者dump
- 无论客户端还是服务端，内存缓存仅仅是为了满足某种功能需求，并不作为读的数据源（客户端只缓存部分数据，服务端不缓存配置内容）

#### 长轮询
Client默认启动周期任务对server进行长轮询感知server的配置变化，server感知到配置变化就发送变更的数据编号，客户端通过数据编号再去拉取最新配置数据；否则超时结束请求（默认10秒）

#### 任务管理
Diamond收到配置请求，先执行数据库操作，然后再向任务管理器的任务栈里插入一条任务，任务管理器感知到新任务后，pick相应的TaskProcessor处理
Diamond的任务管理器是FIFO的，这会造成长延时任务阻塞其他任务的执行。为解决这个问题，Diamond的开发者为每个Task都定制TaskManager

#### 其他一些任务
- Merge任务用于合并aggr
- DumpAllTask会每6小时run一次做全量dump，全量删除老的缓存数据，生成新缓存
- DumpChangeTask做增量dump
- 清除历史数据用于清除1周前的数据库his表数据
- 心跳任务用于记录心跳时间, 节点服务重启时会判断距离上次心跳时间是否已经超过一小时, 超过一小时则做全量dump, 否则做增量
