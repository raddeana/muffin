### 1. malloc 和 free
#### 声明
```c
void* malloc(size_t size);
void* free(void* pointer);
```

#### Example
```c
int* pi;
pi = malloc(100);

if(pi == NULL) {
  printf("out of memory\n");
  exit(1);
}
```

malloc分配一块连续的内存，所以如果内存池不够你需要分配的内存，它会返回一个NULL指针，所以对每个从malloc返回的指针都进行检查是非常有必要的
free的参数要么是NULL，要么是一个先前从malloc，calloc或realloc返回的值，向free传递一个NULL参数并不产生任何后果

### 2. calloc 和 realloc
#### 声明
```c
void* calloc(size_t num_elements, size_t element_size)
void* realloc(void* ptr, size_t new_size)
```
calloc的参数包括所需元素的数量和每个元素的字节数
realloc函数用于修改一个原先已经分配的内存块的大小

### 3. 常见的动态内存错误
- 对NULL指针进行解引用操作
- 对分配的内存进行操作时越过边界
- 释放并非动态内存分配的内存
- 试图释放一块动态内存的内存的一部分以及
- 动态内存被释放之后继续被使用
