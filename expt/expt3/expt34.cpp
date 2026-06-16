#include <iostream>
#include "queue.h"
using namespace std;  
void live1(linkqueue &q,int k,int m)
{
    //链队列
    while (q.count()>m)
    {
        for (int i = 1; i < k; i++)
        {
            int temp=q.front->data; // 获取队头元素
            q.dequeue(); // 将队头元素出队并重新入队，实现循环移动    
            q.enqueue(temp);    
        }
        q.dequeue(); // 删除第 k 个元素                  
    }
     cout<<"剩余元素为：";                      
    while (!q.isEmpty())    
    {                       
        int temp=q.front->data; // 获取队头元素
        cout<<temp<<" "; // 输出队头元素
        q.dequeue(); // 将队头元素出队
    }
     cout<<endl;
}
void live2(queue &q, int k, int m)
{
    //顺序队列
    while (q.count()>m)
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
    cout << "请输入顺序队列的容量: ";
    cin >> n;
    linkqueue q; // 创建一个链式队列                          
    for (int i = 1; i <= n; ++i) {
        q.enqueue(i); // 将 1 到 n 的元素入队                    
    }     
    int k;
    cout << "请输入要删除的第 k 个元素: ";
    cin >> k; 
    cout<<"要留下m个元素:";
    int m;
    cin >> m;
    queue q2(n * k); // 创建一个顺序队列 
    for (int i = 1; i <= n; ++i) {
        q2.enqueue(i); // 将 1 到 n 的元素入队                    
    }      
    live2(q2, k, m); // 调用 live2 函数进行处理                                    
    return 0;
}