#ifndef __WOLF_H__
#define __WOLF_H__
#include "Predator.h"
class Wolf : public Predator {
public:
    Wolf(int x, int y, Game* game, int Maxhunger , int huntrange );
    ~Wolf(){};
    void update();
    void eat();
    void draw();
};

#endif