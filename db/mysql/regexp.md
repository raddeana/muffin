#### MySQL允许使用REGEXP运算符在SQL语句中匹配模式
```sql
SELECT
    column_list
FROM
    table_name
WHERE
    string_column REGEXP pattern;
```

#### string_column
- 此语句执行string_column与模式pattern匹配
- string_column中的值与模式pattern匹配，则WHERE子句中的表达式将返回1，否则返回0
- string_column或pattern为NULL，则结果为NULL
- REGEXP运算符之外，可以使用RLIKE运算符，这是REGEXP运算符的同义词
- REGEXP运算符的否定形式是NOT REGEXP
