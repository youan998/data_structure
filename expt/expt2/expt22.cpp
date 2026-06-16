#include <iostream>
#include "linkedList.h"
#include <vector>
using namespace std;   
void  Publicelement(linkedList& list1, linkedList& list2) {
    linkedList publicList; // 存储公共元素的链表
    Node* i = list1.head;// 外层循环：i 依次遍历 list1 中的每一个节点      
    while (i != nullptr) {
        Node* j = list2.head;// 内层循环：j 负责排查 i 在 list2 中是否存在      
        while (j != nullptr) {
            if (i->data == j->data) {
                publicList.insert(i->data); // 插入公共元素到公共链表
                break; // 找到一个匹配后跳出内层循环
            }
            j = j->next;
        }
        i = i->next;
    }
    if (publicList.head==nullptr)
    {
        cout << "没有公共元素" << endl;
    }
    else{
    cout << "公共元素链表: ";
    publicList.displaylist(); // 输出公共元素链表       
    }
}           
int main() {
    linkedList list1, list2;
    vector<int> values1= {1,3,6,10,15,16,17,18,19,20};
    vector<int> values2= {1,2,3,4,5,6,7,8,9,10,18,20,30};
    for (int value : values1) {
        list1.insert(value);
    }
    for (int value : values2) {
        list2.insert(value);
    }
    cout<<"第一次实验："<<endl;
    Publicelement(list1, list2);
    list1.head=nullptr;
    list2.head=nullptr;
    values1= {1,3,6,10,15,16,17,18,19,20};
    values2= {2,4,5,7,8,9,12,22};
    for (int value : values1) {
        list1.insert(value);
    }           
    for (int value : values2) {
        list2.insert(value);
    }                           
    cout<<"第二次实验："<<endl;         
    Publicelement(list1, list2);    
    list1.head=nullptr;
    list2.head=nullptr;
    values1= {};
    values2= {1,2,3,4,5,6,7,8,9,10};   
    for (int value : values1) {
        list1.insert(value);
    }           
    for (int value : values2) {
        list2.insert(value);
    }       
    cout<<"第三次实验："<<endl;         
    Publicelement(list1, list2);        
    return 0;
}