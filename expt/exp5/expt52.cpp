#include "grpTypeDef.h"
#include "createGrpAdjMatrix.h"
#include "createGrpAdjLinkedList.h"
#include <iostream>
using namespace std;
//无向图G是否是树即这个节点的邻接点如果被访问过且不是父节点，则说明有环。
//最后还需要检查图是否连通，即所有顶点都被访问过。
//G 图
// v当前访问的顶点编号
// parent当前访问顶点的父节点编号
// visited[]访问标记数组  
bool iftree(Graph &G, int v,int parent,int visited[])
{
    visited[v]=1;
    EdgeNode* p = G.VerList[v].firstEdge; // 获取第v个顶点的第一条边
    while (p != NULL)
    {
        if(visited[p->adjVer]==0)
        {
            if (!iftree(G, p->adjVer, v, visited))  // 子树有环，则整图不是树
                return false;
        }
        else if(p->adjVer!=parent)// 如果访问过的邻接点不是父节点，说明有环
        {
            return false;
        }
        p = p->next; // 移动到下一条边
    }
    return true;
}
int main()
{
    Graph G;               
    cout << "===== 邻接表存储的图——判断是否树 =====" << endl;
    // 从文件创建图（邻接表存储）
    char grpFile[] = "udg10.grp";
    if (!CreateGraphFromFile(grpFile, G))
    {
        cout << "创建图失败！" << endl << endl;
        return -1;
    }
    cout << endl;
    int visited[100] = {0};
    bool isTree = iftree(G, 1, -1, visited);
    // 检查连通性：树必须是连通图，所有顶点都应被访问过
    if (isTree)
    {
        for (int i = 1; i <= G.VerNum; i++)// 顶点编号从1开始   
        {
            if (visited[i] == 0)
            {
                isTree = false;
                break;
            }
        }
    }
    if (isTree)
    {
        cout << "图是树！" << endl;
    }
    else
    {
        cout << "图不是树！" << endl;
    }
    // 销毁图
    DestroyGraph(G);
    cout << endl;
    return 0;
}