
ssize_t Write(int fildes, const void *buf, size_t nbyte)
{
    ssize_t retval = write(fildes, buf, nbyte);
    if(retval == -1)
    {
        perror("write() error");
    }

    return retval;
}

ssize_t Read(int fildes, void *buf, size_t nbyte)
{
    int ret = read(fildes, buf, nbyte);
    if(ret == -1)
    {
        perror("read() failed");
    }
    return ret;
}

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    int ret = bind(sockfd, addr, addrlen);
    if(ret == -1)
    {
        perror("bind() failed");
    }
    return ret;
}

int Listen(int sockfd, int backlog)
{
    int ret = listen(sockfd, backlog);
    if(ret == -1)
    {
        perror("listen() failed");
    }
    return ret;
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    int ret = accept(sockfd, addr, addrlen);
    if(ret == -1)
    {
        perror("accept() failed");
    }
    return ret;
}

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    int ret = connect(sockfd, addr, addrlen);
    if(ret == -1)
    {
        perror("connect() failed");
    }
    return ret;
}

int Socket(int domain, int type, int protocol)
{
    int sockfd = socket(domain, type, protocol);
    if(sockfd == -1)
    {
        perror("socket() error");
    }

    return sockfd;
}

int Setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen)
{
    int retval = setsockopt(sockfd, level, optname, optval, optlen);
    if(retval == -1)
    {
        perror("setsockopt() error");
    }

    return retval;
}

int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)
{
    int ret = select(nfds, readfds, writefds, exceptfds, timeout);
    if(ret == -1)
    {
        perror("select() failed");
    }
    return ret;
}
