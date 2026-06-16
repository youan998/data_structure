/**
 * @file    Toposort.cpp
 * @brief   拓扑排序演示程序 —— 分别用邻接矩阵和邻接表建图并排序
 *
 * 用法：
 *   1. 从数据文件加载图（需配合 createGrpAdjMatrix.h / createGrpAdjLinkedList.h）
 *   2. 也可直接在代码中手工构造图进行测试
 */

#include <cstdio>
#include <cstdlib>
#include "grpTypeDef.h"
#include "createGrpAdjMatrix.h"
#include "createGrpAdjLinkedList.h"
#include "Toposort.h"

// 手工构造一个 DAG 并测试两种存储方式的拓扑排序
void TestManualDAG()
{
    printf("========================================\n");
    printf("  手工构造 DAG 测试\n");
    printf("========================================\n\n");

    // -------- 邻接矩阵版本 --------
    Graph G1;

    // 顶点数据：A B C D E F (6个顶点)
    G1.VerNum = 6;
    G1.Data[1] = 'A'; G1.Data[2] = 'B'; G1.Data[3] = 'C';
    G1.Data[4] = 'D'; G1.Data[5] = 'E'; G1.Data[6] = 'F';
    G1.gKind = DG;  // 有向图

    // 初始化邻接矩阵
    for (int i = 1; i <= G1.VerNum; i++)
        for (int j = 1; j <= G1.VerNum; j++)
            G1.AdjMatrix[i][j] = 0;

    // 添加边（邻接矩阵）：A->C, A->D, B->C, B->E, C->D, C->F, D->F, E->F
    G1.AdjMatrix[1][3] = 1;  // A->C
    G1.AdjMatrix[1][4] = 1;  // A->D
    G1.AdjMatrix[2][3] = 1;  // B->C
    G1.AdjMatrix[2][5] = 1;  // B->E
    G1.AdjMatrix[3][4] = 1;  // C->D
    G1.AdjMatrix[3][6] = 1;  // C->F
    G1.AdjMatrix[4][6] = 1;  // D->F
    G1.AdjMatrix[5][6] = 1;  // E->F
    G1.ArcNum = 8;

    printf("【邻接矩阵】");
    int indeg1[MAXVEX + 1];// 计算入度并打印
    CalcInDegreeByMatrix(G1, indeg1);
    printf("各顶点入度：");
    for (int i = 1; i <= G1.VerNum; i++)
        printf("%c:%d  ", G1.Data[i], indeg1[i]);
    printf("\n");

    int result1[MAXVEX + 1];
    if (TopoSortKahnByMatrix(G1, result1))
        PrintTopoResult(result1, G1.VerNum);
    else
        printf("存在环，无法拓扑排序！\n");

    if (TopoSortDFSByMatrix(G1, result1))
    {
        printf("（DFS版）");
        PrintTopoResult(result1, G1.VerNum);
    }

    // -------- 邻接表版本 --------
    Graph G2;
    G2.VerNum = 6;
    for (int i = 1; i <= G2.VerNum; i++)
    {
        G2.VerList[i].data = 'A' + i - 1;
        G2.VerList[i].firstEdge = NULL;
    }
    G2.gKind = DG;

    // 手动添加边（邻接表）：与上面相同的边
    EdgeNode* p;
    auto addListEdge = [&](int u, int v) {
        p = new EdgeNode;
        p->adjVer = v;
        p->eInfo = 1;
        p->next = G2.VerList[u].firstEdge;
        G2.VerList[u].firstEdge = p;
    };
    addListEdge(1, 3); addListEdge(1, 4);
    addListEdge(2, 3); addListEdge(2, 5);
    addListEdge(3, 4); addListEdge(3, 6);
    addListEdge(4, 6); addListEdge(5, 6);
    G2.ArcNum = 8;

    printf("\n【邻接表】");
    int indeg2[MAXVEX + 1];
    CalcInDegreeByList(G2, indeg2);
    printf("各顶点入度：");
    for (int i = 1; i <= G2.VerNum; i++)
        printf("%c:%d  ", G2.VerList[i].data, indeg2[i]);
    printf("\n");

    int result2[MAXVEX + 1];
    if (TopoSortKahnByList(G2, result2))
        PrintTopoResult(result2, G2.VerNum);
    else
        printf("存在环，无法拓扑排序！\n");

    if (TopoSortDFSByList(G2, result2))
    {
        printf("（DFS版）");
        PrintTopoResult(result2, G2.VerNum);
    }

    // 清理邻接表内存
    DestroyGraph(G2);
}

// 测试含环的图
void TestCycleDetection()
{
    printf("\n========================================\n");
    printf("  环检测测试\n");
    printf("========================================\n\n");

    // -------- 邻接矩阵：构造含环的图 --------
    Graph G;
    G.VerNum = 3;
    G.Data[1] = 'X'; G.Data[2] = 'Y'; G.Data[3] = 'Z';
    G.gKind = DG;
    for (int i = 1; i <= G.VerNum; i++)
        for (int j = 1; j <= G.VerNum; j++)
            G.AdjMatrix[i][j] = 0;

    G.AdjMatrix[1][2] = 1;  // X->Y
    G.AdjMatrix[2][3] = 1;  // Y->Z
    G.AdjMatrix[3][1] = 1;  // Z->X  (构成环)
    G.ArcNum = 3;

    printf("【邻接矩阵】X->Y, Y->Z, Z->X (三顶点环)\n");
    printf("Kahn 判 DAG：%s\n", IsDAGByMatrix(G) ? "是 DAG" : "不是 DAG（检测到环）");

    int result[MAXVEX + 1];
    if (!TopoSortKahnByMatrix(G, result))
        printf("Kahn 正确检测到环，无法排序。\n");
    if (!TopoSortDFSByMatrix(G, result))
        printf("DFS  正确检测到环，无法排序。\n");

    // 不带环的正常图
    printf("\n【邻接表】X->Y, Y->Z (无环)\n");
    Graph G2;
    G2.VerNum = 3;
    for (int i = 1; i <= G2.VerNum; i++)
    {
        G2.VerList[i].data = 'X' + i - 1;
        G2.VerList[i].firstEdge = NULL;
    }
    G2.gKind = DG;

    EdgeNode* e = new EdgeNode;  // X->Y
    e->adjVer = 2; e->eInfo = 1; e->next = G2.VerList[1].firstEdge;
    G2.VerList[1].firstEdge = e;
    e = new EdgeNode;  // Y->Z
    e->adjVer = 3; e->eInfo = 1; e->next = G2.VerList[2].firstEdge;
    G2.VerList[2].firstEdge = e;
    G2.ArcNum = 2;

    printf("Kahn 判 DAG：%s\n", IsDAGByList(G2) ? "是 DAG" : "不是 DAG（检测到环）");
    if (TopoSortKahnByList(G2, result))
        PrintTopoResult(result, G2.VerNum);

    DestroyGraph(G2);
}

int main()
{
    printf("╔══════════════════════════════════════╗\n");
    printf("║     拓扑排序库 — Toposort 演示       ║\n");
    printf("║  邻接矩阵 & 邻接表 · Kahn & DFS      ║\n");
    printf("╚══════════════════════════════════════╝\n\n");

    TestManualDAG();
    TestCycleDetection();

    printf("\n测试完毕。\n");
    return 0;
}
