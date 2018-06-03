#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Queue.h"

#define MAX_VERTEX_NUM 10
#define INFINITY 32768

typedef enum { DG, DN, UDG, UDN } GraphKind;

#define ERROR 0
#define TRUE 1

typedef int status;
typedef char ElemType;

typedef struct MNode {
  ElemType vertex[MAX_VERTEX_NUM];          // 顶点
  int Arc[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  // 弧
  int vexnum,arcnum;                        // 弧个数，顶点个数
  GraphKind kind;
} GraphNode, *Graph;

int IsRead[MAX_VERTEX_NUM];  // 标记顶点是否被遍历过

/**
 * 初始化
 * @param {Graph *} 图指针
 * @return none
 */
status Init(Graph *G){
  (*G) = (GraphNode *)malloc(sizeof(GraphNode));
  (*G)->vexnum = 0;
  (*G)->arcnum = 0;

  if ((*G)) {
    return TRUE; 
  }
  else{
    printf("初始化出错...\n");
  }

  return ERROR;
}

/**
 * 查找位置
 * @param {Graph} 图
 * @param {char} 字符
 * @param {char} 字符
 * @param {int} 
 * @param {int} 
 * @return none
 */
void FindPos (Graph G, char a, char b, int *pos1, int *pos2) {
  int i = 0;
  *pos1 = -1; *pos2 = -1;         // 初值
  
  for (i = 0; i < G->vexnum; i++) {
    if(G->vertex[i] == a) {
      (*pos1) = i;
      continue;
    } else if (G->vertex[i] == b) {
      (*pos2) = i;
      continue;
    }
  }
}

/**
 * 建立图
 * @param {Graph} 图
 * @return none
 */
void BuildGraph (Graph G) {
    int choice = 0, 
        num = 0,
        pos1,
        pos2,
        i,
        j,
        weight;
    
    char a, b, ch;
    printf("请选择建立的图的类型:1:有向图，2:有向网，3:无向图，无向网:\n");
    scanf("%d",&choice);
    getchar();
    printf("\n");                                   // 下一行
    
    if (choice == 1) {                              // 有向图
        for (i = 0; i < MAX_VERTEX_NUM; i ++) {     // 初始化弧
          for (j = 0; j < MAX_VERTEX_NUM; j ++){
            G->Arc[i][j] = 0;
          }
        }
        
        G->kind = DG; // 设置图的类型

        printf("请输入顶点(不超过10个，以#结束):\n");
        scanf("%c",&ch);
        while(ch!='#' && num <10){
          G->vertex[num] = ch;
          scanf("%c",&ch);
          num++;
        }
        
        G->vexnum = num;  // 顶点个数
        getchar();        // 清除键盘缓冲区

        printf("请输入对应的弧以a->b格式输入(以#->#结束):\n");
        scanf("%c->%c",&a,&b);
        
        while (a!='#' && b!='#') {
          printf("%c,%c",a,b);
          FindPos(G,a,b,&pos1,&pos2);
          printf("位置a:%d,位置b:%d\n",pos1,pos2);

          // 忽略不存在的顶点
          if (pos1!= -1 && pos2!= -1) {
            G->Arc[pos1][pos2] = 1;
            G->arcnum++;
          }

          scanf("%c->%c",&a,&b);
        }
        
        getchar(); // 清空
    } else if (choice == 2) {
        num = 0;  // 个数初始化
        
        for(i = 0; i < MAX_VERTEX_NUM; i++) { //初始化弧
          for(j = 0; j < MAX_VERTEX_NUM; j++) {
            G->Arc[i][j] = INFINITY;
          }
        }
        
        G->kind = DN; // 设置图的类型
        printf("请输入顶点(不超过10个，以#结束):\n");
        scanf("%c",&ch);
        
        while (ch!='#' && num <10) {
          G->vertex[num] = ch;
          scanf("%c",&ch);
          num++;
        }
        
        G->vexnum = num;  // 顶点个数

        getchar();        // 清除键盘缓冲区

        printf("请输入对应的弧以a->b:weight格式输入(以#->#:0结束):\n");
        scanf("%c->%c:%d",&a,&b,&weight);
        
        while (a!='#' && b!='#') {
          printf("%c,%c",a,b);
          FindPos(G,a,b,&pos1,&pos2);
          printf("位置a:%d,位置b:%d\n",pos1,pos2);

          if (pos1!= -1 && pos2!= -1){  
            // 忽略不存在的顶点
            G->Arc[pos1][pos2] = weight;
            G->arcnum++;
          }

          scanf("%c->%c:%d", &a, &b, &weight);
        }
        
        getchar(); // 清空
    } else if (choice == 3) {
        // 无向图
        num = 0;
        
        for (i = 0; i < MAX_VERTEX_NUM; i ++){ //初始化弧
          for(j = 0; j < MAX_VERTEX_NUM; j ++){
            G->Arc[i][j] = 0;
          }
        }
        
        G->kind = UDG; // 设置图的类型

        printf("请输入顶点(不超过10个，以#结束):\n");
        scanf("%c",&ch);
        
        while(ch!='#' && num <10){
          G->vertex[num] = ch;
          scanf("%c",&ch);
          num++;
        }
        
        G->vexnum = num;  //顶点个数

        getchar();  //清除键盘缓冲区

        printf("请输入对应的弧以a-b格式输入(以#-#结束):\n");
        scanf("%c-%c",&a,&b);
        
        while (a!='#' && b!='#') {
          printf("%c,%c",a,b);
          FindPos(G,a,b,&pos1,&pos2);
          printf("位置a:%d,位置b:%d\n",pos1,pos2);

          if(pos1!= -1 && pos2!= -1){  //忽略不存在的顶点
            G->Arc[pos1][pos2] = 1;
            G->Arc[pos2][pos1] = 1;
            G->arcnum++;
          }

          scanf("%c-%c", &a, &b);
        }
        
        getchar(); // 清空
    } else if (choice == 4) {
        // 无向网
        num = 0;  //个数初始化
        
        for (i = 0; i < MAX_VERTEX_NUM; i++){ //初始化弧
            for(j = 0;j<MAX_VERTEX_NUM; j++){
                G->Arc[i][j] = INFINITY;
            }
        }
        
        G -> kind = DN; //设置图的类型

        printf("请输入顶点(不超过10个，以#结束):\n");
        scanf("%c",&ch);
        
        while(ch!='#' && num <10){
            G->vertex[num] = ch;
            scanf("%c",&ch);
            num++;
        }
        
        G->vexnum = num;  // 顶点个数

        getchar();        // 清除键盘缓冲区

        printf("请输入对应的弧以a-b:weight格式输入(以#-#:0结束):\n");
        scanf("%c->%c:%d",&a,&b,&weight);
        
        while (a!='#' && b!='#') {
            printf("%c,%c",a,b);
            FindPos(G,a,b,&pos1,&pos2);
            printf("位置a:%d,位置b:%d\n",pos1,pos2);
            
            if(pos1!= -1 && pos2!= -1){  //忽略不存在的顶点
                G->Arc[pos1][pos2] = weight;
                G->Arc[pos2][pos1] = weight;
                G->arcnum++;
            }
            
            scanf("%c-%c:%d",&a,&b,&weight);
        }
        
        getchar(); // 清空
    } else {  // 非法输入的选择
        printf("输入非法,请输入正确的数字!!\n");
        return;
    }
}

/**
 * 深度优先搜索for图
 * @param {Graph}
 * @param {int}
 * @return none
 */
void DepthFS (Graph G, int pos) {
  int i = 0,j = 0;
  
  if(IsRead[pos] == 0){
    IsRead[pos] = 1; //从第一个开始
    printf("遍历顶点%c\n",G->vertex[pos]);
  }

  for(i = 0;i<G->vexnum;i++){
    if(G->Arc[pos][i] == 1 && IsRead[i] ==0){  //存在弧
      DepthFS(G,i);
    }
  }
}

/**
 * 深度优先搜索for网
 * @param {Graph} 
 * @param {int}
 * @return none
 */
void DepthFS1 (Graph G, int pos) {
  int i = 0,
      j = 0;
  
  if(IsRead[pos] == 0){
    IsRead[pos] = 1; //从第一个开始
    printf("遍历顶点%c\n",G->vertex[pos]);
  }

  for(i = 0;i<G->vexnum;i++){
    if(G->Arc[pos][i] !=INFINITY && IsRead[i] ==0){  //存在弧且未被遍历
      DepthFS1(G,i);
    }
  }
}

/**
 * 深度优先搜索
 * @param {Graph} 图
 * @return none
 */
void DFS (Graph G) {
  if (G->kind == DG || G->kind == UDG) {
    DepthFS (G, 0);
  } else if (G->kind == DN || G->kind == UDN) {
    DepthFS1 (G, 0);
  }
}

/**
 * 广度优先搜索for图
 * @param {Graph}
 * @param {int} 
 * @return none
 */
void BFS1 (Graph G, int pos) {
  int i = 0,
      temp;

  Queue Q;
  InitQueue(&Q);

  for (i = 0; i <G->vexnum; i++) {
    IsRead[i] = 0;
  }

  if (IsRead[pos] == 0) {
    IsRead[pos] = 1;
    printf("遍历顶点:%c\n",G->vertex[pos]);
  }

  EnterQueue(Q, pos);

  // 当队列不为空
  while (!isEmpty(Q)) {
    OutQueue(Q, &temp);
    
    for(i = 0; i< G->vexnum;i++){
      if(G->Arc[temp][i] == 1 && IsRead[i] == 0){
        IsRead[i] = 1;
        printf("遍历顶点:%c\n",G->vertex[i]);
        EnterQueue(Q, i);
      }
    }
  }

  free(Q);
}

/**
 * 广度优先搜索for图
 * @param {Graph}
 * @param {int} 
 */
void BFS2 (Graph G, int pos) {
  int i = 0, temp;

  Queue Q;
  InitQueue(&Q);

  for (i = 0; i < G -> vexnum; i++) {  //清零
    IsRead[i] = 0;
  }

  if(IsRead[pos] == 0) {
    IsRead[pos] = 1;
    printf("遍历顶点:%c\n",G->vertex[pos]);
  }

  EnterQueue(Q, pos);

  // 当队列不为空
  while (!isEmpty(Q)) {
    OutQueue(Q, &temp);
    for(i = 0; i< G->vexnum; i ++) {
      if(G->Arc[temp][i] != INFINITY && IsRead[i] == 0){
        IsRead[i] = 1;
        printf("遍历顶点:%c\n",G->vertex[i]);
        EnterQueue(Q,i);
      }
    }
  }

  free(Q);
}

/**
 * 广度优先
 * @param {Graph} 
 * @return {void}
 */
void BFS (Graph G) {
  if (G->kind == DG || G->kind == UDG) {
    BFS1(G,0);
  } else if (G->kind == DN || G->kind == UDN) {
    BFS2(G,0);
  }
}
