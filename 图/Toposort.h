#ifndef TOPOSORT_H
#define TOPOSORT_H

#include "grpTypeDef.h"
#include <stack>
#include <queue>

//*******************************************************************//
//* 函 数 名：CalcInDegreeByMatrix                                  *//
//* 函数功能：根据邻接矩阵计算每个顶点的入度                          *//
//* 入口参数：Graph &G，图                                           *//
//* 出口参数：int indegree[]，入度数组（1-indexed，长度 >= VerNum+1）*//
//*******************************************************************//
void CalcInDegreeByMatrix(Graph &G, int indegree[])
{
    for (int i = 1; i <= G.VerNum; i++)
        indegree[i] = 0;

    for (int i = 1; i <= G.VerNum; i++)
    {
        for (int j = 1; j <= G.VerNum; j++)
        {
            // 非0且非INF表示有边 i -> j
            if (G.AdjMatrix[i][j] != 0 && G.AdjMatrix[i][j] < INF)
                indegree[j]++;
        }
    }
}

//*******************************************************************//
//* 函 数 名：CalcInDegreeByList                                    *//
//* 函数功能：根据邻接表计算每个顶点的入度                            *//
//* 入口参数：Graph &G，图                                           *//
//* 出口参数：int indegree[]，入度数组（1-indexed，长度 >= VerNum+1）*//
//*******************************************************************//
void CalcInDegreeByList(Graph &G, int indegree[])
{
    for (int i = 1; i <= G.VerNum; i++)
        indegree[i] = 0;

    for (int u = 1; u <= G.VerNum; u++)
    {
        EdgeNode* p = G.VerList[u].firstEdge;
        while (p != NULL)
        {
            indegree[p->adjVer]++;
            p = p->next;
        }
    }
}

//*******************************************************************//
//* 函 数 名：TopoSortKahnByMatrix                                  *//
//* 函数功能：Kahn算法（BFS）对邻接矩阵存储的图进行拓扑排序          *//
//* 入口参数：Graph &G，图                                           *//
//* 出口参数：int result[]，存放拓扑序列（1-indexed，长度>=VerNum+1）*//
//* 返 回 值：bool，true=排序成功（DAG），false=存在环               *//
//*******************************************************************//
bool TopoSortKahnByMatrix(Graph &G, int result[])
{
    int indegree[MAXVEX + 1];
    CalcInDegreeByMatrix(G, indegree);

    std::queue<int> q;  // 也可用 stack，此处用队列
    for (int i = 1; i <= G.VerNum; i++)
    {
        if (indegree[i] == 0)
            q.push(i);
    }

    int cnt = 0;  // 已输出的顶点数
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        result[++cnt] = u;  // 存入结果数组

        // 遍历 u 的所有邻接顶点
        for (int v = 1; v <= G.VerNum; v++)
        {
            if (G.AdjMatrix[u][v] != 0 && G.AdjMatrix[u][v] < INF)
            {
                indegree[v]--;
                if (indegree[v] == 0)
                    q.push(v);
            }
        }
    }

    // cnt < VerNum 说明图中存在环
    return (cnt == G.VerNum);
}

//*******************************************************************//
//* 函 数 名：TopoSortKahnByList                                    *//
//* 函数功能：Kahn算法（BFS）对邻接表存储的图进行拓扑排序            *//
//* 入口参数：Graph &G，图                                           *//
//* 出口参数：int result[]，存放拓扑序列（1-indexed，长度>=VerNum+1）*//
//* 返 回 值：bool，true=排序成功（DAG），false=存在环               *//
//*******************************************************************//
bool TopoSortKahnByList(Graph &G, int result[])
{
    int indegree[MAXVEX + 1];
    CalcInDegreeByList(G, indegree);

    std::stack<int> s;  // 此处用栈，与原实现保持一致
    for (int i = 1; i <= G.VerNum; i++)
    {
        if (indegree[i] == 0)
            s.push(i);
    }

    int cnt = 0;
    while (!s.empty())
    {
        int u = s.top();
        s.pop();
        result[++cnt] = u;

        EdgeNode* p = G.VerList[u].firstEdge;
        while (p != NULL)
        {
            int v = p->adjVer;
            indegree[v]--;
            if (indegree[v] == 0)
                s.push(v);
            p = p->next;
        }
    }

    return (cnt == G.VerNum);
}

//*******************************************************************//
//* 函 数 名：TopoSortDFSByMatrix                                   *//
//* 函数功能：DFS算法对邻接矩阵存储的图进行拓扑排序                   *//
//* 入口参数：Graph &G，图                                           *//
//* 出口参数：int result[]，存放拓扑序列（1-indexed，长度>=VerNum+1）*//
//* 返 回 值：bool，true=排序成功（DAG），false=存在环               *//
//*******************************************************************//
bool TopoSortDFSByMatrix(Graph &G, int result[])
{
    int visited[MAXVEX + 1] = {0};  // 0=未访问, 1=访问中, 2=已完成
    int cnt = 0;

    for (int start = 1; start <= G.VerNum; start++)
    {
        if (visited[start] != 0) continue;

        // 非递归DFS
        struct Frame { int u; int nextV; int state; };
        Frame stk[MAXVEX + 1];
        int stkTop = 0;
        stk[++stkTop] = {start, 1, 0};

        while (stkTop > 0)
        {
            Frame& f = stk[stkTop];
            if (f.state == 0)  // 首次进入
            {
                visited[f.u] = 1;  // 标记访问中
                f.state = 1;
            }

            bool found = false;
            for (int v = f.nextV; v <= G.VerNum; v++)
            {
                if (G.AdjMatrix[f.u][v] != 0 && G.AdjMatrix[f.u][v] < INF)
                {
                    if (visited[v] == 1)  // 回边，有环
                        return false;
                    if (visited[v] == 0)
                    {
                        f.nextV = v + 1;  // 保存进度
                        stk[++stkTop] = {v, 1, 0};
                        found = true;
                        break;
                    }
                }
            }

            if (!found)  // 所有邻接顶点处理完毕
            {
                visited[f.u] = 2;
                result[++cnt] = f.u;  // 后续会反转
                stkTop--;
            }
        }
    }

    // 反转得到拓扑序（DFS是逆序的）
    for (int i = 1; i <= cnt / 2; i++)
    {
        int tmp = result[i];
        result[i] = result[cnt - i + 1];
        result[cnt - i + 1] = tmp;
    }
    return true;
}

//*******************************************************************//
//* 函 数 名：TopoSortDFSByList                                     *//
//* 函数功能：DFS算法对邻接表存储的图进行拓扑排序                     *//
//* 入口参数：Graph &G，图                                           *//
//* 出口参数：int result[]，存放拓扑序列（1-indexed，长度>=VerNum+1）*//
//* 返 回 值：bool，true=排序成功（DAG），false=存在环               *//
//*******************************************************************//
bool TopoSortDFSByList(Graph &G, int result[])
{
    int visited[MAXVEX + 1] = {0};  // 0=未访问, 1=访问中, 2=已完成
    int cnt = 0;

    // 手动栈实现非递归DFS
    struct Frame
    {
        int u;
        EdgeNode* nextEdge;  // 下一个要处理的边
        int state;           // 0=首次进入, 1=处理邻接点中
    };

    for (int start = 1; start <= G.VerNum; start++)
    {
        if (visited[start] != 0) continue;

        Frame stk[MAXVEX + 1];
        int stkTop = 0;
        stk[++stkTop] = {start, G.VerList[start].firstEdge, 0};

        while (stkTop > 0)
        {
            Frame& f = stk[stkTop];
            if (f.state == 0)
            {
                if (visited[f.u] == 1) return false;  // 回边，有环
                visited[f.u] = 1;
                f.state = 1;
            }

            // 找到下一个未访问的邻接点
            EdgeNode* p = f.nextEdge;
            bool found = false;
            while (p != NULL)
            {
                int v = p->adjVer;
                if (visited[v] == 1) return false;  // 回边，有环
                if (visited[v] == 0)
                {
                    f.nextEdge = p->next;  // 保存进度
                    stk[++stkTop] = {v, G.VerList[v].firstEdge, 0};
                    found = true;
                    break;
                }
                p = p->next;
            }

            if (!found)
            {
                visited[f.u] = 2;
                result[++cnt] = f.u;
                stkTop--;
            }
        }
    }

    // 反转得到拓扑序
    for (int i = 1; i <= cnt / 2; i++)
    {
        int tmp = result[i];
        result[i] = result[cnt - i + 1];
        result[cnt - i + 1] = tmp;
    }
    return true;
}

//*******************************************************************//
//* 函 数 名：IsDAGByMatrix                                         *//
//* 函数功能：判断邻接矩阵存储的图是否为有向无环图（DAG）            *//
//* 入口参数：Graph &G，图                                           *//
//* 返 回 值：bool，true=是DAG，false=存在环                         *//
//*******************************************************************//
bool IsDAGByMatrix(Graph &G)
{
    int result[MAXVEX + 1];
    return TopoSortKahnByMatrix(G, result);
}

//*******************************************************************//
//* 函 数 名：IsDAGByList                                           *//
//* 函数功能：判断邻接表存储的图是否为有向无环图（DAG）              *//
//* 入口参数：Graph &G，图                                           *//
//* 返 回 值：bool，true=是DAG，false=存在环                         *//
//*******************************************************************//
bool IsDAGByList(Graph &G)
{
    int result[MAXVEX + 1];
    return TopoSortKahnByList(G, result);
}

//*******************************************************************//
//* 函 数 名：PrintTopoResult                                       *//
//* 函数功能：打印拓扑排序结果                                       *//
//* 入口参数：int result[]，拓扑序列；int n，顶点数                  *//
//*******************************************************************//
void PrintTopoResult(int result[], int n)
{
    printf("拓扑排序结果：");
    for (int i = 1; i <= n; i++)
        printf("%d ", result[i]);
    printf("\n");
}

#endif // TOPOSORT_H
