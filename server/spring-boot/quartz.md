#### Spring Boot

##### pom 包配置
```xml
<dependencies>
  <dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter</artifactId>
  </dependency>
</dependencies>
```

##### 启动类: @EnableScheduling
```java
@Spring BootApplication
@EnableScheduling
public class Application {
  public static void main(String[] args) {
    SpringApplication.run(Application.class, args);
  }
}
```

##### 定时任务实现类
```java
@Component
public class SchedulerTask {
  private int count = 0;

  @Scheduled(cron="*/6 * * * * ?")
  private void process(){
    System.out.println("this is scheduler task runing  "+(count++));
  }
}
```

##### fixedRate 说明
- @Scheduled(fixedRate = 6000): 上一次开始执行时间点之后 6 秒再执行
- @Scheduled(fixedDelay = 6000): 上一次执行完毕时间点之后 6 秒再执行
- @Scheduled(initialDelay=1000, fixedRate=6000): 第一次延迟 1 秒后执行, 之后按 fixedRate 的规则每 6 秒执行一次

#### Quartz
- Quartz 是 OpenSymphony 开源组织在 Job scheduling 领域又一个开源项目
- 完全由 Java 开发的一个开源的任务日程管理系统
- "任务进度管理器" 就是一个在预先确定（被纳入日程）的时间到达时
- 负责执行（或者通知）其他软件组件的系统

##### Quartz 的优点
- 丰富的 Job 操作 API
- 支持多种配置
- Spring Boot 无缝集成
- 支持持久化
- 支持集群
- Quartz 还支持开源, 是一个功能丰富的开源作业调度库, 可以集成到几乎任何 Java 应用程序中

##### Quartz 体系结构
Job（任务）、JobDetail（任务信息）、Trigger（触发器）、Scheduler（调度器）
- Job（任务）
  - 是一个接口，只定义一个方法 execute(JobExecutionContext context)
  - 在实现接口的 execute 方法中编写所需要定时执行的 Job（任务）
  - JobExecutionContext 类提供了调度应用的一些信息

- JobDetail（任务信息）
  - Quartz 每次调度 Job 时，都重新创建一个 Job 实例，所以它不直接接受一个 Job 的实例
  - 相反它接收一个 Job 实现类（JobDetail，描述 Job 的实现类及其他相关的静态信息，如 Job 名字、描述、关联监听器等信息
  - 以便运行时通过 newInstance() 的反射机制实例化 Job

- Trigger（触发器）是一个类，描述触发 Job 执行的时间触发规则
- Scheduler（调度器）调度器就相当于一个容器，装载着任务和触发器

#### Spring Boot 和 Quartz
##### 配置 maven 支持
```xml
<repositories>
  <repository>
    <id>spring-milestones</id>
    <name>Spring Milestones</name>
    <url>https://repo.spring.io/libs-milestone</url>
    <snapshots>
      <enabled>false</enabled>
    </snapshots>
  </repository>
</repositories>
```
##### 配置 pom.xml
```xml
<parent>
  <groupId>org.springframework.boot</groupId>
  <artifactId>spring-boot-starter-parent</artifactId>
  <version>2.0.0.M6</version>
</parent>
```
```xml
<dependencies>
  <dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-quartz</artifactId>
  </dependency>
</dependencies>
```

##### 简单示例
```java
public class SampleJob extends QuartzJobBean {
    private String name;
    
    public void setName(String name) {
      this.name = name;
    }

    @Override
    protected void executeInternal(JobExecutionContext context) throws JobExecutionException {
      System.out.println(String.format("Hello %s!", this.name));
    }
}
```
```java
@Configuration
public class SampleScheduler {
  @Bean
  public JobDetail sampleJobDetail () {
    return JobBuilder.newJob(SampleJob.class).withIdentity("sampleJob")
            .usingJobData("name", "World").storeDurably().build();
  }

  @Bean
  public Trigger sampleJobTrigger () {
    SimpleScheduleBuilder scheduleBuilder = SimpleScheduleBuilder.simpleSchedule()
            .withIntervalInSeconds(2).repeatForever();
    return TriggerBuilder.newTrigger().forJob(sampleJobDetail())
            .withIdentity("sampleTrigger").withSchedule(scheduleBuilder).build();
  }
}
```
- JobBuilder 无构造函数，所以只能通过 JobBuilder 的静态方法 newJob(Class<? extends Job> jobClass) 生成 JobBuilder 实例
- withIdentity 方法可以传入两个参数withIdentity(String name,String group)来定义 TriggerKey，也可以不设置，像上文示例中会自动生成一个独一无二的 TriggerKey 用来区分不同的 trigger

##### CronSchedule 示例
```java
public class ScheduledJob implements Job {
  @Override  
  public void execute(JobExecutionContext context) throws JobExecutionException {
    System.out.println("schedule job1 is running ...");
  }
} 
```
```java
private void scheduleJob1(Scheduler scheduler) throws SchedulerException {
  JobDetail jobDetail = JobBuilder.newJob(ScheduledJob.class) .withIdentity("job1", "group1").build();
  CronScheduleBuilder scheduleBuilder = CronScheduleBuilder.cronSchedule("0/6 * * * * ?");
  CronTrigger cronTrigger = TriggerBuilder.newTrigger().withIdentity("trigger1", "group1") .withSchedule(scheduleBuilder).build();
  scheduler.scheduleJob(jobDetail,cronTrigger);
}  
```
```java
public void scheduleJobs () throws SchedulerException {
  Scheduler scheduler = schedulerFactoryBean.getScheduler();
  scheduleJob1(scheduler);
  scheduleJob2(scheduler);   
}  
```

##### 何时触发定时任务
- 启动时触发定时任务
```java
@Component
public class MyStartupRunner implements CommandLineRunner {
  @Autowired
  public CronSchedulerJob scheduleJobs;

  @Override
  public void run(String... args) throws Exception {
    scheduleJobs.scheduleJobs();
    System.out.println(">>>>>>>>>>>>>>>定时任务开始执行<<<<<<<<<<<<<");
  }
}
```

- 特定时间启动定时任务
```java
@Configuration
@EnableScheduling
@Component
public class SchedulerListener {  
  @Autowired
  public CronSchedulerJob scheduleJobs;
  
  @Scheduled(cron = "0 30 11 25 11 ?")
  public void schedule() throws SchedulerException {
    scheduleJobs.scheduleJobs();
  }      
}
```
