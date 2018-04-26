### 数学函数:
- ABS(X)	返回X的绝对值
- PI()	返回圆周率，默认显示小数点后6位
- SQRT(X)	返回X的平方根
- MOD(X, Y)	返回X被Y除后的余数
- CEIL(X)	返回不小于X的最小整数值
- CEILING(X)	返回不小于X的最小整数值
- FLOOR(X)	返回不大于X的最大整数值
- RAND()	产生随机数
- RAND(X)	产生随机数，若X参数相同，多次执行，产生的随机数相同
- ROUND(X)	返回对X进行四舍五入操作后的整数值
- ROUND(X, Y)	对X进行四舍五入操作，其值保留到小数点后Y位，若Y为负，则保留到小数点左边Y位
- SIGN(X)	返回X的符号，负则返回-1，零则返回0，正则返回1
- POW(X, Y)	返回X的Y次幂
- POWER(X, Y)	返回X的Y次幂
- EXP(X)	返回e的X次幂
- LOG(X)	返回X的自然对数
- LOG10(X)	返回X的基数为10的对数
- RADIANS(X)	角度转化为弧度
- DEGREES(X)	弧度转化为角度
- SIN(X)	正弦函数
- ASIN(X)	正弦函数的反函数
- COS(X)	余弦函数
- ACOS(X)	余弦函数的反函数
- TAN(X)	正切函数
- ATAN(X)	正切函数的反函数
- COT(X)	余切函数

### 字符串函数:
- CHAR_LENGTH(str) 计算字符串str的字符个数
- CONCAT(s1, s2) 拼接s1, s2
- CONCAT_WS(x, s1, s2) 使用分隔符x将s1, s2拼接起来
- INSERT(s1, x, len, s2) 返回字符串s1，其子字符串起始于x位置和被字符串s2取代的len字符
- LOWER(str) 大写字母转为小写
- LCASE(str) 大写字母转为小写
- UPPER(str) 小写字母转为大写
- UCASE(str) 小写字母转为大写
- LEFT(s, n) 返回字符串s左边n个字符组成的子串
- RIGHT(s, n) 返回字符串s右边n个字符组成的子串
- LPAD(s1, len, s2) 返回字符串s1,其左边被字符串s2填补至len字符长度
- RPAD(s1, len, s2) 返回字符串s1,其右边被字符串s2填补至len字符长度
- LTRIM(s)	删除字符串s左端的空格
- RTRIM(s)	删除字符串s右端的空格
- TRIM(s)	删除字符串s两端的空格
- TRIM(s1 FROM s)	删除字符串s中两端所有的字串s1,未指定s1时默认为空格
- REPEEAT(s, n)	返回n个字符串s拼接成的字符串
- SPACE(n) 返回一个由n个空格组成的字符串
- REPLACE(s, s1, s2) 使用字符串s2替换s中所有的s1
- STRCMP(s1, s2) 字符串比较
- SUBSTRING(s, n, len) 返回字符串s中从n开始长度为len的子串
- MID(s, n, len) 返回字符串s中从n开始长度为len的子串
- LOCATE(str1, str)	返回str1在字符串str中的位置
- POSITION(str1 IN str)	返回str1在字符串str中的位置
- INSTR(str, str1) 返回str1在字符串str中的位置
- REVERSE(s) 返回反转后的字符串
- ELT(n, s1, s2) 返回s1, s2, …中第n个字符串
- FIELD(s, s1, s2) 返回字符串s在s1, s2中所在的位置
- FIND_IN_SET(s1, s2) 返回字符串s1在字符串列表s2中的位置
- MAKE_SET(x, s1, s2) 返回由x的二进制数指定的相应位的字符串组成的字符串

### 日期和时间函数
- CURDATE()	返回当前日期
- CURRENT_DATE() 返回当前日期
- CURTIME()	返回当前时间
- CURRENT_TIME() 返回当前时间
- CURRENT_TIMESTAMP()	返回当前日期和时间组合
- LOCALTIME()	返回当前日期和时间组合
- NOW()	返回当前日期和时间组合
- SYSDATE()	返回当前日期和时间组合
- UNIX_TIMESTAMP() 返回Unix时间戳，1970年之后的秒数
- UNIX_TIMESTAMP(date) 返回Unix时间戳，1970年之后的秒数
- FROM_UNIXTIME(date) 把Unix格式时间戳转化为普通格式时间
- UTC_DATE() 返回当前UTC日期值（世界标准时间）
- UTC_TIME() 返回当前UTC时间值
- MONTH(date)	返回date对应的月份，1-12
- MONTHNAME(date)	返回日期date对应月份的英文名
- DAYNAME(d) 返回日期d对应的英文名称，例如Sunday,Monday等
- DAYOFWEEK(d) 返回日期d对应一周中的第几天，1表示周日，2表示周一，7表示周六
- WEEKDAY(d) 返回日期d对应一周中的第几天，0表示周一，1表示周二，6表示周日
- WEEK(d) 日期d是一年中的第几周
- WEEK(d, mod) 返回日期d是一年中的第几周，mod可以决定一周是从周几开始的
- WEEKOFYEAR(d) 返回某天位于一年中的第几周
- DAYOFYEAR(d) 返回日期d是一年中的第几天
- DAYOFMONTH(d) 返回日期d是当月中的第几天
- YEAR(date) 返回date对应的年份
- QUARTER(date) 返回date在一年中的第几季度
- MINUTE(time) 返回time中的分钟数
- SECOND(time) 返回time中的秒数
- EXTRACT(type FROM date) 提取date中的一部分
- TIME_TO_SEC(time) 将time转化为秒数
- SEC_TO_TIME(seconds) 将秒数转为时分秒形式的时间
- DATE_FORMAT(date, format)	将日期时间格式化

### 条件判断函数、加密解密函数、系统信息函数
- IF(expr, v1, v2) 如果表达式expr是TRUE，返回v1；否则返回v2
- IFNULL(v1, v2) 如果v1不为NULL，返回v1；否则返回v2
- CASE expr WHEN v1 THEN r1 [WHEN v2 THEN r2] [ELSE rn] END	case语句
- VERSION() 返回MySQL服务器版本
- CONNECTION_ID() 返回Mysql服务器当前连接的次数
- DATABASE() 返回使用utf8字符集的默认数据库名
- SCHEMA() 返回使用utf8字符集的默认数据库名
- USER() 返回当前被MYsql服务器验证的用户名和主机名组合
- CURRENT_USER() 返回当前被MYsql服务器验证的用户名和主机名组合
- SYSTEM_USER() 返回当前被MYsql服务器验证的用户名和主机名组合
- SESSION_USER() 返回当前被MYsql服务器验证的用户名和主机名组合
- CHARSET(str) 返回字符串str使用的字符集
- COLLATION(str) 返回字符串str的字符排列方式
- LAST_INSERT_ID() 返回最后一个INSERT或UPDATE或AUTO_INCREMENT列设置的第一个发生的值
- PASSWORD(str) 加密函数
- MD5(str) 计算字符串的MD5 128比特校验和
- ENCODE(str, pswd_str) 加密函数
- DECODE(crypt_str, pswd_str) 解密函数
- FORMAT(x, n) 将数值x保留小数点后n位，结果以字符串形式返回
- CONV(n, from_basem, to_base) 将数值n，从一种进制转化为另一种进制
- INET_ATON(expr) 将字符串网络地址转化为整型
- INET_NTOA(expr) 将数值网络地址转化为字符串网络地址
- GET_LOCK(str, timeout) 获取一个锁
- RELEASE_LOCK(str) 释放锁
- IS_FREE_LOCK(str) 检查锁str是否可以被使用
- IS_USED_LOCK(str) 检查锁str是否正在被使用
- BENCHMARK(count, expr) 重复执行表达式expr，执行count次
- CONVERT(str USING type) 转化字符串str的编码格式
- CAST(x AS type) 将x转化为type类型
- CONVERT(x, type) 将一个类型的x转化为另一种类型

### eg
```sql
SELECT LEN(column_name) FROM table_name;
```

```sql
MIN(DISTINCT expression);
```

```sql
SELECT 
    MIN(buyPrice)
FROM
    products;
```

```sql
SELECT 
  productCode, productName, buyPrice
FROM
  products
WHERE
  buyPrice = (
    SELECT 
      MIN(buyPrice)
    FROM
      products
  );
```

### MySQL MIN与GROUP BY
```sql
SELECT 
  productline, MIN(buyprice)
FROM
  products
GROUP BY productline;
```

```sql
SELECT 
  productline, MIN(buyprice)
FROM
  products
GROUP BY productline;
```

### MySQL MIN与相关子查询
```sql
SELECT 
  productline, productCode, productName, buyprice
FROM
  products a
WHERE
  buyprice = (
    SELECT 
      MIN(buyprice)
    FROM
      products b
    WHERE
      b.productline = a.productline
  );
```

```sql
SELECT 
  a.productline, a.productCode, a.productName, a.buyprice
FROM
  products a
    LEFT JOIN
  products b ON a.productline = b.productline
    AND b.buyprice < a.buyprice
WHERE
  b.productcode IS NULL;
```
