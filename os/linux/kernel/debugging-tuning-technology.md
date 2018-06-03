#### 内核态
- 先介绍下单步调试的方式，相信大部分工程师常用单步调试方式都会选择 GDB，GDB 是最常用的调试工具
- 信号是 GDB 实现断点功能的基础，用 GDB 向某个地址打断点的时候，实际上就是向改地址写入断点指令

##### 内核调试的配置
- 用 GDB 调试内核的话首先需要内核支持 KGDB，配置:
```cmd
$ make configure
  Kernel hacking --->
    _*_ Magic SysRq Key
    [*] Kernel Debugging
    [*] Compile the kernel width debug info
    [*] KGDB: kernel debugging with remote gdb --->
      <*> KGDB: use kgdb over the serial console
```
- 配置成功后编译内核，然后修改 Uboot 启动参数以支持 KGDB 调试:
```cmd
setenv bootargs 'console=ttyS0,115200n8 kgdboc=ttyS0,115200 kgdbwait …… nfsroot=……'
```
- 用 GDB 调试 vmlinux
```cmd
$ arm-none-linux-gnueabi-gdb vmlinux
```

##### Kdump 的调试方式
- 除了单步调试外还有一种场景是我们经常碰到的，在系统运行中 Linux 内核发生崩溃的时候
- 可以通过 Kdump 方式收集内核崩溃前的内存，生成 vmcore 文件，通过 vmcore 文件诊断出内核崩溃的原因
- 其中 kexec 是实现 Kdump 机制的关键，它由两部分组成:
  - 一是内核空间的系统调用 kexec_load，负责在生产内核（production kernel 或 first kernel）启动时将捕获内核（capture kernel 或 sencond kernel）加载到指定地址
  - 用户空间的工具 kexec-tools，他将捕获内核的地址传递给生产内核，从而在系统崩溃的时候能够找到捕获内核的地址并运行
  
经常用到分析 vmcore 的工具就是 crash，掌握 crash 的技巧对于定位问题有着很重要的意义
```cmd
# 进入 crash
crash vmlinuz-4.2.0-27-generic vmcore
# 进入 crash 环境后就可以运用 crash 命令进行调试，比如 bt、dis、struct 等
crash>
```

##### 用户态
讲解内核的顺序我们先讲解如何在用户态用 GDB 工具调试
进入 GDB 后，我们一起来看下是如何使用的
- 设置断点
- 查看断点处情况 (gdb) info b
- 运行代码 (gdb) r
- 单步运行 (gdb) n
- 程序继续运行 (gdb) c
- (gdb) bt
  - (gdb) frame 1 用于打印指定栈帧
  - (gdb) info reg 查看寄存器使用情况
  - (gdb) info stack 查看堆栈使用情况
  - 退出GDB (gdb) q
