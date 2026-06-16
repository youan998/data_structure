#include "createTree.h"
using namespace std;
// 求孩子兄弟链表表示的树（森林）的度 
// 对当前结点T，统计其孩子个数，并递归求各子树的度，返回最大值
int getDegree(csNode* T)
{
    if (T == NULL)
        return 0;
    int maxDegree = 0;       // 记录当前树/森林的最大度
    int childCount = 0;      // 当前结点的孩子个数

    csNode* child = T->firstChild;
    while (child != NULL)
    {
        childCount++;                            // 每遇到一个孩子，计数+1
        // 递归求以该孩子为根的子树中的最大度
        int subDegree = getDegree(child);// 递归求子树的度
        if (subDegree > maxDegree) maxDegree = subDegree;
        child = child->nextSibling;              // 移向下一个兄弟（即下一个孩子）
    }

    // 当前结点的孩子数与已求出的子树最大度比较
    if (childCount > maxDegree)
        maxDegree = childCount;

    return maxDegree;
}

// 求森林（多棵树）的度：遍历森林中每棵树，取最大度
int getForestDegree(csNode* forest)
{
    if (forest == NULL)
        return 0;
    int maxDegree = 0;
    // 森林由多棵树通过nextSibling连接
    // 遍历森林中的每棵树的根
    csNode* p = forest;
    while (p != NULL)
    {
        int degree = getDegree(p);// 求以p为根的树的度
        if (degree > maxDegree)
            maxDegree = degree;
        p = p->nextSibling;  // 下一棵树
    }

    return maxDegree;
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
        cout << "树（森林）的度为：" << getForestDegree(csT);
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
        
        cout << "树（森林）的度为：" << getForestDegree(csT) << endl;
    }
    else
    {
        cout << "读取文件 f20.tre 失败！" << endl;
    }

    return 0;
}