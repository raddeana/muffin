#### 解释器模式
解释器模式（Interpreter Pattern）提供了评估语言的语法或表达式的方式，它属于行为型模式

#### Expression
```java
public interface Expression {
   public boolean interpret(String context);
}
```

#### TerminalExpression
```java
public class TerminalExpression implements Expression {
    
   private String data;

   public TerminalExpression(String data){
      this.data = data; 
   }

   @Override
   public boolean interpret(String context) {
      if(context.contains(data)){
         return true;
      }
      return false;
   }
}
```

#### OrExpression
```java
public class OrExpression implements Expression {
     
   private Expression expr1 = null;
   private Expression expr2 = null;

   public OrExpression(Expression expr1, Expression expr2) { 
      this.expr1 = expr1;
      this.expr2 = expr2;
   }

   @Override
   public boolean interpret(String context) {        
      return expr1.interpret(context) || expr2.interpret(context);
   }
}
```

#### AndExpression
```java
public class AndExpression implements Expression {
   private Expression expr1 = null;
   private Expression expr2 = null;

   public AndExpression (Expression expr1, Expression expr2) { 
      this.expr1 = expr1;
      this.expr2 = expr2;
   }

   @Override
   public boolean interpret (String context) {        
      return expr1.interpret(context) && expr2.interpret(context);
   }
}
```
