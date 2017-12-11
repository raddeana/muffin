/*
 * @端口扫描 sample
 * @author 陈翔宇
 */

#include <string.h>  
#include <Winsock2.h>  
#include <windows.h>
#pragma comment(lib,"ws2_32.lib")

#define DEST_IP "127.0.0.1"
#define DEST_PORT 8080  
  
int main () {
    // 初始化WinSock
    WORD wVersionRequested = MAKEWORD(2, 2);  
    WSADATA wsaData;

    if (WSAStartup(wVersionRequested, &wsaData) != 0) {  
        printf('初始化WinSock失败！\n');
        return 0;
    }

    int sockfd, n;

    struct sockaddr_in dest_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);  

    dest_addr.sin_family = AF_INET;  
    dest_addr.sin_port = htons(DEST_PORT);  
    dest_addr.sin_addr.s_addr = inet_addr(DEST_IP);  
  
    n = connect(sockfd, (struct sockaddr *) & dest_addr, sizeof(struct sockaddr));  
    
    if(n == -1) {
        printf('端口没有开启');
    } else {
        printf('端口开启');
    }
}  