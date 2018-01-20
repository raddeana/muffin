# 基本语法
db.COLLECTION_NAME.aggregate(AGGREGATE_OPERATION)

# eg
db.mycol.aggregate([{$group : {_id : "$by_user", num_tutorial : {$sum : 1}}}])

# 表达式
# 计算总和
$sum

# 计算平均值
$avg

# 获取集合中所有文档对应值得最小值
$min

# 获取集合中所有文档对应值得最大值
$max

# 在结果文档中插入值到一个数组中
$push

# 在结果文档中插入值到一个数组中，但不创建副本
$addToSet

# 根据资源文档的排序获取第一个文档数据
$first

# 根据资源文档的排序获取最后一个文档数据
$last

# pipe
# 修改输入文档的结构。可以用来重命名、增加或删除域，也可以用于创建计算结果以及嵌套文档
$project

# 用于过滤数据，只输出符合条件的文档。$match使用MongoDB的标准查询操作
$match

# 用来限制MongoDB聚合管道返回的文档数
$limit

# 在聚合管道中跳过指定数量的文档，并返回余下的文档
$skip

# 将文档中的某一个数组类型字段拆分成多条，每条包含数组中的一个值
$unwind

# 将集合中的文档分组，可用于统计结果
$group

# 将输入文档排序后输出
$sort

# 输出接近某一地理位置的有序文档
$geoNear
