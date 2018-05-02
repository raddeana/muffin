### RabbitMQ 集群
RabbitMQ 最优秀的功能之一就是内建集群，这个功能设计的目的是允许消费者和生产者在节点崩溃的情况下继续运行，
以及通过添加更多的节点来线性扩展消息通信吞吐量

#### 概念
#### 内部元数据
在单一节点中，RabbitMQ 会将所有这些信息存储在内存中，同时将标记为可持久化的队列、交换器、绑定存储到硬盘上
- 队列元数据
  - 包括队列名称和它们的属性，比如是否可持久化，是否自动删除
- 交换器元数据
  - 交换器名称、类型、属性
- 绑定元数据
  - 内部是一张表格记录如何将消息路由到队列
- vhost 元数据
  - 为 vhost 内部的队列、交换器、绑定提供命名空间和安全属性

#### 集群配置和启动
如果是在一台机器上同时启动多个 RabbitMQ 节点来组建集群的话，只用上面介绍的方式启动第二、第三个节点将会因为节点名称和端口冲突导致启动失败
如果在集群中创建队列，集群只会在单个节点而不是所有节点上创建完整的队列信息（元数据、状态、内容）

- 启动第1个节点
```cmd
RABBITMQ_NODENAME=test_rabbit_1 RABBITMQ_NODE_PORT=5672 ./sbin/rabbitmq-server -detached
```
- 启动第2个节点
```cmd
RABBITMQ_NODENAME=test_rabbit_2 RABBITMQ_NODE_PORT=5673 ./sbin/rabbitmq-server -detached
```

- 停止第2个节点的应用程序
```cmd
./sbin/rabbitmqctl -n test_rabbit_2 stop_app
```

- 重置第2个节点元数据
```cmd
./sbin/rabbitmqctl -n test_rabbit_2 reset
```

- 第2节点加入第1个节点组成的集群
```cmd
./sbin/rabbitmqctl -n test_rabbit_2 join_cluster test_rabbit_1@localhost
```

- 启动第2个节点的应用程序
```cmd
./sbin/rabbitmqctl -n test_rabbit_2 start_app
```

- 第3个节点的配置过程和第2个节点类似
```cmd
RABBITMQ_NODENAME=test_rabbit_3 RABBITMQ_NODE_PORT=5674 ./sbin/rabbitmq-server -detached
./sbin/rabbitmqctl -n test_rabbit_3 stop_app
./sbin/rabbitmqctl -n test_rabbit_3 reset
./sbin/rabbitmqctl -n test_rabbit_3 join_cluster test_rabbit_1@localhost
./sbin/rabbitmqctl -n test_rabbit_3 start_app
```

#### 集群运维

- 停止第2个节点
```cmd
RABBITMQ_NODENAME=test_rabbit_2 ./sbin/rabbitmqctl stop
```

- 节点3的集群状态
```cmd
./sbin/rabbitmqctl -n test_rabbit_3 cluster_status
```
