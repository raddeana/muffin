int main(int argc, char const *argv[])
{
    // 创建一个UDP套接字
    int fd = Socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in srvaddr;
    socklen_t len = sizeof(srvaddr);
    bzero(&srvaddr, len);

    srvaddr.sin_family = AF_INET;
    //srvaddr.sin_addr.s_addr = inet_addr("192.168.0.166");  
    inet_pton(AF_INET, arg[1], &srvaddr.sin_addr);
    srvaddr.sin_port = htons(atoi(argv[2]));


    char buf[SIZE];
    while(1)
    {
        bzero(buf, SIZE);
        fgets(buf, SIZE, stdin);

        sendto(fd, buf, strlen(buf), 0,
                (struct sockaddr *)&srvaddr, len);
    }

    return 0;
}
