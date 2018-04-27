#### 显示存储过程字符
```sql
SHOW PROCEDURE STATUS [LIKE 'pattern' | WHERE expr];
```

```sql
SHOW PROCEDURE STATUS;
```

```sql
SHOW PROCEDURE STATUS WHERE db = 'yiibaidb';
```

```sql
SHOW PROCEDURE STATUS WHERE name LIKE '%product%'
```

#### 显示存储过程的源代码
```sql
SHOW CREATE PROCEDURE stored_procedure_name
```

```sql
SHOW CREATE PROCEDURE GetAllProducts;
```
