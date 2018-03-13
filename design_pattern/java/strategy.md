#### 策略模式
一个类的行为或其算法可以在运行时更改

#### Strategy
```java
public interface Strategy {
   public int doOperation(int num1, int num2);
}
```

#### OperationAdd
```java
public class OperationAdd implements Strategy{
   @Override
   public int doOperation(int num1, int num2) {
      return num1 + num2;
   }
}
```

#### OperationSubstract
```java
public class OperationSubstract implements Strategy {
   @Override
   public int doOperation (int num1, int num2) {
      return num1 - num2;
   }
}
```

#### OperationMultiply
```java
public class OperationMultiply implements Strategy {
   @Override
   public int doOperation(int num1, int num2) {
      return num1 * num2;
   }
}
```

#### Context
```java
public class Context {
   private Strategy strategy;

   public Context(Strategy strategy){
      this.strategy = strategy;
   }

   public int executeStrategy(int num1, int num2){
      return strategy.doOperation(num1, num2);
   }
}
```

