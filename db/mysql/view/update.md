#### MySQL可更新视图
创建可更新视图，定义视图的SELECT语句不能包含以下任何元素:
- 聚合函数
- DISTINCT 子句
- GROUP BY子句
- HAVING 子句
- UNION 或 UNION ALL 子句
- 左连接或外连接
- SELECT子句中的子查询或引用该表的WHERE子句中的子查询出现在FROM子句中
- 引用FROM子句中的不可更新视图
- 仅引用文字值
- 对基表的任何列的多次引用

#### 示例
```sql
CREATE VIEW officeInfo
  AS 
    SELECT officeCode, phone, city
    FROM offices;
```

```sql
SELECT 
  *
FROM
  officeInfo;
```

#### 检查可更新视图信息
```sql
SELECT
    table_name, is_updatable
FROM
    information_schema.views
WHERE
    table_schema = 'yiibaidb';
```

#### 通过视图删除行
```sql
USE testdb;
-- create a new table named items
CREATE TABLE items (
  id INT AUTO_INCREMENT PRIMARY KEY,
  name VARCHAR(100) NOT NULL,
  price DECIMAL(11 , 2 ) NOT NULL
);

-- insert data into the items table
INSERT INTO items(name, price) VALUES('Laptop',700.56), ('Desktop',699.99), ('iPad',700.50) ;

-- create a view based on items table
CREATE VIEW LuxuryItems AS
  SELECT 
    *
  FROM
    items
  WHERE
    price > 700;
-- query data from the LuxuryItems view
SELECT 
  *
FROM
  LuxuryItems;
```

#### DELETE
```sql
DELETE FROM LuxuryItems WHERE id = 3;
```
