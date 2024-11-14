#ifndef __GRAPH_H__
#define __GRAPH_H__

typedef void* Graph;

/**
 * @brief 按照顶点集V和边弧集VR的定义构造图Graph
 * 
 * @param Graph 图
 * @param v 顶点数组
 * @param vr 边弧数组
 * @return Graph 图
 */
typedef Graph CreateGraph(Graph, void* v, void* vr);

/**
 * @brief 销毁图
 * 
 * @param Graph 图
 * @return 0 - 失败 | 1 - 成功
 */
typedef int DestroyGraph(Graph);

/**
 * @brief 若图中存在顶点 u， 则返回u在图中的位置
 * 
 * @param Graph 图
 * @param u 顶点
 * @return u顶点所在的位置
 */
typedef void* LocateVex(Graph, void* u);

/**
 * @brief 获得顶点V的值
 * 
 * @param Graph 图
 * @param v 顶点
 * @return v顶点的值
 */
typedef void* GetVex(Graph, void* v);

/**
 * @brief 将顶点V的值，设置成val
 * 
 * @param Graph 图
 * @param v 顶点
 * @param val 需要设置的值
 * @return 0 - 失败 | 1 - 成功
 */
typedef int PutVex(Graph, void* v, void* val);

/**
 * @brief 返回顶点v的一个邻接顶点，若顶点在G中无邻接顶点，则返回空
 * 
 * @param Graph 图
 * @param v 顶点
 * @return 邻接顶点
 */
typedef void* FirstAdjVex(Graph, void* v);

/**
 * @brief 返回顶点v相对于顶点w的下一个邻接顶点，若w是v的最后一个邻接点，则返回空
 * 
 * @param Graph 图
 * @param v 顶点
 * @return 邻接顶点
 */
typedef void* NextAdjVex(Graph, void* v, void* w);

/**
 * @brief 在图中添加新的顶点v
 * 
 * @param Graph 图
 * @param v 顶点
 * @return 0 - 失败 | 1 - 成功
 */
typedef int InsertVex(Graph, void* v);

/**
 * @brief 删除顶点v及相关的弧
 * 
 * @param Graph 图
 * @param v 顶点
 * @return 0 - 失败 | 1 - 成功
 */
typedef int DeleteVex(Graph, void* v);

/**
 * @brief 向图中增加弧<v, w>，若G是无向图，则还需要添加<w, v>
 * 
 * @param Graph 图
 * @param v 顶点
 * @param w 顶点
 * @return 0 - 失败 | 1 - 成功
 */
typedef int InsertArc(Graph, void* v, void* w);

/**
 * @brief 向图中删除弧<v, w>，若G是无向图，则还需要删除<w, v>
 * 
 * @param Graph 图
 * @param v 顶点
 * @param w 顶点
 * @return 0 - 失败 | 1 - 成功
 */
typedef int DeleteArc(Graph, void* v, void* w);

/**
 * @brief 对图G中进行深度优先遍历,在遍历过程中对每个顶点进行调用
 * 
 * @param Graph 图
 */
typedef void DFSTraverse(Graph);

/**
 * @brief 对图G中进行广度优先遍历,在遍历过程中对每个顶点进行调用
 * 
 * @param Graph 图
 */
typedef void HFSTraverse(Graph);

#endif