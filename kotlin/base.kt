// ========== int 参数，返回值 int ===========
fun sum(a: Int, b: Int): Int {
  return a + b;
}

// ============ 可变参数 ============
fun vars (vararg v:Int){
  for(vt in v){
    print(vt)
  }
}

// =========== lambda（匿名函数）============
fun main(args: Array<String>) {
  val sum: (Int, Int) -> Int = {x,y -> x+y}
  println(sum(1,2))  // 输出 3
}

// ============ 定义常量与变量 =============
val a: Int = 1
val b = 1       // 系统自动推断变量类型为Int
val c: Int      // 如果不在声明时初始化则必须提供变量类型
c = 1           // 明确赋值

var x = 5        // 系统自动推断变量类型为Int
x += 1           // 变量可修改

// ============ 字符串模板 =============
var a = 1
// 模板中的简单名称：
val s1 = "a is $a" 
a = 2
// 模板中的任意表达式：
val s2 = "${s1.replace("is", "was")}, but now is $a"

// ============= NULL检查机制 =============
// 类型后面加?表示可为空
var age: String? = "23"
// 抛出空指针异常
val ages = age!!.toInt()
// 不做处理返回 null
val ages1 = age?.toInt()
// age为空返回-1
val ages2 = age?.toInt() ?: -1

// ============= 可返回空的函数 =============
fun parseInt(str: String): Int? {
  // ...
}

// ============= 类型检测及自动类型转换 =============
fun getStringLength(obj: Any): Int? {
  if (obj is String) {
    // 做过类型判断以后，obj会被系统自动转换为String类型
    return obj.length 
  }

  //在这里还有一种方法，与Java中instanceof不同，使用!is
  // if (obj !is String){
  //   // XXX
  // }

  // 这里的obj仍然是Any类型的引用
  return null
}

// ============= 区间 =============
for (i in 1..4) print(i) // 输出“1234”

for (i in 4..1) print(i) // 什么都不输出

if (i in 1..10) { // 等同于 1 <= i && i <= 10
    println(i)
}

// 使用 step 指定步长
for (i in 1..4 step 2) print(i) // 输出“13”

for (i in 4 downTo 1 step 2) print(i) // 输出“42”


// 使用 until 函数排除结束元素
for (i in 1 until 10) {   // i in [1, 10) 排除了 10
     println(i)
}

