#### 将NULL值映射到其他有意义的值
```sql
SELECT 
    customername, IF(state IS NULL, 'N/A', state) state, country
FROM
    customers
ORDER BY country;
```

#### IFNULL函数将NULL显示为未知
```sql
SELECT customername, 
       IFNULL(state, "N/A") state, 
       country
FROM customers
ORDER BY country;
```
