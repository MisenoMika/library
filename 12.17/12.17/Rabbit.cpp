#include "Rabbit.h"
#include "Game.h"
#include <cstdlib>
Rabbit::Rabbit(int x, int y, Game* game ,int Maxhunger ): Animal(x, y, game, Maxhunger){};

void Rabbit::update() {
    if(!alive()) return;
    
    int dx = rand() % 2;
    int dy = rand() % 2;
    while(dx == 0 || dy == 0){
        dx = rand() % 2;
        dy = rand() % 2;
    }
    int newX = getX() + dx;
    int newY = getY() + dy;
    int dice = rand() % 4;
    switch (dice)
    {
    case 0:
        if( newX< getGame()->getWinW()-1 && newY < getGame()->getWinH()-1 ) {
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
        if(getX() > 5 && getY() < getGame()->getWinH()-1 ) {
            setX(getX() - dx);
            setY(getY() + dy);
            }
        break;
    case 3:
        if( newX< getGame()->getWinW()-1 && getY() > 5 ) {
            setX(getX() + dx);
            setY(getY() - dy);
            }
        break;
    default:
        break;
    }
    // 吃草
    for (vector<Grass*>::iterator it = getGame()->getGrasses().begin(); it != getGame()->getGrasses().end(); ++it) {
        if( (*it)->getProgress() < 3 ) continue;

        int abs1 = abs(getX() - (*it)->getX());
        int abs2 = abs(getY() - (*it)->getY());
        if (abs1 + abs2 == 0){//记得改回去
            eat();
            (*it) -> setProgress(0);
            break;
        }
    }

    // going hungry
    setHunger(getHunger() + 1);
    if (getHunger() >= getMaxHunger()) {
        eaten();
    }
}

void Rabbit::eat() {   
    setHunger(0);
}

void Rabbit::draw() {
    if (alive()) {
        getGame()->getGui().drawSomething(getGame()->getGui().getWin(),getY(), getX(), 'R', 2);
    }
}