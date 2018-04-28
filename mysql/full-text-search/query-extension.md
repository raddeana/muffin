#### 全文搜索引擎将执行以下步骤:
- MySQL全文搜索引擎会查找与搜索查询匹配的所有行
- 它检查搜索结果中的所有行，并找到相关词
- 它再次执行搜索，但是基于相关词而不是用户提供的原始关键词来查询匹配


要使用查询扩展，请在AGAINST()函数中使用WITH QUERY EXPANSION搜索修饰符
```sql
SELECT column1, column2
FROM table1
WHERE MATCH (column1, column2)
      AGAINST ("keyword", WITH QUERY EXPANSION);
```

根据匹配的结果扩展查询结果
