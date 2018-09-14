#### 并发编程包中atomic
- 通过CAS乐观锁保证原子性
- 通过自旋保证当次修改的最终修改成功
- 通过降低锁粒度（多段锁）增加并发性能

```java
import java.util.concurrent.CountDownLatch; 
import java.util.concurrent.atomic.AtomicInteger; 
 
public class App { 
    public static void main(String[] args) throws Exception { 
        CountDownLatch countDownLatch = new CountDownLatch(100);
        AtomicInteger atomicInteger = new AtomicInteger(0);
        
        for (int i = 0; i < 100; i ++) {
            new Thread () {
                @Override
                public void run () {
                    atomicInteger.getAndIncrement();
                    countDownLatch.countDown(); 
                }
            }.start();
        }
 
        countDownLatch.await();
        System.out.println(atomicInteger.get()); 
    }
}
```
