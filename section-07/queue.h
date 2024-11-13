#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef void* Queue;

/**
 * @brief 初始化
 * 
 * @param Queue 队列
 * @return 队列
 */
typedef Queue (*InitQueue)(Queue);

/**
 * @brief 销毁
 * 
 * @param Queue 队列
 * @return 0 - 失败 | 1 - 成功
 */
typedef int (*DestroyQueue)(Queue);

/**
 * @brief 清空队列
 * 
 * @param Queue 队列
 * @return 0 - 失败 | 1 - 成功
 */
typedef int (*ClearQueue)(Queue);

/**
 * @brief 队列是否为空
 * 
 * @param Queue 队列
 * @return 0 - 非空 | 1 - 空
 */
typedef int (*QueueEmpty)(Queue);

/**
 * @brief 获取队列 头部元素
 * 
 * @param Queue 队列
 * @param elem 元素
 * @return elem 元素
 */
typedef void* (*GetHead)(Queue, void*);

/**
 * @brief 进入队列
 * 
 * @param Queue 队列
 * @param elem 元素
 * @return 0 - 失败 | 1 - 成功
 */
typedef int (*EnQueue)(Queue, void*);

/**
 * @brief 删除队列中的对头元素，并返回
 * 
 * @param Queue 队列
 * @param elem 元素
 * @return elem 元素
 */
typedef void* (*DeQueue)(Queue, void*);

/**
 * @brief 队列长度
 * 
 * @param Queue 队列
 * @return 队列长度
 */
typedef long (*QueueLength)(Queue);

#endif