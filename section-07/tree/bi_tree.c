#include <stdlib.h>
#include <stdio.h>
#include "bi_tree.h"

/* 前序遍历递归算法 */
void PreOrderTraverse(BiTree T)
{
    if(T == NULL)
    {
        return;
    }
    printf("%p", T->data); /* 显示结点的数据 */
    PreOrderTraverse(T->lchild); /* 先遍历左子树 */
    PreOrderTraverse(T->rchild); /* 后遍历右子树 */
}

/* 中序遍历 */
void InOrderTraverse(BiTree T)
{
    if (T == NULL)
    {
        return;
    }
    InOrderTraverse(T->lchild); /* 中序遍历左子树 */
    printf("%p", T->data); /* 显示结点数据 */
    InOrderTraverse(T->rchild); /* 中序遍历右子树 */
}

/* 后序遍历 */
void PostOrderTraverse(BiTree T)
{
    if (T == NULL)
    {
        return;
    }
    PostOrderTraverse(T->lchild); /* 现后序遍历左子树 */
    PostOrderTraverse(T->rchild); /* 再后续遍历右字树 */
    printf("%p", T->data); /* 显示结点数据 */
}

/* 按现序输入二叉树中结点的值 */
/* 构建二叉链表表示二叉树T */
BiTree CreateBiTree(BiTree *T)
{
    TElem ch;
    scanf("%c", ch);
    if (ch == '#')
    {
        *T = NULL; // `#`字符表示 空树，即检测到‘#’就终止构建
    } 
    else 
    {
        *T = malloc(sizeof(BiTree));
        if (!*T)
        {
            perror("malloc :");
            return NULL;
        }
        (*T)->data = ch;
        CreateBiTree(&(*T)->lchild); // 构建左子树
        CreateBiTree(&(*T)->rchild); // 构建右子树
    }
}

/*
    线索二叉树
*/
BiThrTree pre; // 全局变量 - 始终指向刚刚访问的结点
void InThreading(BiThrTree p) // 在中序遍历进行中进行线索化
{
    if (!p)
    {
        return;
    }
    InThreading(p->lchild); // 先左侧线索化

    if (!p->lchild)
    {
        // 没有左孩子
        p->LTag = Thread; // 修改标志
        p->lchild = pre;  // 左侧孩子指针 指向 前驱
    }

    if (!pre->rchild)
    {
        // 前驱 没有右孩子
        pre->RTag = Thread; // 修改标志 前驱 标志
        pre->rchild = p; // 前驱的 右孩子指向 后继(当前结点)
    }

    pre = p; // 保持pre指向p的前驱

    InThreading(p->rchild); // 后右侧 线索化
}

/*
T 指向头结点，头结点左键lchild指向根结点(线索化时已绑定)，头结点的右键rchild指向中序遍历的最后一个结点。

中序遍历二叉线索链表示的二叉树T
*/
void InOrderTraverse_Thr(BiThrTree T)
{
    BiThrTree p; // 定义根结点
    p = T->lchild; // 先将p指向根节点

    while(p != T) // 空树或 遍历结束时 p == T
    {
        while (p->LTag == Link) // 当指向孩子时，调整指向到中序序列第一个左孩子结点
        {
            p = p->lchild;
        }

        printf("%p", p->data); // 操作结点
        
        while (p->RTag == Thread && p->rchild != T) // 指向前驱或后继 并且 右孩子不为空
        {
            p = p->rchild;
            printf("%p", p->data);
        }
        p = p->rchild; // p 指向右子树根
    }
}