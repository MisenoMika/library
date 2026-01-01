#ifndef __WEAPON_H__
#define __WEAPON_H__
#include <string>
class Game;
using namespace std;

class Weapon{
protected:
    Game* game;
    int x, y;
    int dx, dy;
    int damage;
    int speed;
    bool isAlive;
    string symbol;
public:
    Weapon(int x, int y, Game* game);
    virtual ~Weapon() {}
    virtual void move() = 0;
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void onHit() = 0;
    
    int getX() const { return x; }
    int getY() const { return y; }
    bool getAlive() const { return isAlive; }
    void setAlive(bool status) { isAlive = status; }

};

#endif