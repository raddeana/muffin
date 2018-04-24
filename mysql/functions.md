Aggregate:
- AVG() 返回平均值
- COUNT() 返回行数
- FIRST() 返回第一个记录的值
- LAST() 返回最后一个记录的值
- MAX() 返回最大值
- MIN() 返回最小值
- SUM() 返回总和

Scalar:
- UCASE() 将某个字段转换为大写
- LCASE() 将某个字段转换为小写
- MID() 从某个文本字段提取字符, MySql 中使用
- SubString(字段，1，end) 从某个文本字段提取字符
- LEN() 返回某个文本字段的长度
- ROUND() 对某个数值字段进行指定小数位数的四舍五入
- NOW() 返回当前的系统日期和时间
- FORMAT() 格式化某个字段的显示方式

#### exa
```sql
SELECT LEN(column_name) FROM table_name;
```
