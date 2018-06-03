var fs = require("fs");
var data = '';

// 创建可读流
var readerStream = fs.createReadStream('test.txt');

// 设置编码为 utf8
readerStream.setEncoding('UTF8');

// 处理流事件
readerStream.on('data', function(chunk) {
   data += chunk;
});

readerStream.on('end',function(){
   console.info(data);
});

readerStream.on('error', function(err){
   console.info(err.stack);
});

console.info("程序执行完毕");