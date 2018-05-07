#### 网络通信部件
常用网络通信框架:
- libevent
- boost
- asio 
- ACE，

网络通信框架至少要解决以下问题:
- 如何检测有新客户端连接
- 如何接受客户端连接
- 如何检测客户端是否有数据发来
- 如何收取客户端发来的数据
- 如何检测连接异常
- 发现连接异常之后，如何处理
- 如何给客户端发送数据
- 如何在给客户端发完数据后关闭连接

#### IO复用机制
##### windows:
- select
- WSAAsyncSelect
- WSAEventSelect
- 完成端口（IOCP）
##### linux系统:
- select
- poll
- epoll
##### 层次：
- 一: select和poll
- 二: WSAAsyncSelect、WSAEventSelect、完成端口（IOCP）、epoll

#### 检测网络事件
```cpp
bool CIUSocket::Recv () {
  int nRet = 0;
  while (true) {
    char buff[512];
    nRet = ::recv(m_hSocket, buff, 512, 0);

    if (nRet == SOCKET_ERROR) {
      if (::WSAGetLastError() == WSAEWOULDBLOCK) {
        break; 
      } else {
        return false;
      }
    } else if (nRet < 1)
      return false;
      m_strRecvBuf.append(buff, nRet);
      ::Sleep(1);
    } 

    return true;
  }
}
```

#### 协议的设计
除了一些通用的协议，如http、ftp协议以外，大多数服务器协议都是根据业务制定的

#### 界定包的界限
- 固定大小，这种方法就是假定每一个包的大小都是固定字节数目
- 指定包结束符，例如以一个\r\n(换行符和回车符)结束，这样对端只要收到这样的结束符，就可以认为收到了一个包，接下来的数据是下一个包的内容
- 指定包的大小，这种方法结合了上述两种方法，一般包头是固定大小，包头中有一个字段指定包 
- 体或者整个大的大小，对端收到数据以后先解析包头中的字段得到包体或者整个包的大小，然后根据这个大小去界定数据的界线

#### 解包
数据格式应该清晰明了

#### 数值类型
```cpp
class BinaryReadStream {
  private:
    const char* const ptr;
    const size_t      len;
    const char*       cur;
    BinaryReadStream(const BinaryReadStream&);
    BinaryReadStream&operator=(const BinaryReadStream&);

  public:
    BinaryReadStream(const char* ptr, size_t len);
    virtual const char* GetData() const;
    virtual size_t GetSize() const;
    bool IsEmpty() const;
    bool ReadString(string* str, size_t maxlen, size_t& outlen);
    bool ReadCString(char* str, size_t strlen, size_t& len);
    bool ReadCCString(const char** str, size_t maxlen, size_t& outlen);
    bool ReadInt32(int32_t& i);
    bool ReadInt64(int64_t& i);
    bool ReadShort(short& i);
    bool ReadChar(char& c);
    size_t ReadAll(char* szBuffer, size_t iLen) const;
    bool IsEnd() const;
    const char* GetCurrent() const{ return cur; }

  public:
    bool ReadLength(size_t & len);
    bool ReadLengthWithoutOffset(size_t &headlen, size_t & outlen);
}

class BinaryWriteStream {
  public:
    BinaryWriteStream(string* data);
    virtual const char* GetData() const;
    virtual size_t GetSize() const;
    bool WriteCString(const char* str, size_t len);
    bool WriteString(const string& str);
    bool WriteDouble(double value, bool isNULL = false);
    bool WriteInt64(int64_t value, bool isNULL = false);
    bool WriteInt32(int32_t i, bool isNULL = false);
    bool WriteShort(short i, bool isNULL = false);
    bool WriteChar(char c, bool isNULL = false);
    size_t GetCurrentPos() const{ return m_data->length(); }
    void Flush();
    void Clear();

  private:
    string* m_data;
}
```

##### 编码
```cpp
std::string outbuf;
BinaryWriteStream writeStream(&outbuf);
writeStream.WriteInt32(msg_type_register);
writeStream.WriteInt32(m_seq);
writeStream.WriteString(retData);
writeStream.Flush();
```
##### 解码
```cpp
BinaryReadStream readStream(strMsg.c_str(), strMsg.length());
int32_t cmd;

if (!readStream.ReadInt32(cmd)) {
return false;
}

// int seq;
if (!readStream.ReadInt32(m_seq)) {
        return false;
}

std::string data;
size_t datalength;
if (!readStream.ReadString(&data, 0, datalength)) {
  return false;
}
```

#### 服务器程序结构
- 定时器事件处理  
- IO复用技术检测socket可读事件、出错事件（如果有数据要发送，则也检测可写事件）  
- 如果有可读事件，对于侦听socket则接收新连接  
- 对于普通socket则收取该socket上的数据，收取的数据存入对应的接收缓冲区，如果出错则关闭连接
- 如果有数据要发送，有可写事件，则发送数据  
- 如果有出错事件，关闭该连接  
- 从接收缓冲区中取出数据解包，分解成不同的业务来处理  
- 程序自定义任务1  
- 程序自定义任务2  

##### muduo 
- eventloop.cpp
```cpp
void EventLoop::loop() {
  assert(!looping_);
  assertInLoopThread();
  looping_ = true;
  quit_ = false;      // FIXME: what if someone calls quit() before loop() ?
  LOG_TRACE << "EventLoop " << this << " start looping";

  while (!quit_) {
    activeChannels_.clear();
    pollReturnTime_ = poller_->poll(kPollTimeMs, &activeChannels_);
    ++ iteration_;

    if (Logger::logLevel() <= Logger::TRACE) {
        printActiveChannels();
    }

    // TODO sort channel by priority
    eventHandling_ = true;
    for (ChannelList::iterator it = activeChannels_.begin(); it != activeChannels_.end(); ++it) {
        currentActiveChannel_ = *it;
        currentActiveChannel_ -> handleEvent(pollReturnTime_);
    }

    currentActiveChannel_ = NULL;
    eventHandling_ = false;
    doPendingFunctors();

    if (frameFunctor_) {
        frameFunctor_();
    }       
  }

  LOG_TRACE << "EventLoop " << this << " stop looping";
  looping_ = false;
}
```
- Channel
```cpp
void Channel::handleEvent(Timestamp receiveTime) {
    std::shared_ptr<void> guard;  
    if (tied_) {
        guard = tie_.lock();
        
        if (guard) {  
            handleEventWithGuard(receiveTime);  
        }
    } else {
        handleEventWithGuard(receiveTime);  
    }  
}  

void Channel::handleEventWithGuard (Timestamp receiveTime) {
    eventHandling_ = true;  
    LOG_TRACE << reventsToString();
    
    if ((revents_ & POLLHUP) && !(revents_ & POLLIN)) {
        if (logHup_) {  
            LOG_WARN << "Channel::handle_event() POLLHUP";  
        }  
        
        if (closeCallback_) {
          closeCallback_();
        }
    }  

    if (revents_ & POLLNVAL) {  
        LOG_WARN << "Channel::handle_event() POLLNVAL";  
    }  

    if (revents_ & (POLLERR | POLLNVAL)) {  
        if (errorCallback_) {
          errorCallback_();
        }
    }
    
    if (revents_ & (POLLIN | POLLPRI | POLLRDHUP)) {  
        //当是侦听socket时，readCallback_指向Acceptor::handleRead  
        //当是客户端socket时，调用TcpConnection::handleRead   
        if (readCallback_) {
          readCallback_(receiveTime);
        }
    }
    
    if (revents_ & POLLOUT) {  
        // 如果是连接状态服的socket，则writeCallback_指向Connector::handleWrite()  
        if (writeCallback_) {
          writeCallback_();
        }
    }  
    eventHandling_ = false;  
} 
```

- Aceptor
```cpp
void Acceptor::handleRead() {  
  loop_->assertInLoopThread();  
  InetAddress peerAddr;  

  // FIXME loop until no more
  int connfd = acceptSocket_.accept(&peerAddr);  
  if (connfd >= 0) {  
    // string hostport = peerAddr.toIpPort();  
    // LOG_TRACE << "Accepts of " << hostport;  
    //newConnectionCallback_实际指向TcpServer::newConnection(int sockfd, const InetAddress& peerAddr)  
    if (newConnectionCallback_) {  
        newConnectionCallback_(connfd, peerAddr);  
    } else {  
        sockets::close(connfd);  
    }  
  } else {  
    LOG_SYSERR << "in Acceptor::handleRead";  
    // Read the section named "The special problem of  
    // accept()ing when you can't" in libev's doc.  
    // By Marc Lehmann, author of livev.  

    if (errno == EMFILE) {  
      ::close(idleFd_);  
      idleFd_ = ::accept(acceptSocket_.fd(), NULL, NULL);  
      ::close(idleFd_);  
      idleFd_ = ::open("/dev/null", O_RDONLY | O_CLOEXEC);  
    }  
  }
}
```
