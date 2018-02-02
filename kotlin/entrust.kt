// ========== 类委托 ==========
interface Base {   
    fun print()
}

// 实现此接口的被委托的类
class BaseImpl(val x: Int) : Base {
    override fun print() { print(x) }
}

// 通过关键字 by 建立委托类
class Derived(b: Base) : Base by b

fun main(args: Array<String>) {
    val b = BaseImpl(10)
    Derived(b).print() // 输出 10
}

// ========== 属性委托 ==========
val/var <属性名>: <类型> by <表达式>

import kotlin.reflect.KProperty

// 定义包含属性委托的类
class Example {
    var p: String by Delegate()
}

// 委托的类
class Delegate {
  operator fun getValue(thisRef: Any?, property: KProperty<*>): String {
    return "$thisRef, 这里委托了 ${property.name} 属性"
  }

  operator fun setValue(thisRef: Any?, property: KProperty<*>, value: String) {
    println("$thisRef 的 ${property.name} 属性赋值为 $value")
  }
}

// ========== 标准委托 ==========
val lazyValue: String by lazy {
  println("computed!")     // 第一次调用输出，第二次调用不执行
  "Hello"
}

// ========== 可观察属性 Observable ==========
import kotlin.properties.Delegates

class User {
  var name: String by Delegates.observable("初始值") {
    prop, old, new ->
    println("旧值：$old -> 新值：$new")
  }
}

// 把属性储存在映射中
val site = Site(mapOf(
  "name" to "菜鸟教程",
  "url"  to "www.runoob.com"
))

// 构造函数接受一个映射参数
val site = Site(mapOf(
  "name" to "菜鸟教程",
  "url"  to "www.runoob.com"
))

// 
