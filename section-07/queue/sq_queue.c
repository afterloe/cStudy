#include <stdlib.h>

#include "sq_queue.h"

/**
 * 循环队列 实现
 */

SqQueue* InitQueue(SqQueue *Q) 
{
    SqQueue* ptr = calloc(1, sizeof(SqQueue));
    ptr->front = 0;
    ptr->rear = 0;
    Q = ptr;
    return Q;
}

long QueueLength(SqQueue *Q) 
{
    return (Q->rear - Q->front + MAXSIZE) % MAXSIZE;
}

int EnQueue(SqQueue *Q, void* elem) 
{
    if ((Q->rear + 1) % MAXSIZE == Q->front) 
    {
        // 队列超出
        return -1;
    }

    Q->data[Q->rear] = elem;
    Q->rear = (Q->rear + 1) % MAXSIZE;

    return Q->rear - 1;
}

void* DeQueue(SqQueue *Q, void* elem)
{
    if (Q->front == Q->rear)
    {
        // 队列为空
        return NULL;
    }
    elem = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;

    return elem;
}