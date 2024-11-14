#ifndef __BI_TREE_H__
#define __BI_TREE_H__

typedef void* TElem;

/*
    二叉树的 链表形式 - 二叉链表
*/
typedef struct _biTNode {
    TElem data; // 二叉树 数据域
    struct _biTNode *lchild; // 左孩子
    struct _biTNode *rchild; // 右孩子
    struct _biTnode *parent; // opt - 双亲， 加上后 就是 三叉链表
} BiTNode, *BiTree;

/*
    线索二叉树
*/
typedef enum {Link, Thread} PointerTag; /* Link = 0 时，表示指针指向左右孩子指针; 1 时指向前驱或后继 */

/**
 * 线索化的过程就是在遍历的时候修改空指针
 */
typedef struct _biThrNode
{
    TElem data;  // 数据域
    struct _biThrNode *lchild; // 左孩子 指针
    struct _biThrNode *rchild; // 右孩子 指针
    PointerTag LTag; // 左标志，为0时（Link） lchild 指向左孩子，为1时（Thread）指向前驱
    PointerTag RTag; // 右标志，为0时（Link） rchild 指向右孩子，为1时（Thread）指向后继
} BiThrNode, *BiThrTree;

#endif