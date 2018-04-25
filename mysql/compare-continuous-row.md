#### Inventory的表，其中包含由CREATE TABLE语句定义的结构
```sql
USE testdb;
CREATE TABLE inventory(
  id INT AUTO_INCREMENT PRIMARY KEY,
  counted_date date NOT NULL,
  item_no VARCHAR(20) NOT NULL,
  qty int(11) NOT NULL
);
```

库存(inventory)表中:
- id 是自动增量列
- count_date 是计数日期
- item_no 是发布到广告资源的商品代码
- qty 是库存中累计的现货数量

#### 使用自连接技术来比较连续的行
```sql
SELECT
    g1.item_no,
    g1.counted_date from_date,
    g2.counted_date to_date,
    (g2.qty - g1.qty) AS receipt_qty
FROM
    inventory g1
        INNER JOIN
    inventory g2 ON g2.id = g1.id + 1
WHERE
    g1.item_no = 'A';
```
