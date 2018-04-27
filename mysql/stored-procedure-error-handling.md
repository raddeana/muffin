#### DECLARE HANDLER
```sql
DECLARE action HANDLER FOR condition_value statement;
```

```sql
DECLARE CONTINUE HANDLER FOR SQLEXCEPTION SET has_error = 1;
```

```sql
DECLARE EXIT HANDLER FOR SQLEXCEPTION
  BEGIN
    ROLLBACK;
    SELECT 'An error has occurred, operation rollbacked and the stored procedure was terminated';
  END;
```

```sql
DECLARE CONTINUE HANDLER FOR NOT FOUND SET no_row_found = 1;
```

```sql
DECLARE CONTINUE HANDLER FOR 1062
SELECT 'Error, duplicate key occurred';
```

#### 存储过程中的MySQL处理程序
```sql
USE testdb;
DELIMITER $$
CREATE PROCEDURE insert_article_tags(IN article_id INT, IN tag_id INT)
BEGIN
  DECLARE CONTINUE HANDLER FOR 1062
  SELECT CONCAT('duplicate keys (',article_id,' , ',tag_id,') found') AS msg;

  -- insert a new record into article_tags
  INSERT INTO article_tags (article_id,tag_id)
  VALUES (article_id, tag_id);

  -- return tag count for the article
  SELECT COUNT(*) FROM article_tags;
END$$
DELIMITER ;
```

```sql
CALL insert_article_tags(1, 1);
CALL insert_article_tags(1, 2);
CALL insert_article_tags(1, 3);
```

```sql
CALL insert_article_tags(1, 3);
```
