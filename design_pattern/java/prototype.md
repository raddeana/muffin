#### 原型模式
原型模式（Prototype Pattern）是用于创建重复的对象，同时又能保证性能

Shape.java
```java
public abstract class Shape implements Cloneable {
  private String id;
  protected String type;
  abstract void draw();

  public String getType(){
    return type;
  }

  public String getId () {
    return id;
  }

  public void setId(String id) {
    this.id = id;
  }

  public Object clone() {
    Object clone = null;
    try {
      clone = super.clone();
    } catch (CloneNotSupportedException e) {
      e.printStackTrace();
    }

    return clone;
  }
}
```

Rectangle.java
```java
public class Rectangle extends Shape {
  public Rectangle (){
    type = "Rectangle";
  }

  @Override
  public void draw () {
    System.out.println("Inside Rectangle::draw() method.");
  }
}
```

Square.java
```java
public class Square extends Shape {
  public Square(){
    type = "Square";
  }

  @Override
  public void draw() {
    System.out.println("Inside Square::draw() method.");
  }
}
```

Circle.java
```java
public class Circle extends Shape {
  public Circle() {
    type = "Circle";
  }

  @Override
  public void draw() {
    System.out.println("Inside Circle::draw() method.");
  }
}
```

ShapeCache.java
```java
import java.util.Hashtable;

public class ShapeCache {
    
   private static Hashtable<String, Shape> shapeMap 
      = new Hashtable<String, Shape>();

   public static Shape getShape(String shapeId) {
      Shape cachedShape = shapeMap.get(shapeId);
      return (Shape) cachedShape.clone();
   }

   // 对每种形状都运行数据库查询，并创建该形状
   // shapeMap.put(shapeKey, shape);
   // 例如，我们要添加三种形状
   public static void loadCache() {
      Circle circle = new Circle();
      circle.setId("1");
      shapeMap.put(circle.getId(),circle);

      Square square = new Square();
      square.setId("2");
      shapeMap.put(square.getId(),square);

      Rectangle rectangle = new Rectangle();
      rectangle.setId("3");
      shapeMap.put(rectangle.getId(),rectangle);
   }
}
```
