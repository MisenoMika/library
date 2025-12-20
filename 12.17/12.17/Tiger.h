#ifndef __TIGER_H__
#define __TIGER_H__
#include "Predator.h"
class Tiger : public Predator {
public:
    Tiger(int x, int y, Game* game, int Maxhunger , int huntrange );
    void update();
    void eat();
    void draw();
};

#endif