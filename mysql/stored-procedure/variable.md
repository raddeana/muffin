#### 声明变量
存储过程中声明一个变量
```sql
DECLARE variable_name datatype(size) DEFAULT default_value;
```

- 在DECLARE关键字后面要指定变量名，变量名必须遵循MySQL表列名称的命名规则
- 指定变量的数据类型及其大小，变量可以有任何MySQL数据类型，如 INT，VARCHAR，DATETIME 等
- 当声明一个变量时，它的初始值为NULL；但是可以使用DEFAULT关键字为变量分配默认值

```sql
DECLARE total_sale INT DEFAULT 0;
DECLARE x, y INT DEFAULT 0;
```

#### 分配变量值
```sql
DECLARE total_count INT DEFAULT 0;
SET total_count = 10;
```

```sql
DECLARE total_products INT DEFAULT 0
SELECT COUNT(*) INTO total_products FROM products
```

- 声明一个名为total_products的变量, 并将其值初始化为0
- 使用 SELECT INTO 语句来分配值给 total_products 变量, 从示例数据库 (yiibaidb) 中的 products 表中选择的产品数量

#### 变量范围 (作用域)
 如果在存储过程中声明一个变量，那么当达到存储过程的END语句时，它将超出范围，因此在其它代码块中无法访问
