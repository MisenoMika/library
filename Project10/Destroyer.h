#ifndef __DESTROYER_H__
#define __DESTROYER_H__
#include "EnemyShip.h"

class Destroyer : public EnemyShip{
    int reloadTime;
    int delayTime;
    int torpedoCount;
public:
    Destroyer(int x, int y, Game* game);
    ~Destroyer() {}
    void update();
    void attack(int dirX, int dirY );
    void attackTorpedo();
    void draw();
    void move();
    void onDeath();
};

#endif