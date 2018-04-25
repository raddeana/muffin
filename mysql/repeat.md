#### 在一列中找到重复的值
```sql
SELECT 
    col, 
    COUNT(col)
FROM
    table_name
GROUP BY col
HAVING COUNT(col) > 1;
```

#### 查询在contacts表中查找具有重复email的所有行
```sql
SELECT 
    email, 
    COUNT(email)
FROM
    contacts
GROUP BY email
HAVING COUNT(email) > 1;
```

#### 在多个列中查找重复值
```sql
SELECT 
    col1, COUNT(col1),
    col2, COUNT(col2),
    ...

FROM
    table_name
GROUP BY 
    col1, 
    col2, ...
HAVING 
       (COUNT(col1) > 1) AND 
       (COUNT(col2) > 1) AND 
       ...
```

```sql
SELECT 
    first_name, COUNT(first_name),
    last_name,  COUNT(last_name),
    email,      COUNT(email)
FROM
    contacts
GROUP BY 
    first_name , 
    last_name , 
    email
HAVING  COUNT(first_name) > 1
    AND COUNT(last_name) > 1
    AND COUNT(email) > 1;
SQL
```
