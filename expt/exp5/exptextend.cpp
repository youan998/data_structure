#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 迷宫的行数和列数
const int ROW = 10;
const int COL = 10;
// 定义一个点结构体 
struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};
// 定义一个方向数组，表示上下左右四个方向                               
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};     
bool isValid(int map[ROW][COL], int x, int y, bool visited[ROW][COL]) {
    //是否可以访问点 (x, y)，需要满足以下条件： 
    if (x < 0 || x >= ROW || y < 0 || y >= COL) // 越界
        return false;                       
    if (map[x][y] == 1) // 墙壁                 
      return false ;
    if (visited[x][y]) // 已访问过             
        return false;
    return true;
} 
// 定义一个节点结构体，用于 BFS 搜索，包含当前节点位置、距离和父节点指针            
struct node {
    node*  parent; // 父节点指针            
    Point pos;     // 当前节点位置      
    int dist;      // 从起点到当前节点的距离                                    
    node(Point _pos, int _dist, node* _parent) : pos(_pos), dist(_dist), parent(_parent) {} 
};
// BFS 搜索迷宫的最短路径               
node searchmin(int map[ROW][COL], Point start, Point end) {
    bool visited[ROW][COL] = {false}; // 访问标记数组     
    queue<node*> q; // BFS 辅助队列，存储当前节点指针               
    q.push(new node(start, 0, nullptr)); // 起点入队 
    visited[start.x][start.y] = true; // 标记起点已访问             
    while (!q.empty()) {
        auto current = q.front();
        q.pop();
        Point pt = current->pos;// 当前节点位置
        int dist = current->dist;
        if (pt.x == end.x && pt.y == end.y) { // 到达终点
            return *current; // 返回当前节点，包含路径信息
        }                           
        // 遍历四个方向                 
        for (int i = 0; i < 4; i++) {
            int newX = pt.x + directions[i][0];
            int newY = pt.y + directions[i][1];
            if (isValid(map, newX, newY, visited)) {
                visited[newX][newY] = true; // 标记新点已访问
                q.push(new node(Point(newX, newY), dist + 1, current)); // 新点入队，路径长度加1
            }
        }                           
    }
    return node(end, -1, nullptr); // 无法到达终点                         
}  
void printPath(node* n,int map[ROW][COL]) {
    if (n == nullptr)
        return;
    map[n->pos.x][n->pos.y] = 8; // 标记路径点
    printPath(n->parent, map); // 递归打印父节点路径
    
}           
int main() {
    // 0: 通道, 1: 墙壁
    int map[ROW][COL] = {
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 1, 0, 1, 1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0, 0, 1, 0, 1, 0},
        {1, 0, 1, 1, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 0, 0, 0, 1, 0, 0, 0}
    };

    Point start(0, 0);  // 起点 (0,0)
    Point end(9, 9);    // 终点 (9,9)

    cout << "===== 迷宫最短路径搜索 (BFS) =====" << endl;
    node result = searchmin(map, start, end);
    if (result.dist != -1) {
        cout << "找到最短路径！" << endl;
        printPath(&result, map); // 打印路径 
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                if (i == start.x && j == start.y) cout << "S ";      // 起点
                else if (i == end.x && j == end.y) cout << "E ";     // 终点
                else if (map[i][j] == 8) cout << "* ";              // 路径
                else if (map[i][j] == 1) cout << "█ ";              // 墙壁
                else cout << ". ";                                   // 空地
        }
        cout << endl;
    }      
    } else {
        cout << "没有路径可达终点！" << endl;
    }
    return 0;   
}