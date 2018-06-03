#### 表结构复制
- like
```sql
create table 表名 like [数据库.]表名

-- 如果是同一个数据库下的表的复制，不需要添加[数据库.]
-- 不会复制数据
```
- create
```sql
create table new_table
as
select * from [数据库名.]old_table;

-- 第二种方式在mysql下可能会丢失列属性，如主键，自增等
```

#### 表数据复制
蠕虫复制
```
insert into new_table select * from [数据库.]old_table
```

#### 限制更新记录总数
```
update table_name set [field] = [value] [where 条件] [limit Num]
```

#### 限制删除记录总数
```
delete from table_name [where 条件] [limit Num]
```
