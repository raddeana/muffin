#### MySQL存储函数语法
```sql
CREATE FUNCTION function_name(param1,param2,…)
    RETURNS datatype
   [NOT] DETERMINISTIC
 statements
```

#### MySQL存储函数示例
```sql
DELIMITER $$
CREATE FUNCTION CustomerLevel(p_creditLimit double) RETURNS VARCHAR(10)
  DETERMINISTIC
BEGIN
  DECLARE lvl varchar(10);
  IF p_creditLimit > 50000 THEN
    SET lvl = 'PLATINUM';
  ELSEIF (p_creditLimit <= 50000 AND p_creditLimit >= 10000) THEN
    SET lvl = 'GOLD';
  ELSEIF p_creditLimit < 10000 THEN
    SET lvl = 'SILVER';
  END IF;
 RETURN (lvl);
END $$
DELIMITER ;
```

```sql
SELECT 
    customerName, CustomerLevel(creditLimit)
FROM
    customers
ORDER BY customerName;
```

```sql
DELIMITER $$
CREATE PROCEDURE GetCustomerLevel(
  IN  p_customerNumber INT(11),
  OUT p_customerLevel varchar(10)
)
BEGIN
  DECLARE creditlim DOUBLE;
  SELECT creditlimit INTO creditlim FROM customers WHERE customerNumber = p_customerNumber;
  SELECT CUSTOMERLEVEL (creditlim) 
  INTO p_customerLevel;
END $$
DELIMITER ;
```

#### MySQL存储函数语法
- 在 CREATE FUNCTION 子句之后指定存储函数的名称
- 列出括号内存储函数的所有参数
- 必须在 RETURNS 语句中指定返回值的数据类型
- 对于相同的输入参数，如果存储的函数返回相同的结果，这样则被认为是确定性的，否则存储的函数不是确定性的
- 将代码写入存储函数的主体中

