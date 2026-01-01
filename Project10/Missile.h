#ifndef __MISSILE_H__
#define __MISSILE_H__
#include "Weapon.h"
#include "Game.h"
class Bomber;
class EnemyShip;
class Missile : public Weapon{
    int ai;
    int moveCount;
    int maxCount;
    int flyTime;
    int delayTime;
    int maxFlyTime;
    EnemyShip* target;
public:
    Missile(int x, int y, Game* game, int ai);
    ~Missile();
    void move();
    void draw();
    void update();
    void onHit();
};

#endif