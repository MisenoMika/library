#include "Explosion.h"
#include "Game.h"

Explosion::Explosion(int x, int y, Game* game)
    : x(x), y(y), game(game), frameCount(0), maxFrames(8)
{
    isAlive = true;
}

void Explosion::update(){
    frameCount++;
    if(frameCount >= maxFrames) {
        isAlive = false;
    }
}

void Explosion::draw(){
    if(frameCount < maxFrames/2) {
        game->getGui().drawSomething(game->getGui().getWin(), y, x, "*", 1);
    }
    else{
        game->getGui().drawSomething(game->getGui().getWin(), y, x-1, "*", 1);
        game->getGui().drawSomething(game->getGui().getWin(), y, x+1, "*", 1);
        game->getGui().drawSomething(game->getGui().getWin(), y-1, x, "*", 1);
        game->getGui().drawSomething(game->getGui().getWin(), y+1, x, "*", 1);
    }

}