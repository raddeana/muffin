#### Iterator Pattern
用于顺序访问集合对象的元素，不需要知道集合对象的底层表示

#### Iterator
```java
public interface Iterator {
   public boolean hasNext();
   public Object next();
}
```

#### Container
```java
public interface Container {
   public Iterator getIterator();
}
```

#### NameRepository
```java
public class NameRepository implements Container {
   public String names[] = {"Robert" , "John" ,"Julie" , "Lora"};

   @Override
   public Iterator getIterator() {
      return new NameIterator();
   }

   private class NameIterator implements Iterator {

      int index;

      @Override
      public boolean hasNext() {
         if(index < names.length){
            return true;
         }
         return false;
      }

      @Override
      public Object next() {
         if(this.hasNext()){
            return names[index++];
         }
         return null;
      }        
   }
}
```
