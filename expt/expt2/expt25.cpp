#include <iostream>
using namespace std;
struct Node {
    int data;
    Node* link;
};
int findKthFromEnd(Node* list, int k) {
    // 合法性检验：处理空指针或非法 k 值
    if (list == nullptr || list->link == nullptr || k <= 0) {
        return 0; 
    }
    
    // 初始化快慢指针，指向第一个实际数据结点
    Node* slow = list->link;
    Node* fast = list->link;

    // 让 fast 指针先向前移动 k-1 步
    for (int i = 0; i < k - 1; ++i) {
        if (fast->link != nullptr) {
            fast = fast->link;
        } else {
            // fast 提前走到了链表尽头，说明链表总长度小于 k
            return 0; 
        }
    }
    // fast 和 slow 同步向后移动
    while (fast->link != nullptr) {
        slow = slow->link;
        fast = fast->link;
    }
    cout << slow->data << endl; 
    return 1;                   
}