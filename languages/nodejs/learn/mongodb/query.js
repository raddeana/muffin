let MongoClient = require('mongodb').MongoClient;
let DB_CONN_STR = 'mongodb://localhost:27017/test';    
 
let selectData = (db, callback) => {  
  // 连接到表  
  let collection = db.collection('site');
  // 查询数据
  let whereStr = {
    "name":'菜鸟教程'
  };

  collection.find(whereStr).toArray((err, result) => {
    if (err) {
      console.info('Error:' + err);
      return;
    }

    callback(result);
  });
}
 
MongoClient.connect(DB_CONN_STR, (err, db) => {
  console.info("连接成功！");

  selectData(db, (result) => {
    console.info(result);
    db.close();
  });
});