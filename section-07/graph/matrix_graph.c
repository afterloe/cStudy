#include <stdio.h>
#include <stdlib.h>

#include "matrix_graph.h"

void CreateMGraph(MGraph* G)
{
    int i, j, k, w;
    printf("input Vertexes and Edges in Graph. \n");
    scanf("%d, %d", &G->numVertexes, &G->numEdges); // 输入顶点数 和 边数
    for (i = 0; i < G->numVertexes; i++)
    {
        scanf(&G->vexs[i]); // 输入顶点信息， 建立顶点表
    }

    for (i = 0; i < G->numVertexes; i++)
    {
        for (j = 0; j < G->numVertexes; j++)
        {
            G->arc[i][j] = INFINITY; // 初始化，给邻接矩阵中所有的元素赋 不存在的值
        }
    }

    for (k = 0; k < G->numEdges; k++)
    {
        printf("input edge (Vi, Vj), i. j and wigth: \n");
        scanf("%d,%d,%d", &i, &j, &w); // 输入 边（Vi， Vj）上的权 w
        G->arc[i][j] = w;
        G->arc[j][i] = G->arc[i][j]; // 无向图， 矩阵对称
    }
}

void CreateALGraph(GraphAdjList* G)
{
    int i, j, k;
    EdgeNode* e;
    printf("input Vertexes and Edges in Graph. \n");
    scanf("%d, %d", &G->numVertexes, &G->numEdges); // 输入顶点数 和 边数
    for (i = 0; i < G->numVertexes; i++) // 建立顶点
    {
        scanf(&G->AdjList[i].data);  // 输入顶点信息
        G->AdjList[i].firstedge = NULL; // 将边表的第一个边设置为空表
    }
    for (k = 0; k < G->numEdges; k++) // 建立边
    {
        printf("input edge (Vi, Vj) \n");
        scnaf("%d,%d", &i, &j); // 输入边(Vi, Vj)上的顶点序号

        e = malloc(sizeof(EdgeNode)); // 生成边表节点
        e->adjvex = j; // 邻接序号为 j
        e->next = G->AdjList[i].firstedge; // 将e指针指向当前顶点指向的节点
        G->AdjList[i].firstedge = e; // 将当前定点的指针指向e

        e = malloc(sizeof(EdgeNode));
        e->adjvex = i; // 邻接点为 i
        e->next = G->AdjList[j].firstedge;
        G->AdjList[j].firstedge = e;
    }
}