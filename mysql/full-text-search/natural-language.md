#### MATCH () 函数指定要搜索的列，AGAINST () 函数确定要使用的搜索表达式

#### 启用
```sql
ALTER TABLE products 
ADD FULLTEXT(productline);
```

#### 如下查询
```sql
SELECT productName, productline
FROM products
WHERE MATCH (productline) AGAINST ("Classic");
```

#### 
```sql
```

#### 重点
- MySQL全文搜索引擎中定义的搜索项的最小长度为 4，这意味着如果搜索长度小于 4 的关键字，例如 car，cat 等，则不会得到任何结果
- 停止词被忽略，MySQL 定义了 MySQL 源代码分发 storage/myisam/ft_static.c 中的停止词列表
