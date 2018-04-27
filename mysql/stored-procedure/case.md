#### 示例
```sql
CASE  case_expression
   WHEN when_expression_1 THEN commands
   WHEN when_expression_2 THEN commands
   ELSE commands
END CASE;
```

```sql
DELIMITER $$
CREATE PROCEDURE GetCustomerShipping(
 in  p_customerNumber int(11), 
 out p_shiping        varchar(50))
BEGIN
  DECLARE customerCountry varchar(50);
  SELECT country INTO customerCountry
  FROM customers
  WHERE customerNumber = p_customerNumber;
    CASE customerCountry
  WHEN  'USA' THEN
    SET p_shiping = '2-day Shipping';
  WHEN 'Canada' THEN
    SET p_shiping = '3-day Shipping';
  ELSE
    SET p_shiping = '5-day Shipping';
  END CASE;
END$$
```

#### 测试脚本
```sql
SET @customerNo = 112;

SELECT country into @country
FROM customers
WHERE customernumber = @customerNo;

CALL GetCustomerShipping(@customerNo,@shipping);

SELECT @customerNo AS Customer,
       @country    AS Country,
       @shipping   AS Shipping;
```
