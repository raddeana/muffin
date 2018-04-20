#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

spQueue queueInit ()
{
    spQueue q;
    q->front = q->rear = 0;
    return q;
}

int queueEmpty(spQueue *q)
{
    return q->front == q->rear;
}


int enqueue (spQueue *q, datatype e)
{
    /* 队满 */
    if (q->rear == MAX_QUEUE_SIZE)
        return false;

    /* 入队 */
    q -> sp_queue_array[q->rear] = e;
    printf("q.sp_queue_array[%d]=%d\n", q->rear, e);
    q->rear += 1;
    
    return true;

}


int dequeue (spQueue *q, datatype *e)
{
    /* 队空 */
    if (queueEmpty(*q)) {
        return false;
    }

    /* 出队 */
    q->rear -= 1;
    *e = q->sp_queue_array[q->rear];
    return true;
}


void clearQueue(spQueue *q)
{
    q->front = q->rear = 0;
}


int getFront(spQueue *q, datatype *e)
{
    /* 队空 */
    if(q->front == q->rear)
        return false;

    /* 获取队头元素 */
    *e = q->sp_queue_array[q->front];
    return true;
}


int queueLen(spQueue *q)
{
    return (q->rear - q->front);
}


void traverseQueue(spQueue *q, void (*visit)(spQueue *q))
{
    visit(q);
}

void visit(spQueue *q)
{
    /* 队空 */
    if (q->front == q->rear) {
        printf("队列为空\n");
    }

    int temp = q->front;
    
    while(temp != q->rear)
    {
        printf("%d ",q->sp_queue_array[temp]);
        temp += 1;
    }
    
    printf("\n");
}
