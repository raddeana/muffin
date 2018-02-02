// getter 和 setter
class Person {
    var lastName: String = "zhang"
        get() = field.toUpperCase()   // 将变量赋值后转换为大写
        set
        
    var no: Int = 100
        get() = field                 // 后端变量
        set(value) {
            if (value < 10) {         // 如果传入的值小于 10 返回该值
                field = value
            } else {
                field = -1            // 如果传入的值大于等于 10 返回 -1
            }
        }
        
    var heiht: Float = 145.4f
        private set
}

// 次级构造函数
// 主构造器
class Runoob constructor(name: String) {
  // 大括号内是类体构成
  var url: String = "http://www.runoob.com"
  var country: String = "CN"
  var siteName = name

  init {
    println("初始化网站名: ${name}")
  }

  // 次构造函数
  constructor (name: String, alexa: Int) : this(name) {
    println("Alexa 排名 $alexa")
  }

  fun printTest() {
    println("我是类的函数")
  }
}

// 抽象类
open class Base {
    open fun f() {}
}

abstract class Derived : Base() {
    override abstract fun f()
}

// 嵌套类
class Outer {                  // 外部类
    private val bar: Int = 1
    class Nested {             // 嵌套类
        fun foo() = 2
    }
}

// 内部类
class Outer {
  private val bar: Int = 1
  var v = "成员属性"
  /**嵌套内部类**/
  inner class Inner {
    fun foo() = bar  // 访问外部类成员
    fun innerTest() {
      var o = this@Outer //获取外部类的成员变量
      println("内部类可以引用外部类的成员，例如：" + o.v)
    }
  }
}

// 匿名内部类
class Test {
  var v = "成员属性"

  fun setInterFace(test: TestInterFace) {
    test.test()
  }
}

// 类的修饰符
abstract    // 抽象类  
final       // 类不可继承，默认属性
enum        // 枚举类
open        // 类可继承，类默认是final的
annotation  // 注解类

// 访问权限修饰符
private    // 仅在同一个文件中可见
protected  // 同一个文件中或子类可见
public     // 所有调用的地方都可见
internal   // 同一个模块中可见
