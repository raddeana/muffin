#### row_number函数
row_number是一个排序函数，返回一行的顺序号，从第一行的1开始

#### row_number - 为每行添加行号
- 使用会话变量
```sql
SET @row_number = 0;

SELECT
    (@row_number:=@row_number + 1) AS num, firstName, lastName
FROM
    employees
LIMIT 5;
```
- 使用会话变量作为派生表
```
SELECT 
    (@row_number:=@row_number + 1) AS num, firstName, lastName
FROM
    employees,(SELECT @row_number:=0) AS t
LIMIT 5;
```
#### row_number - 为每个组添加行号
```
SELECT 
    @row_number:=CASE
        WHEN @customer_no = customerNumber THEN @row_number + 1
        ELSE 1
    END AS num,
    @customer_no:=customerNumber as CustomerNumber,
    paymentDate,
    amount
FROM
    payments
ORDER BY customerNumber;
```
