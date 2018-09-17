#### Java性能优化
- 尽量在合适的场合使用单例
  - 控制资源的使用，通过线程同步来控制资源的并发访问
  - 控制实例的产生，以达到节约资源的目的
  - 控制数据共享，在不建立直接关联的条件下，让多个不相关的进程或线程之间实现通信
- 尽量避免随意使用静态变量
- 尽量避免过多过常地创建Java对象
- 尽量使用final修饰符：带有final修饰符的类是不可派生的。在JAVA核心API中，有许多应用final的例子
- 尽量使用局部变量：调用方法时传递的参数以及在调用中创建的临时变量都保存在栈（Stack）中，速度较快；其他变量，如静态变量、实例变量等，都在堆（Heap）中创建，速度较慢
- 包装类型和基本类型两者的使用场所
- 慎用synchronized，尽量减小synchronize的方法
- 不要使用finalize方法
- 使用基本数据类型代替对象
- 多线程在未发生线程安全前提下应尽量使用HashMap、ArrayList
- 合理的创建HashMap
- 减少对变量的重复计算
- 避免不必要的创建
- 在finally块中释放资源
- 使用移位来代替'a/b'的操作
- 使用移位来代替'a*b'的操作
- 确定StringBuffer的容量
- 早释放无用对象的引用
- 避免使用二维数组
- 避免使用split
- ArrayList & LinkedList
- 使用System.arraycopy ()代替通过来循环复制数组
- 缓存经常使用的对象
- 避免非常大的内存分配
- 慎用异常
- 重用对象
- 初始化变量
- 减少Oracle解析器的解析负担
- 关闭以释放资源
- 过分的创建对象会消耗系统的大量内存
- 在使用同步机制时，应尽量使用方法同步代替代码块同步
- 不要在循环中使用Try/Catch语句，应把Try/Catch放在循环最外层
- 通过StringBuffer的构造函数来设定它的初始化容量，可以明显提升性能
- 合理使用java.util.Vector
- 不用new关键字创建对象的实例
- 不要将数组声明为：public static final
- HaspMap的遍历：
```java
Map<String, String[]> paraMap = new HashMap<String, String[]>(); 
 
for (Entry<String, String[]> entry : paraMap.entrySet()) {
  String appFieldDefId = entry.getKey();
  String[] values = entry.getValue();
} 
```
- array(数组)和ArrayList的使用
- 单线程应尽量使用 HashMap, ArrayList,除非必要，否则不推荐使用HashTable,Vector，它们使用了同步机制，而降低了性能
- StringBuffer,StringBuilder的区别在于：java.lang.StringBuffer 线程安全的可变字符序列
- 使用基本数据类型代替对象
- 使用具体类比使用接口效率高，但结构弹性降低了，但现代IDE都可以解决这个问题
- 考虑使用静态方法，如果你没有必要去访问对象的外部，那么就使你的方法成为静态方法
- 应尽可能避免使用内在的GET,SET方法
- 避免枚举，浮点数的使用
