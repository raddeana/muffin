#### 为查询缓存优化你的查询
```cmd
// 查询缓存不开启 
$r = mysql_query("SELECT username FROM user WHERE signup_date >= CURDATE()"); 

// 开启查询缓存 
$today = date("Y-m-d"); 
$r = mysql_query("SELECT username FROM user WHERE signup_date >= '$today'"); 
```

#### EXPLAIN 你的 SELECT 查询
使用 EXPLAIN 关键字可以让你知道MySQL是如何处理你的SQL语句的

#### 当只要一行数据时使用 LIMIT 1 
```cmd
// 没有效率的： 
$r = mysql_query("SELECT * FROM user WHERE country = 'China'"); 
if (mysql_num_rows($r) > 0) { 
// ... 
} 

// 有效率的： 
$r = mysql_query("SELECT 1 FROM user WHERE country = 'China' LIMIT 1"); 
if (mysql_num_rows($r) > 0) { 
// ... 
}
```

#### 为搜索字段建索引
索引并不一定就是给主键或是唯一的字段；如果在你的表中，有某个字段你总要会经常用来做搜索，那么，请为其建立索引

#### 在Join表的时候使用相当类型的例，并将其索引
```cmd
// 在state中查找company 
$r = mysql_query("SELECT company_name FROM users 
LEFT JOIN companies ON (users.state = companies.state) 
WHERE users.id = $user_id"); 

// 两个 state 字段应该是被建过索引的，而且应该是相当的类型，相同的字符集。
```

#### 千万不要 ORDER BY RAND() 
```cmd
// 千万不要这样做 
$r = mysql_query("SELECT username FROM user ORDER BY RAND() LIMIT 1"); 

// 这要会更好
$r = mysql_query("SELECT count(*) FROM user"); 
$d = mysql_fetch_row($r); 
$rand = mt_rand(0,$d[0] - 1); 

$r = mysql_query("SELECT username FROM user LIMIT $rand, 1");
```

#### 避免 SELECT * 
```cmd
// 不推荐 
$r = mysql_query("SELECT * FROM user WHERE user_id = 1"); 
$d = mysql_fetch_assoc($r); 
echo "Welcome {$d['username']}"; 

// 推荐 
$r = mysql_query("SELECT username FROM user WHERE user_id = 1"); 
$d = mysql_fetch_assoc($r); 
echo "Welcome {$d['username']}";
```

#### 永远为每张表设置一个ID 
为数据库里的每张表都设置一个ID做为其主键，而且最好的是一个INT型的（推荐使用UNSIGNED），并设置上自动增加的 AUTO_INCREMENT标志

#### 使用 ENUM 而不是 VARCHAR 
ENUM 类型是非常快和紧凑的
在实际上，其保存的是 TINYINT，但其外表上显示为字符串。这样一来，用这个字段来做一些选项列表变得相当的完美

#### 从 PROCEDURE ANALYSE() 取得建议
PROCEDURE ANALYSE() 会让 MySQL 帮你去分析你的字段和其实际的数据，并会给你一些有用的建议

#### 尽可能的使用 NOT NULL 
#### Prepared Statements 
Prepared Statements 可以检查一些你绑定好的变量，这样可以保护你的程序不会受到 "SQL注入式" 攻击

#### 无缓冲的查询 
当脚本中执行一个SQL语句的时候，你的程序会停在那里直到没这个SQL语句返回，然后你的程序再往下继续执行

#### 把IP地址存成 UNSIGNED INT 
程序员都会创建一个 VARCHAR(15) 字段来存放字符串形式的IP而不是整形的IP

#### 固定长度的表会更快 
如果表中的所有字段都是“固定长度”的，整个表会被认为是 "static" 或 "fixed-length"
固定长度的表会提高性能，因为MySQL搜寻得会更快一些，因为这些固定的长度是很容易计算下一个数据的偏移量的，所以读取的自然也会很快

#### 垂直分割
"垂直分割" 是一种把数据库中的表按列变成几张表的方法，这样可以降低表的复杂度和字段的数目，从而达到优化的目的

#### 拆分大的 DELETE 或 INSERT 语句
需要在一个在线的网站上去执行一个大的 DELETE 或 INSERT 查询，你需要非常小心，要避免你的操作让你的整个网站停止相应
```cmd
while (1) { 
  // 每次只做1000条 
  mysql_query("DELETE FROM logs WHERE log_date <= '2009-11-01' LIMIT 1000"); 
  
  if (mysql_affected_rows() == 0) { 
    // 没得可删了，退出！ 
    break; 
  } 
  
  // 每次都要休息一会儿 
  usleep(50000); 
}
```

#### 越小的列会越快 
大多数的数据库引擎来说，硬盘操作可能是最重大的瓶颈

#### 选择正确的存储引擎 
MyISAM 适合于一些需要大量查询的应用，但其对于有大量写操作并不是很好。甚至你只是需要update一个字段，整个表都会被锁起来，而别的进程，就算是读进程都无法操作直到读操作完成。另外，MyISAM 对于 SELECT COUNT(*) 这类的计算是超快无比的。 
InnoDB 的趋势会是一个非常复杂的存储引擎，对于一些小的应用，它会比 MyISAM 还慢。他是它支持“行锁” ，于是在写操作比较多的时候，会更优秀。并且，他还支持更多的高级应用，比如：事务。 

#### 越小的列会越快
对于大多数的数据库引擎来说，硬盘操作可能是最重大的瓶颈

#### 选择正确的存储引擎 
MySQL 中有两个存储引擎 MyISAM 和 InnoDB，每个引擎都有利有弊

#### 使用一个对象关系映射器（Object Relational Mapper） 
#### 小心 "永久链接"





