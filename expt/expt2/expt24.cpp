#include <iostream>
#include "linkedList.h"
#include <vector>
using namespace std;
void add(linkedList& list1, linkedList& list2) {
    // 如果 L1 或 L2 为空，安全返回
    if (list1.head == nullptr || list2.head == nullptr) {
        cout<<"无公共元素";
        return;
    }
    // p1 和 p2 分别指向两个链表的第一个真实节点
    Node* p1 = list1.head->next; 
    Node* p2 = list2.head->next; 
    
    // tail 用于拼接新的合并链表，初始指向 L1 的头结点
    Node* tail = list1.head;     

    // 同时遍历两个链表
    while (p1 != nullptr && p2 != nullptr) {
        if (p1->data < p2->data) {
            tail->next = p1;      // 将较小的 p1 接入新链表
            tail = p1;            // tail 指针后移
            p1 = p1->next;        // p1 指针后移
        } 
        else if (p1->data > p2->data) {
            tail->next = p2;      // 将较小的 p2 接入新链表
            tail = p2;
            p2 = p2->next;
        } 
        else { 
            // p1->data == p2->data 的情况（发现重复元素）
            tail->next = p1;      // 保留 p1
            tail = p1;
            p1 = p1->next;
            
            // 释放 L2 中重复的节点
            Node* temp = p2;
            p2 = p2->next;
            delete temp;
        }
    }

    // 将未遍历完的剩余链表直接接到尾部
    if (p1 != nullptr) {
        tail->next = p1;
    } else if (p2 != nullptr) {
        tail->next = p2;
    }
    // 删除 L2 的头结点
    delete list2.head;
    list2.head = nullptr; // 防悬空指针
    list1.displaylist(); // 输出合并后的链表
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
    add(list1, list2);  
    list1.head=nullptr;   
    values1= {1,3,6,10,15,16,17,18,19,20};
    values2= {2,4,5,7,8,9,12,22};
    for (int value : values1) {
        list1.insert(value);
    }                   
    for (int value : values2) {
        list2.insert(value);
    }
    cout<<"第二次实验："<<endl;         
    add(list1, list2);      
    list1.head=nullptr;         
    values1= {};        
    values2= {1,2,3,4,5,6,7,8,9,10};
    for (int value : values1) {
        list1.insert(value);
    }
    for (int value : values2) {
        list2.insert(value);
    }
    cout<<"第三次实验："<<endl;             
    add(list1, list2);                  
    return 0;   
}