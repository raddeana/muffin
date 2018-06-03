#### CAS 命令
CAS（Check-And-Set 或 Compare-And-Swap） 命令用于执行一个"检查并设置"的操作

```
cas key flags exptime bytes unique_cas_token [noreply]
value
```

#### 参数说明
- key：键值 key-value 结构中的 key，用于查找缓存值
- flags：可以包括键值对的整型参数，客户机使用它存储关于键值对的额外信息
- exptime：在缓存中保存键值对的时间长度（以秒为单位，0 表示永远）
- bytes：在缓存中存储的字节数
- unique_cas_token通过 gets 命令获取的一个唯一的64位值
- noreply（可选）： 该参数告知服务器不需要返回数据
- value：存储的值（始终位于第二行）（可直接理解为key-value结构中的value）

```memcached
cas tp 0 900 9
ERROR

cas tp 0 900 9 2
memcached
NOT_FOUND

set tp 0 900 9
memcached
STORED

gets tp
VALUE tp 0 9 1
memcached
END

cas tp 0 900 5 1
redis
STORED

get tp
VALUE tp 0 5
redis
END
```

#### 输出信息
- STORED：保存成功后输出
- ERROR：保存出错或语法错误
- EXISTS：在最后一次取值后另外一个用户也在更新该数据
- NOT_FOUND：Memcached 服务上不存在该键值
