#include "grpTypeDef.h"
#include "createGrpAdjMatrix.h"
#include "createGrpAdjLinkedList.h"
#include <iostream>
using namespace std;
//邻接表存储的图的DFS算法实现
void DFS(Graph &G, int v, int visited[])
{
    visited[v] = 1; // 标记当前顶点已访问
    // 输出映射后的编号（A=1, B=2, ..., J=10）
    cout << (G.VerList[v].data - 'A' + 1) << " ";

    EdgeNode* p = G.VerList[v].firstEdge; // 获取第v个顶点的第一条边
    while (p != NULL)
    {
        if (visited[p->adjVer] == 0) // 如果邻接点未访问过
        {
            DFS(G, p->adjVer, visited); // 递归访问邻接点
        }
        p = p->next; // 移动到下一条边
    }
}                           
//邻接矩阵存储的图的DFS算法实现                         
void DFS2(Graph &G, int v, int visited[])
{
    visited[v] = 1; // 标记当前顶点已访问
    // 输出映射后的编号（A=1, B=2, ..., J=10）
    cout << (G.Data[v] - 'A' + 1) << " ";

    for (int i = 1; i <= G.VerNum; i++)
    {
        if (G.AdjMatrix[v][i] != 0 && visited[i] == 0) // 存在边且未访问
        {
            DFS2(G, i, visited); // 递归访问邻接点
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
    DFS(G, 1, visited); // 从第一个顶点开始进行DFS遍历
    //DFS2(M, 1, visited); // 从第一个顶点开始进行DFS遍历                                         
    // 销毁图
    DestroyGraph(G);
    DestroyGraph(M);
    cout << endl;
    return 0;
}