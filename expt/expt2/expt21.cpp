#include <iostream>
#include "linkedList.h"
#include <vector>
using namespace std;
void Distinguish(linkedList& list) {
    linkedList oddList; // 存储奇数的链表   
    linkedList evenList; // 存储偶数的链表
    Node* current = list.head;
    while (current != nullptr) {
        if (current->data % 2 == 0) {
           evenList.insert(current->data); // 插入偶数到偶数链表
        } else {
            oddList.insert(current->data); // 插入奇数到奇数链表
        }
        current = current->next;
    }                    
    cout << "原始链表: ";
    list.displaylist(); // 输出原始链表                         
    cout << "奇数链表: ";     
    oddList.displaylist(); // 输出奇数链表                                            
    cout << "偶数链表: "; 
    evenList.displaylist(); // 输出偶数链表               
}               
int main() {
    linkedList list;
    vector<int> values = {1,2,3,4,5,6,7,8,9,10,20,30,40,50,60 };
    for (int value : values) {
        list.insert(value);
    }      
    cout << "第一次输入的链表: "<< endl;     
    Distinguish(list);
    list.head = nullptr; // 重置原始链表
    vector<int> newValues = {10,20,30,40,50,60,70,80,90,100};
    for (int value : newValues) {
        list.insert(value);
    }
    cout << "第二次输入的链表: "<< endl;
    Distinguish(list);
    return 0;
}


    