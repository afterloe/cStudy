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
 * @brief 初始化
 */
extern SqQueue* InitQueue(SqQueue *Q);

/**
 * @brief 指定元素 进队列
 */
extern int EnQueue(SqQueue *Q, void* elem);

/**
 * @brief 队列是否为空
 * 
 * @return 0 - 非空 | 1 - 空
 */
extern int QueueEmpty(SqQueue *Q);

/**
 * @brief 指定元素 出队列
 */
extern void* DeQueue(SqQueue *Q, void* elem);

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