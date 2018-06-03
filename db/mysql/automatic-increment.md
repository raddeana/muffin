#### 新建设置
```sql
USE testdb;
CREATE TABLE tmp (
  id int(11) NOT NULL AUTO_INCREMENT,
  name varchar(45) DEFAULT NULL,
  PRIMARY KEY (id)
);
```

#### 修改设置
```sql
ALTER TABLE table_name AUTO_INCREMENT = value;
```

#### 删除设置
```sql
DELETE FROM tmp  WHERE ID = 3;
```

#### 重置 1
```sql
ALTER TABLE tmp AUTO_INCREMENT = 3;
```

#### 重置 2
```sql
TRUNCATE TABLE table_name;
```

#### 重置为 0
```sql
DROP TABLE table_name
CREATE TABLE table_name(...)
```
