### diamond
diamond是淘宝内部使用的一个管理持久配置的系统, 它的特点是简单、可靠、易用, 目前淘宝内部绝大多数系统的配置, 由diamond来进行统一管理
diamond为应用系统提供了获取配置的服务, 应用不仅可以在启动时从diamond获取相关的配置, 而且可以在运行中对配置数据的变化进行感知并获取变化后的配置数据

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
