生成列，此列中的数据是基于预定义的表达式或从其他列计算的
#### MySQL生成列
GENERATED ALWAYS as (expression) 是创建生成列的语法
```sql
DROP TABLE IF EXISTS contacts;

CREATE TABLE contacts (
  id INT AUTO_INCREMENT PRIMARY KEY,
  first_name VARCHAR(50) NOT NULL,
  last_name VARCHAR(50) NOT NULL,
  fullname varchar(101) GENERATED ALWAYS AS (CONCAT(first_name,' ',last_name)),
  email VARCHAR(100) NOT NULL
);
```
```sql
INSERT INTO contacts(first_name,last_name, email)
VALUES('john','doe','john.doe@yiibai.com');
```

#### MySQL生成列的语法
```sql
INSERT INTO contacts(first_name,last_name, email)
VALUES('john','doe','john.doe@yiibai.com');
```

#### 示例
可以使用以下ALTER TABLE … ADD COLUMN语句将名为stock_value的存储的生成列添加到products
```sql
ALTER TABLE products
ADD COLUMN stockValue DOUBLE 
GENERATED ALWAYS AS (buyprice*quantityinstock) STORED;
```

- ALTER TABLE语句需要完整的表重建，因此，如果更改大表是耗时的。 但是，虚拟列并非如此
- 我们可以直接从products表中查询库存值

ALTER TABLE语句需要完整的表重建，因此，如果更改大表是耗时的
```sql
SELECT 
    productName, ROUND(stockValue, 2) AS stock_value
FROM
    products;
```


