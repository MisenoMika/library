#ifndef __GRASS_H__
#define __GRASS_H__
#include "Entity.h"
class Grass : public Entity {
    int progress, growCounter;
public:
    Grass(int x, int y, Game* game);
    ~Grass(){};
    void update();
    void draw();
    bool isEaten(){ return progress == 3;}
    int getProgress(){ return progress;}
    void setProgress(int p){ progress = p;}
};

#endif