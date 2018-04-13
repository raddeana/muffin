#### server
```c
#include<linux/in.h>    
#include<linux/inet.h>    
#include<linux/socket.h>    
#include<net/sock.h>    
    
#include<linux/init.h>    
#include<linux/module.h>    
  
#define BUFFSIZE 1024  
  
void jiang_debug( void )  
{  
    printk("just debug");  
}  
  
int myserver(void)  
{    
    
    struct socket *sock,*client_sock;    
    struct sockaddr_in s_addr;    
    unsigned short portnum=8888;    
    int ret=0;    
  
    memset(&s_addr,0,sizeof(s_addr));    
    s_addr.sin_family=AF_INET;    
    s_addr.sin_port=htons(portnum);    
    s_addr.sin_addr.s_addr=in_aton("192.168.0.70");    
  
  
    sock=(struct socket *)kmalloc(sizeof(struct socket), GFP_KERNEL);    
  
    /* create a socket */    
    ret=sock_create_kern(&init_net, AF_INET,SOCK_STREAM, IPPROTO_TCP,&sock);    
    
    if (ret) {    
        printk("server:socket_create error!\n");    
    }
    
    printk("server:socket_create ok!\n");    
  
    /* bind the socket */    
    ret = kernel_bind(sock,(struct sockaddr *)&s_addr,sizeof(struct sockaddr_in));
    
    if(ret<0){    
        printk("server: bind error\n");    
        return ret;    
    }    
    printk("server:bind ok!\n");    
  
    /*listen*/    
    ret=kernel_listen(sock,10);    
    if (ret<0) {    
        printk("server: listen error\n");    
        return ret;    
    }    
    printk("server:listen ok!\n");    
  
    ret=kernel_accept(sock,&client_sock,10);
    
    if (ret<0){    
        printk("server:accept error!\n");    
        return ret;    
    }    
  
    printk("server: accept ok, Connection Established\n");    
  
    /* kmalloc a receive buffer */    
    char *recvbuf = NULL;    
    recvbuf = kmalloc(1024, GFP_KERNEL);
    
    if (recvbuf == NULL) {
        printk("server: recvbuf kmalloc error!\n");    
        return -1;    
    }
    
    memset(recvbuf, 0, 1024);    
  
    /* receive message from client */    
    struct kvec vec;
    struct msghdr msg;
    memset(&vec,0,sizeof(vec));
    memset(&msg,0,sizeof(msg));
    vec.iov_base=recvbuf;
    vec.iov_len=1024;
    msg.msg_flags=MSG_NOSIGNAL;
    msleep(1000);
    jiang_debug();
    ret=kernel_recvmsg(client_sock,&msg,&vec,1,1024, msg.msg_flags); /* receive message */    
    recvbuf[1023] = 0;  
    printk("receive message:\n %s\n",recvbuf);
            
    /* release socket */
    printk("release socket now\n");
    sock_release(client_sock);
    sock_release(sock);
    
    return ret;
}

static int server_init(void){    
    printk("server init:\n");    
    return (myserver());    
}    

static void server_exit(void){    
    printk("good bye\n"); 
}    

module_init(server_init);    
module_exit(server_exit);    

MODULE_LICENSE("GPL");
```

#### client
```c
#include<linux/in.h>  
#include<linux/inet.h>  
#include<linux/socket.h>  
#include<net/sock.h>  
#include<linux/init.h>  
#include<linux/module.h>  
#define BUFFER_SIZE 1024

int connect_send_recv (void){  
    struct socket *sock;  
    struct sockaddr_in s_addr;  
    unsigned short port_num = 8888;  
    int ret = 0;  
    char *send_buf = NULL;  
    char *recv_buf = NULL;  
    struct kvec send_vec, recv_vec;  
    struct msghdr send_msg, recv_msg;
    
    /* kmalloc a send buffer*/  
    send_buf = kmalloc(BUFFER_SIZE, GFP_KERNEL);
    
    if (send_buf == NULL) {  
        printk("client: send_buf kmalloc error!\n");  
        return -1;  
    }
    
    /* kmalloc a receive buffer */  
    recv_buf = kmalloc(BUFFER_SIZE, GFP_KERNEL);
    
    if (recv_buf == NULL){  
        printk("client: recv_buf kmalloc error!\n");  
        return -1;  
    }
    
    memset(&s_addr, 0, sizeof(s_addr));  
    s_addr.sin_family = AF_INET;  
    s_addr.sin_port = htons(port_num);  
    s_addr.sin_addr.s_addr = in_aton("192.168.0.71");  
    sock = (struct socket *)kmalloc(sizeof(struct socket), GFP_KERNEL);  
    // 创建一个sock, &init_net是默认网络命名空间  
    ret = sock_create_kern(&init_net, AF_INET, SOCK_STREAM, IPPROTO_TCP, &sock);
    
    if (ret < 0) {
        printk("client:socket create error!\n");  
        return ret;  
    }
    
    printk("client: socket create ok!\n");  
    //连接  
    ret = sock->ops->connect(sock, (struct sockaddr *)&s_addr, sizeof(s_addr), 0);
    
    if (ret != 0) {  
        printk("client: connect error!\n");  
        return ret;  
    }
    
    printk("client: connect ok!\n");  
    memset(send_buf, 'a', BUFFER_SIZE);  
    memset(&send_msg, 0, sizeof(send_msg));  
    memset(&send_vec, 0, sizeof(send_vec));  
    send_vec.iov_base = send_buf;  
    send_vec.iov_len = BUFFER_SIZE;
    
    // 发送数据  
    ret = kernel_sendmsg(sock, &send_msg, &send_vec, 1, BUFFER_SIZE);
    
    if (ret < 0) {  
        printk("client: kernel_sendmsg error!\n");  
        return ret;  
    } else if(ret != BUFFER_SIZE){  
        printk("client: ret!=BUFFER_SIZE");  
    }
    
    printk("client: send ok!\n");  
    memset(recv_buf, 0, BUFFER_SIZE);  
    memset(&recv_vec, 0, sizeof(recv_vec));  
    memset(&recv_msg, 0, sizeof(recv_msg));  
    recv_vec.iov_base = recv_buf;  
    recv_vec.iov_len = BUFFER_SIZE;  
    // 接收数据  
    ret = kernel_recvmsg(sock, &recv_msg, &recv_vec, 1, BUFFER_SIZE, 0);  
    printk("client: received message:\n %s\n", recv_buf);  
    // 关闭连接  
    kernel_sock_shutdown(sock, SHUT_RDWR);  
    sock_release(sock);  
    return 0;  
}

static int client_example_init(void){  
    printk("client: init\n");  
    return connect_send_recv();  
}

static void client_example_exit(void){  
    printk("client: exit!\n");  
}

module_init(client_example_init);  
module_exit(client_example_exit);  
MODULE_LICENSE("GPL");
```
