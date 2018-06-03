#### 允许为表中的相同事件和动作时间创建多个触发器。当事件发生时，触发器将依次激活
- FOLLOWS 选项允许新触发器在现有触发器之后激活
- PRECEDES 选项允许新触发器在现有触发器之前激活

```sql
DELIMITER $$
CREATE TRIGGER  trigger_name
[BEFORE|AFTER] [INSERT | UPDATE | DELETE] ON table_name
FOR EACH ROW [FOLLOWS | PRECEDES] existing_trigger_name
BEGIN
END$$
DELIMITER ;
```

```sql
DELIMITER $$

CREATE TRIGGER before_products_update
  BEFORE UPDATE ON products
  FOR EACH ROW
BEGIN
  INSERT INTO price_logs (product_code, price)
  VALUES (old.productCode,old.msrp);
END$$

DELIMITER ;
```

```sql
DELIMITER $$
CREATE TRIGGER before_products_update_2 
   BEFORE UPDATE ON products 
   FOR EACH ROW FOLLOWS before_products_update
BEGIN
   INSERT INTO user_change_logs (product_code, updated_by)
   VALUES (old.productCode, user());
END$$

DELIMITER ;
```

#### 触发器顺序
```sql
SHOW TRIGGERS FROM yiibaidb;
```
