#### 工厂模式

Shape.kt
```kotlin
abstract class Shape {
  abstract fun print ()
}
```

Circle.kt
```kotlin
class Circle : Shape () {
  override fun print () {
    println("print of Circle")
  }
}
```

Triangle.kt
```kotlin
class Triangle : Shape() {
  override fun print () {
    println("print of ConcreteProductB")
  }
}
```

Factory.kt
```kotlin
abstract class Factory {
  abstract fun factoryMethod(): Shape
}
```

CircleFactory.kt
```kotlin
class CircleFactory : Factory () {
  override fun factoryMethod (): Circle {
    println("create Circle")
    return Circle ()
  }
}
```

TriangleFactory.kt
```kotlin
class TriangleFactory : Factory () {
  override fun factoryMethod (): Triangle {
    println("create Triangle")
    return Triangle ()
  }
}
```
