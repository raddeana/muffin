#### 语法
```sql
CREATE 
   [ALGORITHM = {MERGE  | TEMPTABLE | UNDEFINED}]
VIEW [database_name].[view_name] 
AS
[SELECT  statement]
```

#### 算法
- 使用 MERGE 算法，MySQL首先将输入查询与定义视图的SELECT语句组合成单个查询
- 使用 TEMPTABLE 算法，MySQL首先根据定义视图的SELECT语句创建一个临时表，然后针对该临时表执行输入查询
- 创建视图而不指定显式算法时，UNDEFINED是默认算法

#### SELECT语句
- SELECT语句可以在WHERE子句中包含子查询，但FROM子句中的不能包含子查询
- SELECT语句不能引用任何变量，包括局部变量，用户变量和会话变量
- SELECT语句不能引用准备语句的参数

#### 创建视图
```sql
CREATE VIEW SalePerOrder AS
    SELECT 
        orderNumber, SUM(quantityOrdered * priceEach) total
    FROM
        orderDetails
    GROUP by orderNumber
    ORDER BY total DESC;
```

#### 基于另一个视图创建视图
```sql
CREATE VIEW BigSalesOrder AS
    SELECT 
        orderNumber, ROUND(total,2) as total
    FROM
        saleperorder
    WHERE
        total > 60000;
```

#### 使用连接表创建视图
```sql
CREATE VIEW customerOrders AS
    SELECT 
        c.customerNumber,
        p.amount
    FROM
        customers c
            INNER JOIN
        payments p ON p.customerNumber = c.customerNumber
    GROUP BY c.customerNumber
    ORDER BY p.amount DESC;
```

#### 使用子查询创建视图
```sql
CREATE VIEW aboveAvgProducts AS
  SELECT 
    productCode, productName, buyPrice
  FROM
    products
  WHERE
    buyPrice > 
  (
    SELECT 
      AVG(buyPrice)
    FROM
      products
  )
  ORDER BY buyPrice DESC;
```

```sql
SELECT 
  *
FROM
  aboveAvgProducts;
```

