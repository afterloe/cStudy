#ifndef __SQ_QUEUE_H__
#define __SQ_QUEUE_H__

/**
 * 基于数组实现的队列
 * 
 * 确定队列长度选择数组
 */
#define MAXSIZE 128

typedef void* QElem;

typedef struct _sqQueue {
    QElem data[MAXSIZE];
    int front; // 头指针
    int rear; // 尾指针， 若队列不为空， 指向队列尾元素的下一个位置
} SqQueue;


/**
 * 基于链表实现
 * 
 * 不确定长度 选择链表
 */

typedef struct _QNode {
    QElem data; // 数据
    struct _QNode* next; // 下一个节点
} QNode, * QueuePtr;

typedef struct _linkQueue {
    QueuePtr front; // 队头指针
    QueuePtr rear; // 队尾 指针
} LinkQueue;

#endif