#### MySQL变量赋值
```sql
SET @variable_name := value;
```

```sql
SET @counter := 100;
```

```sql
SELECT @variable_name := value;
```

#### MySQL变量示例
```sql
SELECT @msrp:=MAX(msrp) FROM products;
select @msrp as max_price;
```

```sql
SELECT
    productCode, productName, productLine, msrp
FROM
    products
WHERE
    msrp = @msrp;
```

```sql
SELECT @id:=LAST_INSERT_ID();
```

```sql
SELECT
    @buyPrice:=buyprice
FROM
    products
WHERE
    buyprice > 95
ORDER BY buyprice;
```

```sql
SELECT @buyprice;
```
