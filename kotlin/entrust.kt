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

// ========== 把属性储存在映射中 ===========
class Site(val map: Map<String, Any?>) {
    val name: String by map
    val url: String  by map
}

// 构造函数接受一个映射参数
val site = Site(mapOf(
  "name" to "菜鸟教程",
  "url"  to "www.runoob.com"
))

// ========== Not Null ===========

class Foo {
    var notNullBar: String by Delegates.notNull<String>()
}

foo.notNullBar = "bar"
println(foo.notNullBar)

// ========== 局部委托属性 ===========
fun example(computeFoo: () -> Foo) {
    val memoizedFoo by lazy(computeFoo)

    if (someCondition && memoizedFoo.isValid()) {
        memoizedFoo.doSomething()
    }
}

// =========== 翻译规则 ===========
class C {
    var prop: Type by MyDelegate()
}

// 这段是由编译器生成的相应代码：
class C {
    private val prop$delegate = MyDelegate()
    var prop: Type
        get() = prop$delegate.getValue(this, this::prop)
        set(value: Type) = prop$delegate.setValue(this, this::prop, value)
}

// =========== 提供委托 ===========
// 通过定义 provideDelegate 操作符，可以扩展创建属性实现所委托对象的逻辑
// 如果 by 右侧所使用的对象将 provideDelegate 定义为成员或扩展函数，那么会调用该函数来，创建属性委托实例

class ResourceLoader<T>(id: ResourceID<T>) {
    operator fun provideDelegate(
            thisRef: MyUI,
            prop: KProperty<*>
    ): ReadOnlyProperty<MyUI, T> {
        checkProperty(thisRef, prop.name)
        // 创建委托
    }

    private fun checkProperty(thisRef: MyUI, name: String) { …… }
}

fun <T> bindResource(id: ResourceID<T>): ResourceLoader<T> { …… }

class MyUI {
    val image by bindResource(ResourceID.image_id)
    val text by bindResource(ResourceID.text_id)
}

