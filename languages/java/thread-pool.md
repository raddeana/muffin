### 线程池
#### ThreadPoolExecutor
```java
public class ThreadPoolExecutor extends AbstractExecutorService {
   public ThreadPoolExecutor(int corePoolSize, int maximumPoolSize, long keepAliveTime, TimeUnit unit, BlockingQueue<Runnable> workQueue);
   public ThreadPoolExecutor(int corePoolSize, int maximumPoolSize, long keepAliveTime, TimeUnit unit, BlockingQueue<Runnable> workQueue, ThreadFactory threadFactory);
   public ThreadPoolExecutor(int corePoolSize, int maximumPoolSize, long keepAliveTime, TimeUnit unit, BlockingQueue<Runnable> workQueue, RejectedExecutionHandler handler);
   public ThreadPoolExecutor(int corePoolSize, int maximumPoolSize, long keepAliveTime, TimeUnit unit, BlockingQueue<Runnable> workQueue, ThreadFactory threadFactory, RejectedExecutionHandler handler);
}
```

参数的含义:
- corePoolSize: 核心池的大小
- maximumPoolSize: 线程池最大线程数
- keepAliveTime: 表示线程没有任务执行时最多保持多久时间会终止
- unit: 参数keepAliveTime的时间单位
  - TimeUnit类中有7种静态属性
- workQueue: 一个阻塞队列，用来存储等待执行的任务
```java
TimeUnit.DAYS;              // 天
TimeUnit.HOURS;             // 小时
TimeUnit.MINUTES;           // 分钟
TimeUnit.SECONDS;           // 秒
TimeUnit.MILLISECONDS;      // 毫秒
TimeUnit.MICROSECONDS;      // 微妙
TimeUnit.NANOSECONDS;       // 纳秒
```

线程池的排队策略与BlockingQueue有关
- threadFactory: 线程工厂，主要用来创建线程;
- handler: 表示当拒绝处理任务时的策略，有以下四种取值:
  - ThreadPoolExecutor.AbortPolicy: 丢弃任务并抛出RejectedExecutionException异常
  - ThreadPoolExecutor.DiscardPolicy: 也是丢弃任务，但是不抛出异常
  - ThreadPoolExecutor.DiscardOldestPolicy: 丢弃队列最前面的任务，然后重新尝试执行任务（重复此过程）
  - ThreadPoolExecutor.CallerRunsPolicy: 由调用线程处理该任务

```java
public abstract class AbstractExecutorService implements ExecutorService {
   protected <T> RunnableFuture<T> newTaskFor(Runnable runnable, T value) {}
   protected <T> RunnableFuture<T> newTaskFor(Callable<T> callable) {}
   public Future<?> submit(Runnable task) {}
   public <T> Future<T> submit(Runnable task, T result) {}
   public <T> Future<T> submit(Callable<T> task) {}
   private <T> T doInvokeAny(Collection<? extends Callable<T>> tasks, boolean timed, long nanos) throws InterruptedException, ExecutionException, TimeoutException {}
   public <T> T invokeAny(Collection<? extends Callable<T>> tasks) throws InterruptedException, ExecutionException {}
   public <T> T invokeAny(Collection<? extends Callable<T>> tasks, long timeout, TimeUnit unit) throws InterruptedException, ExecutionException, TimeoutException {}
   public <T> List<Future<T>> invokeAll(Collection<? extends Callable<T>> tasks) throws InterruptedException {}
   public <T> List<Future<T>> invokeAll(Collection<? extends Callable<T>> tasks, long timeout, TimeUnit unit) throws InterruptedException {}
}
```
```java
public interface ExecutorService extends Executor {
   void shutdown();
   boolean isShutdown();
   boolean isTerminated();
   boolean awaitTermination(long timeout, TimeUnit unit) throws InterruptedException;
   
   <T> Future<T> submit(Callable<T> task);
   <T> Future<T> submit(Runnable task, T result); 
   Future<?> submit(Runnable task);
   
   <T> List<Future<T>> invokeAll(Collection<? extends Callable<T>> tasks) throws InterruptedException;
   <T> List<Future<T>> invokeAll(Collection<? extends Callable<T>> tasks, long timeout, TimeUnit unit) throws InterruptedException;

   <T> T invokeAny(Collection<? extends Callable<T>> tasks) throws InterruptedException, ExecutionException;
   <T> T invokeAny(Collection<? extends Callable<T>> tasks, long timeout, TimeUnit unit) throws InterruptedException, ExecutionException, TimeoutException;
}
```
```java
public interface Executor {
   void execute(Runnable command);
}
```

#### 线程池实现原理
- 线程池状态
- 任务的执行
- 线程池中的线程初始化
- 任务缓存队列及排队策略
- 任务拒绝策略
- 线程池的关闭
- 线程池容量的动态调整

##### 线程池状态
```java
volatile int runState;
static final int RUNNING    = 0;
static final int SHUTDOWN   = 1;
static final int STOP       = 2;
static final int TERMINATED = 3;
```

- 如果调用了shutdown()方法，则线程池处于SHUTDOWN状态，此时线程池不能够接受新的任务，它会等待所有任务执行完毕
- 如果调用了shutdownNow()方法，则线程池处于STOP状态，此时线程池不能接受新的任务，并且会去尝试终止正在执行的任务
- 当线程池处于SHUTDOWN或STOP状态，并且所有工作线程已经销毁，任务缓存队列已经清空或执行结束后，线程池被设置为TERMINATED状态

##### 任务的执行
```java
private final BlockingQueue<Runnable> workQueue;                  // 任务缓存队列，用来存放等待执行的任务
private final ReentrantLock mainLock = new ReentrantLock();       // 线程池的主要状态锁，对线程池状态（比如线程池大小 runState 等）的改变都要使用这个锁
private final HashSet<Worker> workers = new HashSet<Worker>();    // 用来存放工作集
private volatile long  keepAliveTime;                             // 线程存货时间
private volatile boolean allowCoreThreadTimeOut;                  // 是否允许为核心线程设置存活时间
private volatile int   corePoolSize;                  // 核心池的大小（即线程池中的线程数目大于这个参数时，提交的任务会被放进任务缓存队列）
private volatile int   maximumPoolSize;               // 线程池最大能容忍的线程数
private volatile int   poolSize;                      // 线程池中当前的线程数
private volatile RejectedExecutionHandler handler;    // 任务拒绝策略
private volatile ThreadFactory threadFactory;         // 线程工厂，用来创建线程
private int largestPoolSize;                          // 用来记录线程池中曾经出现过的最大线程数
private long completedTaskCount;                      // 用来记录已经执行完毕的任务个数
```

```java
public void execute(Runnable command) {
   if (command == null) {
       throw new NullPointerException();
   }
   
   if (poolSize >= corePoolSize || !addIfUnderCorePoolSize(command)) {
       if (runState == RUNNING && workQueue.offer(command)) {
           if (runState != RUNNING || poolSize == 0) {
               ensureQueuedTaskHandled(command);
           }
       } else if (!addIfUnderMaximumPoolSize(command)) {
           reject(command); // is shutdown or saturated
       }
   }
}

private boolean addIfUnderCorePoolSize (Runnable firstTask) {
   Thread t = null;
   final ReentrantLock mainLock = this.mainLock;
   mainLock.lock();
   
   try {
       if (poolSize < corePoolSize && runState == RUNNING)
          t = addThread(firstTask); // 创建线程去执行firstTask任务   
       } finally {
          mainLock.unlock();
       }
   }
   
   if (t == null) {
       return false;
   }
   
   t.start();
   return true;
}

private Thread addThread (Runnable firstTask) {
   Worker w = new Worker(firstTask);
   Thread t = threadFactory.newThread(w);  // 创建一个线程，执行任务
   
   if (t != null) {
       w.thread = t;                       // 将创建的线程的引用赋值为w的成员变量       
       workers.add(w);
       int nt = ++poolSize;                // 当前线程数加1
       
       if (nt > largestPoolSize) {
           largestPoolSize = nt;
       }
   }
   
   return t;
}
```

#### From https://blog.csdn.net/Y0Q2T57s/article/details/80251952
