#### 使用UNION语句来组合两个表中的行
```sql
SELECT t1.pk, t1.c1 FROM t1
UNION ALL
SELECT t2.pk, t2.c1 FROM t2
```

#### 根据需要比较的主键和列分组记录
```sql
SELECT id,title
FROM (
    SELECT id, title FROM t1
    UNION ALL
    SELECT id, title FROM t2
) tbl
GROUP BY id, title
HAVING count(*) = 1
ORDER BY id;
```

