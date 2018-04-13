#### ArrayBuffer对象
代表内存之中的一段二进制数据，可以通过“视图”进行操作
"视图" 部署了数组接口，这意味着，可以用数组的方法操作内存

- ArrayBuffer.prototype.byteLength ArrayBuffer实例的byteLength属性，返回所分配的内存区域的字节长度
- ArrayBuffer.prototype.slice 允许将内存区域的一部分，拷贝生成一个新的ArrayBuffer对象
- ArrayBuffer.isView 静态方法isView，返回一个布尔值，表示参数是否为ArrayBuffer的视图实例

#### TypedArray对象
用来生成内存的视图，通过9个构造函数，可以生成9种数据格式的视图，
比如Uint8Array（无符号8位整数）数组视图, Int16Array（16位整数）数组视图, 
Float32Array（32位浮点数）数组视图

- Int8Array：8位有符号整数，长度1个字节
- Uint8Array：8位无符号整数，长度1个字节
- Uint8ClampedArray：8位无符号整数，长度1个字节，溢出处理不同
- Int16Array：16位有符号整数，长度2个字节
- Uint16Array：16位无符号整数，长度2个字节
- Int32Array：32位有符号整数，长度4个字节
- Uint32Array：32位无符号整数，长度4个字节
- Float32Array：32位浮点数，长度4个字节
- Float64Array：64位浮点数，长度8个字节

普通数组的操作方法和属性，对TypedArray数组完全适用

#### DataView对象
用来生成内存的视图，可以自定义格式和字节序，
比如第一个字节是Uint8（无符号8位整数）、第二个字节是Int16（16位整数）、第三个字节是Float32（32位浮点数）

#### 复合视图
在同一段内存之中，可以依次存放不同类型的数据，这叫做 "复合视图"
```
var buffer = new ArrayBuffer(24)
var idView = new Uint32Array(buffer, 0, 1)
var usernameView = new Uint8Array(buffer, 4, 16)
var amountDueView = new Float32Array(buffer, 20, 1)
```

#### DataView视图
DataView实例有以下属性，含义与TypedArray实例的同名方法相同
- DataView.prototype.buffer：返回对应的ArrayBuffer对象
- DataView.prototype.byteLength：返回占据的内存字节长度
- DataView.prototype.byteOffset：返回当前视图从对应的ArrayBuffer对象的哪个字节开始

DataView实例提供8个方法读取内存
- getInt8：读取1个字节，返回一个8位整数
- getUint8：读取1个字节，返回一个无符号的8位整数
- getInt16：读取2个字节，返回一个16位整数
- getUint16：读取2个字节，返回一个无符号的16位整数
- getInt32：读取4个字节，返回一个32位整数
- getUint32：读取4个字节，返回一个无符号的32位整数
- getFloat32：读取4个字节，返回一个32位浮点数
- getFloat64：读取8个字节，返回一个64位浮点数
