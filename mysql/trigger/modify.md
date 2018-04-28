#### 修改事件
```
ALTER EVENT event_name
ON SCHEDULE schedule
ON COMPLETION [NOT] PRESERVE
RENAME TO new_event_name
ENABLE | DISABLE
DO
  event_body
```

#### SHOW EVENTS FROM testdb
##### ALTER EVENT 示例
```sql
USE testdb;
CREATE EVENT test_event_04
ON SCHEDULE EVERY 1 MINUTE
DO
   INSERT INTO messages(message,created_at)
   VALUES('Test ALTER EVENT statement',NOW());
```

##### 改变调度时间
```sql
ALTER EVENT test_event_04
ON SCHEDULE EVERY 2 MINUTE;
```

##### 改变事件的主体代码逻辑
```sql
ALTER EVENT test_event_04
DO
   INSERT INTO messages(message,created_at)
   VALUES('Message from event',NOW());
-- 清空表中的数据
truncate messages;
```

##### 禁用事件
```sql
ALTER EVENT test_event_04
DISABLE;
```

##### 查看事件的状态
```sql
SHOW EVENTS FROM testdb;
```

##### 启用事件
```sql
ALTER EVENT test_event_04
ENABLE;
```

##### 重命名事件
```sql
ALTER EVENT test_event_04
RENAME TO test_event_05;
```

##### 将事件移动到其他数据库
```sql
ALTER EVENT testdb.test_event_05
RENAME TO newdb.test_event_05;
```
