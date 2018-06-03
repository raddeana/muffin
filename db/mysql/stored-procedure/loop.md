#### WHILE 循环
```sql
WHILE expression DO
  statements
END WHILE
```

#### WHILE 循环
```sql
DELIMITER $$
 DROP PROCEDURE IF EXISTS test_mysql_while_loop$$
 CREATE PROCEDURE test_mysql_while_loop ()
 BEGIN
 DECLARE x INT;
 DECLARE str VARCHAR(255);

 SET x = 1;
 SET str = '';

 WHILE x <= 5 DO
 SET str = CONCAT(str,x,',');
 SET x = x + 1; 
 END WHILE;

 SELECT str;
 END$$
DELIMITER ;
```

#### 存储过程中
- 重复构建 str 字符串，直到 x 变量的值大于 5
- 使用 SELECT 语句显示最终的字符串

#### REPEAT 循环
```sql
REPEAT
 statements;
UNTIL expression
END REPEAT
```

```sql
DELIMITER $$
 DROP PROCEDURE IF EXISTS mysql_test_repeat_loop$$
 CREATE PROCEDURE mysql_test_repeat_loop()
 BEGIN
 DECLARE x INT;
 DECLARE str VARCHAR(255);

 SET x = 1;
        SET str =  '';
 REPEAT
 SET  str = CONCAT(str,x,',');
 SET  x = x + 1; 
        UNTIL x  > 5
        END REPEAT;
        SELECT str;
 END$$
DELIMITER ;
```

#### LOOP, LEAVE 和 ITERATE 语句
- LEAVE语句用于立即退出循环, 而无需等待检查条件
- ITERATE语句允许您跳过剩下的整个代码并开始新的迭代

```sql
CREATE PROCEDURE test_mysql_loop()
 BEGIN
 DECLARE x  INT;
        DECLARE str  VARCHAR(255);

 SET x = 1;
        SET str =  '';

 loop_label:  LOOP
 IF  x > 10 THEN 
 LEAVE  loop_label;
 END  IF;

 SET  x = x + 1;
 IF (x mod 2) THEN
     ITERATE  loop_label;
 ELSE
    SET  str = CONCAT(str,x,',');
 END IF;
    END LOOP;    
    SELECT str;
END;
```
