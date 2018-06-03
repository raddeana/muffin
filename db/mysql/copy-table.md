#### MySQL将表复制到新表
```sql
CREATE TABLE new_table
SELECT col1, col2, col3
FROM
  existing_table
WHERE
  conditions;
```

#### 从表中复制数据以及表的所有依赖对象
```sql
CREATE TABLE IF NOT EXISTS new_table LIKE existing_table;

INSERT new_table
SELECT * FROM existing_table;
```

#### MySQL复制表到另一个数据库
```sql
CREATE TABLE destination_db.new_table;
LIKE source_db.existing_table;

INSERT destination_db.new_table;
SELECT * FROM source_db.existing_table;
```

