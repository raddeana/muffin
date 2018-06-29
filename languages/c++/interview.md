#### 变量的声明和定义有什么区别
为变量分配地址和存储空间的称为定义，不分配地址的称为声明

#### sizeof和strlen的区别
- sizeof是一个操作符，strlen是库函数
- sizeof的参数可以是数据的类型，也可以是变量，而strlen只能以结尾为‘\0‘的字符串作参数
- 编译器在编译时就计算出了sizeof的结果
- strlen函数必须在运行时才能计算出来
- sizeof计算的是数据类型占内存的大小，而strlen计算的是字符串实际的长度
- 数组做sizeof的参数不退化，传递给strlen就退化为指针

#### "标准" 宏MIN
```cpp
#define min(a, b) ((a) <= (b) ? (a) : (b))
```

#### 指针可以是volatile吗
因为指针和普通变量一样，有时也有变化程序的不可控性

#### a 和 &a 有什么区别请写出以下代码的打印结果，主要目的是考察 a 和 &a 的区别
```cpp
#include<stdio.h>   
void main (void) {   
  int a[5] = { 1, 2, 3, 4, 5 };
  int *ptr=(int *)(&a+1);
  printf("%d,%d",*(a+1),*(ptr-1));

  return;
}
```

#### 简述C、C++程序编译的内存分配情况
C、C++中内存分配方式可以分为三种
- 从静态存储区域分配: 内存在程序编译时就已经分配好，这块内存在程序的整个运行期间都存在
- 在栈上分配: 在执行函数时，函数内局部变量的存储单元都在栈上创建，函数执行结束时这些存储单元自动被释放
- 从堆上分配: 即动态内存分配，程序在运行的时候用malloc或new申请任意大小的内存，程序员自己负责在何时用free或delete释放内存。动态内存的生存期由程序员决定，使用非常灵活

#### 简述strcpy sprintf与mencpy的区别
- 操作对象不同，strcpy的两个操作对象均为字符串，sprintf的操作源对象可以是多种数据类型，目的操作对象是字符串，memcpy 的两个对象就是两个任意可操作的内存地址，并不限于何种数据类型
- 执行效率不同，memcpy最高，strcpy次之，sprintf的效率最低
- 实现功能不同，strcpy主要实现字符串变量间的拷贝，sprintf主要实现其他数据类型格式到字符串的转化，memcpy主要是内存块间的拷贝

#### 链表与数组的区别
- 存储形式: 数组是一块连续的空间，声明时就要确定长度。链表是一块可不连续的动态空间，长度可变，每个结点要保存相邻结点指针
- 数据查找: 数组的线性查找速度快，查找操作直接使用偏移地址。链表需要按顺序检索结点，效率低
- 数据插入或删除: 链表可以快速插入和删除结点，而数组则可能需要大量数据移动
- 越界问题: 链表不存在越界问题，数组有越界问题

#### 编码实现直接插入排序
```cpp
#include <stdio.h>  

int main()  
{  
    int i,temp,p;  
    int array[10] = {2,6,1,9,4,7,5,8,3,0};  
    printf("Display this array:\n");  
    for(i=0;i<10;i++)  
    {  
        printf("%d ",array[i]);  
    }  

    for(i=1;i<10;i++)  
    {  
        temp = array[i];  
        p = i-1;  
        while(p >= 0 && temp < array[p])  
        {  
            array[p+1] = array[p];  
            p--;  
        }  
        array[p+1] = temp;  
    }  
    printf("\n");  
    printf("After sorting,this array is:\n");  
    for(i=0;i<10;i++)  
    {  
        printf("%d ",array[i]);  
    }     
    printf("\n");  
    return 0;  
}  
```

#### 编码实现冒泡排序
```cpp
#include <stdio.h>  
#define LEN 10  

int main()  
{  
    int a,i,j;  
    int ARRAY[10]={23,1,4,9,6,17,24,56,98,72};  
    printf("\n");  
    printf("Display this array:\n");  
    
    for (a = 0;a < 10;a ++) {  
        printf("%d ",ARRAY[a]);  
    }
    
    printf("\n");  
    for (j = 0;j < 10;j ++) {
        for(i = 0;i < LEN-j-1;i ++) {
            int temp;  
            if (ARRAY[i] > ARRAY[i+1]) {  
                temp=ARRAY[i+1];  
                ARRAY[i+1]=ARRAY[i];  
                ARRAY[i]=temp;  
            }  
        }  
    }
    
    printf("\nAfter sorting,the array is:\n");  
    for(a=0; a < LEN; a++) {  
        printf("%d ",ARRAY[a]);  
    }
    
    printf("\n");  
    return 0;     
}
```

#### 编码实现直接选择排序
```cpp
#include <stdio.h>  

int main () {
    int i, j, t;
    int array[10]={ 2, 7, 1, 8, 5, 9, 3, 4, 0, 6 };  
    printf("\nDisplay this array:\n");  
    for(i = 0; i < 10; i ++) {  
        printf("%d ",array[i]);  
    }
    
    printf("\n");  
    for(i = 1;i <= 9;i ++) {
        int t = i-1;  
        for(j = i;j < 10;j ++) {
            if(array[j] < array[t]) {  
                t=j;  
            }  
        }
        
        if (t != (i-1)) {  
            int temp = 0;  
            temp=array[i-1];  
            array[i-1]=array[t];  
            array[t]=temp;  
        }  
    }  
    
    printf("After sorting,this array is:\n");  
    
    for(i = 0;i < 10;i ++) {
        printf("%d ",array[i]);  
    }  
    
    printf("\n");  
    return 0;  
}  
```

#### typedef和define有什么区别
- 用法不同：typedef用来定义一种数据类型的别名，增强程序的可读性。define主要用来定义常量，以及书写复杂使用频繁的宏
- 执行时间不同：typedef是编译过程的一部分，有类型检查的功能。define是宏定义，是预编译的部分，其发生在编译之前，只是简单的进行字符串的替换，不进行类型的检查
- 作用域不同：typedef有作用域限定; define不受作用域约束，只要是在define声明后的引用都是正确的
- 对指针的操作不同：typedef和define定义的指针时有很大的区别

#### 关键字const
const用来定义一个只读的变量或对象

#### static
static在c中主要用于: 
- 定义全局静态变量 
- 定义局部静态变量 
- 定义静态函数
在c++中新增了两种作用: 
- 定义静态数据成员
- 静态函数成员 
- static定义的变量分配在静态区
- 其定义的变量的默认值为0
- 普通变量的默认值为随机数
- 在定义指针变量时要特别注意

#### extern
extern标识的变量或者函数声明其定义在别的文件中，提示编译器遇到此变量和函数时在其它模块中寻找其定义

#### 简述指针常量与常量指针区别
- 指针常量是指定义了一个指针，这个指针的值只能在定义时初始化，其他地方不能改变
- 指针常量是唯一的，即NULL；常量指针是指定义了一个指针，这个指针指向一个只读的对象，不能通过常量指针来改变这个对象的值
- 指针常量强调的是指针的不可改变性，而常量指针强调的是指针对其所指对象的不可改变性

#### 如何避免 "野指针"
- 指针变量声明时没有被初始化。解决办法：指针声明时初始化，可以是具体的地址值，也可让它指向NULL
- 指针 p 被 free 或者 delete 之后，没有置为 NULL。解决办法：指针指向的内存空间被释放后指针应该指向NULL
- 指针操作超越了变量的作用范围。解决办法：在变量的作用域结束前释放掉变量的地址空间并且让指针指向NULL
