### gRPC通信方式
- Simple RPC 
- Server-side streaming RPC 
- Client-side streaming RPC 
- Bidirectional streaming RPC 

### 服务定义及ProtoBuf
gRPC使用ProtoBuf定义服务， 我们可以一次性的在一个 .proto 文件中定义服务并使用任何支持它的语言去实现客户端和服务器，反过来，它们可以在各种环境中，
从云服务器到你自己的平板电脑—— gRPC 帮你解决了不同语言及环境间通信的复杂性

### protoc编译工具
protoc工具可在https://github.com/google/protobuf/releases 下载到源码

### protobuf语法
- syntax = "proto3"
  - protocol buffer 编译器就会认为你使用的是proto2的语法
- message SearchRequest
  - message 定义实体，c/c++/go中的结构体，php中类
- 基本数据类型 
  - double
  - float
  - int 32
  - int 64
  - unit 32
  - unit 64

### 代理类生成 
- C++, 每一个.proto 文件可以生成一个 .h 文件和一个 .cc 文件 
- Java, 每一个.proto文件可以生成一个 .java 文件
- Python, 每一个.proto文件生成一个模块，其中为每一个消息类型生成一个静态的描述器，在运行时，和一个metaclass一起使用来创建必要的Python数据访问类 
- Go, 每一个.proto生成一个 .pb.go 文件 
- Ruby, 每一个.proto生成一个 .rb 文件 
- Objective-C, 每一个.proto 文件可以生成一个 pbobjc.h 和一个pbobjc.m 文件
- C#, 每一个.proto文件可以生成一个.cs文件
- php, 每一个message消息体生成一个.php类文件，并在GPBMetadata目录生成一个对应包名的.php类文件，用于保存.proto的二进制元数据

### 字段默认值 
- strings, 默认值是空字符串（empty string） 
- bytes, 默认值是空bytes（empty bytes） 
- bools, 默认值是false 
- numeric, 默认值是0 
- enums, 默认值是第一个枚举值（value必须为0） 
- message fields, the field is not set. Its exact value is langauge-dependent. See the generated code guide for details. 
- repeated fields，默认值为empty，通常是一个空list

### 枚举
```cmd
enum WshExportInstStatus {
  INST_INITED = 0;
  INST_RUNNING = 1;
  INST_FINISH = 2;
  INST_FAILED = 3;
}
```

### Maps字段类型
```java
map<key_type, value_type> map_field = N;
```
其中key_type可以是任意Integer或者string类型（所以，除了floating和bytes的任意标量类型都是可以的）value_type可以是任意类型
```java
map<string, Project> projects = 3;
```
- Map的字段可以是repeated
- 序列化后的顺序和map迭代器的顺序是不确定的，所以你不要期望以固定顺序处理Map
- 当为.proto文件产生生成文本格式的时候，map会按照key 的顺序排序，数值化的key会按照数值排序
- 从序列化中解析或者融合时，如果有重复的key则后一个key不会被使用，当从文本格式中解析map时，如果存在重复的key

### 默认值
- 字符串类型默认为空字符串 
- 字节类型默认为空字节 
- 布尔类型默认 false 
- 数值类型默认为 0 值 
- enums类型默认为第一个定义的枚举值，必须是 0

### 服务
服务使用service{}包起来，每个方法使用rpc起一行申明，一个方法包含一个请求消息体和一个返回消息体
```java
service HelloService {
  rpc SayHello (HelloRequest) returns (HelloResponse);
}

message HelloRequest {
  string greeting = 1;
}

message HelloResponse {
  string reply = 1;
}
```


