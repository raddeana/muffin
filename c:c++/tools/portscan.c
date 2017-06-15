#include <winsock2.h>
#include <stdio.h>                      // printf函数要用的头文件
#pragma comment(lib,"ws2_32.lib")

void Help();                            // 申明帮助函数

int main (int argc, char* argv[]) {
    // 申明变量
    WORD wVersion = MAKEWORD(2, 0);     // socket的版本
    WSADATA wsaData;

    // sockaddr_in结构
    struct sockaddr_in sin;
    int iFromPort;                 // 开始端口
    int iToPort;                     // 结束端口
    int iNowPort;                  // 正在扫描的端口
    char* cHost;                  // 要扫描的主机
    SOCKET s;                   // 保存创建socket时的返回值
    int iOpenPort;                // 开放端口个数
    iOpenPort = 0;

    // 如果命令行下参数不是4个（包括portscan.exe本身），提示正确的用法
    if(argc != 4) {
        Help();     // 给出帮助
        return -1;
    }

    // 保存用户输入的要扫描的起始端口和结束端口
    // 由于用户输入的是char型，所以要先转成int型
    iFromPort = atoi(argv[2]);
    iToPort = atoi(argv[3]);
    cHost = argv[1];

    // 对用户输入的端口进行判断
    if(iFromPort > iToPort || iFromPort < 0 || iFromPort >65535 || iToPort <0 || iToPort >65535) {
        printf("起始端口不能大于结束端口，且范围为：1-65535!\n");
        return 0;
    }

    if (WSAStartup(wVersion , &wsaData)) {
        printf("初始化失败！");
        return -1;
    }

    printf("======= 开始扫描 =======\n");

    // 循环连结端口，以判断端口是否开放
    for(iNowPort = iFromPort; iNowPort <= iToPort; iNowPort++) {
        s = socket (AF_INET, SOCK_STREAM, 0);
        
        if (s == INVALID_SOCKET) {
            printf("创建socket()失败！\n");
            WSACleanup();  
        }

        // 给结构成员赋值
        sin.sin_family = AF_INET;
        sin.sin_port = htons (iNowPort);
        sin.sin_addr.S_un.S_addr = inet_addr (cHost);

        // 建立连结
        if(connect(s, (struct sockaddr*)&sin, sizeof(sin)) == SOCKET_ERROR) {
            printf("%s -> %d:未开放\n", cHost, iNowPort);  
            closesocket(s);
        } else {
            printf("%s -> %d:开放\n", cHost, iNowPort);
            iOpenPort ++;
            closesocket(s);
        }  
    }

    printf("======= 扫描结果 =======\n");
    printf("主机：%s 扫描到%d个端口开放", cHost, iOpenPort);

    printf("end === >>> \n");
    printf("end === >>> \n");

    // 关闭socket
    closesocket (s);
    WSACleanup ();

    return 0;
}

// 以下为帮助函数内容
void Help () {
    printf("\nPortScan V1.0 by:MulberryX\n");
    printf("Usage:\n");
    printf("  PortScan.exe <TargetIP> <BeginPort> <EndPort>\n");
    printf("Example:\n");
    printf("  PortScan.exe 127.0.0.1 135 445\n");  
}