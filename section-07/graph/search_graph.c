#include <stdlib.h>
#include <stdio.h>

#include "matrix_graph.h"
#include "sq_queue.h"


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





// 邻接矩阵 的广度遍历算法
void BFSTraverse(MGraph G)
{
    int i, j;
    SqQueue* Q;
    for (i = 0; i < G.numVertexes; i++)
    {
        visited[i] = FALSE;
    }
    Q = InitQueue(Q); // 初始化队列
    for (i = 0; i < G.numVertexes; i++)
    {
        if (visited[i])  // 若节点访问过 则跳出循环
        {
            continue;
        }
        visited[i] = TRUE;
        printf("%p ", G.vexs[i]); // 操作节点数据
        EnQueue(Q, i); // 压节点进入 队列
        while(!QueueEmpty(Q)) // 如果队列不为空
        {
            i = DeQueue(Q, &i); // 队头出列，并将地址赋给i
            for (j = 0; j < G.numVertexes; j++)
            {
                if (G.arc[i][j] == 1 && !visited[j]) // 判断其他顶点与当前顶点存在边，且未被访问过
                {
                    visited[j] = TRUE;
                    printf("%p ", G.vexs[j]);
                    EnQueue(Q, j); // 将找到的顶点加入队列
                }
            }
        }
    }
}

// 邻接表 的广度遍历算法
void BFSAdjTraverse(GraphAdjList GL)
{
    int i;
    EdgeNode *p;
    SqQueue* Q;
    for (i = 0; i < GL->numVertexes; i++)
    {
        visited[i] = FALSE;
    }
    Q = InitQueue(Q);
    for (i = 0; i < GL->numVertexes; i++)
    {
        if(visited[i]) {
            continue;
        }
        visited[i] = TRUE;
        printf("%p ", GL->AdjList[i].data);
        EnQueue(Q, i);
        while (!QueueEmpty(Q))
        {
            i = DeQueue(Q, &i);
            p = GL->AdjList[i].firstedge; // 找到当前顶点边表链表的头指针
            while(p)
            {
                if(!visited[p->adjvex])
                {
                    visited[p->adjvex] = TRUE;
                    printf("%p ", GL->AdjList[p->adjvex].data);
                    EnQueue(Q, p->adjvex);
                }
                p = p->next; // 指向下一个邻接点
            }
        }
        
    }
}