#include "Shell.h"
#include "Weapon.h"
#include "Game.h"
#include "EnemyShip.h"
Shell::Shell(int x, int y, Game* game, int Dx, int Dy, int AI)
    : Weapon(x, y, game) , ai(AI)
{
    symbol = '*';
    damage = 5;
    speed = 2;
    dx = Dx;
    dy = Dy;
    target = nullptr;
}

void Shell::move(){
    int newx = x;
    int newy = y;
    for(int i = 0; i < speed; i++) {
        newx += dx;
        newy += dy;
        if(game->isObstacle(newx, newy)) {
            isAlive = false;
            return;
        }
        else {
            x = newx;
            y = newy;
        }
    }
    if (x < 4) {
        x = 4;
        isAlive = false;
    }
    if (x > game->getWinW()-1) {
        x = game->getWinW()-1;
        isAlive = false;
    }
    if (y < 4) {
        y = 4;
        isAlive = false;
    }
    if (y > game->getWinH() - 1){ 
        y = game->getWinH() - 1;
        isAlive = false;
    }
}

void Shell::update(){
    move();

    if(ai == 1){
        int px = game->getPlayerShip()->getX();
        int py = game->getPlayerShip()->getY();
        
        bool hitX = (x >= px - 1 && x <= px + 1);
        bool hitY = (y >= py - 1 && y <= py + 1);
        
        if(hitX && hitY){
            onHit();
        }
    }
    else if(ai == 2){
        std::list<EnemyShip*>::iterator it;
        for(it= game->getEnemies().begin(); it!= game->getEnemies().end(); ++it){
            if( (*it)->getAlive() == false ) {
                continue;
            }
            int ex = (*it)->getX();
            int ey = (*it)->getY();

            bool hitX = (x >= ex - 1 && x <= ex + 1);
            bool hitY = (y >= ey - 1 && y <= ey + 1);
            if(hitX && hitY){
                target = (*it);
                onHit();
                break;
            }
        }
    }   

}

void Shell::draw(){
    if(ai==1)game->getGui().drawSomething(game->getGui().getWin(), y, x, symbol.c_str(), 0);
    else if(ai==2)game->getGui().drawSomething(game->getGui().getWin(), y, x, symbol.c_str(), 2);
}

void Shell::onHit(){
    isAlive = false;
    if(ai == 1){
        game->getPlayerShip()->hitted(damage);
    }
    else if(ai == 2 && target != nullptr){
        target->hitted(damage);
    }
}