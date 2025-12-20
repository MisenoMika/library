#include "Wolf.h"
#include "Game.h"
#include <cstdlib>

Wolf::Wolf(int x, int y, Game* game, int Maxhunger , int huntrange ):
Predator(x, y, game, Maxhunger, huntrange){};

void Wolf::update() {
    if(!alive()) return;
    
    int dx = rand() % 3;
    int dy = rand() % 3;
    while(dx == 0 || dy == 0){
        dx = rand() % 3;
        dy = rand() % 3;
    }
    int newX = getX() + dx;
    int newY = getY() + dy;
    int dice = rand() % 4;
    switch (dice)
    {
    case 0:
        if( newX< getGame()->getWinW()-2 && newY < getGame()->getWinH()-2 ) {
            setX(getX() + dx);
            setY(getY() + dy);
            } 
        break;
    case 1:
        if( getX() > 5 && getY() > 5) {
            setX(getX() - dx);
            setY(getY() - dy);
            }  
        break;
    case 2:
        if(getX() > 5 && getY() < getGame()->getWinH()-5 ) {
            setX(getX() - dx);
            setY(getY() + dy);
            }
        break;
    case 3:
        if( newX< getGame()->getWinW()-5 && getY() > 5 ) {
            setX(getX() + dx);
            setY(getY() - dy);
            }
        break;
    default:
        break;
    }

    for (list<Animal*>::iterator it = getGame()->getRabbits().begin(); it != getGame()->getRabbits().end(); ++it) {
            int abs1 = abs(getX() - (*it)->getX());
            int abs2 = abs(getY() - (*it)->getY());
        if (abs1 <= getHuntRange() && abs2 <= getHuntRange()){
            eat();
            (*it) -> setAlive(false);
            setX( (*it)->getX() );
            setY( (*it)->getY() );
            break;
        }
    }

    // going hungry
    setHunger(getHunger() + 1);
    if (getHunger() >= getMaxHunger()) {
        eaten();
    }
}

void Wolf::eat(){
    setHunger(0);
}

void Wolf::draw() {
    if (alive()) {
        getGame()->getGui().drawSomething(getGame()->getGui().getWin(),getY(), getX(), 'W', 3);
    }
}