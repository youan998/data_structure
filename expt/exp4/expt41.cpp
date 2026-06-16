#include "CreateBiTree.h"
// 将二叉链表存储的二叉树转换为完全二叉树顺序存储数组
// T: 二叉树根结点指针
// arr: 输出数组（下标从1开始，arr[0]弃用）
// maxIdx: 返回数组中最大下标
void BiTreeToArray(btNode* T, elementType* arr, int& maxIdx)
{
    if (T == NULL)//空树，返回
    {
        maxIdx = 0;
        return;
    }

    // 使用队列进行层次遍历，队列元素存储 (结点指针, 完全二叉树下标)
    struct QNode
    {
        btNode* node;// 结点指针
        int idx;// 完全二叉树下标
    };

    const int MAXQ = 1000;// 队列最大容量
    QNode q[MAXQ];
    int front = 0, rear = 0;

    // 根结点入队，下标为1
    q[rear].node = T;
    q[rear].idx = 1;
    rear++;
    maxIdx = 1;// 初始化最大下标为1         

    while (front < rear)
    {
        QNode cur = q[front];// 获取队头元素
        front++;

        // 将结点数据写入数组对应下标
        arr[cur.idx] = cur.node->data;

        // 左孩子入队
        if (cur.node->lChild != NULL)
        {
            int leftIdx = cur.idx * 2;// 左孩子下标为父结点下标的2倍
            q[rear].node = cur.node->lChild;
            q[rear].idx = leftIdx;
            rear++;
            if (leftIdx > maxIdx)
                maxIdx = leftIdx;
        }

        // 右孩子入队
        if (cur.node->rChild != NULL)
        {
            int rightIdx = cur.idx * 2 + 1;// 右孩子下标为父结点下标的2倍 + 1
            q[rear].node = cur.node->rChild;
            q[rear].idx = rightIdx;
            rear++;
            if (rightIdx > maxIdx)
                maxIdx = rightIdx;
        }
    }
}

// 打印顺序存储数组
void printArray(elementType* arr, int maxIdx)
{
    cout << "完全二叉树顺序存储数组（下标从1开始）：" << endl;
    for (int i = 1; i <= maxIdx; i++)
    {
        cout << i << ":" << arr[i];
        if (i < maxIdx)
            cout << "  ";
        if (i % 10 == 0)  // 每10个换行
            cout << endl;
    }
    cout << endl;
}

int main()
{
    char strLine[NODENUM][3];
    int nArrLen;
    btNode* T = NULL;
    int nRow;
    elementType arr[1000];  // 顺序存储数组
    int maxIdx;// 顺序存储数组最大下标

    // ==================== 第一组数据：bt8.btr ====================
    cout << "========================================" << endl;
    cout << "测试第一组数据：bt8.btr" << endl;
    cout << "========================================" << endl;

    if (ReadFileToArray("BTdata/bt8.btr", strLine, nArrLen))
    {
        nRow = 0;
        T = NULL;
        CreateBiTreeFromFile(T, strLine, nArrLen, nRow);

        cout << "二叉树的层次遍历结果：";
        hieTraverse(T);
        cout << endl;

        // 初始化数组，全部填充 '/' 表示空结点
        for (int i = 0; i < 1000; i++)
            arr[i] = '/';

        BiTreeToArray(T, arr, maxIdx);

        cout << "转换为顺序存储形式（扩展为完全二叉树）：" << endl;
        printArray(arr, maxIdx);
    }
    else
    {
        cout << "读取文件 bt8.btr 失败！" << endl;
    }

    cout << endl;

    // ==================== 第二组数据：bt14.btr ====================
    cout << "========================================" << endl;
    cout << "测试第二组数据：bt14.btr" << endl;
    cout << "========================================" << endl;

    if (ReadFileToArray("BTdata/bt14.btr", strLine, nArrLen))
    {
        nRow = 0;
        T = NULL;
        CreateBiTreeFromFile(T, strLine, nArrLen, nRow);

        cout << "二叉树的层次遍历结果：";
        hieTraverse(T);
        cout << endl;

        // 初始化数组，全部填充 '/' 表示空结点
        for (int i = 0; i < 1000; i++)
            arr[i] = '/';

        BiTreeToArray(T, arr, maxIdx);

        cout << "转换为顺序存储形式（扩展为完全二叉树）：" << endl;
        printArray(arr, maxIdx);
    }
    else
    {
        cout << "读取文件 bt14.btr 失败！" << endl;
    }

    return 0;
}