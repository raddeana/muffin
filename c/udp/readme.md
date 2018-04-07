UDP 服务器步骤如下：
- 创建等链接套接字fd=socket()
- 绑定待链接套接字bind(fd,服务器ip和端口)
- 等待信息recvfrom(fd,对端地址)

UDP 客户端步骤如下：
- 创建待连接套接字fd=scoket()
- 发送信息sendto(fd,服务器ip和端口)
