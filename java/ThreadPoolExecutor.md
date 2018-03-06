#### CAPACITY的高3位来表示运行状态
- RUNNING 接收新任务，并且处理任务队列中的任务
- SHUTDOWN 不接收新任务，但是处理任务队列的任务
- STOP 不接收新任务，不处理任务队列，同时中断所有进行中的任务
- TIDYING 所有任务已经被终止，工作线程数量为 0，到达该状态会执行terminated()
- TERMINATED terminated() 执行完毕

#### 核心参数
- corePoolSize 最小存活的工作线程数量(如果设置allowCoreThreadTimeOut，那么该值为0)
- maximumPoolSize 最大的线程数量，受限于CAPACITY
- keepAliveTime 对应线程的存活时间，时间单位由TimeUnit指定
- workQueue 工作队列，存储待执行的任务
- RejectExecutionHandler 拒绝策略，线程池满后会触发

线程池的最大容量：CAPACITY中的前三位用作标志位，也就是说工作线程的最大容量为(2^29)-1

#### 四种模型
- CachedThreadPool：可缓存的线程池，如果线程池的当前规模超过了处理需求时，那么将回收空闲的线程，当需求增加时，则可以添加新的线程，线程池的规模不存在任何的限制
- FixedThreadPool：固定大小的线程池，提交一个任务时就创建一个线程，直到达到线程池的最大数量，这时线程池的大小将不再变化
- SingleThreadPool：单线程的线程池，它只有一个工作线程来执行任务，可以确保按照任务在队列中的顺序来串行执行，如果这个线程异常结束将创建一个新的线程来执行任务
- ScheduledThreadPool：固定大小的线程池，并且以延迟或者定时的方式来执行任务，类似于Timer

#### 执行任务
- 检查线程池当前状态是否处于RUNNING
- 如果否, 则拒绝该任务
- 如果是, 判断当前线程数量是否为0, 如果为0, 就增加一个工作线程

- 当前线程数量 < corePoolSize, 直接开启新的核心线程执行任务addWorker(command, true)
- 当前线程数量 >= corePoolSize, 且任务加入工作队列成功
- 开启普通线程执行任务addWorker(command, false), 开启失败就拒绝该任务

- poolSize < corePoolSize 且队列为空, 此时会新建线程来处理提交的任务
- poolSize == corePoolSize 此时提交的任务进入工作队列, 工作线程从队列中获取任务执行，此时队列不为空且未满。
- poolSize == corePoolSize 并且队列已满, 此时也会新建线程来处理提交的任务, 但是poolSize < maxPoolSize
- poolSize == maxPoolSize 并且队列已满, 此时会触发拒绝策略

#### 拒绝策略
- AbortPolicy: 默认策略，终止任务，抛出RejectedException
- CallerRunsPolicy: 在调用者线程执行当前任务，不抛异常
- DiscardPolicy: 抛弃策略，直接丢弃任务，不抛异常
- DiscardOldersPolicy: 抛弃最老的任务，执行当前任务，不抛异常

#### 核心函数 runWorker
```java
final void runWorker (Worker w) {
  Thread wt = Thread.currentThread();
  Runnable task = w.firstTask;
  w.firstTask = null;
    
  while (task != null || (task = getTask()) != null) {
    w.lock();
    beforeExecute(wt, task);
    task.run();
    afterExecute(task, thrown);
    w.unlock();
  }
    
  processWorkerExit(w, completedAbruptly);
}
```

#### 获取任务 getTask
- 允许核心线程等待超时，即 allowCoreThreadTimeOut(true)
- 当前线程是普通线程，此时 wc > corePoolSize

#### Conlusion
- ThreadPoolExecutor基于生产者-消费者模式，提交任务的操作相当于生产者，执行任务的线程相当于消费者
- Executors提供了四种基于ThreadPoolExecutor构造线程池模型的方法，除此之外，我们还可以直接继承ThreadPoolExecutor，重写beforeExecute和afterExecute方法来定制线程池任务执行过程
- 使用有界队列还是无界队列需要根据具体情况考虑，工作队列的大小和线程的数量也是需要好好考虑的
- 拒绝策略推荐使用CallerRunsPolicy，该策略不会抛弃任务，也不会抛出异常，而是将任务回退到调用者线程中执行
