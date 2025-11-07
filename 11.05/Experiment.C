#include <iostream>
#include "Experiment.h"
#include "Computing.h"
using namespace std;
void DoExperiment(int count){
    double** M=nullptr;//存储8*1000个PlayPercentage
    //double** P=nullptr;//用于存储8个x下的ave和std（后来才发现是用来存概率的）
    double* percent=nullptr;//用于存储1000次singletest中，每次singletest总计10000次makedecision后得出的PlayPercentage
    percent= new double[count];
    M=new double*[8];
    double ave=0, std=0, sum=0, square=0;
    /*for(int i=0; i<count; i++){
        M[num][i]=percent[];
    }*/
    //P=new double*[8];
    for(int num=0; num<8; num++){
        M[num]=new double[count];
        //P[num]=new double[2];

        Multitest(percent, num+2, count);//i+2即x（概率）
        for(int j=0; j<count; j++){
        M[num][j] = percent[j]; // 填充数据
        }
        CompStatistics(M, count, ave, std, sum, square, num);
        cout<<"p="<<((num+2.0)/10)<<"; ave="<<ave<<"; std="<<std<<endl;
    }
    delete[] percent;
    for(int i=0; i<8; i++){
    delete[] M[i];
    }
   // for(int i=0; i<8; i++)delete[] P[i];
    delete[] M;
   // delete[] P;
}

void Multitest(double*percent, int p, int count){//int p为x的值
    for(int i=0; i<count; i++){
    percent[i]=Singletest(p, 10000);
    }
}

double Singletest( int p,int count){
    int* W=new int[count];//存储Play的次数
   // double* D=new double[1000];//传递每10000次decision后得出的概率
    for(int j=0; j<count; j++){
        W[j]= MakeDecision(p);//得到10000次decision
    }
    double result = CompPlayPercentage(W, count);
    delete[] W;
    return result;
}