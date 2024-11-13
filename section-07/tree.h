#ifndef __TREE_H__
#define __TREE_H__

typedef void* Tree;

/**
 * @brief 构建空树
 * 
 * @param Tree 树
 * @return 构建的树
 */
typedef Tree (*InitTree)(Tree);

/**
 * @brief 销毁树
 * 
 * @param Tree 树
 * @return 0 - 失败 | 1 - 成功
 */
typedef int (*DestroyTree)(Tree);

/**
 * @brief 按照definition中给出的树定义来构建树
 * 
 * @param Tree 树
 * @param definition 树定义
 * @return 构建的树
 */
typedef Tree (*CreateTree)(Tree, void* definition);

/**
 * @brief 清空树
 * 
 * @param Tree 树
 * @return 0 - 失败 | 1 - 成功
 */
typedef int (*ClearTree)(Tree);

/**
 * @brief 树是否为空
 * 
 * @param Tree 树
 * @return 0 - 非空 | 1 - 空
 */
typedef int (*TreeEmpty)(Tree);

/**
 * @brief 树的深度
 * 
 * @param Tree 树
 * @return 树的深度
 */
typedef int (*TreeDepth)(Tree);

/**
 * @brief 返回树的根节点
 * 
 * @param Tree 树
 * @param root 根节点
 * @return 根节点
 */
typedef void* (*Root)(Tree, void*);

/**
 * @brief 返回指定节点的值
 * 
 * @param Tree 树
 * @param cur_e 树中的节点
 * @param val 值
 * @return 值
 */
typedef void* (*Value)(Tree, void*, void*);

/**
 * @brief 给指定节点赋值
 * 
 * @param Tree 树
 * @param cur_e 树中的节点
 * @param val 值
 * @return 0 - 失败 | 1 - 成功
 */
typedef int (*Assign)(Tree, void*, void*);

/**
 * @brief 指定节点的前驱
 * 
 * @param Tree 树
 * @param cur_e 树中的节点
 * @param parent 前驱
 * @return parent 前驱
 */
typedef void* (*Parent)(Tree, void*, void*);

/**
 * @brief 查询指定节点的最左侧孩子
 * 
 * @param Tree 树
 * @param cur_e 树中的节点
 * @param child 子结点
 * @return child 子结点
 */
typedef void* (*LeftChild)(Tree, void*, void*);

/**
 * @brief 查询指定节点的右兄弟
 * 
 * @param Tree 树
 * @param cur_e 树中的节点
 * @param brother 兄弟节点
 * @return brother 兄弟节点
 */
typedef void* (*RightSibling)(Tree, void*, void*);

/**
 * @brief 向树中的 指定节点 增加孩子
 * 
 * 其中cure_e指向树Tree的某个节点， extent为该节点的度加1, 非空树/子结点 child 与Tree不相交， 操作结果为插入child为树Tree中的cur_e指向的第i颗树
 * 
 * @param Tree 树
 * @param cur_e 树中的节点
 * @param extent 度
 * @param child 子结点
 * @return 0 - 失败 | 1 - 成功
 */
typedef int (*InsertChild)(Tree, void*, int, void*);

/**
 * @brief 向树中的 指定节点 删除孩子
 * 
 * 其中cure_e指向树Tree的某个节点， extent为该节点的度, 操作结果为删除Tree中cur_e指向的第i颗树，并返回
 * 
 * @param Tree 树
 * @param cur_e 树中的节点
 * @param extent 度
 * @param child 子结点
 * @return child 子结点
 */
typedef void* (*DeleteChild)(Tree, void*, int, void*);

#endif