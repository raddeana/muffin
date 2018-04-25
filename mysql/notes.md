#### 注释
#### 从 -- 到行尾
```sql
SELECT * FROM users; -- This is a comment
```

#### 从 -- 到行尾
```sql
SELECT 
    lastName, firstName
FROM
    employees
WHERE
    reportsTo = 1002; # get subordinates of Diane
```

#### 注释/* */可以跨越多行
```sql
/**
 * Get sales rep employees
 * that reports to Anthony
 */

SELECT 
    lastName, firstName
FROM
    employees
WHERE
    reportsTo = 1143
        AND jobTitle = 'Sales Rep';
```

#### 可执行注释
- MySQL提供可执行注释来支持不同数据库之间的可移植性
- 这些注释允许嵌入仅能在MySQL中执行，但不能在其他数据库执行SQL代码

```sql
/*! MySQL-specific code */
```
