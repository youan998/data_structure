#include <iostream>
#include <vector>
#include "seqlist.h"
using namespace std; 
void insertlist(list &L, vector<int> value){
    // 插入一组元素到顺序表 L 中，保持 L 中元素的有序性 
    for (int i = 0; i < value.size(); i++) {
        L.insert(value[i]); 
    }
}   
void Publicelement(const list &L1, const list &L2){
    // 找出两个有序顺序表 L1 和 L2 中的公共元素，存储在 publicList 中
    list publicList; 
    // 使用双指针法，分别指向 L1 和 L2 的开头   
    int i = 0, j = 0;
    while (i < L1.size && j < L2.size) {
        if (L1.data[i] == L2.data[j]) {
            publicList.insert(L1.data[i]);
            i++; // 相等时，两个指针一起后移
            j++;
        } else if (L1.data[i] < L2.data[j]) {
            i++; // L1 的元素小，L1 的指针后移去寻找更大的
        } else {
            j++; // L2 的元素小，L2 的指针后移
        }
    }                    
    cout << "公共元素表: ";
    if (publicList.size == 0) {
        cout << "无" << endl;  // 如果没找到，明确告诉用户“无”
    } else {
        publicList.display();  // 找到了就正常打印
    } 
}
int main(){
    list L1, L2;
    vector<int> values1= {1,3,6,10,15,16,17,18,19,20};
    vector<int> values2= {1,2,3,4,5,6,7,8,9,10,18,20,30};
    insertlist(L1, values1); // 插入第一组数据到 L1
    insertlist(L2, values2); // 插入第二组数据到 L2  
    cout <<"第一次测试:"<<endl;       
    Publicelement(L1, L2);   
    L1.size = 0; // 清空 L1
    L2.size = 0; // 清空 L2  
    cout <<"第二次测试:"<<endl;            
    values1={1,3,6,10,15,16,17,18,19,20};
    values2={2,4,5,7,8,9,12,22}; 
    insertlist(L1, values1); 
    insertlist(L2, values2);
    Publicelement(L1, L2);
    L1.size = 0; 
    L2.size = 0;
    cout <<"第三次测试:"<<endl;
    values1={};
    values2={1,2,3,4,5,6,7,8,9,10}; 
    insertlist(L1, values1);
    insertlist(L2, values2);
    Publicelement(L1, L2);
}