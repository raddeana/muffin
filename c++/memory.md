#### 三个部分：静态区，栈，堆。

静态区：保存自动全局变量和static变量（包括static全局和局部变量）。
       静态区的内容在整个程序的生命周期内都存在，有编译器在编译的时候分配（数据段（存储全局数据和静态数据）和代码段（可执行的代码/只读常量））。

栈：保存局部变量。栈上的内容只在函数范围内存在，当函数运行结束的时候，这些内容也会自动销毁。
堆：由malloc系列函数或者new操作符分配的内存。其生命周期由free和delete决定。在没有释放之前一直存在，直到函数结束。

#### malloc、calloc、realloc

malloc 函数原型：(void*)malloc(unsigned size)
calloc 函数原型：void* calloc(size_t numElements, size_t sizeOfElements)
realloc 函数原型：void* realloc(void* ptr, unsigned newsize)

区别：
- 函数malloc不能初始化所分配的空间，而函数calloc能
- calloc函数会将所分配的内存空间中的每一位都初始化为0
- malloc向系统申请size个字节的空间
- realloc可以对给定的指针所指向的空间进行扩大或者缩小
- realloc是从堆上分配空间的
