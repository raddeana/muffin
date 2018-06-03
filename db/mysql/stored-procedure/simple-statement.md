#### GetAllProducts()
```sql
DELIMITER //
 CREATE PROCEDURE GetAllProducts()
   BEGIN
   SELECT * FROM products;
   END //
DELIMITER;
```
- DELIMITER 语句将标准分隔符，分号(;)更改为：//
- 使用 CREATE PROCEDURE 语句创建一个新的存储过程
- BEGIN 和 END 之间的部分称为存储过程的主体


```sql
CREATE PROCEDURE `yiibaidb`.`GetAllProducts`()
BEGIN
    SELECT * FROM yiibaidb.products;
END
```

#### 调用存储过程
```sql
CALL STORED_PROCEDURE_NAME();
```

```sql
CALL GetAllProducts();
```
