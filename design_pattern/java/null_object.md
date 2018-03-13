#### Null Object
在空对象模式（Null Object Pattern）中，一个空对象取代 NULL 对象实例的检查

#### AbstractCustomer
```java
public abstract class AbstractCustomer {
   protected String name;
   public abstract boolean isNil();
   public abstract String getName();
}
```

#### RealCustomer
```java
public class RealCustomer extends AbstractCustomer {

   public RealCustomer(String name) {
      this.name = name;        
   }
   
   @Override
   public String getName() {
      return name;
   }
   
   @Override
   public boolean isNil() {
      return false;
   }
}
```

#### NullCustomer
```java
public class NullCustomer extends AbstractCustomer {

   @Override
   public String getName() {
      return "Not Available in Customer Database";
   }

   @Override
   public boolean isNil() {
      return true;
   }
}
```

#### CustomerFactory
```java
public class CustomerFactory {
   public static final String[] names = {"Rob", "Joe", "Julie"};

   public static AbstractCustomer getCustomer(String name){
      for (int i = 0; i < names.length; i++) {
         if (names[i].equalsIgnoreCase(name)){
            return new RealCustomer(name);
         }
      }
      return new NullCustomer();
   }
}
```
