#### 使用CREATE TABLE语句定义FULLTEXT索引
```sql
CREATE TABLE table_name(
  column1 data_type, 
        column2 data_type,
        column3 data_type, ...

  PRIMARY_KEY (key_column),
  FULLTEXT (column1,column2,..)
);
```

#### 定义现有表的FULLTEXT索引
```sql
ALTER TABLE  table_name  
ADD FULLTEXT(column_name1, column_name2,…)
```

#### 使用CREATE INDEX语句定义FULLTEXT索引
```sql
CREATE FULLTEXT INDEX index_name
ON table_name(idx_column_name, ...)
```

#### 删除全文搜索列
```sql
ALTER TABLE offices
DROP INDEX address;
```
