class Box<T>(box : T) {
  var value = box
}

fun <T> boxIn(value: T) = Box(value)

// 以下都是合法语句
val box4 = boxIn<Int>(1)
val box5 = boxIn(1)     // 编译器会进行类型推断

// 泛型约束
fun <T: Comparable<T>> sort(list: List<T>) {
}

// 型变
// 声明处型变
class Runoob<out A>(val a: A) {
  fun foo(): A {
    return a
  }
}

// 定义一个支持逆变的类
class Runoob<in A>(a: A) {
    fun foo(a: A) {
    }
}

1、Foo<out T> , 其中 T 是一个协变的类型参数, 上界(upper bound)为 TUpper ,Foo<> 等价于 Foo<out TUpper> . 它表示, 当 T 未知时, 你可以安全地从 Foo<> 中 读取TUpper 类型的值.
2、Foo<in T> , 其中 T 是一个反向协变的类型参数, Foo<> 等价于 Foo<inNothing> . 它表示, 当 T 未知时, 你不能安全地向 Foo<> 写入 任何东西.
3、Foo<T> , 其中 T 是一个协变的类型参数, 上界(upper bound)为 TUpper , 对于读取值的场合, Foo<*> 等价于 Foo<out TUpper> , 对于写入值的场合, 等价于 Foo<in Nothing> .

// 星号投射
1、Function<*, String> , 代表 Function<in Nothing, String>；
2、Function<Int, *> , 代表 Function<Int, out Any?>；
3、Function<, > , 代表 Function<in Nothing, out Any?>；
