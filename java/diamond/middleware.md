### server集群数据同步
diamond-server将数据存储在mysql和本地文件中，mysql是一个中心，diamond认为存储在mysql中的数据绝对正确，除此之外，server会将数据存储在本地文件中

- server写数据时，先将数据写入mysql, 然后写入本地文件, 写入完成后发送一个HTTP请求给集群中的其他server, 其他server收到请求, 从mysql中dump刚刚写入的数据至本地文件
- server启动后会启动一个定时任务, 定时从mysql中dump所有数据至本地文件

### client获取server地址
diamond-client在使用时没有指定server地址的代码，地址获取对用户是透明的

### client主动获取数据
client调用getAvailableConfigInfomation(), 即可获取一份最新的可用的配置数据, 获取过程实际上是拼接http url, 使用http-client调用http method的过程

### client运行中感知数据变化
这个特性是通过比较client和server的数据的MD5值实现的
server在启动时, 会将所有数据的MD5加载到内存中（MD5根据某算法得出, 保证数据内容不同，MD5不同，MD5存储在mysql中）, 数据更新时，会更新内存中对应的MD5
client在启动并第一次获取数据后, 会将数据的MD5保存在内存中, 并且在启动时会启动一个定时任务, 定时去server检查数据是否变化
