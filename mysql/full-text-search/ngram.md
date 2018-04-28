#### ngram全文解析器
MySQL 内置的全文解析器使用空格确定单词的开始和结束。当涉及汉语，日语或韩语等表意语言语言时，这是一个限制，因为这些语言不使用分词符
ngram 全文解析器的主要功能是将文本序列标记为 n 个字符的连续序列

```
n = 1: 'm','y','s','q','l'
n = 2: 'my', 'ys', 'sq','ql'
n = 3: 'mys', 'ysq', 'sql'
n = 4: 'mysq', 'ysql'
n = 5: 'mysql'
```

#### 使用 ngram 解析器创建FULLTEXT索引
要创建使用ngram全文解析器的FULLTEXT索引，可以在CREATE TABLE，ALTER TABLE或CREATE INDEX语句中添加WITH PARSER ngram

##### 创建 
```sql
USE testdb;
CREATE TABLE posts (
    id INT PRIMARY KEY AUTO_INCREMENT,
    title VARCHAR(255),
    body TEXT,
    FULLTEXT ( title , body ) WITH PARSER NGRAM
)  ENGINE = INNODB CHARACTER SET UTF8;
```

##### posts表中插入一个新行
```sql
SET NAMES utf8;

INSERT INTO posts(title,body)
VALUES('MySQL全文搜索','MySQL提供了具有许多好的功能的内置全文搜索'),
      ('MySQL教程','学习MySQL快速，简单和有趣');
```

##### 查看ngram如何标记文本
```sql
SET GLOBAL innodb_ft_aux_table="testdb/posts";

SELECT 
    *
FROM
    information_schema.innodb_ft_index_cache
ORDER BY doc_id, position;
```

##### ngram_token_size
```
mysqld --ngram_token_size=1
```

```
[mysqld]
ngram_token_size=1
```

#### 解析器短语搜索
MySQL 将短语搜索转换成 ngram 短语搜索

```
SELECT 
    id, title, body
FROM
    posts
WHERE
    MATCH (title , body) AGAINST ('搜索' );
```
