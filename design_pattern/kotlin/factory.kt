/**
 * 抽象基类，形状
 */
abstract class Shape {
  abstract fun print ()
}

/**
 * 圆形
 */
class Circle : Shape () {
  override fun print () {
    println("print of Circle")
  }
}

/**
 * 三角形
 */
class Triangle : Shape() {
  override fun print () {
    println("print of ConcreteProductB")
  }
}

/**
 * 抽象类工厂
 */
abstract class Factory {
  abstract fun factoryMethod(): Shape
}

/**
 * 圆形工厂
 */
class CircleFactory : Factory () {
  override fun factoryMethod (): Circle {
    println("create Circle")
    return Circle ()
  }
}

/**
 * 三角形工厂
 */
class TriangleFactory : Factory () {
  override fun factoryMethod (): Triangle {
    println("create Triangle")
    return Triangle ()
  }
}
