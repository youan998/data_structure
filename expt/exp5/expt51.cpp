#include "grpTypeDef.h"
#include "createGrpAdjMatrix.h"
#include "createGrpAdjLinkedList.h"
#include <iostream>
using namespace std;
//用邻接表存储的图G，计算边的数目
int CountEdgesFromAdjList(Graph &G)
{
    int edgeCount = 0; // 边数计数器
    for (int i=0;i<G.VerNum;i++)
    {
        EdgeNode* p = G.VerList[i+1].firstEdge; // 获取第i个顶点的第一条边
        while (p != NULL)
        {
            edgeCount++; // 统计边数
            p = p->next; // 移动到下一条边
        }
    }
    if (G.gKind == UDG || G.gKind == UDN){ // 如果是无向图或无向网，边数需要除以2
        return edgeCount /= 2;                 
    }
    else {// 有向图或有向网，边数直接统计
        return edgeCount;  
    }
}

int main()
{
    Graph G;
    int edgeCount;               // 计算得到的边数
    cout << "===== 邻接表存储的图——求边（弧）数目 =====" << endl;
    // 从文件创建图（邻接表存储）
    char grpFile[] = "udg10.grp";
    if (!CreateGraphFromFile(grpFile, G))
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
    // 调用 CountEdgesFromAdjList 计算边数
    edgeCount = CountEdgesFromAdjList(G);
    cout << "边（弧）数目（邻接表遍历计算）：" << edgeCount << endl;
    // 销毁图
    DestroyGraph(G);
    cout << endl;
    return 0;
}