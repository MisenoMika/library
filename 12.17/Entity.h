#ifndef __ENTITY_H__
#define __ENTITY_H__
class Game;
class Entity {
    int x, y;
    Game* game;
public:
    Entity(int x, int y, Game* game):x(x), y(y), game(game) {}
    Entity(): x(0), y(0), game(nullptr){};
    Game* getGame() { return game; }
    int getX(){ return x; }
    int getY(){ return y; }
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    virtual ~Entity() = 0 ;
    virtual void update() = 0;
    virtual void draw() = 0;

};
#endif