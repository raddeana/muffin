#### 访问者模式
在访问者模式（Visitor Pattern）中，我们使用了一个访问者类，它改变了元素类的执行算法

#### ComputerPart
```java
public interface ComputerPart {
   public void accept(ComputerPartVisitor computerPartVisitor);
}
```

#### Keyboard
```java
public class Keyboard implements ComputerPart {
   @Override
   public void accept(ComputerPartVisitor computerPartVisitor) {
      computerPartVisitor.visit(this);
   }
}
```

#### Monitor
```java
public class Monitor implements ComputerPart {
   @Override
   public void accept(ComputerPartVisitor computerPartVisitor) {
      computerPartVisitor.visit(this);
   }
}
```

#### Mouse
```java
public class Mouse implements ComputerPart {
   @Override
   public void accept(ComputerPartVisitor computerPartVisitor) {
      computerPartVisitor.visit(this);
   }
}
```

#### Computer
```java
public interface ComputerPartVisitor {
    public void visit(Computer computer);
    public void visit(Mouse mouse);
    public void visit(Keyboard keyboard);
    public void visit(Monitor monitor);
}
```

#### ComputerPartDisplayVisitor
```java
public class ComputerPartDisplayVisitor implements ComputerPartVisitor {
   @Override
   public void visit(Computer computer) {
      System.out.println("Displaying Computer.");
   }
   
   @Override
   public void visit(Mouse mouse) {
      System.out.println("Displaying Mouse.");
   }
   
   @Override
   public void visit(Keyboard keyboard) {
      System.out.println("Displaying Keyboard.");
   }
   
   @Override
   public void visit(Monitor monitor) {
      System.out.println("Displaying Monitor.");
   }
}
```
