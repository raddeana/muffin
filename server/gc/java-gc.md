### 标记-清除(Mark and Sweep)是最经典的垃圾收集算法

#### 碎片整理(Fragmenting and Compacting)
每次执行清除(sweeping), JVM 都必须保证不可达对象占用的内存能被回收重用
- 在创建新对象时, JVM在连续的块中分配内存
- 写入操作越来越耗时, 因为寻找一块足够大的空闲内存会变得非常麻烦

#### 分代假设(Generational Hypothesis)
VM中的内存被分为年轻代(Young Generation)和老年代(Old Generation)
老年代有时候也称为 年老区(Tenured)
- 大部分对象很快就不再使用
- 还有一部分不会立即无用, 但也不会持续(太)长时间

拆分为这样两个可清理的单独区域，允许采用不同的算法来大幅提高GC的性能

#### 内存池(Memory Pools)
- 堆内存中的内存池划分也是类似的
- 不太容易理解的地方在于各个内存池中的垃圾收集是如何运行的

#### 新生代(Eden, 伊甸园)
- Eden 是内存中的一个区域, 用来分配新创建的对象
- 通常会有多个线程同时创建多个对象, 所以 Eden 区被划分为多个线程本地分配缓冲区 (Thread Local Allocation Buffer, 简称TLAB)
- 通过这种缓冲区划分, 大部分对象直接由JVM 在对应线程的TLAB中分配, 避免与其他线程的同步操作

#### 存活区(Survivor Spaces)
- Eden 区的旁边是两个存活区, 称为 from 空间和 to 空间
- 需要着重强调的的是, 任意时刻总有一个存活区是空的(empty)
- 空的那个存活区用于在下一次年轻代 GC 时存放收集的对象
- 具体的提升阈值由JVM动态调整, 但也可以用参数 -XX: +MaxTenuringThreshold 来指定上限

#### 老年代(Old Generation)
老年代的GC实现要复杂得多
老年代内存空间通常会更大，里面的对象是垃圾的概率也更小
老年代空间的清理算法通常是建立在不同的基础上的
采用移动对象的方式来实现最小化内存碎片
预期老年代中的对象大部分是存活的, 所以不再使用标记和复制(Mark and Copy)算法
- 通过标志位(marked bit),标记所有通过 GC roots 可达的对象
- 删除所有不可达对象
- 整理老年代空间中的内容，方法是将所有的存活对象复制,从老年代空间开始的地方,依次存放

#### 永久代(PermGen)
- Java 8 之前有一个特殊的空间, 称为 "永久代" (Permanent Generation)
- 这是存储元数据(metadata)的地方, 比如 class 信息等

#### 元数据区(Metaspace)
- 估算元数据所需空间那么复杂, Java 8直接删除了永久代(Permanent Generation), 改用 Metaspace
- 像类定义(class definitions)之类的信息会被加载到 Metaspace 中
```java
java -XX:MaxMetaspaceSize=256m com.mycompany.MyApplication
```

#### Minor GC vs Major GC vs Full GC
垃圾收集事件(Garbage Collection events)通常分为: 
- 小型GC(Minor GC) 
- 大型GC(Major GC) 
- 完全GC(Full GC) 

#### 小型GC(Minor GC)
年轻代内存的垃圾收集事件称为小型GC
- 当JVM无法为新对象分配内存空间时总会触发 Minor GC,比如 Eden 区占满时
- Minor GC 事件实际上忽略了老年代。从老年代指向年轻代的引用都被认为是GC Root
- 与一般的认识相反, Minor GC 每次都会引起全线停顿(stop-the-world ), 暂停所有的应用线程
所以 Minor GC 的定义很简单 —— Minor GC 清理的就是年轻代

#### Major GC vs Full GC
- Major GC(大型GC) 清理的是老年代空间(Old space)
- Full GC(完全GC)清理的是整个堆, 包括年轻代和老年代空间

去操心是叫 Major GC 呢还是叫 Full GC, 我们应该关注的是: 某次GC事件, 是否停止所有线程, 或者是与其他线程并发执行
JVM使用的是 并发标记和清除收集器（Concurrent Mark and Sweep collector，-XX:+UseConcMarkSweepGC)

#### 多个阶段执行
- 初始标记阶段(Initial Mark phase): 此阶段是全线停顿(STW)事件,暂停所有应用线程,以便执行初始标记
- 标记和预清理阶段(Markup and Preclean phase): 和应用线程并发执行
- 最终标记阶段(Final Remark phase): 此阶段也是全线停顿(STW)事件
- 清除操作(Sweep)是并发执行的, 不需要暂停应用线程

