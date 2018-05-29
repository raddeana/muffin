#### 导入相关模块
```python
  import multiprocessing
  import time
  import randam
  import os
```

#### 任务函数
```python
def worker(msg):
  t_start = time.time()
  print("%s开始执行，进程号为%d" % (msg,os.getpid()))
  
  # random.random()随机生成0~1之间的浮点数
  time.sleep(random.random()*2)
  t_stop = time.time()
  pring(msg,"执行完毕，耗时%02.f" % (t_stop-t_start))
```

#### 创建进程池
```python
if __name_ == '__main__':
  pool = multiprocessing.Poll(3)
```

#### 添加任务
```python
  # apply阻塞的任务添加方式 任务添加到进程池中的京城中执行 
  # 会阻塞等待任务执行完成 才会继续往下执行
  pool.apply(func=worker, args=('000,'))
  pool.apply(func=worker, args=('111,'))

  # 非阻塞的任务添加添加方式
  # 把任务添加到进程中执行 不阻塞等待任务执行完成
  pool.apply_async(func=worker, args=('222,'))
  pool.apply_async(func=worker, args=('333,'))
  # 主进程一旦退出 就会导致所有任务<子进程 不是通过继承的方式创建出来的>全部结束
```

#### 关闭进程池
```python
  # pool.close()
  # 3 直接终止所有正在运行的子进程
  pool.terminate()
```

#### 任务执行完成
```python
  # 一般使用非阻塞的任务添加方式需要配合.join()
  pool.join()
```
