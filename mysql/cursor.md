#### 具有以下特殊功能
- 使用CREATE TEMPORARY TABLE语句创建临时表。请注意，在CREATE和TABLE关键字之间添加TEMPORARY关键字
- 当会话结束或连接终止时，MySQL会自动删除临时表。当您不再使用临时表时，也可以使用DROP TABLE语句来显式删除临时表
- 一个临时表只能由创建它的客户机访问。不同的客户端可以创建具有相同名称的临时表，而不会导致错误，因为只有创建临时表的客户端才能看到它。 
- 在同一个会话中，两个临时表不能共享相同的名称
- 临时表可以与数据库中的普通表具有相同的名称。 例如，如果在示例数据库(yiibaidb)中创建一个名为employees的临时表，则现有的employees表将变得无法访问
- 对employees表发出的每个查询现在都是指employees临时表。 当删除您临时表时，永久employees表可以再次访问

#### 创建
```sql
CREATE TEMPORARY TABLE top10customers
SELECT p.customerNumber, 
       c.customerName, 
       FORMAT(SUM(p.amount),2) total
FROM payments p
INNER JOIN customers c ON c.customerNumber = p.customerNumber
GROUP BY p.customerNumber
ORDER BY total DESC
LIMIT 10;
```

#### 查询
```sql
SELECT * FROM top10customers;
```
#### 删除
```sql
DROP TEMPORARY TABLE table_name;
```

#### 在一些情况下，服务器会在处理 query 的时候创建内部临时表
- 位于内存中，使用 MEMORY 存储引擎 (内存临时表)
- 位于磁盘上，使用 MyISAM 存储引擎 (磁盘临时表)

- ORDER BY 子句和 GROUP BY 子句不同，
  - ORDERY BY price GROUP BY name；

- 在 JOIN 查询中，ORDER BY 或者 GROUP BY 使用了不是第一个表的列
  - SELECT * from TableA, TableB ORDER BY TableA.price GROUP by TableB.name

- ORDER BY 中使用了 DISTINCT 关键字
  - ORDERY BY DISTINCT(price)

- SELECT 语句中指定了 SQL_SMALL_RESULT 关键字
  - SQL_SMALL_RESULT 的意思就是告诉 MySQL，结果会很小，请直接使用内存临时表，不需要使用索引排序
  - SQL_SMALL_RESULT 必须和 GROUP BY、DISTINCT 或 DISTINCTROW 一起使用
  - 一般情况下，我们没有必要使用这个选项，让 MySQL 服务器选择即可

- 由 FROM 语句中的子查询产生的派生表
- 由于子查询或者 semi-join materialization 所创建的表

#### 直接使用磁盘临时表的场景
- 表包含 TEXT 或者 BLOB 列
- GROUP BY 或者 DISTINCT 子句中包含长度大于 512 字节的列
- 使用 UNION 或者 UNION ALL 时，SELECT 子句中包含大于 512 字节的列

#### 临时表相关配置
- tmp_table_size: 指定系统创建的内存临时表最大大小
- max_heap_table_size: 指定用户创建的内存表的最大大小

#### mysql 复制和临时表 temporary table

#### 复制和临时表
当临时表打开时，不要直接停止 slave 服务：
- 使用 stop slave sql_thread 语句
- 使用 show status 查看 Slave_open_temp_tables 的值
- 如果这个值不是 0 ，使用 start slave sql_thread 重启从库 SQL 线程，一会儿后再重复执行这个步骤
- 当这个值是 0 时，使用 mysqladmin shutdown 命令停止 slave

所有的临时表都是被复制的，无论是否匹配 --replicate-do-db
--replicate-do-table 或者 --replicate-wild-do-table
复制临时表都会发生 
--replicate-ignore-table 和 --replicate-wild-ignore-table 两个选项是用来忽略临时表的

#### master端配置
```
[mysqld]
  #Master start
  #日志输出地址 主要同步使用
  log-bin=/var/log/mysql/updatelog
  #同步数据库
  binlog-do-db=cnb
  #主机id 不能和从机id重复
  server-id=1
  #Master end
```

#### slave端配置
```
[mysqld]
  #Slave start
  #从机id，区别于主机id
  server-id=2
  
  #主机ip，供从机连接主机用
  master-host=192.168.0.24
  
  #主机端口
  master-port=3307
  
  #刚才为从机复制主机数据新建的账号
  master-user=slave
  
  #刚才为从机复制主机数据新建的密码
  master-password=123456
  
  #重试间隔时间10秒
  master-connect-retry=10
  
  #需要同步的数据库
  replicate-do-db=cnb
  
  #启用从库日志，这样可以进行链式复制
  log-slave-updates
  
  #从库是否只读，0表示可读写，1表示只读
  read-only=1   

  #只复制某个表
  #replicate-do-table=tablename
  
  #只复制某些表（可用匹配符）
  #replicate-wild-do-table=tablename%
  
  #只复制某个库
  #replicate-do-db=dbname
  
  #不复制某个表
  #replicate-ignore-table=tablename
  
  #不复制某些表
  #replicate-wild-ignore-table=tablename%
  
  #不复制某个库
  #replicate-ignore-db=dbname
  #Slave end
```

#### 基于mysql主从复制测试对临时表和内存表的支持
临时表测试:
- 在主服务器上
  - 创建临时表 tmp1
    ```sql
      create temporary table tmp1(id int not null)
    ```
  - 插入数据
    ```sql
      insert into tmp1(id) values(26)
    ```
  - 查看数据
    ```sql
      select * from tmp1
    ```
- 从服务器上查看
  - 从服务器连接主服务器的状态是否正常
  ```sql
    show slave status\G
  ```
  - 查看是否同步了临时表
  ```sql
    select * from tmp1;
  ```
- 在主服务器上删除 tmp1 表
  ```sql
    drop table tmp1;
  ```

#### 内存表测试:
- 主服务器上操作：
  - 创建内存表 tmp_test2
    ```sql
      CREATE TABLE tmp_test2 (
        Id int(11) AUTO_INCREMENT,
        name varchar(255)
      ) ENGINE = MEMORY;
    ```
  - 插入数据
    ```sql
      insert into tmp_test2(id) values(10);
    ```
  - 查看数据
    ```sql
      select * from tmp_test2;
    ```
- 在从服务器上查看状态
  - 从服务器连接主服务器状态是否正常
  ```sql
    show slave status\G
  ```
  - 查看数据
  ```sql
    select * from tmp_test2
  ```
  - 在主服务器上删除 tmp_test2 表
  ```sql
    drop table tmp_test2
  ```
  
#### 临时表在MySQL的复制中的处理
- 执行 STOP SLAVE 语句
- 使用 SHOW STATUS 检查 slave_open_temp_tables 变量的值
- 如果值为 0，使用 mysqladmin shutdown 命令关闭从服务器
- 如果值不为 0，用 START SLAVE 重启从服务器线程
- 后面再重复该程序看下次的运气是否好一些

