#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// Kruskal 算法实现：构建最小生成树         
// 1. 解决“候选边的存储”：定义边的结构体
struct Edge {
    int u, v;       // 边的两个顶点
    int weight;     // 边的权值
};

// 比较函数：用于将边按权值从小到大排序
bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

// 2. 解决“判断是否构成回路”：并查集的核心数组
const int MAX_V = 100;
int parent_node[MAX_V]; // 记录每个顶点的“老大”（根节点）

// 并查集：初始化，一开始每个顶点都是一个独立的集合（自己是自己的老大）
void initDisjointSet(int n) {
    for (int i = 1; i <= n; i++) {
        parent_node[i] = i; 
    }
}

// 并查集：查找顶点 x 所在集合的“老大”
// 如果两个顶点的老大是同一个人，说明它们在同一个连通块里，连起来就会成环！
int findRoot(int x) {
    if (parent_node[x] == x)
        return x;
    // 路径压缩：顺便把路上的节点直接连到老大上，提高后续查找效率
    return parent_node[x] = findRoot(parent_node[x]); 
}

// Kruskal 算法主函数
// 参数：n 为顶点数，edges 为所有边的集合
void Kruskal(int n, vector<Edge>& edges) {
    int mst_weight = 0; // 记录最小生成树的总权值
    int edge_count = 0; // 记录已加入最小生成树的边数

    // 第一步：将所有边按权值从小到大排序 (贪心策略的体现)
    sort(edges.begin(), edges.end(), compareEdges);

    // 初始化并查集
    initDisjointSet(n);

    cout << "选取的边如下：" << endl;

    // 第二步：按权值从小到大遍历所有边
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].weight;

        // 查找顶点 u 和 v 的根节点
        int root_u = findRoot(u);
        int root_v = findRoot(v);

        // 如果根节点不同，说明加入这条边不会产生回路
        if (root_u != root_v) {
            // 将边加入生成树（打印出来）
            cout << "(" << u << ", " << v << ") 权值: " << w << endl;
            mst_weight += w;
            edge_count++;

            // 合并集合：让 root_v 认 root_u 为老大
            parent_node[root_v] = root_u;

            // 对应图片中：T中所含边数 == n-1 时，生成树构建完毕，提前退出
            if (edge_count == n - 1) {
                break;
            }
        }
        // 如果 root_u == root_v，说明它们已经连通，加上这条边会成环，直接丢弃（什么都不做）
    }

    if (edge_count == n - 1) {
        cout << "最小生成树总权值为: " << mst_weight << endl;
    } else {
        cout << "图不连通，无法构建最小生成树！" << endl;
    }
}

int main() {
    int n = 6; // 假设有 6 个顶点
    vector<Edge> edges = {
        {1, 2, 6}, {1, 3, 1}, {1, 4, 5},
        {2, 3, 5}, {2, 5, 3}, {3, 4, 5},
        {3, 5, 6}, {3, 6, 4}, {4, 6, 2}, {5, 6, 6}
    };

    Kruskal(n, edges);
    return 0;
}