#### 大数据量分页查询
mysql大数据量使用limit分页，随着页码的增大，查询效率越低下
如果对于有where 条件，又想走索引用limit的，必须设计一个索引，将where 放第一位，limit用到的主键放第2位，而且只能select 主键

#### 直接使用数据库提供的SQL语句
- 语句样式: MySQL中,可用如下方法: SELECT * FROM 表名称 LIMIT M,N
- 适应场景: 适用于数据量较少的情况(元组百/千级)
- 原因/缺点: 全表扫描,速度会很慢，且有的数据库结果集返回不稳定(如某次返回1, 2, 3,另外的一次返回2, 1, 3). Limit限制的是从结果集的M位置处取出N条输出，其余抛弃

#### 建立主键或唯一索引，利用索引
- 语句样式: MySQL中,可用如下方法: SELECT * FROM 表名称 WHERE id_pk > (pageNum*10) LIMIT M
- 适应场景: 适用于数据量多的情况(元组数上万)
- 原因: 索引扫描，速度会很快

#### 基于索引再排序
- 语句样式: MySQL中,可用如下方法: SELECT * FROM 表名称 WHERE id_pk > (pageNum*10) ORDER BY id_pk ASC LIMIT M
- 适应场景: 适用于数据量多的情况(元组数上万)
- 原因: 索引扫描，速度会很快. 但MySQL的排序操作，只有ASC没有DESC

#### 基于索引使用prepare
- 语句样式: MySQL中,可用如下方法: PREPARE stmt_name FROM SELECT * FROM 表名称 WHERE id_pk > (？* ？) ORDER BY id_pk ASC LIMIT M
- 适应场景: 大数据量
- 原因: 索引扫描,速度会很快. prepare语句又比一般的查询语句快一点

#### 利用MySQL支持ORDER操作可以利用索引快速定位部分元组，避免全表扫描
```sql
SELECT * FROM your_table WHERE pk>=1000 ORDER BY pk ASC LIMIT 0, 20 
```

#### 利用 "子查询 / 连接 + 索引" 快速定位元组的位置,然后再读取元组
```sql
SELECT * FROM your_table WHERE id <=> 
(SELECT id FROM your_table ORDER BY id desc LIMIT ($page - 1) * $pagesize ORDER BY id desc LIMIT $pagesize
```
```sql
SELECT * FROM your_table AS t1 JOIN (SELECT id FROM your_table ORDER BY id desc LIMIT ($page-1)*$pagesize AS t2 WHERE t1.id <=>
```

#### 测试实验
- 直接用limit start, count分页语句
  - limit语句的查询时间与起始记录的位置成正比
  - mysql的limit语句是很方便，但是对记录很多的表并不适合直接使用
- 对limit分页问题的性能优化方法
- 复合索引优化方法
