#include <iostream>
#include "linkedList.h"
#include <vector>
using namespace std;   
void deleteElement(linkedList& list) {
    // 如果链表为空或只有一个节点，直接输出并返回
    if (list.head == nullptr || list.head->next == nullptr) {
        list.displaylist();
        return;
    }
    // 使用双指针法：slow 负责追踪当前节点，fast 负责寻找下一个不同的节点
    Node* slow = list.head;
    Node* fast = list.head->next;
    while (fast != nullptr ){
        if (fast->data == slow->data) {
            Node* temp = fast; // 保存要删除的节点              
            slow->next = fast->next; // 删除重复元素 
            fast = fast->next; // 移动快指针           
            delete temp; // 释放内存
                    
        }   
        else {
            slow = slow->next; // 移动慢指针
            fast = fast->next; // 移动快指针
        }
    }
    list.displaylist(); // 输出删除重复元素后的链表      
    //外层循环 O(n)，内层循环 O(1)，总的时间复杂度为 O(n)。               
}
int main(){
    linkedList list;
    vector<int> values= {1,2,3,4,5,6,7,8,9};
    for (int value : values) {
        list.insert(value);
    }       
    cout << "第一次实验："<< endl;
    deleteElement(list);
    list.head=nullptr;          
    values= {1,1,2,2,2,3,4,5,5,5,6,6,7,7,8,8,9};
    for (int value : values) {
        list.insert(value);
    }                               
    cout << "第二次实验："<< endl;  
    deleteElement(list);
    list.head=nullptr;  
    values= {1,2,3,4,5,5,6,7,8,8,9,9,9,9,9};
    for (int value : values) {
        list.insert(value);
    }                   
    cout << "第三次实验："<< endl;              
    deleteElement(list);        
    return 0;
}