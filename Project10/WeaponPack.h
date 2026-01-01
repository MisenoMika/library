#ifndef __WEAPONPACK_H__
#define __WEAPONPACK_H__
#include "Item.h"
#include <string>
class Game;

class WeaponPack : public Item{
public:
    WeaponPack(int x, int y, Game* game);
    ~WeaponPack(){};
    void update();
    void draw();
    void onPick();
};  

#endif