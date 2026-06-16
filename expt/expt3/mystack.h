#ifndef MYSTACK_H
#define MYSTACK_H 

enum error_code {
    SUCCESS = 0,
    STACK_OVERFLOW,
    STACK_UNDERFLOW
};

// ================= 顺序栈模板 =================
template <typename T>  // 声明这是一个模板，T 是一个类型占位符
struct stack {
    T* arr;          // 动态数组，存储类型为 T 的元素
    int top;         // 栈顶指针（作为数组下标，永远是 int，不需要变）
    int capacity;    // 栈的容量

    // 构造函数：初始化栈                       
    stack(int size) {
        arr = new T[size]; // 创建存储 T 类型数据的数组
        capacity = size;
        top = -1; 
    }   

    // 析构函数：释放栈内存                                     
    ~stack() {
        delete[] arr;
    }

    // 防御性编程：禁用拷贝构造和赋值操作
    stack(const stack&) = delete;
    stack& operator=(const stack&) = delete;

    // 成员函数：入栈操作                       
    error_code push(T value) { // 传入 T 类型的数据
        if (top == capacity - 1) {
            return STACK_OVERFLOW; 
        }
        arr[++top] = value; 
        return SUCCESS;
    }

    // 成员函数：出栈操作                       
    error_code pop(T &value) { // 传出 T 类型的数据
        if (top == -1) {
            return STACK_UNDERFLOW; 
        }
        value = arr[top--]; 
        return SUCCESS;
    }           

    // 成员函数：获取栈顶元素                                       
    error_code peek(T &value) {
        if (top == -1) {
            return STACK_UNDERFLOW; 
        }
        value = arr[top]; 
        return SUCCESS;
    }
    bool isEmpty() {
        // 栈空的条件是 top == -1，因为 top 是数组下标，初始值为 -1     
        return top == -1;
    }                                   
};

// ================= 链栈模板 =================
template <typename T> // 链栈也同样声明为模板
struct stacklink {
    struct node {
        T data;       // 节点里存的是 T 类型的数据
        node* next;
    };
    node* top; // 栈顶指针      

    stacklink() {
        top = nullptr; 
    }                                       

    ~stacklink() {
        node* current = top;
        while (current != nullptr) {
            node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }   
    // 防御性编程：禁用拷贝构造和赋值操作               
    stacklink(const stacklink&) = delete;
    stacklink& operator=(const stacklink&) = delete;
    // 成员函数：入栈操作
    void push(T value) {
        node* newNode = new node();
        newNode->data = value;
        newNode->next = top; 
        top = newNode; 
    }
    // 成员函数：将栈顶元素出栈并返回该元素的值
    error_code pop(T &value) { 
        if (top == nullptr) {
            return STACK_UNDERFLOW; 
        }
        node* temp = top;                                        
        value = temp->data;  
        top = top->next;     
        delete temp;       
        return SUCCESS; 
    }
    // 成员函数：获取栈顶元素的值但不修改栈                     
    error_code peek(T &value) { 
        if (top == nullptr) {
           return STACK_UNDERFLOW; 
        }
        value = top->data;
        return SUCCESS;
    }
    bool isEmpty() {
        return top == nullptr;
    }           
};
#endif // MYSTACK_H