#### 工厂模式

```kotlin
abstract class Shape {
  abstract fun print ()
}
```

```kotlin
class Circle : Shape () {
  override fun print () {
    println("print of Circle")
  }
}
class Triangle : Shape() {
  override fun print () {
    println("print of ConcreteProductB")
  }
}
```

```kotlin
abstract class Factory {
  abstract fun factoryMethod(): Shape
}
```

```kotlin
class CircleFactory : Factory () {
  override fun factoryMethod (): Circle {
    println("create Circle")
    return Circle ()
  }
}

class TriangleFactory : Factory () {
  override fun factoryMethod (): Triangle {
    println("create Triangle")
    return Triangle ()
  }
}
```
