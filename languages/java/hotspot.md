#### JVM (HotSpot)
- Serial收集器
Serial收集器是最基本、发展历史最悠久的收集器

- ParNew收集器
ParNew收集器其实就是Serial收集器的多线程版本，
除了使用多线程进行垃圾收集之外，
其余行为包括Serial收集器可用的所有控制参数、收集算法、Stop The World、对象分配规则、回收策略等都与 Serial 收集器完全一样

- Parallel Scavenge（并行回收）收集器
Parallel Scavenge收集器是一个新生代收集器，它也是使用复制算法的收集器，又是并行的多线程收集器

- Serial Old 收集器
Parallel Old 是Parallel Scavenge收集器的老年代版本，使用多线程和 "标记-整理" 算法

- Parallel Old 收集器
Serial Old是Serial收集器的老年代版本，它同样是一个单线程收集器，使用标记整理算法。这个收集器的主要意义也是在于给Client模式下的虚拟机使用

- CMS收集器
CMS (Concurrent Mark Sweep) 收集器是一种以获取最短回收停顿时间为目标的收集器

- G1收集器
G1收集器之所以能建立可预测的停顿时间模型，是因为它可以有计划地避免在真个Java堆中进行全区域的垃圾收集
