// Kotlin 扩展
// 扩展函数 swap
fun MutableList<Int>.swap(index1: Int, index2: Int) {
  val tmp = this[index1]        // this 对应该列表
  this[index1] = this[index2]
  this[index2] = tmp
}

// 扩展声明为成员
class D {
  fun bar() { println("D bar") }
}

class C {
  fun baz() { println("C baz") }

  fun D.foo() {
    bar()   // 调用 D.bar
    baz()   // 调用 C.baz
  }

  fun caller(d: D) {
    d.foo()   // 调用扩展函数
  }
}
