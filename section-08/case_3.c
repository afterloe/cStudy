#include <stdlib.h>
#include <stdio.h>

#ifndef __CASE_3_C__
#define __CASE_3_C__

/**
 * @struct _biNode 二叉树节点
 * @brief 定义一颗二叉树 \n
 * 包含数据、左右孩子
 */
typedef struct _biTNode
{
    void* data; // 数据
    struct _biTNode* lchild; // 左孩子
    struct _biTNode* rchild; // 右孩子
} BiTNode, * BiTree;

/**
 * @brief 递归查询二叉排序树T中是否存在 key
 *
 *
 * @param[in] T 二叉树
 * @param[in] key 需要查询的值
 * @param[in] f T的前驱，根节点传NULL
 * @param[in] p 二叉查询树的指针
 * @ref 若查询成功，p会指向该数据元素所在的节点 \n
 * @ref 否则P会指向最后一个访问的节点
 * @return 执行结果
 * @retval 1    成功
 * @retval 0    失败
 * @par 调用示例
 * @code
 * void* ret = SearchBST(t, key, NULL, &t);
 * @endcond
 * @see ::SearchBST
 */
extern int SearchBST(BiTree T, void* key, BiTree f, BiTree* p);

/**
 * @brief 当树中不存在data元素时，进行插入
 *
 *
 * @param [in] T 二叉树
 * @param [in] data 数据
 * @return 执行结果
 * @retval 1    成功
 * @retval 0    失败
 * @par 调用示例
 * @code
 * int ret = InsertBST(T, 2);
 * @endcode
 * @see ::InesertBST
 */
extern int InesertBST(BiTree* T, void* data);

/**
 * @brief 删除树中指定的元素data
 *
 *
 * @param [in] T 二叉树
 * @param [in] data 数据
 * @return 执行结果
 * @retval 1    成功
 * @retval 0    失败
 * @par 调用示例
 * @code
 * int ret = DeleteBST(T, 2);
 * @endcode
 * @see ::DeleteBST
 */
extern int DeleteBST(BiTree* T, void* data);

#endif

int main(int argc, char** argv)
{
    int data, ret;
    BiTree T = NULL;
    char cmd;
    while (1)
    {
        printf("wait input cmd: ");
        scanf(" %c", &cmd);
        switch (cmd)
        {
        case 'q':
            printf("byb! ]\n");
            if (T != NULL)
            {
                free(T);
            }
            return EXIT_SUCCESS;
        case 'c':
            T = malloc(sizeof(BiTree));
            printf("create BiTree SUCCESS \n");
            break;
        case 'i':
            printf("input insert value: ");
            scanf("%d", &data);
            ret = InesertBST(&T, data);
            printf("INSERT %s \n", ret? "SUCCESS": "FAILD");
            break;
        case 's':
            printf("search value: ");
            scanf("%d", &data);
            ret = SearchBST(T, data, NULL, NULL);
            printf("%s FIND \n", ret? "": "Not");
            break;
        case 'd':
            printf("delete value: ");
            scanf("%d", &data);
            ret = DeleteBST(&T, data);
            printf("DELETE %s \n", ret? "SUCCESS": "FAILD");
            break;
        default:
            printf("cmd supper: q -> quit; c -> create; i -> insert, s -> search, d -> delete \n");
            break;
        }
    }
    return EXIT_SUCCESS;
}

int SearchBST(BiTree T, void* key, BiTree f, BiTree* p)
{
    if (!T)
    {
        // 查询不成功
        *p = f;
        return 0;
    }
    else if (key == T->data)
    {
        // 查找成功
        *p = T;
        return 1;
    }
    else if (key > T->data)
    {
        return SearchBST(T->lchild, key, T, p);
    }
    else
    {
        return SearchBST(T->rchild, key, T, p);
    }
}

int InesertBST(BiTree* T, void* data)
{
    BiTree ptr, node;
    if (!SearchBST(*T, data, NULL, &ptr))
    {
        // 查找不成功
        node = calloc(1, sizeof(BiTNode));
        node->data = data;
        node->lchild = node->rchild = NULL;
        if (!ptr)
        {
            *T = node;
        }
        else if (data < ptr->data)
        {
            ptr->lchild = node;
        }
        else
        {
            ptr->rchild = node;
        }
        return 1;
    }
    else
    {
        // 查找成功
        return 0;
    }
}

int DeleteBST(BiTree* T, void* data)
{
    if (!*T)
    {
        return 0;
    }
    else
    {
        if (data == (*T)->data)
        {
            // 找到关键字等于 key的元素
            return Delete(T);
        }
        else if (data < (*T)->data)
        {
            return DeleteBST(&(*T)->lchild, data);
        }
        else
        {
            return DeleteBST(&(*T)->rchild, data);
        }
    }
}

/**
 * @brief 删除树中的节点，并重新连接他的左或右子树，保持二叉树形状
 *
 *
 * @param[in] p 二叉树指针
 * @return 执行结果
 * @retval 1    成功
 * @retval 0    失败
 * @see ::DeleteBST
 */
int Delete(BiTree* p)
{
    BiTree q, s;
    if ((*p)->rchild == NULL) // 右子树为空， 则 只需要重新连接他的左子树
    {
        q = *p;
        *p = (*p)->lchild;
        free(q);
    }
    else if ((*p)->lchild == NULL) // 左子树为空， 则 只需要重新连接他的右子树
    {
        q = *p;
        *p = (*p)->rchild;
        free(q);
    }
    else // 左右 子树 均不为空
    {
        q = *p;
        s = (*p)->lchild;
        while (s->rchild) // 转 左， 然后向右的尽头（找到待删除节点的 前驱）
        {
            q = s;
            s = s->rchild;
        }
        (*p)->data = s->data; // s 指向被删节点的前驱
        if (q != *p)
        {
            q->rchild = s->lchild; // 重新连接 q 的右子树
        }
        else
        {
            q->lchild = s->lchild; // 重新连接 q 的 左子树
        }
        free(s);
    }

    return 1;
}