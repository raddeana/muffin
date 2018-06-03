#### 触发器是一组SQL语句，当对相关联的表上的数据进行更改时，会自动调用该语句
#### 每个表最多可以定义六个触发器
- BEFORE INSERT   - 在数据插入表之前被激活触发器
- AFTER INSERT    - 在将数据插入表之后激活触发器
- BEFORE UPDATE   - 在表中的数据更新之前激活触发器
- AFTER UPDATE    - 在表中的数据更新之后激活触发器
- BEFORE DELETE   - 在从表中删除数据之前激活触发器
- AFTER DELETE    - 从表中删除数据之后激活触发器

```sql
(BEFORE | AFTER)_tableName_(INSERT | UPDATE | DELETE)
```

```sql
tablename_(BEFORE | AFTER)_(INSERT | UPDATE | DELETE)
```

#### 触发存储
- tablename.TRG文件将触发器映射到相应的表
- triggername.TRN文件包含触发器定义

#### 触发器不能
- 使用在SHOW，LOAD DATA，LOAD TABLE，BACKUP DATABASE，RESTORE，FLUSH和RETURN语句之上
- 使用隐式或明确提交或回滚的语句，如COMMIT，ROLLBACK，START TRANSACTION，LOCK/UNLOCK TABLES，ALTER，CREATE，DROP，RENAME等
- 使用准备语句，如PREPARE，EXECUTE等
- 使用动态SQL语句
