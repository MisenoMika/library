#ifndef __ITEM_H__
#define __ITEM_H__
#include <string>

class Game;
using namespace std;
class Item{
protected:
    int x, y;
    Game* game;
    bool isAlive;
    int pickRange;
    string symbol;
public:
    Item(int x, int y, Game* game);
    virtual ~Item(){};
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void onPick()=0;

    int getX() const { return x; }
    int getY() const { return y; }
    bool getAlive() const { return isAlive; }
    void setAlive(bool status) { isAlive = status; }
};

#endif