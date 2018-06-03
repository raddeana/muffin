#### 查询返回 contacts 表中的重复 email 值
```sql
SELECT 
    email, COUNT(email)
FROM
    contacts
GROUP BY email
HAVING COUNT(email) > 1;
```

#### 使用DELETE JOIN语句删除重复的行
```sql
DELETE t1 FROM contacts t1
        INNER JOIN
    contacts t2 
WHERE
    t1.id < t2.id AND t1.email = t2.email;
```

#### 使用直接表删除重复的行
- 创建一个新表，其结构与要删除重复行的原始表相同
```
CREATE TABLE source_copy FROM source;
```

- 将原始表中的不同行插入直接表
```
INSERT INTO source_copy
SELECT * FROM source
GROUP BY col; -- column that has duplicate values
```

- 删除原始表并将直接表重命名为原始表
```
DROP TABLE source;
ALTER TABLE source_copy RENAME TO source;
```

