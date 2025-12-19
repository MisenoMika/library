#include "Grass.h"
#include "Game.h"

Grass::Grass(int x, int y, Game* game):Entity(x, y, game)
{
    progress = 0;
    growCounter = 0;
}
void Grass::update()
{   
    growCounter++;
    if (growCounter >= 1 && progress < 3) {
        progress++;
        growCounter = 0; 
    }
}
    


void Grass::draw(){
    char graph;
    switch(progress){
        case 0:
            graph = ' ';
            break;
        case 1:
            graph = '.';
            break;
        case 2:
            graph = ':';
            break;
        case 3:
            graph = '*';
            break;
    }
    getGame()->getGui().drawSomething(getGame()->getGui().getWin(),getY(), getX(), graph, 1);
}