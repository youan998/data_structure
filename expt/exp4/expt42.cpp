#include "CreateBiTree.h"
#include <iostream>           
// 辅助函数 1：在二叉树中递归查找值为 x 的结点本身  
btNode* getNode(btNode* T, elementType x) {
    if (T == NULL) return NULL;
    if (T->data == x) return T;  // 找到了
    
    btNode* p = getNode(T->lChild, x); // 去左子树找
    if (p != NULL) return p;
    return getNode(T->rChild, x);      // 去右子树找
}
btNode* getParent(btNode* T, elementType x) {
    if (T == NULL) return NULL;
    
    // 如果当前结点的左孩子或右孩子是 x，那么当前结点就是 x 的父结点！
    if ((T->lChild != NULL && T->lChild->data == x) ||
        (T->rChild != NULL && T->rChild->data == x)) {
        return T;
    }
    // 否则继续往左子树深处找
    btNode* p = getParent(T->lChild, x);
    if (p != NULL) return p;
    // 左边没找到，再往右子树深处找
    return getParent(T->rChild, x);
}
void queryNodeInfo(btNode* T, elementType x) {// 查询结点 x 的父结点、兄弟结点和孩子结点        
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
    // 2. 找父结点和兄弟结点
    if (T->data == x) {
        cout << "结点 '" << x << "' 是根结点，没有父结点和兄弟结点" << endl;
    }   
    else {
        btNode* parent = getParent(T, x); 
        cout << "结点 '" << x << "' 的父结点是：'" << parent->data << "'" << endl;
        // 兄弟结点：如果父结点的左孩子是 x，那么兄弟就是父结点的右孩子；反之亦然           
        if (parent->lChild != NULL && parent->lChild->data == x&& parent->rChild != NULL) {
                cout << "结点 '" << x << "' 的右兄弟结点是：'" << parent->rChild->data << "'" << endl;
        }
        else if (parent->rChild != NULL && parent->rChild->data == x&& parent->lChild != NULL ) {
                cout << "结点 '" << x << "' 的左兄弟结点是：'" << parent->lChild->data  << "'" << endl;
        }
        else {
            cout << "没有兄弟结点。" << endl;
        }
    }
    // 3. 找孩子结点
    if (target->lChild != NULL) {
        cout << "结点 '" << x << "' 的左孩子是：'" << target->lChild->data << "'" << endl;
    }
    if (target->rChild != NULL) {
        cout << "结点 '" << x << "' 的右孩子是：'" << target->rChild->data << "'" << endl;
    }
    if (target->lChild == NULL && target->rChild == NULL){
        cout << "结点 '" << x << "' 没有孩子结点。" << endl;
    }                       
}
int main()
{
    char strLine[NODENUM][3];// 从文件读取的二叉树数据数组      
    int nArrLen;// 数组行数
    btNode* T = NULL;// 二叉树根结点指针    
    int nRow;
    elementType x;
    // ==================== 第一组数据：bt8.btr ====================
    cout << "========================================" << endl;
    cout << "测试第一组数据：bt8.btr" << endl;
    cout << "========================================" << endl;
    if (ReadFileToArray("BTdata/bt8.btr", strLine, nArrLen))
    {
        nRow = 0;
        T = NULL;
        CreateBiTreeFromFile(T, strLine, nArrLen, nRow);// 从数组创建二叉树         
        cout<<"请输入要查询的结点值：x=";
        cin>>x;
        queryNodeInfo(T, x);// 查询结点信息 
    }
    else
    {
        cout << "读取文件 bt8.btr 失败！" << endl;
    }

    cout << endl;

    // ==================== 第二组数据：bt14.btr ====================
    cout << "========================================" << endl;
    cout << "测试第二组数据：bt21.btr" << endl;
    cout << "========================================" << endl;

    if (ReadFileToArray("BTdata/bt21.btr", strLine, nArrLen))
    {
        nRow = 0;
        T = NULL;
        CreateBiTreeFromFile(T, strLine, nArrLen, nRow);
        cout<<"请输入要查询的结点值：x=";
        cin>>x;
        queryNodeInfo(T, x);
    }
    else
    {
        cout << "读取文件 bt21.btr 失败！" << endl;
    }
    return 0;
}