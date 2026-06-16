#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

// 节点定义
struct Node {
    int data;
    struct Node* next;
};

// 链表定义
struct linkedList {
    struct Node* head;

    // 构造函数：初始化 head    
    linkedList() {
        head = nullptr;
    }

    // 析构函数：释放链表内存
    ~linkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // 成员函数：基础插入（直接放到尾部）                       
    void insert(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // 成员函数：打印输出               
    void displaylist() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

#endif // LINKEDLIST_H