#ifndef __PLAYERSHIP_H__
#define __PLAYERSHIP_H__
#include <string>
#include <set>
class Game;
using namespace std;
class PlayerShip{
    int health;
    int maxHealth;
    int x, y;
    int lastdirection;
    int dx, dy;
    int speed;
    int coins;
    int maxCoins;
    int level;
    int shellCount;
    int missileCount;
    int burstCount, burstLeft, burstdirX, burstdirY;
    //int burstX_2, burstY_2, burstX_3, burstY_3;
    int delayTime;
    int reloadTime;
    bool isAlive;
    string symbol1;
    string symbol2;
    string symbol3;
    Game* game;
public:
    PlayerShip(int x, int y, Game* game);
    ~PlayerShip(){};
    void move(int& key);
    void attack(int& key);
    void hitted(int damage);
    void levelUp();
    void update(int& key);
    void draw();
    void setAlive(bool status){ isAlive = status; }
    bool getAlive() const { return isAlive; }
    void addcoins(int amount){ coins += amount; }
    void addShells(int amount){ shellCount += amount; }
    void addMissiles(int amount){ missileCount += amount; }
    void addHealth(int amount){ 
        if(abs(maxHealth - health) <= amount){
            health = maxHealth;
        }
        else {
            health += amount;
        }
    }
    void setX(int newx){ x = newx; }
    void setY(int newy){ y = newy; }

    int getX() const { return x; }
    int getY() const { return y; }
    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }
    int getMaxCoins() const { return maxCoins; }
    int getShellCount() const { return shellCount; }
    int getMissileCount() const { return missileCount; }
    int getCoins() const {return coins;}


};

#endif