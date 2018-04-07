线程实际上是在进程基础上的进一步划分。
如果一个进程消失，则线程肯定会消失，如果线程消失，进程未必会消失。
所有的线程都是在进程的基础上并发进行（同时运行）

- 继承Thread类；
- 实现Runnable接口；

#### java的多线程实现
##### 继承Thread类
Thread类是在java.lang包中定义的，一个类只要继承了thread类，此类就称为多线程操作类
在Thread子类中，必须明确的覆写Thread类中的run()方法，此方法是线程的主体
如果线程已经启动了，再调用start()方法，则会产生异常
```java
class 类名 extends Thread{
	属性；
	方法；
	public void run () {}
}
```

```java
public class MyThread extends Thread {  
  //继承Thread类，作为线程的实现类
	private String name;   //表示线程的名称
	public MyThread(String name) {
		this.name = name;    //通过构造方法配置name属性
	}
  
	@Override
	public void run() {   //覆写run()方法，作为线程的操作主体
		for (int i = 0; i < 10; i++) {
			System.out.println(this.name + "运行，i=" + i);
		}
	}
  
	public static void main(String[] args) {
		MyThread mt1 = new MyThread("线程A"); //实例化对象
		MyThread mt2 = new MyThread("线程B"); //实例化对象
		mt1.start();  //调用线程主体
		mt2.start();  //调用线程主体	
	}
}
```

##### 实现Runnable接口
```java
class 类名 implements Runnable{
	属性；
	方法；
	public void run(){}
}
```
如果要启动线程，需要依靠Thread类，因为Runnable接口中没有start()方法
```java
public Thread(Runnable target)
public class MyThread1 implements Runnable {  
  //继承Thread类，作为线程的实现类
	private String name;   //表示线程的名称
	public MyThread1(String name) {
		this.name = name;    //通过构造方法配置name属性
	}
  
	@Override
	public void run() {   //覆写run()方法，作为线程的操作主体
		for (int i = 0; i < 10; i++) {
			System.out.println(this.name + "运行，i=" + i);
			try {
				Thread.sleep(500);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
  
	public static void main(String[] args) {
		MyThread1 mt1 = new MyThread1("线程A"); //实例化对象
		MyThread1 mt2 = new MyThread1("线程B"); //实例化对象
		Thread t1 = new Thread(mt1);
		Thread t2 = new Thread(mt2);
		t1.start();
		t2.start();
	}
}
```

##### Thread类与Runnable接口
- Thread类是Runnable接口的子类
- 类的关系上看，类似于代理模式

##### 区别
使用Thread类在操作多线程的时候无法达到资源共享的目的，而使用Runnable接口实现的多线程操作可以实现资源共享
```java
private int ticket = 5
```

好处：
- 适合多个线程处理同一个资源
- 避免单继承局限带来的影响
- 增强了程序的健壮性，代码能够被多个线程共享，代码与数据是独立的

##### 程序的状态
- 创建状态：准备好了一个多线程对象，Thread t1 = new Thread()
- 就绪状态：调用start()方法，等待CPU进行调度
- 运行状态：调用run()方法
- 阻塞状态：暂时停止执行，可能将资源交给其他线程使用
- 终止状态（死亡状态）：线程执行完毕，不在使用

