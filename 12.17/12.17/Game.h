#ifndef _GAME_H_
#define _GAME_H_
#include "Gui.h"
#include "Entity.h"
#include "Grass.h" 
#include "Animal.h"
#include <vector>
#include <list>
using namespace std;

class Game {
private:
    Gui gui;   
    int winH, winW;            
    std::vector<Grass*> grasses;
    std::list<Animal*> rabbits; 
    std::list<Animal*> wolves; 
    std::list<Animal*> tigers; 

public:
    Game(int tigersnum, int wolvesnum, int rabbitsnum);
    ~Game();
    void update(int& key, int& day);
    int getWinH() const { return winH; }
    int getWinW() const { return winW; }
    Gui& getGui() { return gui; }
    std::vector<Grass*>& getGrasses() { return grasses; }
    std::list<Animal*>& getRabbits() { return rabbits; }
    std::list<Animal*>& getWolves() { return wolves; }

    void addRabbit(int x, int y, int Maxhunger );
    void addWolf(int x, int y, int Maxhunger, int Huntrange); 
    void addTiger(int x, int y, int Maxhunger, int Huntrange);
};
#endif