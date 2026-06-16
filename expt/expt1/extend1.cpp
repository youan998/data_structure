#include <iostream>  
#include "seqlist.h"    
using namespace std;        
// 核心逻辑1：求并集 C = A ∪ B
list unionList(const list &A, const list &B) {
    list C;
    int i = 0, j = 0;
    while (i < A.size && j < B.size) {
        if (A.data[i] == B.data[j]) {
            C.insert(A.data[i]);
            i++;
            j++;
        } else if (A.data[i] < B.data[j]) {
            C.insert(A.data[i]);
            i++;
        } else {
            C.insert(B.data[j]);
            j++;
        }
    }
    // 将剩余元素追加到末尾
    while (i < A.size) { C.insert(A.data[i]); i++; }
    while (j < B.size) { C.insert(B.data[j]); j++; }
    return C;
}

// 核心逻辑2：求交集 C = A ∩ B
list intersectionList(const list &A, const list &B) {
    list C;
    int i = 0, j = 0;
    while (i < A.size && j < B.size) {
        if (A.data[i] == B.data[j]) {
            C.insert(A.data[i]);
            i++;
            j++;
        } else if (A.data[i] < B.data[j]) {
            i++;
        } else {
            j++;
        }
    }
    return C;
}

// 核心逻辑3：求差集 C = A - B
list differenceList(const list &A, const list &B) {
    list C;
    int i = 0, j = 0;
    while (i < A.size && j < B.size) {
        if (A.data[i] == B.data[j]) {
            i++;
            j++;
        } else if (A.data[i] < B.data[j]) {
            C.insert(A.data[i]);
            i++;
        } else {
            j++;
        }
    }
    // 将 A 中剩余元素追加到末尾
    while (i < A.size) { C.insert(A.data[i]); i++; }
    return C;
}

// 附加逻辑：实现 A = A op B 的原地覆盖
void assignUnion(list &A, const list &B) {
    list C = unionList(A, B);
    A = C; // C++ 中同类型结构体可以直接赋值，覆盖原表
}
void assignIntersection(list &A, const list &B) {
    list C = intersectionList(A, B);
    A = C;
}
void assignDifference(list &A, const list &B) {
    list C = differenceList(A, B);
    A = C;
}