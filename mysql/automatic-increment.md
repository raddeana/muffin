#### n个最高记录，需要执行以下步骤:
- 得到n个最高记录，并按升序排列。第n个最高记录是结果集中的最后一个记录
- 按顺序对结果集进行排序，并获得第一个结果集

```sql
SELECT 
    productCode, productName, buyPrice
FROM
    products
ORDER BY buyPrice DESC
LIMIT 1 , 1;
```

```sql
SELECT * FROM table_name AS a WHERE n - 1 = (
  SELECT COUNT (primary_key_column)
  FROM products b
  WHERE b.column_name > a.column_name
)
```

```sql
SELECT 
  productCode, productName, buyPrice
FROM
  products a
WHERE
  1 = (SELECT 
      COUNT(productCode)
    FROM
      products b
    WHERE
      b.buyPrice > a.buyPrice);
```
