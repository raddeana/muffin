// 传统用法
var max = a 
if (a < b) max = b

// 使用 else 
var max: Int
if (a > b) {
    max = a
} else {
    max = b
}
 
// 作为表达式
val max = if (a > b) a else b

// 
when (x) {
  1 -> print("x == 1")
  2 -> print("x == 2")
  else -> { // 注意这个块
    print("x 不是 1 ，也不是 2")
  }
}
