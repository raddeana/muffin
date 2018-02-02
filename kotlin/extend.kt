// Kotlin 中所有类都继承该 Any 类，它是所有类的超类，对于没有超类型声明的类是默认超类

Any 默认提供了三个函数:
equals()
hashCode()
toString()

// 关键字
open class Base(p: Int)           // 定义基类
class Derived(p: Int) : Base(p)

// 子类有主构造函数
open class Person(var name : String, var age : Int){}
class Student(name : String, age : Int, var no : String, var score : Int) : Person(name, age) {}

// 子类没有主构造函数
class Student : Person {
  constructor(ctx: Context) : super(ctx) {} 
  constructor(ctx: Context, attrs: AttributeSet) : super(ctx,attrs) {}
}

// 用户基类
open class Person{
  open fun study(){           // 允许子类重写
    println("我毕业了")
  }
}

// 子类继承 Person 类
class Student:Person () {
  override fun study () {     // 重写方法
    println("我在读大学")
  }
}

// super
open class A {
  open fun f () { print("A") }
  fun a() { print("a") }
}

interface B {
  fun f() { print("B") } //接口的成员变量默认是 open 的
  fun b() { print("b") }
}

class C() : A() , B{
  override fun f() {
    super<A>.f() // 调用 A.f()
    super<B>.f() // 调用 B.f()
  }
}

// 属性重写
// sample one
open class Foo {
  open val x: Int get { …… }
}

class Bar1 : Foo() {
  override val x: Int = ……
}

// sample two
interface Foo {
  val count: Int
}

class Bar1(override val count: Int) : Foo

class Bar2 : Foo {
  override var count: Int = 0
}
