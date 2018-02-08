Shape.kt
```kotlin
interface Shape {
  fun draw();
}
```

Rectangle.kt
```kotlin
class Rectangle : Shape {
  @override fun draw () {
    print("print rectangle")
  }
}
```

Circle.kt
```kotlin
class Circle : Shape {
  override fun draw () {
    print("print circle")
  }
}
```

Color.kt
```kotlin
interface Color {
  fun draw()
}
```

Red.kt
```kotlin
class Red : Color {
  override fun draw () {
    print("print red")
  }
}
```

Blue.kt
```kotlin
class Blue : Color {
  override fun draw () {
    print("print blue")
  }
}
```

AbstractFactory.kt
```kotlin
abstract class AbstractFactory {
  abstract Color getColor(String color)
  abstract Shape getShape(String shape)
}
```

ShapeFactory.kt
```kotlin
class ShapeFactory : AbstractFactory {
  override fun getShape (shapeType: String) : Shape?{
    if (shapeType == null) {
      return null
    }
    
    when (shapeType) {
      "Circle" -> return Circle()
      "Rectangle" -> return Rectangle()
      else -> {
        return null
      }
    }
  }
  
  override fun getColor (colorType: String) : Color? {
    return null
  }
}
```

ColorFactory.kt
```kotlin
class ColorFactory : AbstractFactory {
  override fun getShape (shapeType: String) {
    return null
  }
  
  override fun getColor (colorType: String) {
    if (colorType == null) {
      return null
    }
    
    when (colorType) {
      "Red" -> return Red()
      "Blue" -> return Blue()
      else -> {
        return null
      }
    }
  }
}
```
