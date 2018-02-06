#### 基本语法
set key flags exptime bytes [noreply] 
value 

#### 参数说明
- key: 键值 key-value 结构中的 key，用于查找缓存值。
- flags: 可以包括键值对的整型参数，客户机使用它存储关于键值对的额外信息 。
- exptime: 在缓存中保存键值对的时间长度（以秒为单位，0 表示永远）
- bytes: 在缓存中存储的字节数
- noreply（可选）: 该参数告知服务器不需要返回数据
- value: 存储的值（始终位于第二行）（可直接理解为key-value结构中的value）

#### 实例
key → runoob
flag → 0
exptime → 900 (以秒为单位)
bytes → 9 (数据存储的字节数)
value → memcached

```shell
set runoob 0 900 9
memcached
STORED

get runoob
VALUE runoob 0 9
memcached

END
```

#### 输出信息说明
- STORED: 保存成功后输出
- ERROR: 在保持失败后输出
