#include <iostream>
#include <ctime>
#include "Decision.h"
using namespace std;

int main(){
    srand(time(0));
    int* w = nullptr;  // 初始化指针，避免野指针
    int* d = nullptr;
    float var=0;//可玩耍的次数
    w=new int[20]();//weather
    d=new int[20]();//decision

    int num=0;//输入值
    int a=0;//有效输入次数
    for(int i=0;i<20;i++){
        cout<<"Please enter 20 integers"<<endl;
        cin>>num;
        *(w+i)=num;
        if(*(w+i)<-1 || *(w+i)>=6){
            cout<<"Illegal input"<<endl; 
            i--;
            continue;
        }
        if(*(w+i)==-1){
            break;
        }
        weather((w+i), (d+i),var);
        a++;

        w-i;
        d-i;
    }
    
    result(w, d, a);

    percentage(var, a);
    delete [] w;
    delete [] d;
    system("Pause");
    return 0;
}

