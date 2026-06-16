#include "CreateBiTree.h"
#include <iostream> 
using namespace std;        
// 核心算法：DFS 查找并打印所有叶子结点到根结点的路径
// 这里的 pathLen利用值传递实现天然的路径回溯
void printLeafToRootPaths(btNode* T, elementType path[], int pathLen) {
    if (T == NULL) return; // 空结点直接返回

    // 1. 将当前结点存入路径数组，并将路径长度 + 1
    path[pathLen] = T->data;
    pathLen++;

    // 2. 判断当前结点是不是“叶子结点”（左右孩子都为空）
    if (T->lChild == NULL && T->rChild == NULL) {
        cout << "叶子结点 '" << T->data << "' 到根的路径: ";
        
        // 遍历路径数组，逆序打印路径（从叶子结点到根结点）
        for (int i = pathLen - 1; i >= 0; i--) {
            cout << path[i];
            if (i > 0) cout << " -> "; 
        }
        cout << endl;
    } 
    else {
        printLeafToRootPaths(T->lChild, path, pathLen);
        printLeafToRootPaths(T->rChild, path, pathLen);
    }
}
int main()
{
    char strLine[NODENUM][3];// 从文件读取的二叉树数据数组      
    int nArrLen;// 数组行数
    btNode* T = NULL;// 二叉树根结点指针    
    int nRow;
    // ==================== 第一组数据：bt261.btr ====================
    cout << "========================================" << endl;
    cout << "测试第一组数据：bt261.btr" << endl;
    cout << "========================================" << endl;
    if (ReadFileToArray("BTdata/bt261.btr", strLine, nArrLen))
    {
        nRow = 0;
        T = NULL;
        CreateBiTreeFromFile(T, strLine, nArrLen, nRow);// 从数组创建二叉树
        elementType path[NODENUM]; // 存储路径的数组，长度足够大    
        printLeafToRootPaths(T, path, 0); // 从根结点开始，路径长度初始为 0                                       
    }
    else
    {
        cout << "读取文件 bt261.btr 失败！" << endl;
    }

    cout << endl;

    // ==================== 第二组数据：bt21.btr ====================
    cout << "========================================" << endl;
    cout << "测试第二组数据：bt21.btr" << endl;
    cout << "========================================" << endl;

    if (ReadFileToArray("BTdata/bt21.btr", strLine, nArrLen))
    {
        nRow = 0;
        T = NULL;
        CreateBiTreeFromFile(T, strLine, nArrLen, nRow);// 从数组创建二叉树
        elementType path[NODENUM]; 
        printLeafToRootPaths(T, path, 0);                              
    }
    else
    {
        cout << "读取文件 bt21.btr 失败！" << endl;
    }
    return 0;
}