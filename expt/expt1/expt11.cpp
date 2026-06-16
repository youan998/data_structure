#include <iostream>
#include "seqlist.h"
using namespace std;   
void insertlist(list &L, int value){
    // 插入元素 value 到顺序表 L 中，保持 L 中元素的有序性          
    if(L.size >= 100){
        cout << "顺序表已满 " << value << "." << endl;
    } 
    // 如果新值比第一个元素还小，直接插入到开头                         
    else if (value <= L.data[0]) 
    {
        for(int i=L.size;i>0;i--){
            L.data[i]=L.data[i-1];  
        }
        L.data[0]=value;
        L.size++;                   
    }
    // 如果新值比最后一个元素还大，直接插入到末尾               
    else if (value >= L.data[L.size-1]) 
    {
                L.data[L.size] = value;
                L.size++;
    }
    else {
        for (int i = 0; i <= L.size; i++)
        {
            if (value < L.data[i])
            {
                for (int j = L.size; j > i; j--)
                {
                    L.data[j] = L.data[j-1];// 从后往前挪动元素，腾出位置
                }
                L.data[i] = value;
                L.size++;
                break;
            }
            
        }
        
    }
}
//测试代码
int main(){
    list L;
    int values[] = {10,20,30,40,50,60,70,80,90,100};    
    for (int i = 0; i < 10; i++)
    {
        L.insert(values[i]);
    }
    int x[]={25, 85, 110, 8};
    for (int i = 0; i < 4; i++)
    {
        insertlist(L,x[i]);
    }
    L.display();        
}