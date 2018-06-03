#### 触发器的位置
```sql
/data_folder/database_name/table_name.trg
```

#### SHOW TRIGGERS 返回以下列
- Trigger: 存储触发器的名称
- Event: 指定事件
- Table: 指定触发器与例如相关联的表
- Statement: 存储调用触发器时要执行的语句或复合语句
- Timing: 接受两个值：BEFORE和AFTER，它指定触发器的激活时间
- Created: 在创建触发器时记录创建的时间
- sql_mode: 指定触发器执行时的SQL模式
- Definer: 记录创建触发器的帐户


#### 删除触发器
```sql
DROP TRIGGER table_name.trigger_name;
```

