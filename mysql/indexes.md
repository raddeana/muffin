### 索引
索引(Index)是帮助MySQL高效获取数据的数据结构
快速查找排好序的一种数据结构
Mysql索引主要有两种结构：B+Tree索引和Hash索引
如果没有特别指明，一般指B树结构组织的索引(B+Tree索引)

#### explain
对 SELECT 语句进行分析, 并输出 SELECT 执行的详细信息, 以供开发人员针对性优化
expain出来的信息有10列，分别是id、select_type、table、type、possible_keys、key、key_len、ref、rows、Extra

- id: SELECT 查询的标识符. 每个 SELECT 都会自动分配一个唯一的标识符
- select_type: SELECT 查询的类型
- table: 查询的是哪个表
- partitions: 匹配的分区
- type: join 类型
- possible_keys: 此次查询中可能选用的索引
- key: 此次查询中确切使用到的索引.
- ref: 哪个字段或常数与 key 一起被使用
- rows: 显示此查询一共扫描了多少行. 这个是一个估计值.
- filtered: 表示此查询条件所过滤的数据的百分比
- extra: 额外的信息

#### select_type
- SIMPLE: 表示此查询不包含 UNION 查询或子查询
- PRIMARY: 表示此查询是最外层的查询
- SUBQUERY: 子查询中的第一个 SELECT
- UNION: 表示此查询是 UNION 的第二或随后的查询
- DEPENDENT UNION: UNION 中的第二个或后面的查询语句, 取决于外面的查询
- UNION RESULT: UNION 的结果
- DEPENDENT SUBQUERY: 子查询中的第一个 SELECT, 取决于外面的查询. 即子查询依赖于外层查询的结果.
- DERIVED: 衍生，表示导出表的SELECT（FROM子句的子查询）

#### type
- system: 表中只有一条数据. 这个类型是特殊的 const 类型
- const: 针对主键或唯一索引的等值查询扫描, 最多只返回一行数据. const 查询速度非常快, 因为它仅仅读取一次即可
- eq_ref: 此类型通常出现在多表的 join 查询, 表示对于前表的每一个结果, 都只能匹配到后表的一行结果
- ref: 此类型通常出现在多表的 join 查询, 针对于非唯一或非主键索引, 或者是使用了 最左前缀 规则索引的查询
- range: 表示使用索引范围查询, 通过索引字段范围获取表中部分数据记录
- index: 表示全索引扫描(full index scan), 和 ALL 类型类似, 只不过 ALL 类型是全表扫描, 而 index 类型则仅仅扫描所有的索引, 而不扫描数据
- index 类型通常出现在: 所要查询的数据直接在索引树中就可以获取到, 而不需要扫描数据. 当是这种情况时, Extra 字段 会显示 Using index

#### possible_keys

#### key

#### ref

#### rows

#### filtered

#### extra

