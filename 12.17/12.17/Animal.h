#ifndef __ANIMAL_H__
#define __ANIMAL_H__
#include "Entity.h"
class Animal: public Entity {
    int hunger, maxHunger;
    bool isAlive;
public:
    Animal(int x, int y, Game* game, int Maxhunger);
    virtual ~Animal(){};
    bool alive() { return isAlive; }
    void setAlive(bool status) {isAlive = status; }
    virtual void eat() = 0;
    void eaten() { isAlive = false; }//需要重写（死亡后应该移除）
    int getHunger() { return hunger; }
    int getMaxHunger() { return maxHunger; }
    void setHunger(int h) { hunger = h; }
};

#endif