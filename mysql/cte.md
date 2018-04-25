#### CTE
公用表表达式是一个命名的临时结果集，仅在单个SQL语句(例如SELECT，INSERT，UPDATE或DELETE)的执行范围内存在

#### CTE语法
CTE的结构包括名称，可选列列表和定义CTE的查询。 定义CTE后，可以像SELECT，INSERT，UPDATE，DELETE或CREATE VIEW语句中的视图一样使用它
```sql
WITH cte_name (column_list) AS (query)
SELECT * FROM cte_name;
```

#### MySQL CTE示例
CTE查询示例数据库中的customers表中的数据
```sql
WITH customers_in_usa AS (
  SELECT 
    customerName, state
  FROM
    customers
  WHERE
    country = 'USA'
)

SELECT
    customerName
 FROM
    customers_in_usa
 WHERE
    state = 'CA'
 ORDER BY customerName;
```

#### 另外一个例子
```sql
WITH topsales2013 AS (
    SELECT 
        salesRepEmployeeNumber employeeNumber,
        SUM(quantityOrdered * priceEach) sales
    FROM
        orders
            INNER JOIN
        orderdetails USING (orderNumber)
            INNER JOIN
        customers USING (customerNumber)
    WHERE
        YEAR(shippedDate) = 2013
            AND status = 'Shipped'
    GROUP BY salesRepEmployeeNumber
    ORDER BY sales DESC
    LIMIT 5
)

SELECT 
    employeeNumber, firstName, lastName, sales
FROM
    employees
        JOIN
    topsales2013 USING (employeeNumber);
```

#### 更高级的 MySQL CTE 示例
```sql
WITH salesrep AS (
    SELECT 
        employeeNumber,
        CONCAT(firstName, ' ', lastName) AS salesrepName
    FROM
        employees
    WHERE
        jobTitle = 'Sales Rep'
),
customer_salesrep AS (
    SELECT 
        customerName, salesrepName
    FROM
        customers
            INNER JOIN
        salesrep ON employeeNumber = salesrepEmployeeNumber
)

SELECT 
    *
FROM
    customer_salesrep
ORDER BY customerName;
```

#### WITH子句用法
```sql
WITH ... SELECT ...
WITH ... UPDATE ...
WITH ... DELETE ...
```

```sql
SELECT ... WHERE id IN (WITH ... SELECT ...)
SELECT * FROM (WITH ... SELECT ...) AS derived_table
```

```sql
CREATE TABLE ... WITH ... SELECT ...
CREATE VIEW ... WITH ... SELECT ...
INSERT ... WITH ... SELECT ...
REPLACE ... WITH ... SELECT ...
DECLARE CURSOR ... WITH ... SELECT ...
EXPLAIN ... WITH ... SELECT ...
```
