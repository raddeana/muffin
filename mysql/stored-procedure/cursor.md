#### MySQL游标
```sql
DECLARE cursor_name CURSOR FOR SELECT_statement;
```

```sql
OPEN cursor_name;
```

```sql
FETCH cursor_name INTO variables list;
```

```sql
CLOSE cursor_name;
```

```sql
DECLARE CONTINUE HANDLER FOR NOT FOUND SET finished = 1;
```

#### 示例
```sql
DECLARE finished INTEGER DEFAULT 0;
DECLARE email varchar(255) DEFAULT "";

-- declare cursor for employee email
DEClARE email_cursor CURSOR FOR 
 SELECT email FROM employees;

-- declare NOT FOUND handler
DECLARE CONTINUE HANDLER 
FOR NOT FOUND SET finished = 1;
```

```sql
OPEN email_cursor;
```

```sql
CLOSE email_cursor;
```

```sql
DELIMITER $$

CREATE PROCEDURE build_email_list (INOUT email_list varchar(4000))
BEGIN
 DECLARE v_finished INTEGER DEFAULT 0;
        DECLARE v_email varchar(100) DEFAULT "";
        
 -- declare cursor for employee email
 DEClARE email_cursor CURSOR FOR 
 SELECT email FROM employees;

 -- declare NOT FOUND handler
 DECLARE CONTINUE HANDLER 
        FOR NOT FOUND SET v_finished = 1;

 OPEN email_cursor;
 get_email: LOOP

 FETCH email_cursor INTO v_email;

 IF v_finished = 1 THEN 
 LEAVE get_email;
 END IF;

 -- build email list
 SET email_list = CONCAT(v_email,";",email_list);
 END LOOP get_email;
 CLOSE email_cursor;
END$$
DELIMITER ;
```

build_email_list
```sql
  SET @email_list = "";
  CALL build_email_list(@email_list);
  SELECT @email_list;
```
