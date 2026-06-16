#include <iostream>
#include "mystack.h" 
#include <vector>
using namespace std;
int totalcount = 0;//记录出栈的序列个数
      
void generateSequences(int n, int current_num, stack<int>& s, vector<int>& path) {
    //current_num 是当前要入栈的数字，初始值为 1，递归过程中逐渐增加，直到超过 n
    //当 path 的长度等于 n 时，说明已经生成了一个完整的出栈序列
    if (path.size()==n)
    {
        totalcount++;
        return;
    }
    if(current_num<=n)
    // 选择入栈 current_num 并继续递归生成序列
    {
        s.push(current_num);
        generateSequences(n, current_num + 1, s, path);
        // 回退：将 current_num 从栈顶出栈，继续尝试其他可能的出栈序列  
        int temp;// 这里的 temp 只是一个占位符，因为 pop 函数需要一个引用参数来存储出栈的值
        s.pop(temp);
    }
    // 选择出栈一个元素并继续递归生成序列               
    if(!s.isEmpty())
    {
        int x;// 获取栈顶元素并出栈 
        s.pop(x);
        path.push_back(x);// 将出栈的元素添加到当前路径中
        generateSequences(n, current_num, s, path);//选择出栈一个元素并继续递归生成序列
        path.pop_back();     // 回退：将刚才出栈的元素从路径中移除，并重新入栈
        s.push(x);   
    }
}           
int main() {
    stack<int> s(100);  
    vector<int> path;   
    int n ;
    cin >> n;
    cout<<"输入n的值为："<<n<<endl;
    generateSequences(n, 1, s, path);   
    cout << "总的出栈序列数: " << totalcount << endl;               
}