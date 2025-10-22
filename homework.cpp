
#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

int main()
{
    srand(time(0));
    int n=0, i;
    int a[20]={6};//存储天气
    int b[20]={6};//存储决策
    for(NULL;n<20; n++)
    {   
    cout<<"Please input an integer from 1 to 5(if you input -1 then the program ends)"<<endl;
    cin>>i;
    if(i==-1){
        break;
    }
    if(i!=-1){
        a[n]=i;
        int f=rand()%14;
        if(f<=9){//decide to play.step1
            switch(i)
            {
                case 1:{//sunny&humid
                 int j=rand()%5;//step2
                 cout<<"j is "<<j<<endl;
                    if(j<=2){//decide to play.step2
                        int c=rand()%13;
                        cout<<"c is "<<c<<endl;
                        if(c<=9){
                            b[n]=1;

                        }
                        else{
                            b[n]=0;
                        }
                    }
                    else{
                        b[n]=0;//该次循环结果为not play
                    }
                    break;
                }
                
                case 2:{ 
                    int k=rand()%5;//step2
                    cout<<"k is "<<k<<endl;
                    if(k<=2){//decide to play.step2
                        int d=rand()%7;
                        cout<<"d is "<<d<<endl;
                        if(d<=2){
                            b[n]=1;
                        }
                        else{
                            b[n]=0;
                        }
                    }
                    else{
                        b[n]=0; //该次循环结果为not play
                    }
                    break;
                }
                
                case 3:{
                    int l=rand()%5;//step2
                    cout<<"l is "<<l<<endl;
                    if(l<=2){//decide to play.step2
                        int e=rand()%7;
                        if(e<=2){
                            b[n]=1;
                        }
                        else{
                            b[n]=0;
                        }
                    }
                    else{
                        b[n]=0; //该次循环结果为not play
                    }
                    break;
                }
                
                case 4:{
                    int m=rand()%5;//step2
                    cout<<"m is "<<m<<endl;
                    if(m<=3){//decide to play.step2
                        int e=rand()%12;
                        if(e<=9){
                            b[n]=1;
                        }
                        else{
                            b[n]=0;
                        }
                    }
                    else{
                        b[n]=0; //该次循环结果为not play
                    }
                    break;
                }
                
                case 5:{
                    b[n]=1;
                    break;
                }
                default:;
                break;
            }
        }
        else if(f>9){//decide not to play.step1
            b[n]=0;
        }
    }//if等于-1的大括号
    
    }//20次for的if
    for(int num=0;num<20;num++)
    {
        if(b[num]==1)
        {
            if(a[num]==1){
            cout<<"The weather is sunny and rainy"<<endl;
            }
            if(a[num]==2){
            cout<<"The weather is sunny and not rainy"<<endl;
            }
            if(a[num]==3){
            cout<<"The weather is rainy and windy"<<endl;
            }
            if(a[num]==4){
            cout<<"The weather is rainy and not windy"<<endl;          
            }
            if(a[num]==5){
            cout<<"The weather is overcast"<<endl;
            }
            cout<<"Decision:Play"<<endl;
        }
        if(b[num]==0)
            {
                if(a[num]==1){
                cout<<"The weather is sunny and rainy"<<endl;
                cout<<"Decision:Not Play"<<endl;
                }
                if(a[num]==2){
                cout<<"The weather is sunny and not rainy"<<endl;
                cout<<"Decision:Not Play"<<endl;
                }
                if(a[num]==3){
                cout<<"The weather is rainy and windy"<<endl;
                cout<<"Decision:Not Play"<<endl;
                }
                if(a[num]==4){
                cout<<"The weather is rainy and not windy"<<endl;   
                 cout<<"Decision:Not Play"<<endl;
                }
                if(a[num]==5){
                    cout<<"The weather is overcast"<<endl;
                    cout<<"Decision:Not Play"<<endl;
                }
                
            }
    }
    system("Pause");
    return 0;
}