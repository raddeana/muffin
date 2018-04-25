#### MySQL UUID
UID代表通用唯一标识符。UUID是基于 "RFC 4122" 通用唯一标识符 (UUID) URN命名空间定义的
UUID被设计为在空间和时间全球独一无二的数字
预期两个UUID值是不同的，即使它们在两个独立的服务器上生成

#### UUID值是一个128位的数字，表示为以下格式的十五进制数字的utf8字符串:
```sql
aaaaaaaa-bbbb-cccc-dddd-eeeeeeeeeeee
```

#### 要生成UUID值，请使用UUID()函数
```sql
UUID()
```

#### MySQL UUID与自动递增INT作为主键
- UUID值在表，数据库甚至在服务器上都是唯一的，允许您从不同数据库合并行或跨服务器分发数据库
- UUID值不会公开有关数据的信息，因此它们在URL中使用更安全
- 可以在避免往返数据库服务器的任何地方生成UUID值

#### UUID值也有一些缺点
- 存储UUID值 (16字节) 比整数 (4字节) 或甚至大整数 (8字节) 占用更多的存储空间
- 调试似乎更加困难，想像一下 WHERE id ='9d6212cf-72fc-11e7-bdf0-f0def1e6646c' 和 WHERE id = 10 那个舒服一点
- 使用UUID值可能会导致性能问题，因为它们的大小和没有被排序

#### 可以以紧凑格式(BINARY)存储UUID值，并通过以下功能显示人机可读格式
- UUID_TO_BIN
- BIN_TO_UUID
- IS_UUID

#### 示例
```sql
USE testdb;
CREATE TABLE customers (
  id BINARY(16) PRIMARY KEY,
  name VARCHAR(255)
);
```

```sql
INSERT INTO customers(id, name) VALUES(UUID_TO_BIN(UUID()),'John Doe'), (UUID_TO_BIN(UUID()),'Will Minsu'), (UUID_TO_BIN(UUID()),'Mary Jane');
```

```sql
SELECT 
    BIN_TO_UUID(id) id, 
    name
FROM
    customers;
```
