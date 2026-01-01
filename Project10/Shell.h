#ifndef __SHELL_H__
#define __SHELL_H__
#include "Weapon.h"
#include "Game.h"
class Shell : public Weapon{
    int ai;
    EnemyShip* target;
public:
    Shell(int x, int y, Game* game, int dx, int dy, int ai);
    ~Shell() {}
    void move();
    void draw();
    void update();
    void onHit();

};

#endif