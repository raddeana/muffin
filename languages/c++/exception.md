#### 异常处理语句
- try 程序块：该区段包含可能会发生异常的代码，在发生了异常之后，通过throw抛出异常
- throw 程序块： throw语句用于抛出异常，在C++中，被抛出的异常可以是内置类型的对象，也可以是自定义类型的对象
- catch 程序块： 对异常进行捕捉，处理特定类型的异常

```cpp
#include<stdio.h>
#include<setjmp.h>
#include<signal.h>
#include<iostream>
using namespace std;
#include<string>



void test () {
    try{
        char* p = new char[0x7fffffff];  //抛出异常
    }
    catch(exception e){
        cout << e.what() << endl;
    }
}

int main(){
    test();
    return 0;
}
```

#### 异常的抛出和捕获
- 异常是通过抛出对象而引发的，该对象的类型决定了应该激活哪一个处理代码
- 被选中的处理代码是调用链中与该对象类型匹配且离抛出异常位置最近的那一个
- 抛出异常后会释放局部存储对象，所以被抛出的对象也就归还给系统了
- throw表达式会初始化一个抛出特殊的异常对象的副本（匿名对象），异常对象由编译管理，异常对象再传给对应的catch处理之后撤销

#### 异常栈展开
##### 异常结构体—EXP
- piPrev 成员指向链表的上一个节点，它主要用于在函数调用栈中逐级向上寻找匹配的 catch 块，并完成栈回退工作
- piHandler 成员指向完成异常捕获和栈回退所必须的数据结构（主要是两张记载着关键数据的表："try" 块表：tblTryBlocks及 "栈回退表"：tblUnwind）
- nStep 成员用来定位 try 块，以及在栈回退表中寻找正确的入口

##### 异常栈展开
```cpp
#include<stdio.h>
#include<setjmp.h>
#include<signal.h>
#include<iostream>
using namespace std;
#include<string>

void testB (int a, int b) {
    testA(a, b);
    int n = 1;   // next statement
    
    return;
}

void testA (int a, int b) {
    return;
}
```

##### 栈回退（Stack Unwind）机制
异常结构体EXP中的 nStep 除了能够跟踪对象创建、销毁阶段以外，还能够标识当前执行点是否在 try 块中，以及（如果当前函数有多个 try 块的话）究竟在哪个 try 块中
在具体实现异常捕获时，首先，C++ 异常处理器检查发生异常的位置是否在当前函数的某个 try 块之内

##### 异常捕获的匹配规则
允许从非 const 对象到 const 类型对象的转换
允许从派生类类型到基类类型的转换
将数组转换成指向数组类型的指针，将函数转换为指向函数类型的指针

##### 异常的重新抛出
#### 异常规范
- 成员函数再累内声明和类外定义两处必须有相同的异常规范
- 函数抛出一个没有列在它异常规范中的异常时（且函数中抛出异常没有在函数内部进行处理），系统调用 C++ 标准库中定义的函数 unexpected()
- 如果异常规范为throw()，则表示不得抛出任何异常，该函数不用放在try块中
- 派生类的虚函数的异常规范必须基类虚函数的异常规范一样或者更严格（是基类虚函数的异常的子集）





