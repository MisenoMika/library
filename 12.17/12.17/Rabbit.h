#ifndef __RABBIT_H__
#define __RABBIT_H__
#include "Animal.h"

class Rabbit : public Animal {;
public:
    Rabbit(int x, int y, Game* game, int Maxhunger );
    ~Rabbit(){};
    void update();
    void eat();
    void draw();
};

#endif