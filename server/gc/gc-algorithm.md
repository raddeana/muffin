### GC 算法
#### 记录(census)所有的存活对象, 在垃圾收集中有一个叫做 标记(Marking) 的过程专门干这件事

##### 标记可达对象(Marking Reachable Objects)
现代JVM中所有的GC算法,第一步都是找出所有存活的对象
- 当前正在执行的方法里的局部变量和输入参数
- 活动线程(Active threads)
- 内存中所有类的静态字段(static field)
- JNI引用

##### 删除不可达对象(Removing Unused Objects)
- 清除(sweeping)
- 整理(compacting)
- 复制(copying)

GC遍历(traverses)内存中整体的对象关系图(object graph), 从GC根元素开始扫描, 到直接引用，以及其他对象 (通过对象的属性域)
所有GC访问到的对象都被标记(marked)为存活对象

- Sweep(清除)
Mark and Sweep(标记-清除) 算法的概念非常简单: 直接忽略所有的垃圾
- Compact(整理)
标记-清除-整理算法(Mark-Sweep-Compact), 将所有被标记的对象(存活对象), 迁移到内存空间的起始处, 消除了 标记 - 清除 算法的缺点
- Copy(复制)
标记-复制算法(Mark and Copy) 和 标记-整理算法(Mark and Compact) 十分相似: 两者都会移动所有存活的对象
