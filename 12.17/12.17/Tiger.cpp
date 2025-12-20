#include "Tiger.h"
#include "Game.h"
#include "Predator.h"
#include <cstdlib>


Tiger::Tiger(int x, int y, Game* game, int Maxhunger , int huntrange ):
Predator(x, y, game, Maxhunger, huntrange){};

void Tiger::update() {
    if(!alive()) return;
    
    int dx = rand() % getHuntRange();
    int dy = rand() % getHuntRange();
    while(dx == 0 || dy == 0){
        dx = rand() % 3;
        dy = rand() % 3;
    }
    int newX = getX() + dx;
    int newY = getY() + dy;
    int newX_not = getX() - dx;
    int newY_not = getY() - dy;
    int dice = rand() % 4;
    switch (dice)
    {
    case 0://x+,y+
        if( newX > 5 && newX< getGame()->getWinW()-1 && newY > 5 &&newY < getGame()->getWinH()-1 ) {
            setX(newX);
            setY(newY);
            } 
        break;
    case 1://x-,y-
        if( newX_not > 5 && newY_not > 5) {
            setX(newX_not);
            setY(newY_not);
            }  
        break;
    case 2://x-,y+
        if(newX_not > 5 && newY < getGame()->getWinH()-1 && newY > 5 ) {
            setX(newX_not);
            setY(newY);
            }
        break;
    case 3://x+,y-
        if( newX > 5 && newX< getGame()->getWinW()-3 && newY_not > 5 ) {
            setX(newX);
            setY(newY_not);
            }
        break;
    default:
        break;
    }

    for (list<Animal*>::iterator it = getGame()->getRabbits().begin(); it != getGame()->getRabbits().end(); ++it) {
            int abs1 = abs(getX() - (*it)->getX());
            int abs2 = abs(getY() - (*it)->getY());
        if (abs1 <= getHuntRange() && abs2 <= getHuntRange()){
            //getGame()->setMessageTiger("Tiger eat Rabbit.");
            eat();
            (*it) -> setAlive(false);
            setX( (*it)->getX() );
            setY( (*it)->getY() );
            break;
        }
    }
    if(getHunger() > 0 && rand()%3 > 1){
        for (list<Animal*>::iterator it = getGame()->getWolves().begin(); it != getGame()->getWolves().end(); ++it) {
                int abs1 = abs(getX() - (*it)->getX());
                int abs2 = abs(getY() - (*it)->getY());
            if (abs1 <= getHuntRange() && abs2 <= getHuntRange()){
                //getGame()->setMessageTiger("Tiger eat Wolf.");
                eat();
                (*it) -> setAlive(false);
                setX( (*it)->getX() );
                setY( (*it)->getY() );
                break;
            }
        }
    }
    // going hungry
    setHunger(getHunger() + 1);
    if (getHunger() >= getMaxHunger()) {
        eaten();
    }
}

void Tiger::eat(){
    setHunger(0);
}

void Tiger::draw() {
    if (alive()) {
        getGame()->getGui().drawSomething(getGame()->getGui().getWin(),getY(), getX(), 'T', 4);
    }
}