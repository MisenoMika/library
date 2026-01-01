#ifndef __MEDICALPACK_H__
#define __MEDICALPACK_H__
#include "Item.h"
#include <string>
class Game;
using namespace std;
class MedicalPack : public Item{
public:
    MedicalPack(int x, int y, Game* game);
    ~MedicalPack(){};
    void update();
    void draw();
    void onPick();
};

#endif