#include <iostream>
#include <ctime>
#include "Decision.h"
using namespace std;


Decision::Decision(double percent):x(percent){}
int Decision::MakeDecision (int weather)
{
    int dice;
    dice = (rand () % 10) +1;
    weather =rand()%5 +1;
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