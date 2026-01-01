#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

class Game;
class Explosion {
    int x, y;
    int frameCount;
    int maxFrames;
    bool isAlive;
    Game* game;
    
public:
    Explosion(int x, int y, Game* game);
    ~Explosion() {}
    
    void update();
    void draw();
    bool getAlive() const { return isAlive;}
};

#endif