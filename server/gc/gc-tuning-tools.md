#### JVM 在程序执行的过程中, 提供了GC行为的原生数据
- 各个内存池的当前使用情况
- 各个内存池的总容量
- 每次GC暂停的持续时间
- GC暂停在各个阶段的持续时间

#### JMX API
从 JVM 运行时获取GC行为数据, 最简单的办法是使用标准 JMX API 接口
常见的 JMX客户端是 JConsole 和 JVisualVM (可以安装各种插件,十分强大)

#### JMX API 获取的信息
- CollectionCount: 垃圾收集器执行的GC总次数
- CollectionTime:
  - 收集器运行时间的累计
  - 这个值等于所有GC事件持续时间的总和
- LastGcInfo:
  - 最近一次GC事件的详细信息
  - 包括 GC事件的持续时间 (duration), 开始时间 (startTime) 和 结束时间 (endTime), 以及各个内存池在最近一次GC之前和之后的使用情况
- MemoryPoolNames: 各个内存池的名称
- Name: 垃圾收集器的名称
- ObjectName: 由JMX规范定义的 MBean的名字
- Valid: 此收集器是否有效

#### JVisualVM
JVisualVM 工具的 "VisualGC" 插件提供了基本的 JMX客户端功能, 还实时显示出 GC事件以及各个内存空间的使用情况

#### jstat
jstat 也是标准JDK提供的一款监控工具(Java Virtual Machine statistics monitoring tool),可以统计各种指标
jstat 对于快速确定GC行为是否健康非常有用

#### GC日志
通过日志内容也可以得到GC相关的信息

#### GCViewer
来将庞大的GC日志解析为直观易读的图形信息

#### 分析器(Profilers)
- hprof 分析器内置于JDK之中; 在各种环境下都可以使用, 一般优先使用这款工具
- Java VisualVM
- AProf 是由 Devexperts 开发的 AProf
