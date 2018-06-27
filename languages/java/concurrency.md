#### 并发编程的原则和技巧
- 单一职责原则
分离并发相关代码和其他代码（并发相关代码有自己的开发、修改和调优生命周期）
- 限制数据作用域
两个线程修改共享对象的同一字段时可能会相互干扰，导致不可预期的行为，解决方案之一是构造临界区，但是必须限制临界区的数量
- 使用数据副本
数据副本是避免共享数据的好方法，复制出来的对象只是以只读的方式对待
- 线程应尽可能独立
让线程存在于自己的世界中，不与其他线程共享数据

#### 并发编程
- 所有线程可以很容易的共享同一进程中的对象
- 能够引用这些对象的任何线程都可以修改这些对象
- 为了保护数据，对象可以被锁住

#### synchronized实现同步和锁
- 只能锁定对象，不能锁定基本数据类型
- 被锁定的对象数组中的单个对象不会被锁定
- 同步方法可以视为包含整个方法的synchronized(this) { … }代码块
- 静态同步方法会锁定它的Class对象
- 内部类的同步是独立于外部类的
- synchronized修饰符并不是方法签名的组成部分，所以不能出现在接口的方法声明中
- 非同步的方法不关心锁的状态，它们在同步方法运行时仍然可以得以运行
- synchronized实现的锁是可重入的锁

#### 被volatile修饰的变量
- 变量的值在使用之前总会从主内存中再读取出来
- 对变量值的修改总会在完成之后写回到主内存中

#### java.util.concurrent
- 更好的线程安全的容器
- 线程池和相关的工具类
- 可选的非阻塞解决方案
- 显示的锁和信号量机制

#### 原子类
```java
/**
 * ID序列生成器
 */
public class IdGenerator {
    private final AtomicLong sequenceNumber = new AtomicLong(0);

    public long next() {
        return sequenceNumber.getAndIncrement(); 
    }
}
```

#### 显示锁
- 锁只有一种类型，而且对所有同步操作都是一样的作用
- 锁只能在代码块或方法开始的地方获得，在结束的地方释放
- 线程要么得到锁，要么阻塞，没有其他的可能性

#### 提升锁机制
- 可以添加不同类型的锁，例如读取锁和写入锁
- 可以在一个方法中加锁，在另一个方法中解锁
- 可以使用tryLock方式尝试获得锁，如果得不到锁可以等待、回退或者干点别的事情，当然也可以在超时之后放弃操作

#### 实现
- ReentrantLock - 比synchronized稍微灵活一些的重入锁
- ReentrantReadWriteLock - 在读操作很多写操作很少时性能更好的一种重入锁

#### CountDownLatch
```java
import java.util.concurrent.CountDownLatch;

/**
 * 工人类
 */
class Worker {
    private String name;        // 名字
    private long workDuration;  // 工作持续时间

    /**
     * 构造器
     */
    public Worker(String name, long workDuration) {
        this.name = name;
        this.workDuration = workDuration;
    }

    /**
     * 完成工作
     */
    public void doWork() {
        System.out.println(name + " begins to work...");
        
        try {
            Thread.sleep(workDuration); // 用休眠模拟工作执行的时间
        } catch(InterruptedException ex) {
            ex.printStackTrace();
        }
        
        System.out.println(name + " has finished the job...");
    }
}

/**
 * 测试线程
 */
class WorkerTestThread implements Runnable {
    private Worker worker;
    private CountDownLatch cdLatch;

    public WorkerTestThread(Worker worker, CountDownLatch cdLatch) {
        this.worker = worker;
        this.cdLatch = cdLatch;
    }

    @Override
    public void run() {
        worker.doWork();        // 让工人开始工作
        cdLatch.countDown();    // 工作完成后倒计时次数减1
    }
}

class CountDownLatchTest {

    private static final int MAX_WORK_DURATION = 5000;  // 最大工作时间
    private static final int MIN_WORK_DURATION = 1000;  // 最小工作时间

    // 产生随机的工作时间
    private static long getRandomWorkDuration(long min, long max) {
        return (long) (Math.random() * (max - min) + min);
    }

    public static void main(String[] args) {
        CountDownLatch latch = new CountDownLatch(2);   // 创建倒计时闩并指定倒计时次数为2
        Worker w1 = new Worker("骆昊", getRandomWorkDuration(MIN_WORK_DURATION, MAX_WORK_DURATION));
        Worker w2 = new Worker("王大锤", getRandomWorkDuration(MIN_WORK_DURATION, MAX_WORK_DURATION));

        new Thread(new WorkerTestThread(w1, latch)).start();
        new Thread(new WorkerTestThread(w2, latch)).start();

        try {
            latch.await();  // 等待倒计时闩减到0
            System.out.println("All jobs have been finished!");
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
```

#### ConcurrentHashMap
- putIfAbsent: 如果还没有对应的键值对映射，就将其添加到HashMap中
- remove: 如果键存在而且值与当前状态相等（equals比较结果为true），则用原子方式移除该键值对映射
- replace: 替换掉映射中元素的原子操作

#### CopyOnWriteArrayList
```java
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

class AddThread implements Runnable {
    private List<Double> list;

    public AddThread(List<Double> list) {
        this.list = list;
    }

    @Override
    public void run() {
        for(int i = 0; i < 10000; ++i) {
            list.add(Math.random());
        }
    }
}

public class Test05 {
    private static final int THREAD_POOL_SIZE = 2;

    public static void main(String[] args) {
        List<Double> list = new ArrayList<>();
        ExecutorService es = Executors.newFixedThreadPool(THREAD_POOL_SIZE);
        es.execute(new AddThread(list));
        es.execute(new AddThread(list));
        es.shutdown();
    }
}
```

```java
List<Double> list = new CopyOnWriteArrayList<>();
```

#### Queue
```java
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * 公共常量
 */
class Constants {
    public static final int MAX_BUFFER_SIZE = 10;
    public static final int NUM_OF_PRODUCER = 2;
    public static final int NUM_OF_CONSUMER = 3;
}

/**
 * 工作任务
 */
class Task {
    private String id;  // 任务的编号

    public Task() {
        id = UUID.randomUUID().toString();
    }

    @Override
    public String toString() {
        return "Task[" + id + "]";
    }
}

/**
 * 消费者
 */
class Consumer implements Runnable {
    private List<Task> buffer;

    public Consumer(List<Task> buffer) {
        this.buffer = buffer;
    }

    @Override
    public void run() {
        while(true) {
            synchronized(buffer) {
                while(buffer.isEmpty()) {
                    try {
                        buffer.wait();
                    } catch(InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                Task task = buffer.remove(0);
                buffer.notifyAll();
                System.out.println("Consumer[" + Thread.currentThread().getName() + "] got " + task);
            }
        }
    }
}

/**
 * 生产者
 */
class Producer implements Runnable {
    private List<Task> buffer;

    public Producer(List<Task> buffer) {
        this.buffer = buffer;
    }

    @Override
    public void run() {
        while(true) {
            synchronized (buffer) {
                while(buffer.size() >= Constants.MAX_BUFFER_SIZE) {
                    try {
                        buffer.wait();
                    } catch(InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                Task task = new Task();
                buffer.add(task);
                buffer.notifyAll();
                System.out.println("Producer[" + Thread.currentThread().getName() + "] put " + task);
            }
        }
    }

}

public class Test06 {
    public static void main(String[] args) {
        List<Task> buffer = new ArrayList<>(Constants.MAX_BUFFER_SIZE);
        ExecutorService es = Executors.newFixedThreadPool(Constants.NUM_OF_CONSUMER + Constants.NUM_OF_PRODUCER);
        for(int i = 1; i <= Constants.NUM_OF_PRODUCER; ++i) {
            es.execute(new Producer(buffer));
        }
        for(int i = 1; i <= Constants.NUM_OF_CONSUMER; ++i) {
            es.execute(new Consumer(buffer));
        }
    }
}
```

#### BlockingQueue
```java
import java.util.UUID;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.LinkedBlockingQueue;

/**
 * 公共常量
 */
class Constants {
    public static final int MAX_BUFFER_SIZE = 10;
    public static final int NUM_OF_PRODUCER = 2;
    public static final int NUM_OF_CONSUMER = 3;
}

/**
 * 工作任务
 */
class Task {
    private String id;  // 任务的编号

    public Task() {
        id = UUID.randomUUID().toString();
    }

    @Override
    public String toString() {
        return "Task[" + id + "]";
    }
}

/**
 * 消费者
 */
class Consumer implements Runnable {
    private BlockingQueue<Task> buffer;

    public Consumer(BlockingQueue<Task> buffer) {
        this.buffer = buffer;
    }

    @Override
    public void run() {
        while(true) {
            try {
                Task task = buffer.take();
                System.out.println("Consumer[" + Thread.currentThread().getName() + "] got " + task);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

/**
 * 生产者
 */
class Producer implements Runnable {
    private BlockingQueue<Task> buffer;

    public Producer(BlockingQueue<Task> buffer) {
        this.buffer = buffer;
    }

    @Override
    public void run() {
        while(true) {
            try {
                Task task = new Task();
                buffer.put(task);
                System.out.println("Producer[" + Thread.currentThread().getName() + "] put " + task);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

        }
    }

}

public class Test07 {
    public static void main(String[] args) {
        BlockingQueue<Task> buffer = new LinkedBlockingQueue<>(Constants.MAX_BUFFER_SIZE);
        ExecutorService es = Executors.newFixedThreadPool(Constants.NUM_OF_CONSUMER + Constants.NUM_OF_PRODUCER);
        for(int i = 1; i <= Constants.NUM_OF_PRODUCER; ++i) {
            es.execute(new Producer(buffer));
        }
        for(int i = 1; i <= Constants.NUM_OF_CONSUMER; ++i) {
            es.execute(new Consumer(buffer));
        }
    }
}
```

#### 并发模型
- 临界资源: 并发环境中有着固定数量的资源
- 互斥: 对资源的访问是排他式的
- 饥饿: 一个或一组线程长时间或永远无法取得进展
- 死锁: 两个或多个线程相互等待对方结束
- 活锁: 想要执行的线程总是发现其他的线程正在执行以至于长时间或永远无法执行

#### Semaphore
```java
//import java.util.concurrent.ExecutorService;
//import java.util.concurrent.Executors;
import java.util.concurrent.Semaphore;

/**
 * 存放线程共享信号量的上下问
 */
class AppContext {
    public static final int NUM_OF_FORKS = 5;   // 叉子数量(资源)
    public static final int NUM_OF_PHILO = 5;   // 哲学家数量(线程)

    public static Semaphore[] forks;    // 叉子的信号量
    public static Semaphore counter;    // 哲学家的信号量

    static {
        forks = new Semaphore[NUM_OF_FORKS];

        for (int i = 0, len = forks.length; i < len; ++i) {
            forks[i] = new Semaphore(1);    // 每个叉子的信号量为1
        }

        counter = new Semaphore(NUM_OF_PHILO - 1);  // 如果有N个哲学家，最多只允许N-1人同时取叉子
    }

    /**
     * 取得叉子
     * @param index 第几个哲学家
     * @param leftFirst 是否先取得左边的叉子
     * @throws InterruptedException
     */
    public static void putOnFork(int index, boolean leftFirst) throws InterruptedException {
        if(leftFirst) {
            forks[index].acquire();
            forks[(index + 1) % NUM_OF_PHILO].acquire();
        }
        else {
            forks[(index + 1) % NUM_OF_PHILO].acquire();
            forks[index].acquire();
        }
    }

    /**
     * 放回叉子
     * @param index 第几个哲学家
     * @param leftFirst 是否先放回左边的叉子
     * @throws InterruptedException
     */
    public static void putDownFork(int index, boolean leftFirst) throws InterruptedException {
        if(leftFirst) {
            forks[index].release();
            forks[(index + 1) % NUM_OF_PHILO].release();
        }
        else {
            forks[(index + 1) % NUM_OF_PHILO].release();
            forks[index].release();
        }
    }
}

/**
 * 哲学家
 */
class Philosopher implements Runnable {
    private int index;      // 编号
    private String name;    // 名字

    public Philosopher(int index, String name) {
        this.index = index;
        this.name = name;
    }

    @Override
    public void run() {
        while(true) {
            try {
                AppContext.counter.acquire();
                boolean leftFirst = index % 2 == 0;
                AppContext.putOnFork(index, leftFirst);
                System.out.println(name + "正在吃意大利面（通心粉）...");   // 取到两个叉子就可以进食
                AppContext.putDownFork(index, leftFirst);
                AppContext.counter.release();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

public class Test04 {
    public static void main(String[] args) {
        String[] names = { "柏拉图", "亚里士多德", "卢梭", "休谟", "培根" };   // 5位哲学家的名字

        for(int i = 0, len = names.length; i < len; ++i) {
            new Thread(new Philosopher(i, names[i])).start();
        }
    }
}
```

#### java7
引入了TransferQueue，它比BlockingQueue多了一个叫transfer的方法，如果接收线程处于等待状态，该操作可以马上将任务交给它，否则就会阻塞直至取走该任务的线程出现
可以用TransferQueue代替BlockingQueue，因为它可以获得更好的性能

##### future 接口
- get(): 获取结果。如果结果还没有准备好，get方法会阻塞直到取得结果；当然也可以通过参数设置阻塞超时时间
- cancel(): 在运算结束前取消
- isDone(): 可以用来判断运算是否结束

```java
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.Future;
import java.util.concurrent.RecursiveTask;

class Calculator extends RecursiveTask<Integer> {
    private static final long serialVersionUID = 7333472779649130114L;

    private static final int THRESHOLD = 10;
    private int start;
    private int end;

    public Calculator(int start, int end) {
        this.start = start;
        this.end = end;
    }

    @Override
    public Integer compute() {
        int sum = 0;
        
        if ((end - start) < THRESHOLD) {    // 当问题分解到可求解程度时直接计算结果
            for (int i = start; i <= end; i++) {
                sum += i;
            }
        } else {
            int middle = (start + end) >>> 1;
            // 将任务一分为二
            Calculator left = new Calculator(start, middle);
            Calculator right = new Calculator(middle + 1, end);
            left.fork();
            right.fork();
            // 注意：由于此处是递归式的任务分解，也就意味着接下来会二分为四，四分为八...

            sum = left.join() + right.join();   // 合并两个子任务的结果
        }
        
        return sum;
    }
}

public class Test08 {
    public static void main(String[] args) throws Exception {
        ForkJoinPool forkJoinPool = new ForkJoinPool();
        Future<Integer> result = forkJoinPool.submit(new Calculator(1, 10000));
        System.out.println(result.get());
    }
}
```
