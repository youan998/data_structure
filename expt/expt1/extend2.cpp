#include <iostream>
#include "seqlist.h"
using namespace std;        
int findMedian(const list &A, const list &B) {
    //时间复杂度 O(n)，空间复杂度 O(1)
    // 确保两个顺序表等长
    if (A.size != B.size || A.size == 0) {
        cout << "输入序列不合法或不等长";
        return -1; 
    }
    
    int i = 0, j = 0;// A 和 B 的当前索引   
    int current = 0;
    int L = A.size;
    
    // 合并后的中位数恰好是第 L 个被提取的较小元素
    // 因此只需进行 L 次步进比对
    for (int step = 0; step < L; step++) {
        // 如果 A 的元素较小，或者 B 已经遍历完
        if (i < A.size && (j >= B.size || A.data[i] < B.data[j])) {
            current = A.data[i];
            i++;
        } else {
            // 否则取 B 的元素
            current = B.data[j];
            j++;
        }
    }
    
    return current;
}