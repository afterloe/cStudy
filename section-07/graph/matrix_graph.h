#ifndef __MATRIX_GRAPH_H__
#define __MATRIX_GRAPH_H__

typedef void* VertexType; // 顶点类型， 由用户定义
typedef void* EdgeType; // 边上的权值类型，由用户定义

/**
 * 采用 邻接矩阵 结构的 图存储
 */
#define MAXVEX 100 // 最大顶点数， 由用户定义
#define INFINITY 65535 // 用65535 来代表一个不存在的数

typedef struct _mGraph
{
    VertexType vexs[MAXVEX]; // 顶点集合
    EdgeType arc[MAXVEX][MAXVEX]; // 邻接矩阵， 边表, 权的值存储在这里
    int numVertexes; // 图中顶点数
    int numEdges; // 图中边数
} MGraph;

/**
 * 采用 邻接表 结构的 图存储
 */
typedef struct _edgeNode  // 边表节点
{
    int adjvex; // 邻接点域， 存储该顶点对应的下标
    EdgeType weight; // 权域， 用于存储权的值，对于非网图可以不需要
    struct _edgeNode* next; // 链域， 指向下一个邻接点
} EdgeNode;

typedef struct _vertexNode // 顶点表节点
{
    VertexType data; // 顶点域， 存储顶点的数据信息
    EdgeNode* firstedge; // 边表头指针
} VertexNode, AdjList[MAXVEX];

typedef struct _graphAdjList // 图的最外层
{
    AdjList AdjList; // 顶点表 节点信息
    int numVertexes; // 图中顶点数
    int numEdges; // 图中边数
} *GraphAdjList;

/**
 * 十字链表 - 快速计算顶点的出度和入度
 */
 //表示链表中存储弧的结点
typedef struct _arcBox {
    int tailvex; // 弧尾 对应顶点在顺序表中的位置下标
    int headvex; //弧头 对应顶点在顺序表中的位置下标
    struct _arcBox* hlik; // hlik 指向下一个以当前顶点为弧头的弧结点；
    struct _arcBox* tlink;  // tlink 指向下一个以当前顶点为弧尾的弧结点；
    EdgeType weight; // opt - 存储弧的权 相关信息
} ArcBox;

//表示顺序表中的各个顶点
typedef struct _vexNode {
    VertexType data; //顶点的数据域
    ArcBox* firstin; // 指向以该顶点为弧头的链表首个结点
    ArcBox* firstout;  // 指向以该顶点为弧尾的链表首个结点
} VexNode;

//表示十字链表存储结构
typedef struct _oLGraph {
    VexNode xlist[MAXVEX];  // 存储顶点的顺序表
    int vexnum, arcnum; // 记录图的顶点数和弧数
} OLGraph;

#endif