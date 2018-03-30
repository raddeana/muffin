#### 基本语法
db.COLLECTION_NAME.ensureIndex({KEY:1})

#### 建索引过程会阻塞其它数据库操作，background可指定以后台方式创建索引，即增加 "background" 可选参数。 "background" 默认值为false。
background

#### 建立的索引是否唯一。指定为true创建唯一索引。默认值为false.
unique

#### 索引的名称。如果未指定，MongoDB的通过连接索引的字段名和排序顺序生成一个索引名称。
name

#### 在建立唯一索引时是否删除重复记录,指定 true 创建唯一索引。默认值为 false.
dropDups

#### 对文档中不存在的字段数据不启用索引；这个参数需要特别注意，如果设置为true的话，在索引字段中不会查询出不包含对应字段的文档。默认值为 false
sparse

#### 指定一个以秒为单位的数值，完成 TTL设定，设定集合的生存时间
expireAfterSeconds

#### 索引的版本号。默认的索引版本取决于mongod创建索引时运行的版本
v

#### 索引权重值，数值在 1 到 99,999 之间，表示该索引相对于其他索引字段的得分权重
weights

#### 对于文本索引，该参数决定了停用词及词干和词器的规则的列表。 默认为英语
default_language

#### 对于文本索引，该参数指定了包含在文档中的字段名，语言覆盖默认的language，默认值为 language
language_override

#### =============================================================================================
#### 覆盖索引查询

db.users.ensureIndex({ gender: 1, user_name: 1 })
db.users.find({ gender: "M" },{ user_name:1,_id: 0 })

#### 最后，如果是以下的查询，不能使用覆盖索引查询：

#### 所有索引字段是一个数组
#### 所有索引字段是一个子文档

#### =============================================================================================
#### 查询分析

db.users.ensureIndex({ gender: 1, user_name: 1 })
db.users.find({ gender: "M" }, { user_name: 1, _id: 0 }).explain()

#### 字段为 true ，表示我们使用了索引
indexOnly

#### 因为这个查询使用了索引，MongoDB 中索引存储在B树结构中，所以这是也使用了 BtreeCursor 类型的游标。如果没有使用索引，游标的类型是 BasicCursor。这个键还会给出你所使用的索引的名称，你通过这个名称可以查看当前数据库下的system.indexes集合（系统自动创建，由于存储索引信息，这个稍微会提到）来得到索引的详细信息
cursor

#### 当前查询返回的文档数量
n

#### 表明当前这次查询一共扫描了集合中多少个文档，我们的目的是，让这个数值和返回文档的数量越接近越好
nscanned/nscannedObjects

#### 当前查询所需时间，毫秒数
millis

#### 当前查询具体使用的索引
indexBounds

#### =============================================================================================
#### 使用 hint 来强制 MongoDB 使用一个指定的索引

db.users.find({ gender: "M" },{ user_name: 1, _id: 0 }).hint({ gender:1, user_name:1 })
db.users.find({ gender: "M" },{ user_name: 1, _id: 0 }).hint({ gender: 1, user_name: 1 }).explain()

#### =============================================================================================
#### 高级索引

db.users.ensureIndex({ "address.city": 1, "address.state": 1, "address.pincode": 1 })
db.users.find({ "address.city": "Los Angeles" })
db.users.find({ "address.city": "Los Angeles", "address.state": "California"})
db.users.find({ "address.city": "Los Angeles", "address.state": "California", "address.pincode": "123" })

#### =============================================================================================
#### 索引限制

#### 额外开销
每个索引占据一定的存储空间，在进行插入，更新和删除操作时也需要对索引进行操作。所以，如果你很少对集合进行读取操作，建议不使用索引

#### 内存（RAM）使用
由于索引是存储在内存（RAM）中, 你应该确保该索引的大小不超过内存的限制
如果索引的大小大于内存的限制, MongoDB会删除一些索引, 这将导致性能下降

#### 查询限制
索引不能被以下的查询使用：

正则表达式及非操作符，如 $nin, $not, 等
算术运算符，如 $mod, 等
$where 子句

#### 索引键限制

#### 插入文档超过索引键限制

#### 最大范围
集合中索引不能超过64个
索引名的长度不能超过128个字符
一个复合索引最多可以有31个字段




