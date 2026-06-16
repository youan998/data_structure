#include <iostream>
#include "queue.h"
using namespace std;        
void live(clclequeue &q,int k,int m)
{
    //k 是每次要删除的第 k 个元素，m 是要留下的元素个数
    while ((q.rear+q.capacity-q.front)%q.capacity>m)
    {
        for (int i = 1; i < k; i++)
        {
            int temp=q.arr[q.front]; // 获取队头元素
            q.dequeue(); // 将队头元素出队并重新入队，实现循环移动    
            q.enqueue(temp);    
        }
        q.dequeue(); // 删除第 k 个元素                  
    }
     cout<<"剩余元素为：";              
    while (!q.isEmpty())    
    {
        int temp=q.arr[q.front]; // 获取队头元素
        cout<<temp<<" "; // 输出队头元素
        q.dequeue(); // 将队头元素出队
    }
     cout<<endl;
}
int main() {
    int n;
    cout << "请输入队列的容量: ";
    cin >> n;
    clclequeue q(n+1); // 创建一个容量为 n+1 的循环队列 
    for (int i = 1; i <= n; ++i) {
        q.enqueue(i); // 将 1 到 n 的元素入队                    
    }     
    int k;
    cout << "请输入要删除的第 k 个元素: ";
    cin >> k; 
    cout<<"要留下m个元素:";
    int m;
    cin >> m;
    live(q, k, m); // 调用 live 函数进行处理                               
    return 0;
}