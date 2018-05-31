#### 内核定时器使用
内核定时器是内核用来控制在未来某个时间点（基于jiffies）调度执行某个函数的一种机制，其实现位于 <Linux/timer.h> 和 kernel/timer.c 文件中
被调度的函数肯定是异步执行的，它类似于一种 "软件中断"，而且是处于非进程的上下文中，所以调度函数必须遵守以下规则：
- 没有 current 指针、不允许访问用户空间
- 因为没有进程上下文，相关代码和被中断的进程没有任何联系
- 不能执行休眠（或可能引起休眠的函数）和调度
- 任何被访问的数据结构都应该针对并发访问进行保护，以防止竞争条件
内核定时器的调度函数运行过一次后就不会再被运行了（相当于自动注销），但可以通过在被调度的函数中重新调度自己来周期运行
在SMP系统中，调度函数总是在注册它的同一CPU上运行，以尽可能获得缓存的局域性

#### 数据结构
```c
struct timer_list {
  struct list_head entry; 
  unsigned long expires;
  void (*function)(unsigned long);
  unsigned long data; 
  struct tvec_base *base;
};
```

```c
DEFINE_TIMER(timer_name, function_name, expires_value, data);
```

```c
struct timer_list mytimer;
void init_timer(struct timer_list *timer);
```

```c
static inline void setup_timer(struct timer_list * timer, void (*function)(unsigned long), unsigned long data)
{
  timer->function = function;
  timer->data = data;
  init_timer(timer);
}
```

#### 注册
```c
add_timer(struct timer_list *timer)
```

#### 重新注册（修改）
```c
mod_timer(struct timer_list *timer, unsigned long expires)
```

#### 注销
```c
del_timer(struct timer_list *timer)
del_timer_sync(struct timer_list *timer)
```

#### 使用范例
```c
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/time.h>
#include <linux/timer.h>

static struct timer_list tm;
struct timeval oldtv;

void callback(unsigned long arg)
{
    struct timeval tv;
    char *strp = (char*)arg;
    
    printk("%s: %lu, %s\n", __func__, jiffies, strp);

    do_gettimeofday(&tv);
    printk("%s: %ld, %ld\n", __func__,
        tv.tv_sec - oldtv.tv_sec,          // 与上次中断间隔 s
        tv.tv_usec- oldtv.tv_usec);        // 与上次中断间隔 ms
    

    oldtv = tv;
    tm.expires = jiffies+1*HZ;    
    add_timer(&tm);                        // 重新开始计时
}

static int __init demo_init(void)
{
    printk(KERN_INFO "%s : %s : %d - ok.\n", __FILE__, __func__, __LINE__);
    init_timer(&tm);                              // 初始化内核定时器

    do_gettimeofday(&oldtv);                      // 获取当前时间
    tm.function= callback;                        // 指定定时时间到后的回调函数
    tm.data    = (unsigned long)"hello world";    // 回调函数的参数
    tm.expires = jiffies+1*HZ;                    // 定时时间
    add_timer(&tm);                               // 注册定时器

    return 0;
}

static void __exit demo_exit(void)
{
    printk(KERN_INFO "%s : %s : %d - ok.\n", __FILE__, __func__, __LINE__);
    del_timer(&tm);        // 注销定时器
}

module_init(demo_init);
module_exit(demo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Farsight");
MODULE_DESCRIPTION("Demo for kernel module");
```
