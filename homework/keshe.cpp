#include <iostream>
#include <vector>
#include "grpTypeDef.h"
#include "createGrpAdjLinkedList.h"
using namespace std;

//  求所有简单路径 
void setGraphpath(Graph& G, int visited[], vector<int>& path, int& pathNum,
                  int v, int end, vector<vector<int>>& allpath) {
    visited[v] = 1;
    path.push_back(v);

    if (v == end) {
        allpath.push_back(path);
        pathNum++;
    } else {
        EdgeNode* eR = G.VerList[v].firstEdge;
        while (eR) {
            if (!visited[eR->adjVer])
                setGraphpath(G, visited, path, pathNum, eR->adjVer, end, allpath);
            eR = eR->next;
        }
    }

    visited[v] = 0;
    path.pop_back();
}

// 打印所有简单路径
void printPath(Graph& G, int start, int end) {
    int visited[MAXVEX + 1] = {0};
    vector<int> path;
    vector<vector<int>> allpath;
    int pathNum = 0;
    setGraphpath(G, visited, path, pathNum, start, end, allpath);

    cout << "从顶点 " << G.VerList[start].data
         << " 到顶点 " << G.VerList[end].data
         << " 的所有简单路径（共 " << pathNum << " 条）：" << endl;

    for (int i = 0; i < (int)allpath.size(); i++) {
        cout << "路径 " << i + 1 << ": ";
        for (int v : allpath[i]) cout << G.VerList[v].data << " ";
        cout << endl;
    }
}

//  求指定长度K的简单路径
void printPathByLength(Graph& G, int start, int end, int K, int& count) {
    int visited[MAXVEX + 1] = {0};
    vector<int> path;
    vector<vector<int>> allpath;
    int pathNum = 0;
    setGraphpath(G, visited, path, pathNum, start, end, allpath);

    count = 0;
    cout << "从顶点 " << G.VerList[start].data
         << " 到顶点 " << G.VerList[end].data
         << " 的长度为 " << K << " 的简单路径：" << endl;

    for (int i = 0; i < (int)allpath.size(); i++) {
        if ((int)allpath[i].size() - 1 == K) {
            cout << "路径 " << ++count << ": ";
            for (int v : allpath[i]) cout << G.VerList[v].data << " ";
            cout << endl;
        }
    }
    if (!count) cout << "（无）" << endl;
    else        cout << "共 " << count << " 条" << endl;
}

// 主函数 
int main() {
    // 系统初始化：加载所有图
    Graph G[3] = {};
    char grpFile[3][20] = {"test1.txt", "test2.txt", "test3.txt"};
    
    cout << "================ 系统初始化 ================" << endl;
    for (int i = 0; i < 3; i++) {
        if (!CreateGraphFromFile(grpFile[i], G[i])) {
            cout << "[!] 创建图 " << grpFile[i] << " 失败！" << endl;
            return -1;
        }
        cout << "[*] 成功创建图 " << grpFile[i] << "！" << endl;
    }

    // 交互式主循环，允许用户反复进行测试
    while (true) {
        cout << "\n============= 简单路径求解系统 =============" << endl;
        cout << "  1. 求解起点到终点的【所有简单路径】" << endl;
        cout << "  2. 求解起点到终点的【指定长度简单路径】" << endl;
        cout << "  0. 退出系统" << endl;
        cout << "============================================" << endl;
        cout << "请输入功能序号 (0-2): ";

        int choice;
        // 防御性编程：防止用户输入字母导致死循环
        if (!(cin >> choice)) { 
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[!] 输入无效，请输入数字！" << endl;
            continue;
        }

        // 退出选项
        if (choice == 0) {
            cout << "\n[*] 感谢使用，系统正在退出..." << endl;
            break;
        }
        // 错误输入拦截
        if (choice != 1 && choice != 2) {
            cout << "[!] 无效的选择，请重新输入！" << endl;
            continue;
        }

        // 3分步引导用户输入参数
        int graphId;
        cout << "\n请选择要操作的图编号 (1-3): ";
        cin >> graphId;
        if (graphId < 1 || graphId > 3) {
            cout << "[!] 图编号不存在，已返回主菜单！" << endl;
            continue; 
        }
        int gIndex = graphId - 1; // 转换为数组索引

        char startChar, endChar;
        cout << "请输入起点和终点（用空格隔开，如 A G）: ";
        cin >> startChar >> endChar;

        // 校验顶点是否存在
        int start = 0, end = 0;
        for (int i = 1; i <= G[gIndex].VerNum; i++) {
            if (G[gIndex].VerList[i].data == startChar) start = i;
            if (G[gIndex].VerList[i].data == endChar)   end   = i;
        }

        if (start == 0 || end == 0) {
            cout << "[!] 错误：起点或终点在图 " << graphId << " 中不存在！" << endl;
            continue; // 容错处理：不退出程序，而是跳过本次循环，回到主菜单
        }

        // 4. 执行核心算法并展示结果
        cout << "\n----------------- 运行结果 -----------------" << endl;
        if (choice == 1) {
            printPath(G[gIndex], start, end);
        } else if (choice == 2) {
            int K;
            cout << "请输入指定路径长度 K（边数）: ";
            cin >> K;
            int count = 0;
            printPathByLength(G[gIndex], start, end, K, count);
        }
        cout << "--------------------------------------------" << endl;
    }

    // 释放资源
    for (int i = 0; i < 3; i++) {
        DestroyGraph(G[i]);
    }
    
    return 0;
}