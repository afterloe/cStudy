#ifndef __ORDER_STACK_H__
#define __ORDER_STACK_H__
/**
 * 元素大小可控 用顺序栈，否则用 链栈
 */


/**
 * 顺序栈
 * 
 * 使用数组实现，top表示栈顶位置，当top 小于 MAX_SIZE - 1 时 表示 栈满
 */

#define MAX_SIZE 1500

typedef int SElem;

typedef struct _sq_stack
{
    SElem data[MAX_SIZE];
    int top;  // 用于栈顶指针
} SqStack;

/**
 * 链式存储的栈 - 链栈
 * 
 * 使用链表实现
 */
typedef struct _stack_node
{
    SElem data;
    struct _stack_node *next;
} StackNode, *LinkStackPtr;

typedef struct _link_stack
{
    LinkStackPtr top;
    int count;
} LinkStack;

/**
 * 当新的元素压进栈后，将栈顶的指针给到新元素，再将next指向之前的元素
 */

#endif