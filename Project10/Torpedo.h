#ifndef __TORPEDO_H__
#define __TORPEDO_H__
#include "Weapon.h"
class PlayerShip;
class Game;
class EnemyShip;

class Torpedo : public Weapon {
    int destY;
    int moveCount;
    int duration;
    EnemyShip* target;
    PlayerShip* playerTarget;
public:  
    Torpedo(int x, int y, Game* game, int destY);
    ~Torpedo() {};
    void move();
    void draw();
    void update();
    void onHit();
};

#endif