#### 关于动态申请内存
- 内存分配方式三种
  - 从静态存储区域分配: 内存在程序编译的时候就已经分配好，这块内存在程序的整个运行期间都存在；全局变量，static变量
  - 在栈上创建: 在执行函数时，函数内局部变量的存储单元都可以在栈上创建
  - 用 malloc 或 new 申请内存之后，应该立即检查指针值是否为 NULL，防止使用指针值为NULL的内存，不要忘记为数组和动态内存赋初值

#### 进程和线程
- 调度: 线程作为调度和分配的基本单位，进程作为拥有资源的基本单位
- 并发性: 不仅进程之间可以并发执行，同一个进程的多个线程之间也可并发执行
- 拥有资源: 进程是拥有资源的一个独立单位，线程不拥有系统资源，但可以访问隶属于进程的资源
- 系统开销: 创建撤消进程，系统都要为之分配和回收资源，系统的开销明显大于创建撤消线程多进程与多线程

#### C++ 指针
指针是一个变量，专门存放内存地址，特点是能访问所指向的内存
指针本身占据了4个字节的长度
- int **ptr
- int (*ptr)[3]
- int *(*ptr)[4]
- ptr++: 指针ptr的值加上了 sizeof(int)
- ptr+=5: 将指针ptr的值加上 5 * sizeof(int)

#### 复制指针解析
- int (*func)(int *p);
  - (*func)()是一个函数，func是一个指向这类函数的指针，就是一个函数指针，这类函数具有int*类型的形参，返回值类型是 int
- int (*func)(int *p, int (*f)(int*));
  - func是一个指向函数的指针，这类函数具有int *和int (*)(int*)这样的形参。形参int (*f)(int*），f也是一个函数指针
- int (*func[5])(int *p);
  - func数组的元素是函数类型的指针，它所指向的函数具有int*类型的形参，返回值类型为int
- int (*(*func)[5])(int *p);
  - func是一个指向数组的指针，这个数组的元素是函数指针，这些指针指向具有int*形参，返回值为int类型的函数
- int (*(*func)(int *p))[5];
  - func是一个函数指针，这类函数具有int*类型的形参，返回值是指向数组的指针，所指向的数组的元素是具有5个int元素的数组

#### 函数指针详解
函数指针是指向一个函数入口的指针
一个函数指针只能指向一种类型的函数，即具有相同的返回值和相同的参数的函数
- 函数指针数组定义: void(*fun[3])(void*);  
- 相应指向类A的成员函数的指针: void (A::*pmf)(char *, const char *)
- 指向外部函数的指针: void (*pf)(char *, const char *)
- void strcpy (char * dest, const char * source)
- pf = strcpy

#### 野指针
- 指针变量没有被初始化。指针变量在创建的同时应当被初始化，要么将指针设置为NULL，要么让它指向合法的内存
```c
  char *p = NULL;
  char *str = (char *) malloc(100);
```
- 指针p被free或者delete之后，没有置为NULL
- 指针操作超越了变量的作用范围
- 所指向的内存值对象生命期已经被销毁

#### 引用和指针有什么区别
- 引用必须初始化，指针则不必；引用初始化以后不能改变，指针可以改变其指向的对象
- 不存在指向空值的引用，但存在指向控制的指针
- 引用是某个对象的别名，主要用来描述函数和参数和返回值
- 而指针与一般的变量是一样的，会在内存中开辟一块内存
- 如果函数的参数或返回值是类的对象的话，采用引用可以提高程序的效率

#### C++ 中的 Const 用法
- char * const p;                                   // 指针不可改,也就说指针只能指向一个地址,不能更改为其他地址，修饰指针本身
- char const * p;                                   // 所指内容不可改,也就是说*p是常量字符串，修饰指针所指向的变量
- const char * const p ; char const * const p;      // 内容和指针都不能改


#### const常量与define宏定义的区别
- 编译器处理方式不同，define宏是在预处理阶段展开，生命周期止于编译期；只是一个常数、一个命令中的参数，没有实际的存在
- 类型和安全检查不同，define宏没有类型，不做任何类型检查，仅仅是展开；const常量有具体的类型，在编译阶段会执行类型检查
- 存储方式不同，define宏仅仅是展开，有多少地方使用，就展开多少次，不会分配内存；const常量会在内存中分配（可以是堆中也可以是栈中）

#### 解释堆和栈的区别
- 栈区（stack）— 由编译器自动分配释放，存放函数的参数值，局部变量的值等。其操作方式类似于数据结构中的栈
  - 在大多数的C编译器中，参数是由右往左入栈的，然后是函数中的局部变量
  - 在Windows下,栈是向低地址扩展的数据结构，是一块连续的内存的区域，栈的大小是2M
  
- 堆区 (heap)— 一般由程序员分配释放，若程序员不释放，程序结束时可能由 OS 回收
  - 注意它与数据结构中的堆是两回事，分配方式倒是类似于链表，需要程序员自己申请，并指明大小，在 c 中 malloc 函数在 C++ 中用 new 运算符
  - 一般是在堆的头部用一个字节存放堆的大小

#### 论述含参数的宏和函数的优缺点
- 函数调用时，先求出实参表达式的值，然后代入形参；而使用带参的宏只是进行简单的字符替换
- 函数调用是在程序运行时处理的，分配临时的内存单元；而宏展开是在编译时进行的，在展开时不进行内存分配，不进行值得传递处理，没有 "返回值" 概念
- 对函数中的形参和实参都要定义类型，类型要求一致，如不一致则进行类型转换；而宏不存在类型问题
- 调用函数只可得到一个返回值，而用宏则可以设法得到几个结果
- 实用宏次数多时，宏展开后源程序变长，没展开一次源程序增长，函数调用则不会
- 宏替换不占用运行时间，只占编译时间，而函数调用占用运行时间

#### C++的空类，默认产生哪些类成员函数
```cpp
{
  public:
    Empty();                            // 缺省构造函数
    Empty（const Empty& ）;             // 拷贝构造函数
    ~Empty();                           // 虚构函数
    Empty& operator(const Empty& )      // 赋值运算符
    Empty& operator&();                 // 取址运算符
    const Empty* operator&() const;     // 取址运算符 const
}
```

#### 类和结构体的区别
- 结构体在默认情况下的成员都是public的, 而类在默认情况下的成员是private的
- 结构体和类都必须使用new创建，struct保证成员按照声明顺序在内存在存储，而类不保证

#### C++ 四种强制类型转换
- const_cast 字面上理解就是去const属性，去掉类型的const或volatile属性
```cpp
struct SA {
  int k
};

const SA ra;

ra.k = 10;                      // 直接修改const类型，编译错误   
SA& rb =  const_cast<SA&>(ra);
rb.k = 10;                      // 可以修改
```
- static_cast 基本类型之间和具有继承关系的类型之间的转换
```cpp
int a;
double d = static_cast<double>(a);   // 基本类型转换

int &pn = &a;     
void *p = static_cast<void*>(pn);    // 任意类型转换为 void
```
- dynamic_cast 动态类型转换，运行时类型安全检查(转换失败返回NULL)
```cpp
class BaseClass {
  public: int m_iNum;
  virtual void foo () {};
};

class DerivedClass:BaseClass {
  public: char* szName[100];
  void bar () {};
};

BaseClass* pb = new DerivedClass();

DerivedClass *p2 = dynamic_cast<DerivedClass *>(pb);
BaseClass* pParent = dynamic_cast<BaseClass*>(p2);
```
- reinterpreter_cast 转换的类型必须是一个指针、引用、算术类型、函数指针或者成员指针
```cpp
int DoSomething () {
  return 0;
};

typedef void(*FuncPtr) () {};
FuncPtr funcPtrArray[10];
funcPtrArray[0] = reinterpreter_cast<FuncPtr>(&DoSomething);
```
#### memset, memcpy 和 strcpy 的根本区别
- memset用来对一段内存空间全部设置为某个字符，一般用在对定义的字符串进行初始化为' '或''；它对较大的结构体或数组进行清零操作的一种最快方法
```cpp
char temp[30];
memset(temp, '\0', sizeof(temp));
```
- memcpy用来做内存拷贝，你可以拿它拷贝任何数据类型的对象，可以指定拷贝的数据长度
- strcpy就只能拷贝字符串了，它遇到'\0'就结束拷贝
```cpp
  char a[100], b[50];
  strcpy(a, b);
```

#### 将 "引用" 作为函数参数
- 传递引用给函数与传递指针的效果是一样的
- 使用引用传递函数的参数，在内存中并没有产生实参的副本，它是直接对实参操作，当参数数据较大时，引用传递参数的效率和所占空间都好
- 如果使用指针要分配内存单元，需要重复使用 "*指针变量名" 形式进行计算，容易出错且阅读性较差

#### 在C++程序中调用C编译后的函数，为什么要加extern C的声明
因为C++支持函数重载，而C不支持函数重载，函数被C++编译后在库中的名字与C语言的不同

#### Template
- Template可以独立于任何特定的类型编写代码，是泛型编程的基础
- 当我们编写的类和函数能够多态的用于跨越编译时不相关的类型时，用Template
- 模板主要用于STL中的容器,算法,迭代器等以及模板元编程
- C++ 的 template 是实现在库设计和嵌入式设计中的关键，能实现抽象和效率的结合
- 同时template还能有效地防止代码膨胀

#### why Template class
- 可用来创建动态增长和减小的数据结构
- 它是类型无关的，因此具有很高的可复用性
- 它在编译时而不是运行时检查数据类型，保证了类型安全
- 它是平台无关的，可移植性
- 可用于基本数据类型

#### static
- 函数体内作用范围为该函数体，该变量内存只被分配一次，具有记忆能力
- 在模块内的static全局变量可以被模块内所有函数访问，但不能被模块外其它函数访问
- 在模块内的static函数只可被这一模块内的其它函数调用，这个函数的使用范围被限制在声明它的模块内
- 在类中的static成员变量属于整个类所拥有，对类的所有对象只有一份拷贝
- 在类中的static成员函数属于整个类所拥有，这个函数不接收this指针，因而只能访问类的static成员变量

#### 头文件的作用是什么
- 通过头文件来调用库功能
- 头文件能加强类型安全检查

#### extern C
因为C++支持函数重载，而C不支持函数重载，函数被C++编译后在库中的名字与C语言的不同
void foo(int x, int y)
该函数被C编译器编译后在库中的名字为_foo
C++编译器则产生像_foo_int_int之类的名字；C++ 提供 extern C 来解决名字匹配问题

#### 哪些函数不能被声明为虚函数
普通函数（非成员函数），构造函数，内联成员函数、静态成员函数、友元函数

#### 数组指针
数组int c[3][3]; 为什么c，*c的值相等，（c+1），（*c+1）的值不等, c，*c，**c，代表什么意思
- c是第一个元素的地址，*c是第一行元素的首地址，其实第一行元素的地址就是第一个元素的地址
- c: 数组名；是一个二维指针, 它的值就是数组的首地址, 也即第一行元素的首地址 (等于 *c), 也等于第一行第一个元素的地址 (& c[0][0]); 可以说成是二维数组的行指针
- *c: 第一行元素的首地址；是一个一维指针，可以说成是二维数组的列指针
- **c: 二维数组中的第一个元素的值
- (c + 1): c是行指针, (c + 1)是在c的基础上加上二维数组一行的地址长度, 即从&c[0][0]变到了&c[1][0]
- (*c + 1): *c是列指针，(*c + 1) 是在*c的基础上加上二数组一个元素的所占的长度, &c[0][0]变到了&c[0][1], 从而 (c + 1) 和 (*c + 1) 的值就不相等了

#### 定义int **pa[4][3],则变量pa占有的内存空间是多少
int **p, 在32位机器上 sizeof（p） = 4; 总共占有4*3*sizeof (p)= 48

#### 拷贝构造函数相关问题, 深拷贝, 浅拷贝, 临时对象
- 一个对象以值传递的方式传入函数体
- 一个对象以值传递的方式从函数返回
- 一个对象需要通过另外一个对象进行初始化

深拷贝: 如果一个类拥有资源, 深拷贝意味着拷贝了资源和指针
浅拷贝: 如果对象存在资源, 而浅拷贝只是拷贝了指针，没有拷贝资源

#### 指针和引用有什么分别
引用必须初始化, 即引用到一个有效的对象; 而指针在定义的时候不必初始化, 可以在定义后面的任何地方重新赋值

#### "标准" 宏MIN
```cpp
#define MIN(A, B) ((A) <= (B)? (A):(B))
```

#### 用一个宏定义FIND求一个结构体struc中某个变量相对struc的偏移量
```cpp
# define FIND (struc, e)(size_t)&( ((struc*)0)->e)
```
其中（struc*）0表示将常量0转化为struc*类型指针所指向的地址

#### 在main函数执行之前，还会执行什么代码和工作
- 运行全局构造器, 全局对象的构造函数会在main函数之前执行
- 设置栈指针, 初始化static静态和global全局变量, 即数据段的内容
- 将未初始化部分的赋初值：数值型short, int, long 等为0, bool为FALSE, 指针为NULL等
- 将main函数的参数, argc, argv 等传递给 main 函数

#### 如何判断一段程序是由 C 编译程序还是由 C++ 编译程序编译的
- C++ 编译时定义了 __cplusplus
- C 编译时定义了 _STDC_

#### BOOL, int, float, 指针类型的变量 a 与 "零值" 的比较语句
```cpp
  BOOL: if（!a）or if(a)
  int : if( 0 == a)
  float : const EXPRESSION EXP = 0.000001;
  
  if(a < EXP && a > -EXP)
    pointer: if(a != NULL) or  if(a == NULL)
```

#### 已知String类定义如下,尝试写出类的成员函数实现
```cpp
class {
  public:
    String (const char*str = NULL);                  // 通用构造函数
    String (const String& another);                  // 拷贝构造函数
    ~String ();                                      // 析构函数
    String& operator = =  (const String& rhs);       // 赋值函数
    private:
    char* m_data;                                    // 用于保存字符串
};
```

```cpp
String::String (const char* str) {
  if (str == NULL) {
    m_data = new char[1];
    m_data[0] = '\0';
  } else {
    m_data = new char[strlen(str)+1];
    strcpy(m_data, str);
  }
}   

String::String(const String& another) {
  m_data = new char[strlen(another.m_data)+1];
  strcpy(m_data, another.m_data); 
}                          

String::String& operator = = (const String& rhs) {
  if (this == &rhs) {
    return &this;
  }

  delete[]  m_data;
  m_data = new char(strlen(rhs.m_data) + 1);   // 删除原来的数据，新开一块内存
  strcpy(m_data, rhs.m_data); 
  
  return *this;
}

~String () {
    delete[] m_data;
}
```

#### 运算符重载的三种方式
- 普通函数, 友元函数, 类成员函数

#### 不允许重载的5个运算符
- .* (成员指针访问运算符)   
- :: (域运算符)
- sizeof 长度运算符   
- ? : 条件运算符   
- . (成员访问运算符)

#### 友元关系
单向的, 非传递的, 不能继承的

#### 关键字 volatile
一个定义为 volatile 的变量是说这变量可能会被意想不到地改变，编译器就不会去假设这个变量的值了
- 并行设备的硬件寄存器 (如: 状态寄存器)
- 一个中断服务子程序中会访问到的非自动变量(Non-automatic variables)
- 多线程应用中被几个任务共享的变量

#### 动态连接库的两种方式
- 载入时动态链接 (load-time dynamic linking), 模块非常明确调用某个导出函数, 使得他们就像本地函数一样
- 运行时动态链接 (run-time dynamic linking), 运行时可以通过 LoadLibrary 或 Loa

#### i ++ 相比 ++ i 哪个更高效
- ++ i 比i ++ 效率高
- i ++ 要多调用一次类的构造和析够函数

#### windows平台下网络编程
有阻塞, select, 基于窗体的事件模型, 事件模型, 重叠模型, 完成端口模型

#### 内核级线程
线程有两种类型:
- 用户级线程
  - 用户线程指不需要内核支持而在用户程序中实现的线程, 其不依赖于操作系统核心, 应用进程利用线程库提供创建、同步、调度, 和管理线程的函数来控制用户线程
- 内核级线程
  - 内核级线程需要内核的参与, 由内核完成线程的调度; 其依赖于操作系统核心, 由内核的内部需求进行创建和撤销

#### Windows内存管理
内存管理有块式管理，页式管理，段式和段页式管理
- 块式管理: 把主存分为一大块、一大块的, 当所需的程序片断不在主存时就分配一块主存空间, 把程序片断load入主存, 就算所需的程序片度只有几个字节也只能把这一块分配给它; 这样会造成很大的浪费, 平均浪费了50％的内存空间, 但时易于管理。
- 页式管理: 把主存分为一页一页的, 每一页的空间要比一块一块的空间小很多, 显然这种方法的空间利用率要比块式管理高很多
- 段式管理: 把主存分为一段一段的, 每一段的空间又要比一页一页的空间小很多, 这种方法在空间利用率上又比页式管理高很多, 但是也有另外一个缺点; 一个程序片断可能会被分为几十段, 这样很多时间就会被浪费在计算每一段的物理地址上, 计算机最耗时间的大家都知道是I/O吧
- 段页式管理: 结合了段式管理和页式管理的优点。把主存分为若干页，每一页又分为若干段，好处就很明显

#### C++编译器自动为类产生的四个确缺省函数
- 默认构造函数
- 拷贝构造函数
- 析构函数
- 赋值函数

#### 动态连接库
- 载入时动态链接 (load-time dynamic linking),模块非常明确调用某个导出函数, 使得他们就像本地函数一样
- 这需要链接时链接那些函数所在DLL的导入库，导入库向系统提供了载入DLL时所需的信息及DLL函数定位
- 运行时动态链接 (run-time dynamic linking), 运行时可以通过LoadLibrary或LoadLibraryEx 函数载入 DLL
- DLL载入后，模块可以通过调用GetProcAddress获取DLL函数的出口地址，然后就可以通过返回的函数指针调用DLL函数了

#### 类模板
描述了能够管理其他数据类型的通用数据类型，通常用于建立包含其他类型的容器类
```
template<class T>

class TemplateSample {
  private:
    T&emtity;              // 使用参数类型成员
  public:
    void F(T& arg);        // 使用参数类型定义成员函数
}
```

#### 函数模板（泛型）
函数模板技术定义了参数化的非成员函数, 使得程序能够使用不同的参数类型调用相同的函数, 而至于是何种类型, 则是由编译器确定从模板中生成相应类型的代码
```cpp
template<class T>

T Add (T a, T b) {
   T result = a + b;
   return a + b;        // 将两个参数使用“+”运算符进行运算，这两个参数并不知道是何种类型
}
```

```cpp
#include<iostream> // 包含标准输入输出头文件
#include<string>   // C++中的字符串处理头文件

using namespace std;

template<class T>

// 函数模板
T Add (T a, T b) {
   T result = a + b;
   return a + b;    // 将两个参数使用 "+" 运算符进行运算，这两个参数并不知道是何种类型
}

int main (int argc, char* argv[]) {
   cout << "2+3=" << Add(2,3) << endl;                               // 输出整形的+运算结果
   cout << "sdf+123=" << Add(string("sdf"), string("123")) <<endl;
  return 0;
}
```

#### 泛型编程
```cpp
#include<iostream>
#include<string>

using namespaces std;

template<class T>

T Add(T a, T b) {

   T result;           // 使用参数化的类型定义变量
   result = a + b;
  return result;
}

int main (int argc, char* argv[]) {
  cout<<"2+3="<<Add(2,3)<<endl;  
  cout<<"sdf+123="<<Add(string("sdf"), string("123"));
  return 0;
}
```

#### 参数传递的方式
- 传值方式适合一般的数值传递, 并且不改变原数据, 但是要消耗内存空间
- 传递指针方式适合传递数组和指针, 由于传递的是地址, 所以直接操作会改变原数据
- 引用方式和指针方式比较类似, 是相对比较新的一种方式, 一般情况下能用传地址的就能用引用

#### STL
STL是一个标准的C++库，容器只是其中一个重要的组成部分,有顺序容器和关联容器
- 顺序容器 
  - vector<T>
  - deque<T>
  - list<T>
- 关联容器 
  - set<Key>
  - set<Key>
  - map<Key, T>
  - multimap<Key, T>
