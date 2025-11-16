#ifndef __WEATHER_H__
#define __WEATHER_H__
#include <ctime>
#include <iostream>
class Weather
{
    int current;
public:
    Weather();
    int getWeather();
    void updateWeather();
};
#endif