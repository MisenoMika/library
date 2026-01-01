#ifndef __CRUISER_H__
#define __CRUISER_H__
#include "EnemyShip.h"
#include <string>
using namespace std;
class Game;
class Cruiser : public EnemyShip{
    int reloadTime;
    int delayTime;
    int delayTime_2;
    string symbol1;
    string symbol2;
    string symbol3;
    string symbol4;
public:
    Cruiser(int x, int y, Game* game);
    ~Cruiser() {}
    void update();
    void attack(int dirX, int dirY );
    void attackMissile();
    void draw();
    void move();
    void onDeath();
};

#endif