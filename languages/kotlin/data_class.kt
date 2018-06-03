// 只包含数据的类
data class User(val name: String, val age: Int)

// 拷贝数据类
fun copy(name: String = this.name, age: Int = this.age) = User(name, age)

// 密封类
sealed class Expr
data class Const(val number: Double) : Expr()
data class Sum(val e1: Expr, val e2: Expr) : Expr()
object NotANumber : Expr()

fun eval(expr: Expr): Double = when (expr) {
  is Const -> expr.number
  is Sum -> eval(expr.e1) + eval(expr.e2)
  NotANumber -> Double.NaN
}
