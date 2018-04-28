#### 全文检索
```sql
SELECT productName, productline
FROM products
WHERE MATCH(productName) 
      AGAINST('Truck' IN BOOLEAN MODE)                               // 等价于 AGAINST('Truck')
```

```sql
  SELECT productName, productline
  FROM products
  WHERE MATCH(productName) AGAINST('Truck -Pickup' IN BOOLEAN MODE ); // 排除 Pickup
```

#### 运算符
- +	包括，这个词必须存在。
- -	排除，这个词不能存在。
- >	包括并增加排名值。
- <	包括并降低排名值。
- ()	将单词分组成子表达式(允许将其包括，排除，排序等作为一个组)。
- ~	否定一个词的排名值。
- *	通配符，在结尾的单词
- “”	定义一个短语(与单个单词列表相反，整个短语匹配包含或排除)。

#### 功能
- MySQL 不按照布尔全文搜索中相关性降低的顺序自动排序行
- 要执行布尔查询，InnoDB 表需要 MATCH 表达式的所有列具有 FULLTEXT 索引
- MySQL 在 InnoDB 表上的搜索查询上不支持多个布尔运算符
- InnoDB 全文搜索不支持尾部加号 (+) 或减号 (-) 号
- 不适用 50％ 阈值
