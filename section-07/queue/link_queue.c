#include <stdlib.h>
#include <stdio.h>

#include "sq_queue.h"

int EnQueue(LinkQueue* Q, void* elem)
{
    QueuePtr node = malloc(sizeof(QueuePtr));
    if (!node)
    {
        perror("malloc :");
        return -1;
    }
    node->data = elem;
    node->next = NULL;

    Q->rear->next = node; // 把新节点放到 队尾的后继
    Q->rear = node; // 把新节点设置为 对尾

    return 1;
}

void* DeQueue(LinkQueue* Q, void* elem)
{
    QueuePtr ptr;
    if (Q->front == Q->rear)
    {
        // 队列为空
        return NULL;
    }

    ptr = Q->front->next; // 将要删除的节点暂存
    elem = ptr->data; // 取值
    Q->front->next = ptr->next;  // 将头节点位置重新指回 被删节点的 下一个节点

    if (Q->rear == ptr)
    {
        // 如果被删节点是队尾， 则队尾 赋值给对头， 队列为空
        Q->rear = Q->front;
    }
    free(ptr);

    return elem;
}