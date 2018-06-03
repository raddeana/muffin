let MongoClient = require('mongodb').MongoClient;
let DB_CONN_STR = 'mongodb://localhost:27017/test';
 
let insertData = (db, callback) => {  
  // 连接到表 site
  let collection = db.collection('site');
  // 插入数据
  let data = [{
    'name': "菜鸟教程", 
    'url': "www.runoob.com"
  }, {
    'name': "菜鸟工具", 
    'url': "c.runoob.com"
  }];

  collection.insert(data, (err, result) => {
    if (err) {
      console.info('Error:' + err);
      return;
    }

    callback(result);
  });
}
 
MongoClient.connect(DB_CONN_STR, (err, db) => {
  console.info("连接成功！");

  insertData(db, (result) => {
    console.info(result);
    db.close();
  });
});