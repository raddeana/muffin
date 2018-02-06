#### ubantu
sudo apt-get install libevent libevent-deve
sudo apt-get install memcached

#### 运行
/usr/local/memcached/bin/memcached -h

#### 启动选项
- d是启动一个守护进程
- m是分配给Memcache使用的内存数量，单位是MB
- u是运行Memcache的用户
- l是监听的服务器IP地址，可以有多个地址
- p是设置Memcache监听的端口，最好是1024以上的端口
- c是最大运行的并发连接数，默认是1024
- P是设置保存Memcache的pid文件

