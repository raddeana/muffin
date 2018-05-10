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
- 
- 
- 



