#### 更新已存在的文档
db.collection.update(
   <query>,
   <update>,
   {
     upsert: <boolean>,
     multi: <boolean>,
     writeConcern: <document>
   }
)

#### 方法通过传入的文档来替换已有文档
db.collection.save(
   <document>,
   {
     writeConcern: <document>
   }
)
