#include <stdio.h>
#include <stdlib.h>

#include "matrix_graph.h"

void MiniSpanTree_Prim(MGraph G)
{
    int min, i, j, k;
    int adjvex[MAXVEX]; // 保存相关顶点的下标
    int lowcost[MAXVEX]; // 保存相关顶点间的权值
    lowcost[0] = 0; // 初始化第一个权之为0, 即V0顶点加入生成树, 值为0 表示次下标的顶点已加入生成树
    adjvex[0] = 0; // 初始化第一个顶点下标为0
    for (i = 1; i < G.numVertexes; i++)
    {
        // 循环除下标为0 外的全部顶点
        lowcost[i] = G.arc[0][i]; // 将V0顶点与之有边的权值加入数组
        adjvex[i] = 0; // 初始化下标
    }

    for (i = 1; i < G.numVertexes; i++)
    {
        min = INFINITY; // 初始化 最小权值
        j = 1; k = 0;
        while(j < G.numVertexes) // 循环全部顶点
        {
            if (lowcost[j] != 0 && lowcost[j] < min)
            {
                // 如果权值不为0 且 权值 小于 min
                min = lowcost[j]; // 让最小值等于权值
                k = j; // 将当前最小下标给k
            }
            j++;
        }
        printf("(%d, %d) ", adjvex[k], k); // 打印当前顶点边中 权值最小的边
        lowcost[k] = 0; // 将当前顶点的权值设置为0, 表示此顶点已完成人物
        for (j = 1; j < G.numVertexes; j++) // 循环所有顶点
        {
            if (lowcost[j] != 0 && G.arc[k][j] < lowcost[j])
            {
                // 若下标为k顶点各边权值小于此前这些顶点未被加入生成树权值
                lowcost[j] = G.arc[k][j]; // 将最小权值存入 lowcost
                adjvex[j] = k; // 向下标为k的顶点存入 adjvex
            }
        }
    }
}