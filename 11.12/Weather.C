#include <time.h>
#include "Weather.h"
using namespace std;

Weather::Weather(){
    current=rand()%5+1;
}
int Weather::getWeather(){
    return current;
}
void Weather::updateWeather(){
    int dice=rand()%10+1;
    switch(current){
        case 1:{
            if(dice<=1)current=1;
            if(dice>=2 && dice<=4)current=2;
            if(dice>=5 && dice<=8)current=5;
            if(dice>=9)current=3;
            break;
        }
        case 2:{
            if(dice<=2)current=2;
            if(dice>=3 && dice<=5)current=1;
            if(dice>=6 && dice<=8)current=5;
            if(dice==9)current=3;
            if(dice==10)current=4;
            break;
        }
        case 3:{
            if(dice<=1)current=3;
            if(dice>=2 && dice<=4)current=5;
            if(dice>=5 && dice<=6)current=1;
            if(dice>=7 && dice<=9)current=4;
            if(dice==10)current=2;
            break;
        }
        case 4:{
            if(dice<=2)current=4;
            if(dice>=3 && dice<=4)current=5;
            if(dice>=5 && dice<=7)current=1;
            if(dice>=8 && dice<=9)current=3;
            if(dice==10)current=2;
            break;
        }
        case 5:{
            if(dice<=2)current=5;
            if(dice>=3 && dice<=4)current=1;
            if(dice>=5 && dice<=6)current=2;
            if(dice>=7 && dice<=8)current=3;
            if(dice>=9 && dice<=10)current=4;
            break;
        }
        default:
        current = (rand() % 5) + 1;
        break;        
    }
}
