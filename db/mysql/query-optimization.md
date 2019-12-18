### 连接查询的优化
- ON、USING字句中的列确认有索引，如果连接的顺序为B、A，那么只需在A表的列上创建索引即可，无需在B中建索引，可以减少不必要索引开销
```sql
SELECT B.*, A.* FROM B JOIN A ON B.col1 = A.col2 
```

#### 使用EXPLAIN 检查连接，看ROWS列，如果该列值太高，比如几千，上万的，那么就需要考虑是否索引无效后者连接表的顺序不对了
- 考虑在应用层实现连接查询
```sql
SELECT a.* FROM A WHERE a.id IN(1,2,3,4,5,6,7,8,9,10);
```

### GROUP BY、DISTINCT、ORDER BY 语句优化
- 如果多张表进行连接查询，ORDER BY 的列应属于连接顺序的第一张表
- 需要保证索引列和ORDER BY的列相同，且各列按照相同的方向进行排序
- 指定ORDER BY NULL：默认情况下，MYSQL将排序所有GROUP BY的查询，如果想要避免排序结果所产生的消耗，可以指定ORDER BY NULL。

```sql
select count(1) from sys_dept group by dept_id order by null limit 3 
```

### 子查询优化
- 对于数据库来说，大部分情况下，连接比子查询更快，优化器一般可以生成更佳的执行计划
- 可以余弦装载数据，更高效的处理查询，子查询生成的临时表也没有索引，因此效率会更低
```sql
SELECT c1 FROM t1 where t1.c1 IN (SELECT c1 FROM t2);
```
```sql
SELECT c1 FROM t1.c1 FROM t1,t2 WHERE t1.c1 = t2.c2 
```

### 优化IN列表
对于IN列表，MySQL会排序里面的值，并使用二分查找方式去定位数据，把IN字句改写成OR形式其实没什么用
```
SELECT * FROM A where A.ID IN(SELECT id FROM B) 
```

### 优化UNION
UNION语句默认是去除重复记录，需要用到排序操作，如果结果集很大，成本会很高，建议尽量使用UNION ALL 语句，对于UNION多个分表场景，应尽可能在数据库分表的时候，就确定各个分表数据唯一性，这样就无需使用UNION来去重了

### 优化BLOB、TEXT类型字段的查询
由于mysql内存临时表暂不支持BLOB、TEXT类型，如果包含他们的查询就要用到基于磁盘的临时表，性能会很低，所以如无必要，查询条件就不要这2种类型
- 如果必须使用，可以考虑拆分表，把BLOB、TEXT字段分离到单独的表中
- 如果有许多大字段，可以考虑合并这些字段到一个字段，存储一个大200KB比存储20个10KB更有效
- 考虑使用COMPRESS（），再存储


