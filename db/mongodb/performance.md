### 监控
- mongodb可以通过profile来监控数据，进行优化
- 查看当前是否开启profile功能用命令：db.getProfilingLevel()返回level等级，值为0|1|2，分别代表意思：0代表关闭，1代表记录慢命令，2代表全部
- 开始profile功能为db.setProfilingLevel(level)

#### 例子
- level为1的时候，慢命令默认值为100ms，更改为db.setProfilingLevel(level, slowms) 如db.setProfilingLevel(1,50)这样就更改为50毫秒
- 通过db.system.profile.find() 查看当前的监控日志
- 通过执行db.system.profile.find({millis:{$gt:500}})能够返回查询时间在500毫秒以上的查询命令

#### 可选查询条件
- ts：命令执行时间
- info：命令的内容
- query：代表查询
- order.order： 代表查询的库与集合
- reslen：返回的结果集大小，byte数
- nscanned：扫描记录数量
- nquery：后面是查询条件
- nreturned：返回记录数及用时
- millis：所花时间

### 索引
- 如果发现查询时间相对长，那么就需要做优化
- 首选就是为待查询的字段建立索引，不过需要特别注意的是，索引不是万能灵药
- 如果需要查询超过一半的集合数据，索引还不如直接遍历来的好

#### exlpain查询执行情况
```cmd
> db.order.find({ "status": 1.0, "user.uid": { $gt: 2663199.0 } }).explain()
{
    "cursor" : "BasicCursor",#游标类型
    "nscanned" : 2010000,#扫描数量
    "nscannedObjects" : 2010000,#扫描对象
    "n" : 337800,#返回数据
    "millis" : 2838,#耗时
    "nYields" : 0,
    "nChunkSkips" : 0,
    "isMultiKey" : false,
    "indexOnly" : false,
    "indexBounds" : {#使用索引（这里没有）
        
    }
}
```

### 数据库设计优化
#### 完全分离（范式化设计）
```cmd
{
     "_id" : ObjectId("5124b5d86041c7dca81917"),
     "title" : "如何使用MongoDB", 
      "author" : [ 
               ObjectId("144b5d83041c7dca84416"),
              ObjectId("144b5d83041c7dca84418"),
              ObjectId("144b5d83041c7dca84420"),
     ]
}
```
#### 完全内嵌（反范式化设计）
```cmd
{
       "_id" : ObjectId("5124b5d86041c7dca81917"),
       "title" : "如何使用MongoDB",
       "author" : [
                {
                    　　　　 "name" : "丁磊"
                   　　　　  "age" : 40,
                     　　　　"nationality" : "china",
                },
                {
                   　　　　  "name" : "马云"
                  　　　　   "age" : 49,
                   　　　　  "nationality" : "china",
                },
                {
                   　　　　  "name" : "张召忠"
                  　　　　   "age" : 59,
                  　　　　   "nationality" : "china",
                },
      ]
}
```

#### 部分内嵌（折中方案）
```cmd
{
       "_id" : ObjectId("5124b5d86041c7dca81917"),
       "title" : "如何使用MongoDB",
       "author" : [ 
               {
                     　　　　"_id" : ObjectId("144b5d83041c7dca84416"),
                   　　　　  "name" : "丁磊"
                },
                {
                    　　　　 "_id" : ObjectId("144b5d83041c7dca84418"),
                  　　　　   "name" : "马云"
                },
                {
                    　　　　 "_id" : ObjectId("144b5d83041c7dca84420"),
                   　　　　  "name" : "张召忠"
                },
      ]
}
```

### 其他
#### 热数据法
使用MongoDB，你最好保证你的热数据在你机器的内存大小之下，保证内存能容纳所有热数据

#### 文件系统法
MongoDB的数据文件是采用的预分配模式，并且在Replication里面，Master和Replica Sets的非Arbiter节点都是会预先创建足够的空文件用以存储操作日志

#### 硬件法
这里的选择包括了对磁盘RAID的选择，也包括了磁盘与SSD的对比选择
