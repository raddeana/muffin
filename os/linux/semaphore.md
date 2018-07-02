#### 信号量概念引入
进程间通信中，共享内存无疑是最快的进程间通信，但是共享内存没有进行同步互斥，而信号量的功能就是实现同步和互斥

#### 同步和互斥
- 由于各进程要求共享资源，而且有些资源需要互斥使用，因此各进程间竞争使用这些资源，进程的这种关系为进程的互斥
- 就是一个进程使用这份资源另外一个进程就不能使用，这样两个进程之间就是互斥关系
- 系统中某些资源一次只允许一个进程使用，称这样的资源为临界资源或互斥资源
- 在进程中涉及到互斥资源的程序段叫临界区

#### 进程同步
多个进程要相互配合共同完成一项任

#### 信号量值含义
- S > 0: S表示可用资源的个数
- S = 0: 表示无可用资源，无等待进程
- S < 0: |S|表示等待队列中进程个数

```c
struct semaphore
{
    int value;
    pointer_PCB queue;
}
```

#### P、V原语
- P原语 就相当于 -- 操作
```c
P(s) {
    s.value = s.value --;
    if (s.value < 0) {
        // 该进程状态置为等待状状态
        // 将该进程的PCB插入相应的等待队列s.queue末尾
    }
}
```

- V原语 相当于 ++ 操作
```c
V(s) {
    s.value = s.value ++;
    if (s.value <= 0) {
        // 唤醒相应等待队列 s.queue 中等待的一个进程
        // 改变其状态为就绪态
        // 并将其插入就绪队列
    }
}
```

#### 信号量结构
```c
struct semid_ds {
    struct ipc_perm sem_perm;     /* Ownership and permissions */
    time_t       sem_otime;       /* Last semop time */
    time_t       sem_ctime;       /* Last change time */
    unsigned short sem_nsems;     /* No. of semaphores in set */
}
```

#### 信号量集函数




