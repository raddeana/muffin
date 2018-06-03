#### 优化算法时间复杂度
list 和 set 查找某一个元素的时间复杂度分别是O(n)和O(1)
- 分治
- 分支界限
- 贪心
- 动态规划
#### 减少冗余数据
#### 合理使用 copy 与 deepcopy
对于 dict 和 list 等数据结构的对象，直接赋值使用的是引用的方式
#### 使用 dict 或 set 查找元素
python dict 和 set 都是使用 hash 表来实现(类似c++11标准库中unordered_map)，查找元素的时间复杂度是O(1)
dict 的效率略高(占用的空间也多一些)
#### 合理使用生成器（generator）和 yield
使用()得到的是一个 generator 对象，所需要的内存空间与列表的大小无关，所以效率会高一些
#### 优化循环
#### 优化包含多个判断表达式的顺序
#### 使用 join 合并迭代器中的字符串
join 对于累加的方式，有大约5倍的提升
#### 选择合适的格式化字符方式
#### 不借助中间变量交换两个变量的值
使用a,b=b,a而不是c=a;a=b;b=c;来交换a,b的值，可以快1倍以上

#### 使用 if is
使用 if is True 比 if == True 将近快一倍
#### 使用级联比较x < y < z

#### while 1 比 while True 更快
while 1 比 while true 快很多，原因是在 python2.x 中，True 是一个全局变量，而非关键字
#### 使用最佳的反序列化方式
#### 使用C扩展(Extension)
主要有 CPython(python最常见的实现的方式)原生API, ctypes,Cython，cffi三种方式，它们的作用是使得 Python 程序可以调用由C编译成的动态链接库，其特点分别是:
- CPython 原生 API: 通过引入 Python.h 头文件，对应的C程序中可以直接使用Python 的数据结构
- ctypes: 通常用于封装(wrap)C程序，让纯 Python 程序调用动态链接库（Windows 中的 dll 或 Unix 中的 so 文件）中的函数
- Cython: Cython 是 CPython 的超集，用于简化编写C扩展的过程
- cffi: cffi提供了在 python 使用C类库的方式，可以直接在 python 代码中编写C代码，同时支持链接到已有的C类库
#### 并行编程
因为 GIL 的存在，Python 很难充分利用多核 CPU 的优势
- 多进程：对于 CPU 密集型的程序，可以使用 multiprocessing 的 Process,Pool 等封装好的类，通过多进程的方式实现并行计算
- 对于 IO 密集型的程序，multiprocessing.dummy 模块使用 multiprocessing 的接口封装 threading，使得多线程编程也变得非常轻松(比如可以使用 Pool 的 map 接口，简洁高效)
- multiprocessing 中的 Managers 类提供了可以在不同进程之共享数据的方式，可以在此基础上开发出分布式的程序
#### PyPy
PyPy 是用 RPython(CPython 的子集)实现的 Python，根据官网的基准测试数据，它比 CPython 实现的 Python 要快6倍以上
#### 使用性能分析工具
除了上面在 ipython 使用到的 timeit 模块，还有 cProfile
