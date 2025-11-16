#ifndef __WORLD_H__
#define __WORLD_H__
#include "Weather.h"
#include "Group.h"
class World
{
    Group** group;//行为小组数量，列存储每个对着每个组的指针
    size_t count;//小组数量
    Weather* w;
public:
    World(size_t);
    ~World();
    void DoSimulation();
};
#endif
