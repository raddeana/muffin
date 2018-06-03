#### 进程状态
- TASK_RUNNING 运行
- TASK_INTERRUPTIBLE 可中断
- TASK_UNINTERRUPTIBLE 不可中断
- __TASK_TRACED 被其他进程跟踪的进程
- __TASK_STOPPED 停止

#### 设置当前进程状态
- 设置当前进程状态 set_task_state ()
- 写时拷贝 fork () 
- 不拷贝父进程页表项 vfork ()
- 创建进程 clone ()
- 内核进程 kthread_run ()
- 进程终结 do_exit ()
- 孤儿进程 forget_original_parent () find_new_reaper ()

