#### 信号概念
- 是进程间通讯的一种有限制的方式
- 是一种异步的通知机制，用来提醒进程一个事件已经发生
- 当一个信号发送给一个进程，操作系统中断了进程正常的控制流程，此时，任何非原子操作都将被中断
- 如果进程定义了信号的处理函数，那么它将被执行，否则就执行默认的处理函数

#### 产生信号的方式
- 用户在终端下按下某些键的时候，就会给正在运行的进程发送一个信号
- 硬件异常产生信号：当我们运行一个除以 0 的程序的时候，CPU的运算器会产生异常，内核将这个异常解释为SIGFPE信号发送给进程，再比如当我们访问非法内存时，MMU会产生异常，内核将此异常解释为一个SIGSEGV信号发送给进程
- 用系统函数kill 可以给一个进程发送信号

#### 调用系统函数给进程发送信号
kill（给一个指定的进程发送信号） - 信号的标号或者信号 进程的pid，raise（给当前进程发送信号），就不需要指定pid了直接发送信号

#### 软件条件产生信号
SIGALRM信号,alarm函数就可以产生SIGALRM信号
通过alarm设置一个闹钟就是告诉内核多长时间之后会给进程发送SIGALRM信号，该信号的默认动作是终止进程

#### 阻塞信号
- 实际执行信号的处理动作叫做信号递达
- 信号从产生到递达状态称为信号未决
- 进程可以选择阻塞哪些信号
- 被阻塞的信号会一直处于未决状态，直到进程解决对信号的阻塞状态，信号才会执行递达的动作

```c
void MyHandler(int sig) {
  printf("sig = %d",sig);
}

void PrintSigset(sigset_t *set) {
  int i = 1;
  
  for(; i<=31 ;i++) {
    if(sigismember(set,i)) {
      printf("1");
    } else {
      printf("0");
    }
  }
  
  printf("\n");
}

int main() {
  //捕捉SIGINT信号
  signal(SIGINT,MyHandler);
  
  //吧SIGINT信号屏蔽掉
  sigset_t set;
  sigset_t oset;
  sigemptyset(&set);
  sigaddset(&set,SIGINT);
  sigprocmask(SIG_BLOCK,&set,&oset);

  //循环读取，未决信号集
  while(1)
  {
    sigset_t pending_set;
    sigpending(&pending_set);
    PrintSigset(&set);
    sleep(1);
  }
  
  return 0;
}
```

#### 可重入函数
个函数被不同的控制流执行，有可能在一个控制流还没有结束的时候，另一个控制流就再次进入了该进程，这函数就是可冲入函数
- 调用了malloc/free，malloc用全局链表来管理堆的
- 调用了标准I/O库函数

#### volatile限定符
```c
#include<stdio.h>
#include<signal.h>

// 保证内存的可见性
volatile int g_val = 1;
void MyHandler (int sig) {
  (void) sig;
  g_val = 0;
}

int main() {
  // 信号处理函数
  signal(SIGINT,MyHandler);
  while(g_val);
  return 0;
}
```

#### SIGCHLD信号
如果我们一下创建多个子进程，然后父进程wait子进程的时候，如果同时有多个子进程完成
那么父进程只会处理一个子进程其他的都会变成僵尸进程，那其实我们呢就可以用waitpid函数来一个一个非阻塞式的等待
当许多子进程同时完成时，调用waitpid函数一个一个的回收，然后继续等待下一次SIGCHLD信号的到达，然后继续调用信号处理函数处理子进程

```c
void MyHandler (int sig) {
  (void) sig;
  // int ret = wait(NULL);
  // 循环处理当前一起结束的进程
  while(1) {
    int ret = waitpid(-1,NULL,WNOHANG);
    if(ret > 0) {
      printf("waitpid %d\n",ret);
      continue;
    }
    // 还有其他的未结束的进程，直接返回，因为接下来的还有其他的进程会触发此处理函数
    else if (ret == 0) {
      break;
    }
    // 子进程都结束了
    else{
      break;
    }
  }
}

int main () {
  // 忽略掉SINCHID信号，自动销毁子进程
  signal(SIGCHLD,MyHandler);
  int i = 0;
  
  for(;i<20;i++) {
    pid_t ret = fork();
    
    if (ret < 0) {
      perror("fork error\n");
      return 1;
    }
    
    // 子进程打印pid
    if (ret == 0) {
      printf("child = %d\n",getpid());
      sleep(3);
      exit(0);
    }
    // 父进程直接执行下一次循环
  }
  
  while(1) {
    printf("father work!\n");
    sleep(1);
  }
  
  return 0;
}
```

可直接把SIGCHLD信号忽略掉，然后进程就会自动的将这些子进程销毁掉
```c

int main()
{
  // 忽略掉SINCHID信号，自动销毁子进程
  signal(SIGCHLD,SIG_IGN);
  int i = 0;

  for(;i<20;i++) {
    pid_t ret = fork();
    if (ret < 0) {
      perror("fork error\n");
      return 1;
    }
    // 子进程打印pid
    if (ret == 0) {
      printf("child = %d\n",getpid());
      sleep(3);
      exit(0);
    }
    // 父进程直接执行下一次循环
  }
  
  while(1) {
    printf("father work!\n");
    sleep(1);
  }
}
```



