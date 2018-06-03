#### Celery
支持使用任务队列的方式在分布的机器／进程／线程上执行任务调度
Celery的架构由三部分组成，消息中间件（message broker），任务执行单元（worker）和任务执行结果存储（task result store）组成
- 消息中间件
Celery本身不提供消息服务，但是可以方便的和第三方提供的消息中间件集成
- 任务执行单元
Worker是Celery提供的任务执行的单元，worker并发的运行在分布式的系统节点中
- 任务结果存储
Task result store用来存储Worker执行的任务的结果，Celery支持以不同方式存储任务的结果
包括AMQP, Redis，memcached, MongoDB，SQLAlchemy, Django ORM，Apache Cassandra, IronCache

Celery还支持不同的并发和序列化的手段
- 并发 Prefork, Eventlet, gevent, threads/single threaded
- 序列化 pickle, json, yaml, msgpack. zlib, bzip2 compression， Cryptographic message signing

#### tasks.py
```python
from celery import Celery

app = Celery('tasks', backend='amqp', broker='amqp://guest@localhost//')
app.conf.CELERY_RESULT_BACKEND = 'db+sqlite:///results.sqlite'

@app.task
def add(x, y):
    return x + y
```

```python
celery -A tasks worker --loglevel=info
```
- 其中－A参数表示的是Celery App的名字
- 注意这里我使用的是SQLAlchemy作为结果存储
- 对应的python包要事先安装好




