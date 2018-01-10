var os = require("os");

// CPU 的字节序
console.info('endianness: ' + os.endianness());
// 操作系统名
console.info('type: ' + os.type());
// 操作系统名
console.info('platform: ' + os.platform());
// 系统内存总量
console.info('total memory: ' + os.totalmem() + " bytes.");
// 操作系统空闲内存量
console.info('free memory: ' + os.freemem() + " bytes.");