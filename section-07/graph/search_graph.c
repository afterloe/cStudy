#include <stdlib.h>
#include <stdio.h>

#include "matrix_graph.h"


#define TRUE  1
#define FALSE 0

typedef int Boolean; // 定义 Boolean变量， 值为TRUE 或 FALSE
Boolean visited[MAXVEX];  // 访问标志 树组

// 邻接矩阵 的 深度优先递归算法
void DFS(MGraph G, int i)
{
    int j;
    visited[i] = TRUE;
    printf("%p", G.vexs[i]); // 打印顶点 或 其他操作
    for (j = 0; j < G.numVertexes; j++)
    {
        if(G.arc[i][j] == 1 && !visited[j])
        {
            DFS(G, j); // 递归调用
        }
    }
}

// 邻接矩阵 深度优先 遍历操作
void DFSTraverse(MGraph G)
{
    int i;
    for (i = 0; i < G.numVertexes; i++)
    {
        visited[i] = FALSE;  // 初始化所有的顶点状态 为未访问 状态
    }
    for (i = 0; i < G.numVertexes; i++)
    {
        if (!visited[i]) // 对未访问过的顶点调用 DFS， 若是连通图，只会执行一次
        {
            DFS(G, i);
        }
    }
}


// 邻接表的深度优先 递归算法
void DFSAdjList(GraphAdjList GL, int i)
{
    EdgeNode *p;
    visited[i] = TRUE;
    printf("%p", GL->AdjList[i].data);
    p = GL->AdjList[i].firstedge;
    while (p)
    {
        if (!visited[p->adjvex])
        {
            DFSAdjList(GL, p->adjvex);
        }
        p = p->next;
    }
}

// 邻接表的深度遍历操作
void DFSAdjTraverse(GraphAdjList GL)
{
    int i;
    for (i = 0; i < GL->numVertexes; i++)
    {
        visited[i] = FALSE;
    }
    for (i = 0; i < GL->numVertexes; i++)
    {
        if (!visited[i])
        {
            DFSAdjList(GL, i);
        }
    }
}