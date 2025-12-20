#ifndef __PREDATOR_H__
#define __PREDATOR_H__
#include "Animal.h"

class Predator : public Animal {
    int huntrange;
public:
    Predator(int x, int y, Game* game, int Maxhunger, int huntrange);
    virtual ~Predator(){};
    int getHuntRange() { return huntrange; }

};

#endif