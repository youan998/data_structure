#ifndef GRPTYPEDEF_H
#define GRPTYPEDEF_H

#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

#define MAXVEX 100    //最大顶点数
#define INF 65535     //无穷大

//图类型枚举
typedef enum {
    UDG,  //无向图
    UDN,  //无向网
    DG,   //有向图
    DN    //有向网
} GraphKind;

typedef char elementType;  //顶点元素类型
typedef int eInfoType;     //边信息类型（权值）
typedef int cellType;      //邻接矩阵单元格类型

//邻接表边结点
typedef struct EdgeNode {
    int adjVer;             //邻接点编号
    eInfoType eInfo;        //边信息
    struct EdgeNode* next;  //下一条边
} EdgeNode;

//邻接表顶点结点
typedef struct {
    elementType data;       //顶点数据
    EdgeNode* firstEdge;    //第一条边
} VexNode;

//图结构体（同时支持邻接矩阵和邻接表两种存储方式）
typedef struct {
    elementType Data[MAXVEX + 1];          //顶点数据（邻接矩阵用）
    cellType AdjMatrix[MAXVEX + 1][MAXVEX + 1]; //邻接矩阵
    VexNode VerList[MAXVEX + 1];           //邻接表顶点数组
    int VerNum;     //顶点数
    int ArcNum;     //边数
    GraphKind gKind; //图类型
} Graph;

//删除字符串左边空格
void strLTrim(char* str);

//销毁图（邻接表用）
void DestroyGraph(Graph &G);

#endif