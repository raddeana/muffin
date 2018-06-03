#### malloc 和 free
```c
void* malloc (size_t size)
void* free (void* pointer)
```
```c
int* pi
pi = malloc(100)

if(pi == NULL) {
  printf("out of memory\n")
  exit(1)
}
```

malloc分配一块连续的内存，所以如果内存池不够你需要分配的内存，它会返回一个NULL指针，所以对每个从malloc返回的指针都进行检查是非常有必要的
free的参数要么是NULL，要么是一个先前从malloc，calloc或realloc返回的值，向free传递一个NULL参数并不产生任何后果

#### new
new返回指定类型的指针，并且可以自动计算所需要的大小
```c
  int *p;
  p = new int;         // 返回类型为int *类型，分配的大小为sizeof(int)
  p = new int[100];    // 返回类型为int *类型，分配的大小为sizeof(int) * 100
  
  int *p;
  p = (int *)malloc(sizeof(int));
```

#### calloc
calloc的参数包括所需元素的数量和每个元素的字节数
calloc在动态分配完内存后，自动初始化该内存空间为零
```c
void* calloc(size_t num_elements, size_t element_size)
```

#### realloc
realloc函数用于修改一个原先已经分配的内存块的大小
```c
void* realloc(void* ptr, size_t new_size)
```

#### 常见的动态内存错误
- 对NULL指针进行解引用操作
- 对分配的内存进行操作时越过边界
- 释放并非动态内存分配的内存
- 试图释放一块动态内存的内存的一部分以及
- 动态内存被释放之后继续被使用

#### 一些警告
- 不检查从malloc函数返回的指针是否为NULL指针
- 访问动态分配的内存之外的内存
- 向free函数传递一个并非由malloc函数返回的指针
- 在动态内存被释放之后再访问它
