#ifndef __STACK_H__
#define __STACK_H__

typedef void* Stack;

/**
 * @brief 初始化
 *
 * @param Stack指针
 * @return Stack指针
 */
typedef Stack(*InitStack)(Stack);

/**
 * @brief 销毁
 *
 * @param Stack指针
 * @return 0 - 失败 | 1 - 成功
 */
typedef int (*DestroyStack)(Stack);

/**
 * @brief 清空
 * 
 * @param Stack指针
 * @return 0 - 失败 | 1 - 成功
 */
typedef int (*CleanStack)(Stack);

/**
 * @brief 是否为空
 * 
 * @param Stack指针
 * @return 0 - 不为空 | 1 - 空
 */
typedef int (*IsEmpty)(Stack);

/**
 * @brief 返回栈顶元素
 * 
 * @param Stack指针
 * @param 元素
 * @return 元素
 */
typedef void* (*GetTop)(Stack, void*);

/**
 * @brief 进栈
 * 
 * @param Stack指针
 * @param 元素
 * @return 0 - 失败 | 1 - 成功
 */
typedef int (*Push)(Stack, void*);

/**
 * @brief 出栈，将顶部元素删除并返回
 * 
 * @param Stack指针
 * @param 元素
 * @return 元素
 */
typedef void* (*Pop)(Stack, void*);

/**
 * @brief 返回栈中元素个数
 * 
 * @param Stack指针
 * @return 元素个数
 */
typedef long (*StackLength)(Stack);

#endif