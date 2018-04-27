#### CASCADC
#### 无校验
```sql
CREATE OR REPLACE VIEW v1 
AS
    SELECT 
        c
    FROM
        t1
    WHERE
        c > 10;
```

#### 添加校验
```sql
CREATE OR REPLACE VIEW v2 
AS
    SELECT 
        c
    FROM
        v1 
WITH CASCADED CHECK OPTION;
```

#### 校验依然有效
```sql
CREATE OR REPLACE VIEW v3 
AS
    SELECT 
        c
    FROM
        v2
    WHERE
        c < 20;
```

#### local
#### 校验无效
```sql
ALTER VIEW v2 AS
    SELECT 
        c
    FROM
        v1 
WITH LOCAL CHECK OPTION;
```
