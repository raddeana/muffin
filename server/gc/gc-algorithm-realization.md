#### GC 算法 (实现篇) - GC参考手册
| Young                   | Tenured                | JVM options                                |
| Incremental (增量GC)	  |  Incremental	          |  -Xincgc                                  |
| Serial	                |  Serial	               |  -XX:+UseSerialGC                          |
| Parallel Scavenge	      |  Serial                |  -XX:+UseParallelGC -XX:-UseParallelOldGC  |
| Parallel New	          |  Serial	               |  N/A                                       |
| Serial	                |  Parallel Old	         |  N/A                                       |
| Parallel Scavenge	      |  Parallel Old	         |  -XX:+UseParallelGC -XX:+UseParallelOldGC  |
| Parallel New	          |  Parallel Old	         |  N/A                                       |
| Serial	                |  CMS	                 |  -XX:-UseParNewGC -XX:+UseConcMarkSweepGC  |
| Parallel                |  Scavenge	CMS	         |  N/A                                       |
| Parallel New	          |  CMS	                 |  -XX:+UseParNewGC -XX:+UseConcMarkSweepGC  |
| G1	                                             |  -XX:+UseG1GC                              |

#### 工作原理
- 年轻代和老年代的串行GC (Serial GC)
- 年轻代和老年代的并行GC (Parallel GC)
- 年轻代的并行GC (Parallel New) + 老年代的CMS (Concurrent Mark and Sweep)
- G1, 负责回收年轻代和老年代

#### Serial GC (串行GC)
- Serial GC 对年轻代使用 mark-copy(标记-复制) 算法, 对老年代使用 mark-sweep-compact(标记-清除-整理)算法
- 两者都是单线程的垃圾收集器, 不能进行并行处理
- 两者都会触发全线暂停(STW), 停止所有的应用线程
- 这种GC算法不能充分利用多核CPU
- 不管有多少CPU内核, JVM 在垃圾收集时都只能使用单个核心

指定一个JVM启动参数即可, 同时对年轻代和老年代生效
```cmd
java -XX:+UseSerialGC com.mypackages.MyExecutableClass
```
```cmd
-XX: +PrintGCDetails -XX:+PrintGCDateStamps 
-XX: +PrintGCTimeStamps
```

#### Minor GC(小型GC)
#### Full GC(完全GC)
#### Parallel GC(并行GC)
并行垃圾收集器这一类组合, 在年轻代使用 标记-复制(mark-copy)算法, 在老年代使用 标记-清除-整理(mark-sweep-compact)算法
年轻代和老年代的垃圾回收都会触发STW事件,暂停所有的应用线程来执行垃圾收集
两者在执行 标记和 复制/整理阶段时都使用多个线程, 因此得名 "(Parallel)"
```cmd
java -XX:+UseParallelGC com.mypackages.MyExecutableClass
java -XX:+UseParallelOldGC com.mypackages.MyExecutableClass
java -XX:+UseParallelGC -XX:+UseParallelOldGC com.mypackages.MyExecutableClass
```
#### 对系统资源的有效使用, 能达到更高的吞吐量
- 在 GC 期间, 所有 CPU 内核都在并行清理垃圾, 所以暂停时间更短
- 在两次 GC 周期的间隔期, 没有GC线程在运行, 不会消耗任何系统资源

#### Minor GC(小型GC)
第一次GC事件是清理年轻代的小型GC(Minor GC)



