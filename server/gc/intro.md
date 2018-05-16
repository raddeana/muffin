#### 垃圾收集简介
垃圾收集(Garbage Collection)的意思就是 —— 找到垃圾并进行清理
但现有的垃圾收集实现却恰恰相反: 垃圾收集器跟踪所有正在使用的对象, 并把其余部分当做垃圾

##### 手动内存管理(Manual Memory Management)
- 自动垃圾收集算法极为先进, 但我们先来看看什么是手动内存管理
- 如果要存储共享数据, 必须显式地进行 内存分配(allocate)和内存释放(free)
- 如果忘记释放, 则对应的那块内存不能再次使用
- 内存一直被占着, 却不再使用，这种情况就称为内存泄漏(memory leak)

```c
int send_request() {
    size_t n = read_size();
    int *elements = malloc(n * sizeof(int));

    if(read_elements(n, elements) < n) {
        // elements not freed!
        return -1;
    }

    free(elements)
    return 0;
}
```

##### 智能指针(Smart Pointers)
- 自动垃圾收集算法, 使用的是引用计数 (reference counting)
- 针对每个对象, 只需要记住被引用的次数, 当引用计数变为 0 时, 这个对象就可以被安全地回收 (reclaimed) 了

```c
int send_request() {
    size_t n = read_size();
    shared_ptr<vector<int>> elements = make_shared<vector<int>>();

    if (read_elements(n, elements) < n) {
        return -1;
    }

    return 0;
}
```

#### 自动内存管理
##### 引用计数 (Reference Counting)
C++ 共享指针方式, 可以应用到所有对象
许多语言都采用这种方法, 包括 Perl、Python 和 PHP

##### 标记-清除 (Mark and Sweep)
JVM 明确定义了什么是对象的可达性(reachability)
- 局部变量(Local variables)
- 活动线程(Active threads)
- 静态域(Static fields)
- JNI引用(JNI references)

JVM使用标记-清除算法(Mark and Sweep algorithm),来跟踪所有的可达对象(即存活对象),确保所有不可达对象(non-reachable objects)占用的内存都能被重用
- Marking(标记): 遍历所有的可达对象,并在本地内存(native)中分门别类记下
- Sweeping(清除): 这一步保证了,不可达对象所占用的内存, 在之后进行内存分配时可以重用

