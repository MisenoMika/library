#ifndef __GUNBOAT_H__
#define __GUNBOAT_H__
#include "EnemyShip.h"

class GunBoat : public EnemyShip{
    int reloadTime;
    int delayTime;
public:
    GunBoat(int x, int y, Game* game);
    ~GunBoat() {};
    void update();
    void attack(int dirX, int dirY );
    void draw();
    void move();
    void onDeath();  
};

#endif