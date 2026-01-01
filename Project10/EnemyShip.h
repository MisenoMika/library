#ifndef __ENEMYSHIP_H__
#define __ENEMYSHIP_H__
#include "Explosion.h"
#include <string>
using namespace std;
class Game;
class EnemyShip{
protected:
    int health;
    int x, y;
    int dx, dy;
    int speed;
    int shellCount;
    int missileCount;
    bool isAlive;
    string symbol;
    Game* game;
public:
    EnemyShip(int x, int y, Game* game);
    virtual ~EnemyShip() {};
    virtual void update() = 0;
    virtual void attack(int dirX, int dirY)=0;
    virtual void draw() = 0;
    virtual void move() = 0;
    virtual void onDeath() = 0;  // 死亡时调用，子类可重写
    
    void hitted(int damage);
    int getX() const { return x; }
    int getY() const { return y; }
    bool getAlive() const { return isAlive; }
    void setAlive(bool status) { isAlive = status; }
};

#endif