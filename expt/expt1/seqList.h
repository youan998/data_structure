#ifndef SEQLIST_H
#define SEQLIST_H

#include <iostream>

struct list {
    int data[100];
    int size;

    // 构造函数：初始化 size
    list() {
        size = 0;
    }

    // 析构函数
    ~list() {
    }

    // 成员函数：基础插入（直接放到尾部）
    void insert(int value) {
        if (size < 100) {
            data[size] = value;
            size++;
        } else {
            std::cout << "表已满" << std::endl;
        }
    }

    // 成员函数：打印输出
    void display() {
        for (int i = 0; i < size; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

#endif