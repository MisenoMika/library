#include "Torpedo.h"
#include "Game.h"
#include "Weapon.h"
#include "EnemyShip.h"
#include "PlayerShip.h"
Torpedo::Torpedo(int x, int y, Game* game, int destinationY)
    : Weapon(x, y, game) 
{
    speed = 1;
    damage = 50;
    dx = 1;
    dy = 1;
    symbol = "{O}";
    destY = destinationY;
    moveCount = 0;
    duration = 0;
    target = nullptr;
    playerTarget = nullptr;
}

void Torpedo::move(){
    int newx = x;
    int newy = y;
    if(y == destY){
        if(x == game->getWinW()-2){
            dx = -1;
        }
        else if(x == 5){
            dx = 1;
        }
        if(moveCount % 2 == 0){
            newx += dx*speed;
        }
        moveCount++;
    }
    else{
        if(destY < y){
            newy -= speed;
        }
        else{
        newy += speed;
        }
    }
    if(game->isObstacle(newx, newy)) {
        isAlive = false;
        return;
    }
    else {
        x = newx;
        y = newy;
    }
}

void Torpedo::update(){
    duration++;
    move();

    int px = game->getPlayerShip()->getX();
    int py = game->getPlayerShip()->getY();
        
    bool hitX = (x >= px - 1 && x <= px + 1);
    bool hitY = (y >= py - 1 && y <= py + 1);
        
    if(hitX && hitY){
        playerTarget= game->getPlayerShip();
        onHit();
    }

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
    if(duration > 200){
        isAlive = false;
    }
}

void Torpedo::onHit(){
    if(target != nullptr){
        target->hitted(damage);
    }
    if(playerTarget != nullptr){
        playerTarget->hitted(damage);
    }
    isAlive = false;
}

void Torpedo::draw(){
    game->getGui().drawSomething(game->getGui().getWin(), y, x, symbol.c_str(), 3);
}