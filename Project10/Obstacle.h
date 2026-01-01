#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__
#include <string>
using namespace std;
class Game;
class Obstacle{
protected:
    int x, y;
    int colorPair;
    string symbol;
    Game* game;
public: 
    Obstacle(int x, int y, Game* game, string sym = "#", int color = 0);
    ~Obstacle(){};
    void update();
    void draw();
    bool isObstacle(int checkX, int checkY); 

    int getX() const { return x; }
    int getY() const { return y; }
};

#endif