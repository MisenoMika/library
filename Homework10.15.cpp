#include <iostream>//预运行 引入指令库
using namespace std;//标准名空间
int main()//Where your 程序begins
{  
    double d1, d2,d3;
    cout<<"Please input 3 double-precision floating-point num";
    cin>>d1>>d2>>d3;

    double ave=(d1+d2+d3)/3;
    cout<<"Average of 3num is"<<ave<<endl;
    
    double max=d1;
    if (d1>d2){
        NULL ;
    }
    else {
        max=d2 ;
    }

    if (d2>d3){
        NULL ;
    }
    else{
        max=d3;
    }

    cout<<"The maximum of three numbers is"<<max<<endl;
    cout<<"Press ENTER to output the ave2"<<endl;
    system("pause");
    
    d1*=6;//将一个数字乘以6
    double ave2=(d1+d2+d3)/3;
    cout<<"The ave2 is"<<ave2<<endl;
    system("Pause");
    return 0;
    
}