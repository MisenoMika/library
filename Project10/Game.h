#ifndef _GAME_H_
#define _GAME_H_
#include "Gui.h"
#include "Weapon.h"
#include "PlayerShip.h"
#include "Obstacle.h"
class EnemyShip;
class Bomber;
class Destoryer;
class GunBoat;
class Explosion;
class Item;

#include <list>

class Game {
    Gui gui;   
    int winH, winW;     
    bool running;       
    int level;
    int lastlevel;
    int delaytime;
    int delaytime_2;
    int BomberCount;
    int GunBoatCount;
    int DestroyerCount;
    int CruiserCount;
    int MedicalPackCount;
    int WeaponPackCount;
    int maxBomberCount;
    int maxGunBoatCount;
    int maxDestroyerCount;
    int maxCruiserCount;
    int maxMedicalPackCount;
    int maxWeaponPackCount;
    PlayerShip* playership;
    std::list<Obstacle*> obstacles;
    std::list<Weapon*> weapons; 
    std::list<EnemyShip*> enemies; 
    std::list<Explosion*> explosions;
    std::list<Item*> items; 
    std::string mapfile;

public:
    Game(string mafile);
    ~Game();
    void update();
    int getWinH() const { return winH; }
    int getWinW() const { return winW; }
    PlayerShip* getPlayerShip() const { return playership; }
    Gui& getGui() { return gui; }
    std::list<Weapon*>& getWeapons() { return weapons; }
    std::list<EnemyShip*>& getEnemies() { return enemies; }
    std::list<Explosion*>& getExplosions() { return explosions; }
    std::list<Item*>& getItems() { return items; }
    std::list<Obstacle*>& getObstacles() { return obstacles; }
    bool isObstacle(int x, int y);
    bool isRunning() const { return running; }
    void setRunning(bool status) { running = status; }
    void setLevel(int lvl) { level = lvl; }

    int getLevel() const { return level; }
    void addBomber();
    void addDestroyer();
    void addGunBoat();
    void addCruiser();
    void addObstacle(int x, int y, int selection, string sym = "#", int color = 0);
    void reset();
    void clearScreen();
    void loadMap(string& mapfile);

};
#endif