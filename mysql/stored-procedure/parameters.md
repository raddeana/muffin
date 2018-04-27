#### 在MySQL中，参数有三种模式：IN，OUT或INOUT
- IN - 是默认模式。在存储过程中定义IN参数时，调用程序必须将参数传递给存储过程
- OUT - 可以在存储过程中更改OUT参数的值，并将其更改后新值传递回调用程序
- INOUT - INOUT参数是IN和OUT参数的组合

#### 语法
```sql
  MODE param_name param_type (param_size)
```
- 根据存储过程中参数的目的，MODE可以是IN，OUT或INOUT
- param_name是参数的名称。参数的名称必须遵循MySQL中列名的命名规则
- 在参数名之后是它的数据类型和大小。和变量一样，参数的数据类型可以是任何有效的MySQL数据类型

#### 示例
- IN
```sql
USE `yiibaidb`;
DROP procedure IF EXISTS `GetOfficeByCountry`;
DELIMITER $$
USE `yiibaidb`$$
CREATE PROCEDURE GetOfficeByCountry(IN countryName VARCHAR(255))
 BEGIN
 SELECT * 
 FROM offices
 WHERE country = countryName;
 END$$
DELIMITER;
```

- OUT
```sql
USE `yiibaidb`;
DROP procedure IF EXISTS `CountOrderByStatus`;
DELIMITER $$
CREATE PROCEDURE CountOrderByStatus(IN orderStatus VARCHAR(25), OUT total INT)
BEGIN
 SELECT count(orderNumber)
 INTO total
 FROM orders
 WHERE status = orderStatus;
END$$
DELIMITER;
```

- INOUT
```sql
DELIMITER $$
CREATE PROCEDURE set_counter(INOUT count INT(4), IN inc INT(4))
BEGIN
 SET count = count + inc;
END$$
DELIMITER;
```
