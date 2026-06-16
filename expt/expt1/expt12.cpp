#include <iostream>
#include <vector>
#include "seqlist.h"
using namespace std; 
void Distinguish(list L){
    list oddList; // 存储奇数的顺序表   
    list evenList; // 存储偶数的顺序表
    for (int i = 0; i < L.size; i++) {
        if (L.data[i] % 2 == 0) {
            evenList.insert(L.data[i]); // 插入偶数到偶数表
        } else {
            oddList.insert(L.data[i]); // 插入奇数到奇数表
        }
    }                    
    cout << "原始表: ";
    L.display(); // 输出原始表                         
    cout << "奇数表: ";     
    oddList.display(); // 输出奇数表                                            
    cout << "偶数表: "; 
    evenList.display(); // 输出偶数表               

}
//测试代码
int main(){
    list L1, L2;
    vector<int> values1= {1,2,3,4,5,6,7,8,9,10,20,30,40,50,60};
    vector<int> values2= {10,20,30,40,50,60,70,80,90,100};
    for (int i = 0; i < values1.size(); i++) {
        L1.insert(values1[i]);
    }
    for (int i = 0; i < values2.size(); i++) {
        L2.insert(values2[i]);
    }
    cout<<"第一组数据:"<<endl;
    Distinguish(L1);
    cout<<"第二组数据:"<<endl;
    Distinguish(L2);

    return 0;
}