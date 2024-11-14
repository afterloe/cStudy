#ifndef __PARENT_TREE__
#define __PARENT_TREE__

// 双亲表示法 - 基于数组实现

// 没有的用 -1 表示
#define MAX_TREE_SIZE 100

typedef void* TElem;

typedef struct _parentTreeNode {
    TElem data; // 节点数据
    int parent; // 双亲的位置

    int firstchild; // opt - 最左侧孩子的位置
    int rightsib; // opt - 右侧兄弟的位置
} PTNode;

/*
 * 结构不是固定的，看业务是否适合，是否方便
 */

typedef struct _parentTree {
    PTNode nodes[MAX_TREE_SIZE]; // 节点数组
    int root; // 根节点位置
    int nodeNum; // 节点数
} PTree;

// 孩子表示法 - 数组 + 多重链表

// # 方法1： 每个节点有多个指针域，其最大值就是树的度，其中每个指针指向一颗子树的根节点
// > 由于树中的各节点的度相差很大，会有很多空的指针域，浪费比较多的空间。但各节点的度相差很小如二叉树，则空间又被充分利用了

// # 方法2： 指针域按需分配 节点内多一个度的大小
// > 空间利用率高，但每个指针需要维护度的数值，运算时间上消耗较大

// # 方法3： 减少空指针的浪费，又减少计算时间的方法
// > 把每个结点的孩子结点排列起来，以单链表作为存储结构，则n个结点就有n个孩子链表，若叶子结点则此链表为空。
// > 然后n个头指针又组成一个线性表，采用顺序存储结构，在一个一维数组中。

typedef struct _cTNode {
    int child; // 数据域， 用于存储某个结点再表头数组中的下标。
    struct _cTNode *next;  // 值相某结点的下一个孩子结点的指针
} *ChildPtr, *NodePtr;

typedef struct _cTBox {
    TElem data; // 数据
    ChildPtr firstchild; // 结点的第一个孩子

    NodePtr parent; // opt - 双亲的指针
    NodePtr rightsib; //  opt - 右侧兄弟的指针
} CTBox;

typedef struct _cTree {
    CTBox nodes[MAX_TREE_SIZE]; // 结点数组
    int root; // 根结点位置
    int nodeNum; // 结点数
} CTree;

// 孩子兄弟表示法
// > 任意一个棵树，它的结点的第一个孩子如个存在就是唯一，他的右兄弟如果存在也是唯一的
typedef struct _cSNode {
    TElem data;
    struct _cSNode *firstchild;  // 左侧第一个孩子
    struct _cSNode *rightsib; // 右兄弟
    struct _cSNode *parent; // opt - 父结点
} CSNode, *CSTree;
#endif