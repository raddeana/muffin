#### 观察者模式
当对象间存在一对多关系时，则使用观察者模式（Observer Pattern）

#### Subject
```java
import java.util.ArrayList;
import java.util.List;

public class Subject {
    
   private List<Observer> observers = new ArrayList<Observer> ();
   private int state;

   public int getState () {
      return state;
   }

   public void setState (int state) {
      this.state = state;
      notifyAllObservers ();
   }

   public void attach (Observer observer) {
      observers.add(observer);
   }

   public void notifyAllObservers () {
      for (Observer observer : observers) {
         observer.update ();
      }
   }     
}
```

#### Observer
```java
public abstract class Observer {
   protected Subject subject;
   public abstract void update ();
}
```

#### BinaryObserver
```java
public class BinaryObserver extends Observer{
   public BinaryObserver (Subject subject){
      this.subject = subject;
      this.subject.attach(this);
   }

   @Override
   public void update () {
      System.out.println("Binary String: " + Integer.toBinaryString(subject.getState())); 
   }
}
```

#### OctalObserver
```java
public class OctalObserver extends Observer {
   public OctalObserver(Subject subject){
      this.subject = subject;
      this.subject.attach(this);
   }

   @Override
   public void update () {
     System.out.println("Octal String: " + Integer.toOctalString(subject.getState())); 
   }
}
```

#### HexaObserver
```java
public class HexaObserver extends Observer{
   public HexaObserver (Subject subject) {
      this.subject = subject;
      this.subject.attach(this);
   }

   @Override
   public void update () {
      System.out.println("Hex String: " + Integer.toHexString(subject.getState()).toUpperCase()); 
   }
}
```
