#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include "Computing.h"
#include "Experiment.h"
using namespace std;


int MakeDecision (int p)
{
    double x=(p+0.0)/10;

    int dice;
    dice = (rand () % 10) +1;
    int weather =rand()%5 +1;
    if (dice <= 10*x) return 1;
    //now consider weather
    if (weather == 5) return 0;

    if (weather < 3)//sunny
    {
        dice = rand () % 10 +1;

        if (dice > (10-5*x)){  //error
            if (weather == 1)
            {             //humid
                dice = (rand () % 10) +1;
                if (dice > 5*x) return 0;    //play
                else return 1;    //not play
            }
            else if(weather==2)
            {
                dice = (rand () % 10) +1;
                if (dice > 10-10*x) return 0;    //play
                else return 1;    //not play
            }
        }
        else return 1;
    }
    else//rainy
    {
        dice = (rand () % 10)+1;
        if (dice > 10*x){    //play
            if (weather == 3)
            {            //windy
                dice = (rand () % 10) +1;
                if (dice > (10-10*x)) return 0;    //play
                else return 1;    //not play
            }
            else if(weather==4)//weather==4 notwindy
            {
                dice =(rand () % 10) +1;
                if (dice > (5*x)) return 0;    //play
                else return 1;    //not play
            }
        }
        else if(dice <=10*x)return 1;
    }
    return 1;
}
double CompPlayPercentage(int* D, int count){
    int plays = 0;
    for (int i = 0; i < count; i++) {
        if (D[i] == 0) plays++;
    }

    return (plays + 0.0) / (count) ;
}
void CompStatistics(double** M, int count, double& ave, double& std, double& sum, double& square, int& num){
    sum=0, square=0;

            for(int j=0; j<count;j++){
            sum += M[num][j];
            }
        
        /*ave=sum/count;
        square=pow(sum, 2);
        std=sqrt(square/count);*/
        ave = sum / count;// 计算每个样本与平均值的平方差之和
        for(int j=0; j<count;j++){
        square += pow(M[num][j] - ave, 2);
        }
        std = sqrt(square / count); // 平方差的均值开根号
        
}