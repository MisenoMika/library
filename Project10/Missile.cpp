#include "Missile.h"
#include "Weapon.h"
#include "EnemyShip.h"
#include "Game.h"
#include "Bomber.h"
#include <cmath>
Missile::Missile(int x, int y, Game* game, int AI)
    :Weapon(x, y, game) 
{
    ai = AI;
    damage = 20;
    speed = 1;
    symbol = "=>";
    moveCount = 1;
    target = nullptr;
    maxCount = 3;
    flyTime = 0;
    maxFlyTime = 140;
    delayTime = 0;//Not used currently
    dx = 0;
    dy = 0;
}

Missile::~Missile(){}
void Missile::move(){
    if(ai == 1){
        int targetX = game->getPlayerShip()->getX();
        int targetY = game->getPlayerShip()->getY();
        int newx = x;
        int newy = y;
        int oldDx = dx;
        int oldDy = dy;
        if(targetX > x) {
            dx = 1;
            symbol = "=>";
        } 
        else if (targetX < x) {
            dx = -1;
            symbol = "<=";
        }
        else {
            dx = 0;
        }
        
        if(targetY > y) {
            dy = 1;
        } 
        else if (targetY < y) {
            dy = -1;
        }
        else {
            dy = 0;
        }

        if(rand() % 100 < (85 - 5*game->getLevel()) && (oldDx != 0 || oldDy != 0)) {
            dx = oldDx;
            dy = oldDy;
        }
        //delayTime = 8 + (rand() % 5);

        newx += dx * speed;
        newy += dy * speed;
        if(game->isObstacle(newx, newy)) {
            isAlive = false;
            return;
        }
        else {
            x = newx;
            y = newy;
        }
        //delayTime--;
    }
    else if(ai == 2){
        int newx = x;
        int newy = y;
        std::list<EnemyShip*>::iterator it;
        float tempDistance = 99999;
        int targetX = 0;
        int targetY = 0;
        for(it= game->getEnemies().begin(); it!= game->getEnemies().end(); ++it){
            EnemyShip* temptarget = *it;
            if( temptarget == nullptr || temptarget->getAlive() == false ) {
                continue;
            }
            if(dynamic_cast<Bomber*>(temptarget) == nullptr) {
                int distance_x = temptarget->getX();
                int distance_y = temptarget->getY();
                float distance = sqrt( (distance_x - x)*(distance_x - x) + (distance_y - y)*(distance_y - y) );
                if(distance < tempDistance){
                    tempDistance = distance;
                    targetX = distance_x;
                    targetY = distance_y;
                    target = temptarget;
                }
            }
        }
        if(target != nullptr){
                if(targetX > x) {
                    newx += speed;
                    symbol = "=>";
                } 
                else if (targetX < x) {
                    newx -= speed;
                    symbol = "<=";
                }
                if(targetY > y) {
                    newy += speed;
                } 
                else if (targetY < y) {
                    newy -= speed;
                }
            }
        else {
            newx += speed;
            symbol = "=>";
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
    if (x < 5 || x >= game->getWinW() || y < 5 || y >= game->getWinH()) {
        isAlive = false;
    }
}

void Missile::update(){
    flyTime++;
    if(moveCount == maxCount){
        move();
        moveCount = 0;
        if(maxCount>0 && (flyTime%3) == 0)maxCount--;
    }
    else {
        moveCount++;
    }

    if(ai == 1){
        int px = game->getPlayerShip()->getX();
        int py = game->getPlayerShip()->getY();
        
        bool hitX = (x >= px - 1 && x <= px + 1);
        bool hitY = (y >= py - 1 && y <= py + 1);
        
        if(hitX && hitY){
            onHit();
        }
    }
    else if(ai == 2 && target != nullptr){
        int ex = target->getX();
        int ey = target->getY();

        bool hitX = (x >= ex - 1 && x <= ex + 1);
        bool hitY = (y >= ey - 1 && y <= ey + 1);
        if(hitX && hitY){
            onHit();
        }
    }
    if(flyTime >= maxFlyTime){
        isAlive = false;
    }
}

void Missile::draw(){
    if(ai == 2)game->getGui().drawSomething(game->getGui().getWin(), y, x, symbol.c_str(), 2);
    else if(ai == 1)game->getGui().drawSomething(game->getGui().getWin(), y, x, symbol.c_str(), 4);
}

void Missile::onHit(){
    isAlive = false;
    if(ai == 1)game->getPlayerShip()->hitted(damage);
    else if(target != nullptr && ai == 2)target->hitted(damage);
}