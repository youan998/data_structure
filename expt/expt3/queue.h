#ifndef QUEUE_H 
#define QUEUE_H   
using namespace std;  
enum Error_code {
    SUCCESS = 0,
    STACK_OVERFLOW,
    STACK_UNDERFLOW
};      
// ================= 循环队列结构体 =================              
struct clclequeue
{
    int* arr;          // 动态数组，存储队列元素            
    int front;        // 队头指针   
    int rear;         // 队尾指针       
    int capacity;     // 队列容量           
    clclequeue(int size) {
        arr = new int[size];
        capacity = size;
        front = rear = 0; 
    }
    ~clclequeue() {
        delete[] arr;
    }            
    // 禁用拷贝构造和赋值操作      
    clclequeue(const clclequeue&) = delete;
    clclequeue& operator=(const clclequeue&) = delete;
    // 成员函数：判断队列是否满了           
    bool isFull() {
        return (rear + 1) % capacity == front;// 循环队列满的条件是 rear 的下一个位置是 front   
    }       
    bool isEmpty() {
        return front == rear;
    }
    Error_code enqueue(int value) {
        if (isFull()) {
            return STACK_OVERFLOW; 
        }
        arr[rear] = value;
        rear = (rear + 1) % capacity; 
        return SUCCESS;
    }
    Error_code dequeue() {
        if (isEmpty()) {
            return STACK_UNDERFLOW; 
        }
        front = (front + 1) % capacity;
        return SUCCESS;
    }
};
struct node
     {
        int data; // 数据域
        node* next; // 指针域
        node(int value) : data(value), next(nullptr) {} // 构造函数
    };  
// ================= 链式队列结构体 =================           
struct linkqueue
{
    node* front; // 队头指针            
    node* rear;  // 队尾指针                                
    linkqueue() : front(nullptr), rear(nullptr) {} // 构造函数                              
    ~linkqueue() { // 析构函数，释放所有节点内存
        while (front != nullptr) {
            node* temp = front;
            front = front->next;
            delete temp;
        }
    }     
    // 禁用拷贝构造和赋值操作             
    linkqueue(const linkqueue&) = delete;           
    linkqueue& operator=(const linkqueue&) = delete;  
    // 成员函数：判断队列是否为空                         
    bool isEmpty() {
        return front == nullptr;
    }                   
    void enqueue(int value) {
        node* newNode = new node(value);
        if (isEmpty()) {
            front = rear = newNode; // 队列为空时，front 和 rear 都指向新节点
        } else {
            rear->next = newNode; // 将新节点链接到队尾
            rear = newNode; // 更新 rear 指针
        }
    }
    void dequeue() {
        if (isEmpty()) {
            return; // 队列为空，无需出队
        }
        node* temp = front; // 保存当前队头节点
        front = front->next; // 更新 front 指针指向下一个节点
        delete temp; // 释放原队头节点的内存
        if (front == nullptr) { // 如果出队后队列变空，更新 rear 指针
            rear = nullptr;
        }
    }       
    int count() {
        int count = 0;
        node* current = front;
        while (current != rear) {
            count++;
            current = current->next;
        }
        count++; // 计算 rear 节点  
        return count;// 返回队列中元素的数量
    }
};
// ================= 顺序队列结构体 =================               
struct queue
{
    int* arr;          // 动态数组，存储队列元素            
    int front;        // 队头指针   
    int rear;         // 队尾指针       
    int capacity;     // 队列容量           
    queue(int size) {
        arr = new int[size];
        capacity = size;
        front = rear = 0; 
    }
    ~queue() {
        delete[] arr;
    }               
    // 禁用拷贝构造和赋值操作           
    queue(const queue&) = delete;
    queue& operator=(const queue&) = delete;
    // 成员函数：判断队列是否满了           
    bool isFull() {
        return rear == capacity; 
    }
    bool isEmpty() {
        return front == rear;
    }           
    // 成员函数：入队操作           
    void enqueue(int value) {
        if (isFull()) {
            return; // 队列已满，无法入队
        }
        arr[rear] = value;
        rear++;
    }
    void dequeue() {
        if (isEmpty()) {
            return; // 队列为空，无需出队
        }
        // 采用最标准、最高效的顺序队列出队法：只移动头指针
        front++; 
    }
    int count() {
        return rear - front; // 返回队列中元素的数量
    }                   
};
#endif // QUEUE_H       