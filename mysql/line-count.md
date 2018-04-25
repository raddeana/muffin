#### 获取单个表的MySQL行计数
```sql
SELECT COUNT(*) FROM table_name;
```

#### 获取MySQL两个或多个表的行计数
```sql
SELECT 
    'customers' tablename, 
     COUNT(*) rows
FROM
    customers 
UNION 
SELECT 
    'orders' tablename, 
     COUNT(*) rows
FROM
    orders;
```

请按照以下步骤:
- 获取数据库中的所有表名
```sql
SELECT 
    table_name
FROM
    information_schema.tables
WHERE table_schema = 'yiibaidb' AND table_type = 'BASE TABLE';
```
- 构造一个SQL语句，包含由UNION分隔的所有表的所有SELECT COUNT(*)FROM table_name语句
```sql
SELECT 
    CONCAT(GROUP_CONCAT(CONCAT('SELECT \'',
                        table_name,
                        '\' table_name,COUNT(*) rows FROM ',
                        table_name)
                SEPARATOR ' UNION '),
            ' ORDER BY table_name')
INTO @sql 
FROM
    table_list;
```
查询作为派生表，并以字符串形式返回SQL语句
```sql
WITH table_list AS (
SELECT
    table_name
  FROM information_schema.tables 
  WHERE table_schema = 'yiibaidb' AND
        table_type = 'BASE TABLE'
)
SELECT CONCAT(
  GROUP_CONCAT(CONCAT("SELECT '",table_name,"' table_name,COUNT(*) rows FROM ",table_name) SEPARATOR " UNION "),
  ' ORDER BY table_name'
)
INTO @sql
FROM table_list;
```
- 使用准备语句执行SQL语句
```sql
USE yiibaidb;
PREPARE s FROM  @sql;
EXECUTE s;
DEALLOCATE PREPARE s;
```
- 使用一个查询获取数据库中所有表的MySQL行计数
```sql
SELECT 
    table_name, 
    table_rows
FROM
    information_schema.tables
WHERE
    table_schema = 'yiibaidb'
ORDER BY table_rows desc;
```
