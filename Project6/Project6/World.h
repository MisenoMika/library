#ifndef _WORLD_H_
#define _WORLD_H_
#include "Group.h"
#include "Weather.h"

class World {
    Group** groups;
    size_t count;
    size_t size;
    Weather* weather;
    void HandleGroupSplit();
    void HandleGroupMerge();
public:
    World(size_t c);
    void DoSimulation();
    ~World();     
};
#endif
