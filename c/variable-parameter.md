#### 可变参数函数调用
```c
sum(8L, 1L, 2L, 3L, 4L, 5L, 6L, 7L, 8L);
```

#### 调用约定
64位架构下，前6个基础类型（long、int、short 、 char和pointer）参数通过寄存器传递，第7个参数开始用栈传递
通过寄存器传递可减少压栈和弹栈开销，提升性能
具体来说，前6个参数分别通过寄存器 rdi，rsi，rdx，rcx，r8 和 r9 寄存器传递
剩下的参数，依次通过调用者的rsp + 0，rsp + 8，rsp + 16，……，rsp + 8 * N 这些地址空间传递

#### Linux实现方案
```h
#define va_start(v,l)   __builtin_va_start(v,l)
#define va_end(v)       __builtin_va_end(v)
#define va_arg(v,l)     __builtin_va_arg(v,l)
```
