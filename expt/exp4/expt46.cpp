#include "createTree.h"
using namespace std;
void printgeneraliedlist(csNode* T)
{// 递归打印孩子兄弟链表表示的树（森林）为广义表形式                                    
    if (T == NULL)
        return;

    // 1. 打印当前结点
    cout << T->data;

    // 2. 如果有孩子，说明有子树，用一对括号把子树包起来
    if (T->firstChild != NULL) {
        cout << "(";
        printgeneraliedlist(T->firstChild); // 递归打印孩子
        cout << ")";
    }

    // 3. 如果有亲兄弟，说明是同级，用逗号隔开
    if (T->nextSibling != NULL) {
        cout << ",";
        printgeneraliedlist(T->nextSibling); // 递归打印兄弟
    }
}
int main()
{
    pTree pT;
    csNode* csT = NULL;

    // ==================== 第一组测试数据：tree11.tre ====================
    cout << "========================================" << endl;
    cout << "测试第一组数据：tree11.tre" << endl;
    cout << "========================================" << endl;

    initialTree(pT);
    if (CreateTreeFromFile("tData/tree11.tre", pT))
    {
        createCsTree(csT, pT);
        printgeneraliedlist(csT);
    }
    else
    {
        cout << "读取文件 tree11.tre 失败！" << endl;
    }

    cout << endl;

    // ==================== 第二组测试数据：f20.tre ====================
    cout << "========================================" << endl;
    cout << "测试第二组数据：f20.tre" << endl;
    cout << "========================================" << endl;
    initialTree(pT);
    csT = NULL;
    if (CreateTreeFromFile("tData/f20.tre", pT))
    {
        // 从双亲表示创建孩子兄弟链表
        createCsTree(csT, pT);        
        printgeneraliedlist(csT);
    }
    else
    {
        cout << "读取文件 f20.tre 失败！" << endl;
    }

    return 0;
}