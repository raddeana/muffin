单例类只能有一个实例
单例类必须自己创建自己的唯一实例
单例类必须给所有其他对象提供这一实例

#### 懒汉式
线程不安全
```java
public class Singleton {  
  private static Singleton instance;  
  private Singleton (){}  

  public static Singleton getInstance() {  
    if (instance == null) {  
      instance = new Singleton();  
    }  
    return instance;  
  } 
}
```

#### 懒汉式
线程安全
```java
public class Singleton {  
  private static Singleton instance;  
  private Singleton (){}  
  public static synchronized Singleton getInstance() {  
    if (instance == null) {  
        instance = new Singleton();  
    }
    return instance;  
  }  
} 
```

#### 饿汉式
线程安全
```java
public class Singleton {  
  private static Singleton instance = new Singleton();  
  private Singleton (){}  
    public static Singleton getInstance() {  
    return instance;  
  } 
}  
```

#### 双检锁/双重校验锁
这种方式采用双锁机制，安全且在多线程情况下能保持高性能
```java
public class Singleton {  
  private volatile static Singleton singleton;  
  private Singleton (){}  
  public static Singleton getSingleton() {  
    if (singleton == null) {  
      synchronized (Singleton.class) {  
        if (singleton == null) {  
            singleton = new Singleton();  
        }  
      }  
    }
    
    return singleton;  
  } 
}  
```

#### 登记式/静态内部类
```java
public class Singleton {  
  private static class SingletonHolder {  
    private static final Singleton INSTANCE = new Singleton();  
  }

  private Singleton () {}
    public static final Singleton getInstance() {
    return SingletonHolder.INSTANCE;
  }
}   
```

#### 枚举
```java
public enum Singleton {  
  INSTANCE;  
  public void whateverMethod() {}
}  
```
