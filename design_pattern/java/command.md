### 命令模式
将一个请求封装成一个对象，从而使您可以用不同的请求对客户进行参数化

#### Order.java
```java
public interface Order {
   void execute();
}
```

#### Stock.java
```java
public class Stock {
    
   private String name = "ABC";
   private int quantity = 10;

   public void buy () {
      System.out.println("Stock [ Name: " + name+", Quantity: " + quantity + " ] bought");
   }
   
   public void sell () {
      System.out.println("Stock [ Name: " + name + ", Quantity: " + quantity +" ] sold");
   }
}
```

#### BuyStock.java
```java
public class BuyStock implements Order {
   private Stock abcStock;

   public BuyStock (Stock abcStock) {
      this.abcStock = abcStock;
   }

   public void execute() {
      abcStock.buy();
   }
}
```

#### SellStock.java
```java
public class SellStock implements Order {
   private Stock abcStock;

   public SellStock (Stock abcStock) {
      this.abcStock = abcStock;
   }

   public void execute () {
      abcStock.sell();
   }
}
```

#### Broker.java
```java
import java.util.ArrayList;
import java.util.List;

public class Broker {
   private List<Order> orderList = new ArrayList<Order>(); 

   public void takeOrder (Order order){
      orderList.add(order);        
   }

   public void placeOrders () {
      for (Order order : orderList) {
         order.execute();
      }
      
      orderList.clear();
   }
}
```
