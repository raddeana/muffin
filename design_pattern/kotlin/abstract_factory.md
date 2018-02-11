/**
 * 接口形状
 */
interface Shape {
  fun draw();
}

/**
 * 方形
 */
class Rectangle : Shape {
  @override fun draw () {
    print("print rectangle")
  }
}

/**
 * 圆形
 */
class Circle : Shape {
  override fun draw () {
    print("print circle")
  }
}

/**
 * 抽象类颜色
 */
interface Color {
  fun draw()
}

/**
 * 红色
 */
class Red : Color {
  override fun draw () {
    print("print red")
  }
}

/**
 * 蓝色
 */
class Blue : Color {
  override fun draw () {
    print("print blue")
  }
}

/**
 * 抽象类工厂
 */
abstract class AbstractFactory {
  abstract Color getColor(String color)
  abstract Shape getShape(String shape)
}

/**
 * 形状工厂
 */
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

/**
 * 颜色工厂
 */
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

/**
 * 工厂生产者
 */
class FactoryProducer {
  fun getFactory (type: String) : AbstractFactory? {
    if (type == 'SHAPE') {
      return new ShapeFactory()
    } else if (type == 'COLOR') {
      return new ColorFactory()
    } else {
      return null
    }
  }
}
