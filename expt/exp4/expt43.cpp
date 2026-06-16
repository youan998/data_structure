#include "CreateBiTree.h"
#include <iostream> 
// 辅助函数在二叉树中递归查找值为 x 的结点本身  
btNode* getNode(btNode* T, elementType x) {
    if (T == NULL) return NULL;
    if (T->data == x) return T;  // 找到了
    
    btNode* p = getNode(T->lChild, x); // 去左子树找
    if (p != NULL) return p;
    return getNode(T->rChild, x);      // 去右子树找
}
btNode* getancestor(btNode* T, elementType x,elementType y) {// 查找 x 和 y 的最近公共祖先
    if (T == NULL) return NULL;
    if (T->data == x || T->data == y) return T; // 如果当前结点是 x 或 y，那么当前结点就是最近公共祖先                          
    //后续递归在左右子树中找 x 和 y 的最近公共祖先
    btNode* lefttree = getancestor(T->lChild, x,y); // 去左子树找
    btNode* righttree = getancestor(T->rChild, x,y);// 去右子树找
    if (lefttree != NULL && righttree != NULL)
        return T;
    if (lefttree != NULL) return lefttree;
    if (righttree != NULL) return righttree;
    return NULL;
}
void queryNodeInfo(btNode* T, elementType x,elementType y) {
    if (T == NULL) {
        cout << "这是一棵空树！" << endl;
        return;
    }
    // 1. 先验证这个结点到底存不存在
    btNode* target = getNode(T, x);// 查找值为 x 的结点
    if (target == NULL) {
        cout << " 提示：结点 '" << x << "' 不在这棵二叉树中" << endl;
        return;
    }
    target = getNode(T, y);// 查找值为 y 的结点                 
    if (target == NULL) {
        cout << " 提示：结点 '" << y << "' 不在这棵二叉树中" << endl;
        return;
    }
    if (getancestor(T, x,y) != NULL)// 如果最近公共祖先存在
    {
        cout << "结点 '" << x << "' 和结点 '" << y << "' 的最近公共祖先是：'" << getancestor(T, x,y)->data << "'" << endl;
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
        queryNodeInfo(T, 'g','u'); // 查询结点 g 和 u 的最近公共祖先                                       
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
        queryNodeInfo(T, 'e','h'); // 查询结点 e 和 h 的最近公共祖先                                
    }
    else
    {
        cout << "读取文件 bt21.btr 失败！" << endl;
    }
    return 0;
}