#### 智能指针
shared_ptr 是为了解决 auto_ptr 在对象所有权上的局限性(auto_ptr 是独占的), 在使用引用计数的机制上提供了可以共享所有权的智能指针
- shared_ptr 对象除了包括一个所拥有对象的指针外, 还必须包括一个引用计数代理对象的指针
- 时间上的开销主要在初始化和拷贝操作上, * 和 -> 操作符重载的开销跟 auto_ptr 是一样
- 开销并不是我们不使用shared_ptr的理由, 永远不要进行不成熟的优化, 直到性能分析器告诉你这一点

```cpp
std::shared_ptr<int> sp1 = std::make_shared<int>(10);
std::shared_ptr<std::string> sp2 = std::make_shared<std::string>("Hello c++");
```

```cpp
auto sp3 = std::make_shared<int>(11)
printf("sp3=%d\n", *sp3)

auto sp4 = std::make_shared<std::string>("C++11")
printf("sp4=%s\n", (*sp4).c_str())
```

#### 成员函数
- use_count 返回引用计数的个数
- unique 返回是否是独占所有权( use_count 为 1)
- swap 交换两个 shared_ptr 对象(即交换所拥有的对象)
- reset 放弃内部对象的所有权或拥有对象的变更, 会引起原有对象的引用计数的减少
- get 返回内部对象(指针), 由于已经重载了()方法, 因此和直接使用对象是一样的

```cpp
  std::shared_ptr<int> sp0(new int(2));
  std::shared_ptr<int> sp1(new int(11));
  std::shared_ptr<int> sp2 = sp1;
  printf("%d\n", *sp0);               // 2
  printf("%d\n", *sp1);               // 11
  printf("%d\n", *sp2);               // 11

  sp1.swap(sp0);
  printf("%d\n", *sp0);               // 11
  printf("%d\n", *sp1);               // 2
  printf("%d\n", *sp2);               // 11

  std::shared_ptr<int> sp3(new int(22));
  std::shared_ptr<int> sp4 = sp3;

  printf("%d\n", *sp3);               // 22
  printf("%d\n", *sp4);               // 22

  sp3.reset();                        
  printf("%d\n", sp3.use_count());    // 0
  printf("%d\n", sp4.use_count());    // 1
  printf("%d\n", sp3);                // 0
  printf("%d\n", sp4);                // 指向所拥有对象的地址

  std::shared_ptr<int> sp5(new int(22));
  std::shared_ptr<int> sp6 = sp5;
  std::shared_ptr<int> sp7 = sp5;

  printf("%d\n", *sp5);               // 22
  printf("%d\n", *sp6);               // 22
  printf("%d\n", *sp7);               // 22
  printf("%d\n", sp5.use_count());    // 3
  printf("%d\n", sp6.use_count());    // 3
  printf("%d\n", sp7.use_count());    // 3

  sp5.reset(new int(33));                        
  
  printf("%d\n", sp5.use_count());    // 1
  printf("%d\n", sp6.use_count());    // 2
  printf("%d\n", sp7.use_count());    // 2
  printf("%d\n", *sp5);               // 33
  printf("%d\n", *sp6);               // 22
  printf("%d\n", *sp7);               // 22
```

#### shared_ptr
shared_ptr 的赋值构造函数和拷贝构造函数
```cpp
  std::shared_ptr<int> sp1 = std::make_shared<int>(10);
  std::shared_ptr<int> sp2 = std::make_shared<int>(11);
  
  auto sp3 = sp2; 或 auto sp3(sp2);
  printf("sp1.use_count = %d\n", sp1.use_count());  // 1
  printf("sp2.use_count = %d\n", sp2.use_count());  // 2
  printf("sp3.use_count = %d\n", sp3.use_count());  // 2
  
  sp3 = sp1;
  printf("sp1.use_count = %d\n", sp1.use_count());  // 2
  printf("sp2.use_count = %d\n", sp2.use_count());  // 1
  printf("sp3.use_count = %d\n", sp3.use_count());  // 2
```

#### 何时需要使用 shared_ptr
- 程序不知道自己需要使用多少对象. 如使用窗口类, 使用 shared_ptr 为了让多个对象能共享相同的底层数据
- 程序不知道所需对象的准确类型
- 程序需要在多个对象间共享数据

#### 自定义释放器(函数)
自定义释放器(函数), 它能完成对 shared_ptr 中保存的指针进行释放操作, 还能处理 shared_ptr 的内部对象未完成的部分工作
```cpp
  class CConnnect
  {
      void Disconnect () { PRINT_FUN(); }
  };

  void Deleter (CConnnect* obj)
  {
      obj->Disconnect(); // 做其它释放或断开连接等工作
      delete obj; // 删除对象指针
  }

  std::shared_ptr<CConnnect> sps(new CConnnect, Deleter);
```

#### 注意事项
- shared_ptr 作为被保护的对象的成员时, 小心因循环引用造成无法释放资源
```cpp
  class CB;
  class CA;

  class CA
  {
  public:
      CA () { }
      ~CA () { PRINT_FUN(); }

      void Register(const std::shared_ptr<CB>& sp)
      {
          m_sp = sp;
      }

  private:
      std::shared_ptr<CB> m_sp;
  };

  class CB
  {
  public:
      CB () {};
      ~CB () { PRINT_FUN(); };

      void Register(const std::shared_ptr<CA>& sp)
      {
          m_sp = sp;
      }

  private:
      std::shared_ptr<CA> m_sp;
  };

  std::shared_ptr<CA> spa(new CA);
  std::shared_ptr<CB> spb(new CB);

  spb -> Register(spa);
  spa -> Register(spb);
  printf("%d\n", spb.use_count()); // 2
  printf("%d\n", spa.use_count()); // 2
```
- 小心对象内部生成 shared_ptr
```cpp
  class Y : public std::enable_shared_from_this<Y> {
    public:
        std::shared_ptr<Y> GetSharePtr()
        {
            return shared_from_this();
        }
  };
```
- 小心多线程对引用计数的影响
  - 如果是轻量级的锁, 比如 InterLockIncrement 等, 对程序影响不大; 如果是重量级的锁, 就要考虑因为 share_ptr 维护引用计数而造成的上下文切换开销
  - 多线程同时对 shared_ptr 读写时, 行为不确定, 因为shared_ptr本身有两个成员px，pi. 多线程同时对 px 读写要出问题, 与一个 int 的全局变量多线程读写会出问题的原因一样
- 与 weak_ptr 一起工作时, weak_ptr 在使用前需要检查合法性
```cpp
  std::weak_ptr<A> wp;
  {
      std::shared_ptr<A>  sp(new A);          // sp.use_count()==1
      wp = sp;                                // wp不会改变引用计数，所以sp.use_count()==1
      std::shared_ptr<A> sp2 = wp.lock();     // wp没有重载->操作符。只能这样取所指向的对象
  }
  printf("expired:%d\n", wp.expired());       // 1
  std::shared_ptr<A> sp_null = wp.lock();     // sp_null .use_count()==0;
```
- shared_ptr 不支持数组, 如果使用数组, 需要自定义删除器, 如下是一个利用 lambda 实现的删除器: std::shared_ptr<int> sps(new int[10], [](int *p){delete[] p;});
```cpp
  for (size_t i = 0; i < 10; i ++) {
      *((int*)sps.get() + i) = 10 - i;
  }

  for (size_t i = 0; i < 10; i ++) {
      printf("%d -- %d\n", i, *((int*)sps.get() + i));
  }
```
