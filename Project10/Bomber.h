#ifndef __BOMBER_H__
#define __BOMBER_H__
#include "EnemyShip.h"
#include <string>
using namespace std;
class Game;
class Bomber : public EnemyShip {
    int moveCount;
    int reloadTime;
    string symbol1;
    string symbol2;
    string symbol3;
public:
    Bomber(int x, int y, Game* game);
    ~Bomber() {};
    void update();
    void attack(int dirX, int dirY );
    void attackTorpedo();
    void draw();
    void move();
    void onDeath(){};
};
#endif