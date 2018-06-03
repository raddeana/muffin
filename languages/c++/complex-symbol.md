#### ::
- 作用域限定符，当在类体中直接定义函数时，不需要在函数名字的前面加上类名，但是在类体外实现函数定义的时候，必须加上类名并且加上作用域限定符
```cpp
Student::Display()
```
- 静态成员数据，既可以通过对象名引用，也可以通过类名加::来引用
```cpp
class Test {
  public:
    Display();
  private:
    static int a;
}

Test::a;
```
- 静态成员函数，也是既可以通过对象名引用，也可以通过类名+::引用
- 引用在类中定义的，typedef新类型
```cpp
class MyClass {
  public: 
    typedef int INT;
}

MyClass ::INT b;
```
- 在子类的重写函数中调用父类的函数
- 类有两个方法，a方法和b方法，在a方法中调用b方法，就可以使用::当然不用也可以
