#include "Decision.h"
#include <ctime>
#include <stdlib.h>
#include <iostream>

using namespace std;

void weather(int*w,int*d, float& var){
    int a=rand()%14;
    if(a>9)  *d=0;
    switch(*w){
        case 1:
            if(rand()%5<=2 && rand()%13<9){
                *(d)=1;
                var++;
                }
                break;
        case 2:if(rand()%5<=2 && rand()%7<2){
                *(d)=1;
                var++;
                }
                break;
        case 3:if(rand()%5<=2 && rand()%13<9){
                *(d)=1;
                var++;
                }
                break;
        case 4:if(rand()%5<=3 && rand()%13<9){
                *(d)=1;
                var++;
                }
                break;
        case 5:*(d)=1;
                var++;
                break;
        default:
        *(d)=0;
        break;
    }

}

void result(int*w, int*d,int& num){
    for(int i=0;i<num;i++){
        if(*(d+i)==1){
            switch(*(w+i)){
                case 1:
                    cout<<"No."<<i+1<<"The weather is sunny and humid"<<endl;
                    break;
                case 2:
                    cout<<"No."<<i+1<<"The weather is sunny and not humid"<<endl;
                    break;
                case 3:
                    cout<<"No."<<i+1<<"The weather is rainy and windy"<<endl;
                    break;
                case 4:
                    cout<<"No."<<i+1<<"The weather is rainy and not windy"<<endl;
                    break;
                case 5:
                    cout<<"No."<<i+1<<"The weather is overcast"<<endl;
                    break;
                default:
                break;
            }
            cout<<"Play"<<endl;
        }
        if(*(d+i)==0){
            switch(*(w+i)){
                case 1:
                    cout<<"No."<<i+1<<"The weather is sunny and humid"<<endl;
                    break;
                case 2:
                    cout<<"No."<<i+1<<"The weather is sunny and not humid"<<endl;
                    break;
                case 3:
                    cout<<"No."<<i+1<<"The weather is rainy and windy"<<endl;
                    break;
                case 4:
                    cout<<"No."<<i+1<<"The weather is rainy and not windy"<<endl;
                    break;
                case 5:
                    cout<<"No."<<i+1<<"The weather is overcast"<<endl;
                    break;
                default:
                break;
            }
            cout<<"Not play"<<endl;
         } 
    }
}

void percentage(float var,int& n){
       cout<<"The percentage is "<<(var/ n)*100<<"%"<<endl;
}