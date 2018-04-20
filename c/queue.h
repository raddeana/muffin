/**
  创建新队列
  判空
  进队
  出队
  清空队
  获得队头元素
  遍历队
  销毁队
  length
*/
/* 顺序队列接口定义头文件*/
#define true 1
#define false 0
#define MAX_QUEUE_SIZE 100

typedef int datatype;
typedef struct queue {
    datatype queue_array[MAX_QUEUE_SIZE];
    int front;
    int rear;
} spQueue;

/* 静态顺序链的接口定义 */
/* 静态链的初始化 */
spQueue queueInit();

/**
 * 判断队列是否为空,若为空
 * 返回true
 * 否则返回false
 */
int queueEmpty(spQueue *q);

/**
 * 插入元素e为队q的队尾新元素 
 * 插入成功返回true，队满返回false
 */
int enqueue(spQueue *q, datatype e);


/** 
 * 队头元素出队
 * 用e返回出队元素，并返回true，若队空返回false
 */
int dequeue(spQueue *q, datatype *e);

/** 
 * 清空队 
 */
void clearQueue(spQueue *q);

/** 
 * 获得队头元素
 * 队列非空，用e返回队头元素，并返回true，否则返回false
 */
int getfront(spQueue *q, datatype *e);

/** 
 * 获得length
 */
int queueLen(spQueue *q);

/**
 * 遍历队 
 */
void queueTraverse(spQueue *q, void(*visit)(spQueue *q));
void visit(spQueue *q);
