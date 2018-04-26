#### ORDER BY RAND()
```sql
SELECT 
    *
FROM
    tbl
ORDER BY RAND()
LIMIT 1;
```

#### N个随机记录
```sql
SELECT 
    *
FROM
    table
ORDER BY RAND()
LIMIT N;
```

#### INNER JOIN子句选择随机记录
```sql
SELECT 
  ROUND(RAND() * ( SELECT 
        MAX(id)
    FROM
        table)) as id;
```

```sql
SELECT 
    t.*
FROM
    table AS t
        JOIN
    (SELECT 
        ROUND(RAND() * (SELECT 
          MAX(id)
            FROM
          table )) AS id
    ) AS x
WHERE
    t.id >= x.id
LIMIT 1;
```

#### MySQL使用变量选择随机记录
```sql
SELECT 
    table. *
FROM
    (SELECT 
        ROUND(RAND() * (SELECT 
                    MAX(id)
                FROM
                    table)) random_num,
            @num:=@num + 1
    FROM
        (SELECT @num:=0) AS a, table
    LIMIT N) AS b,
    table AS t
WHERE
    b.random_num = t.id;
```


