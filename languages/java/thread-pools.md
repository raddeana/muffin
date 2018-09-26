### JAVA4种线程池的使用
Java通过Executors提供四种线程池，分别为：
- newCachedThreadPool：创建一个可缓存线程池，如果线程池长度超过处理需要，可灵活回收空闲线程，若无可回收，则新建线程
- newFixedThreadPool：创建一个定长线程池，可控制线程最大并发数，超出的线程会在队列中等待
- newScheduledThreadPool：创建一个定长线程池，支持定时及周期性任务执行
- newSingleThreadExecutor：创建一个单线程化的线程池，它只会用唯一的工作线程来执行任务，保证所有任务按照指定顺序(FIFO, LIFO, 优先级)执行

#### newCachedThreadPool
创建一个可缓存线程池，如果线程池长度超过处理需要，可灵活回收空闲线程，若无可回收，则新建线程
```java
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ThreadPoolExecutorTest {
  public static void main (String[] args) {
    ExecutorService cachedThreadPool = Executors.newCachedThreadPool();

    for (int i = 0; i < 10; i++) {
     final int index = i;

      try {
        Thread.sleep(index * 1000);
      } catch (InterruptedException e) {
        e.printStackTrace();
      }

      cachedThreadPool.execute(new Runnable () {
        public void run () {
          System.out.println(index);
        }
      });
    }
  }
}
```

#### newFixedThreadPool
创建一个定长线程池，可控制线程最大并发数，超出的线程会在队列中等待
```java
import java.util.concurrent.ExecutorService;  
import java.util.concurrent.Executors;  
public class ThreadPoolExecutorTest {  
 public static void main(String[] args) {
  ExecutorService fixedThreadPool = Executors.newFixedThreadPool(3);
  
  for (int i = 0; i < 10; i++) {  
   final int index = i;  
   fixedThreadPool.execute(new Runnable() {  
    public void run() {  
     try {  
      System.out.println(index);  
      Thread.sleep(2000);  
     } catch (InterruptedException e) {  
      e.printStackTrace();  
     }  
    }  
   });  
  }  
 }  
}
```

#### newScheduledThreadPool
创建一个定长线程池，支持定时及周期性任务执行
```java
import java.util.concurrent.Executors;  
import java.util.concurrent.ScheduledExecutorService;  
import java.util.concurrent.TimeUnit;  
public class ThreadPoolExecutorTest {  
 public static void main(String[] args) {  
  ScheduledExecutorService scheduledThreadPool = Executors.newScheduledThreadPool(5);  
  scheduledThreadPool.schedule(new Runnable() {  
   public void run () {  
    System.out.println("delay 3 seconds");  
   }
  }, 3, TimeUnit.SECONDS);  
 }
}
```

#### newSingleThreadExecutor
创建一个单线程化的线程池，它只会用唯一的工作线程来执行任务，保证所有任务按照指定顺序(FIFO, LIFO, 优先级)执行
```java
import java.util.concurrent.ExecutorService;  
import java.util.concurrent.Executors;  
public class ThreadPoolExecutorTest {  
 public static void main(String[] args) {  
  ExecutorService singleThreadExecutor = Executors.newSingleThreadExecutor();  
  for (int i = 0; i < 10; i++) {  
   final int index = i;  
   singleThreadExecutor.execute(new Runnable() {  
    public void run() {  
     try {  
      System.out.println(index);  
      Thread.sleep(2000);  
     } catch (InterruptedException e) {  
      e.printStackTrace();  
     }  
    }  
   });  
  }  
 }  
} 
```
