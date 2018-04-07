int main(int argc, char const *argv[])
{
    // 创建一个UDP套接字
    int fd = Socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in srvaddr;
    socklen_t len = sizeof(srvaddr);
    bzero(&srvaddr, len);

    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = htons(atoi(argv[1]));
    srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // 绑定本地IP和端口
    Bind(fd, &srvaddr, len);

    // 迭代服务器
    char buf[SIZE];
    while(1)
    {
        bzero(buf, SIZE);
        recvfrom(fd, buf, SIZE, 0, NULL, NULL);

        printf("%s", buf);
    }

    return 0;
}
