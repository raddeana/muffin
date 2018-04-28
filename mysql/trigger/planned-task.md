MySQL 事件是基于预定义的时间表运行的任务，因此有时它被称为预定事件
MySQL 事件也被称为“时间触发”，因为它是由时间触发的，而不是像触发器一样更新表来触发的
MySQL 事件类似于UNIX中的cron作业或Windows中的任务调度程序

#### 查看事件调度程序线程的状态
```sql
SHOW PROCESSLIST;
```

#### 启用和启动事件调度程序线程，需要执行以下命令
```sql
SET GLOBAL event_scheduler = ON;
```
```sql
SET GLOBAL event_scheduler = OFF;
```

#### 创建时间
```sql
CREATE EVENT [IF NOT EXIST] event_name
ON SCHEDULE schedule
DO
event_body
```

- 在 CREATE EVENT 子句之后指定事件名称。事件名称在数据库模式中必须是唯一的
- 在 ON SCHEDULE 子句后面加上一个表
- 如果事件是一次性事件，则使用语法: AT timestamp [+ INTERVAL]，
- 如果事件是循环事件，则使用EVERY子句: EVERY interval STARTS timestamp [+INTERVAL] ENDS timestamp [+INTERVAL]
- 将DO语句放在DO关键字之后。请注意，可以在事件主体内调用存储过程
- 如果您有复合SQL语句，可以将它们放在BEGIN END块中

#### 到时间保存
```sql
CREATE EVENT [IF NOT EXIST] event_name
ON SCHEDULE schedule
ON COMPLETION PRESERVE
DO
event_body
```

#### 示例
```sql
CREATE EVENT test_event_02
ON SCHEDULE AT CURRENT_TIMESTAMP + INTERVAL 1 MINUTE
ON COMPLETION PRESERVE
DO
   INSERT INTO messages(message, created_at)
   VALUES('Test MySQL Event 2', NOW());
```

#### 删除 MySQL 事件
```sql
DROP EVENT [IF EXISTS] event_name;
```
