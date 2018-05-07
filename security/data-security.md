#### 最新MongoDB 3.4集群认证安全
- MongoDB 3.4集群搭建
- replica集群搭建
- 超级系统用户及数据库用户创建
- MongoDB 3.4安全认证
- 密钥文件 keyFile 创建
- 权限控制起效

#### 最新ElasticSearch 5.2.1集群认证安全
- ES 5.2.1集群搭建流程及常遇问题
- 管理插件x-pack认证
- 插件Head认证
- ES认证license更新

#### 客户端驱动使用问题
- MongoDB 3.4.1认证安全时Java Driver使用及问题
- ES 5.2.1认证机制下Java Client使用

#### 集群认证
start.sh
```sh
bin/mongod --dbpath "/data/mongo" --logpath "./logs/running.log"  --replSet "wcg" --port "17305" --logappend --fork &
```
