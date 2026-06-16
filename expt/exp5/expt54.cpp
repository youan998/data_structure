#include "grpTypeDef.h"
#include "createGrpAdjMatrix.h"
#include "createGrpAdjLinkedList.h"
#include <iostream>
#include <queue>
using namespace std;
//邻接表存储的图的BFS算法实现
void BFS(Graph &G, int v, int visited[])
{
    queue<int> q;        // BFS 辅助队列
    visited[v] = 1;      // 标记起点已访问
    q.push(v);           // 起点入队

    while (!q.empty())
    {
        int cur = q.front();  // 取出队首顶点
        q.pop();
        // 输出映射后的编号（A=1, B=2, ..., J=10）
        cout << (G.VerList[cur].data - 'A' + 1) << " ";

        EdgeNode* p = G.VerList[cur].firstEdge;
        while (p != NULL)
        {
            if (visited[p->adjVer] == 0)
            {
                visited[p->adjVer] = 1;  // 入队时就标记，防止重复入队
                q.push(p->adjVer);
            }
            p = p->next;
        }
    }
}                   
//临界矩阵存储的图的BFS算法实现 
void BFS2(Graph &G, int v, int visited[])
{
    queue<int> q;        // BFS 辅助队列
    visited[v] = 1;      // 标记起点已访问
    q.push(v);           // 起点入队

    while (!q.empty())
    {
        int cur = q.front();  // 取出队首顶点
        q.pop();
        // 输出映射后的编号（A=1, B=2, ..., J=10）
        cout << (G.Data[cur] - 'A' + 1) << " ";

        for (int i = 1; i <= G.VerNum; i++)
        {
            if (G.AdjMatrix[cur][i] != 0 && visited[i] == 0) // 存在边且未访问
            {
                visited[i] = 1;  // 入队时就标记，防止重复入队
                q.push(i);
            }
        }                                           
    }
}                                       
int main()
{
    Graph G;    // 邻接表存储的图
    Graph M;    // 邻接矩阵存储的图           
    // 从文件创建图（邻接表存储）
    char grpFile[] = "udg10.grp";
    if (!CreateGraphFromFile(grpFile, G))
    {
        cout << "创建图失败！" << endl << endl;
        return -1;
    }
    if (!CreateGrpFromFile(grpFile, M))
    {
        cout << "创建图失败！" << endl << endl;
        return -1;
    }                                                                                       
    // 输出图的基本信息
    cout << "图类型：";
    switch (G.gKind)
    {
        case UDG: cout << "无向图(UDG)"; break;
        case UDN: cout << "无向网(UDN)"; break;
        case DG:  cout << "有向图(DG)";  break;
        case DN:  cout << "有向网(DN)";  break;
    }
    cout << endl;
    int visited[100] = {0};
    BFS(G, 1, visited); // 从第一个顶点开始进行BFS遍历
    //BFS2(M, 1, visited); // 从第一个顶点开始进行BFS遍历                                         
    // 销毁图
    DestroyGraph(G);
    DestroyGraph(M);
    cout << endl;
    return 0;
}