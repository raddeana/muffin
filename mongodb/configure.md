#### 重要配置参数
- processManagement
  - fork: <true | false>
  - 是否以fork模式运行mongod/mongos进程，默认为false
 
- net
  - bindIp: <127.0.0.1>
  - port: 27017
  - maxIncomingConnections: 65536
  - wireObjectCheck: true
  - ipv6: false

- storage
  - dbPath: db
  - indexBuildRetry: true
  - repairPath: _tmp
  - engine: mmapv1
  - journal: enabled: true
  - directoryPerDB: false
  - syncPeriodSecs: 60

- mmapv1（如下配置仅对MMAPV1引擎生效）
  - quota
  - enforced: false
  - maxFilesPerDB: 8
  - smallFiles: false
  - journal: commitIntervalMs: 100
  - nsSize

- wiredTiger 如下配置仅对wiredTiger引擎生效
  - engineConfig
  - cacheSizeGB: 8
  - journalCompressor: snappy
  - directoryForIndexes: false

- replication
  - oplogSizeMB: 10240
  - enableMajorityReadConcern: false
  - replSetName: <无默认值>
  - secondaryIndexPrefetch: all
  - localPingThresholdMs: 15

- sharding
  - clusterRole: <无默认值>
  - archiveMovedChunks: true
  - autoSplit: true
  - configDB: <无默认值>
  - chunkSize: 64

- sytemsLog
  - verbosity：0
  - quiet：true
  - traceAllExceptions：true
  - path：logs/mongod.log
  - logAppend：false
  - logRotate：rename
  - localPingThresholdMsdestination: file

#### 与安全有关的配置
- security:
  - authorization: enabled
  - clusterAuthMode: keyFile
  - keyFile: /srv/mongodb/keyfile
  - javascriptEnabled: true
- setParameter:
  - enableLocalhostAuthBypass: true
  - authenticationMechanisms: SCRAM-SHA-1

#### 与性能有关的参数
- setParameter:
  - connPoolMaxShardedConnsPerHost: 200
  - connPoolMaxConnsPerHost: 200
  - notablescan: 0

#### 配置样例
```
systemLog:  
    quiet: false  
    path: /data/mongodb/logs/mongod.log  
    logAppend: false  
    destination: file  
processManagement:  
    fork: true  
    pidFilePath: /data/mongodb/mongod.pid  
net:  
    bindIp: 127.0.0.1  
    port: 27017  
    maxIncomingConnections: 65536  
    wireObjectCheck: true  
    ipv6: false   
storage:  
    dbPath: /data/mongodb/db  
    indexBuildRetry: true  
    journal:  
        enabled: true  
    directoryPerDB: false  
    engine: mmapv1  
    syncPeriodSecs: 60   
    mmapv1:  
        quota:  
            enforced: false  
            maxFilesPerDB: 8  
        smallFiles: true      
        journal:  
            commitIntervalMs: 100  
    wiredTiger:  
        engineConfig:  
            cacheSizeGB: 8  
            journalCompressor: snappy  
            directoryForIndexes: false    
        collectionConfig:  
            blockCompressor: snappy  
        indexConfig:  
            prefixCompression: true  
operationProfiling:  
    slowOpThresholdMs: 100  
    mode: off  
```
```
replication:  
    oplogSizeMB: 10240  
    replSetName: rs0  
    secondaryIndexPrefetch: all  
```
```
sharding:  
    clusterRole: shardsvr  
    archiveMovedChunks: true  
```

--repair "修复" 数据库

#### mongodump&mongorestore
mongodump将整个databases全部内容导出到一个二进制文件中，可以在其他mongod使用mongorestore来加载整个文件
#### mongoimport&mongoexport
mongoexport将数据导出为JSON或者CSV格式，以便其他应用程序解析
mongostat指令可以间歇性的打印出当前mongod实例中“数据存储”、“flush”、读写次数、网络输出等参数，是查看mongod性能的有效手段
