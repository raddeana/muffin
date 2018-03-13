#### Memento Pattern
备忘录模式（Memento Pattern）保存一个对象的某个状态，以便在适当的时候恢复对象

#### Memento
```java
public class Memento {
   private String state;

   public Memento (String state) {
      this.state = state;
   }

   public String getState () {
      return state;
   }    
}
```

#### Originator
```java
public class Originator {
   private String state;

   public void setState (String state) {
      this.state = state;
   }

   public String getState () {
      return state;
   }

   public Memento saveStateToMemento () {
      return new Memento(state);
   }

   public void getStateFromMemento (Memento Memento) {
      state = Memento.getState();
   }
}
```

#### CareTaker
```java
import java.util.ArrayList;
import java.util.List;

public class CareTaker {
   private List<Memento> mementoList = new ArrayList<Memento>();

   public void add (Memento state) {
      mementoList.add(state);
   }

   public Memento get (int index) {
      return mementoList.get(index);
   }
}
```
