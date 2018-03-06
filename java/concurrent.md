```java
public class ShareVariable {
  public Integer count = 0;
  public static void main(String[] args) {
    final ShareVariable shareVariable = new ShareVariable();
    Executor executor = Executors.newFixedThreadPool(10);
    
    for(int i = 0; i < 1000; i ++){
      executor.execute(new Runnable() {
        @Override
        public void run() {
          shareVariable.count++;
        }
      });
    }
    
    try {
      Thread.sleep (5000);
    } catch (InterruptedException e) {
      e.printStackTrace ();
    }
    
    System.out.println("Final Count Value:" + shareVariable.count);
  }
}
```
Final Count Value: 973

#### 充血模型
```java
@Component
public class Counter {
  @Autowired
  NumDao numDao;
  
  @Transactional
  public void test () {
    Num num = numDao.findOne("1");
    num.setCount(num.getCount() + 1);
    numDao.save(num);
  }
}
```
```java
Counter counter;
 
public String test () {
  Executor executor = Executors.newFixedThreadPool(10);
  
  for (int i = 0; i < 1000; i ++){
    executor.execute(new Runnable () {
      @Override
      public void run () {
        counter.test();
      }
    });
  }
  
  return "test";
}
```

#### 贫血模型
```java
@RequestMapping("test")
@ResponseBody
public String test () throws InterruptedException {
  final CountDownLatch countDownLatch = new CountDownLatch(1000);
  long start = System.currentTimeMillis();
  Executor executor = Executors.newFixedThreadPool(10);

  for (int i = 0; i < 1000; i ++){
    executor.execute(new Runnable () {
      @Override
      public void run () {
        jdbcTemplate.execute("update test_num set count = count + 1 where id = '1'");
        countDownLatch.countDown();
      }
    });
  }

  countDownLatch.await();
  long costTime = System.currentTimeMillis() - start;
  System.out.println("共花费：" + costTime + "s");
  return "testSql";
}
```

