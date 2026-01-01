#include "GunBoat.h"
#include "Shell.h"
#include "Game.h"
#include "Obstacle.h"
#define X_morethanPlayer(x) (x > game->getPlayerShip()->getX())
#define Y_morethanPlayer(y) (y > game->getPlayerShip()->getY())

GunBoat::GunBoat(int x, int y, Game* game)
    : EnemyShip(x, y, game)
{
    health = 20;
    speed = 1;
    shellCount = 10;
    missileCount = 0;
    symbol = "o";
    reloadTime = 0;
    delayTime = 0;
    dx = 0;
    dy = 0;
}

void GunBoat::update(){
    int dice = rand()%3;
    if(dice == 0)move();
    if(x==game->getPlayerShip()->getX()){
        if(Y_morethanPlayer(y)){
            attack(0, -1);
        }
        else {
            attack(0, 1);
        }
    }
    else if(y==game->getPlayerShip()->getY()){
        if(X_morethanPlayer(x)){
            attack(-1, 0);
        }
        else {
            attack(1, 0);
        }
    }
    draw();
}

void GunBoat::onDeath(){
    game->getPlayerShip()->addcoins(10);
}


void GunBoat::attack(int dirX, int dirY){
    if(shellCount > 0 && reloadTime <= 0){
        Shell* shell = new Shell(x-1, y, game, dirX, dirY, 1);
        game->getWeapons().push_back(shell);
        shellCount--;
        reloadTime = 10;
    }
    else if(reloadTime > 0){
        reloadTime--;
    }
}

void GunBoat::move(){
    int newx = x;
    int newy = y;
    if(X_morethanPlayer(x)){
        dx = -1;
    }
    else{
        dx = 1;
    }
    if(Y_morethanPlayer(y)){
        dy = -1;
    }
    else{
        dy = 1;
    }

    if(x == game->getWinW()-1){
        dx = -1;
    }
    else if(x == 5){
        dx = 1;
    }
    if(y == game->getWinH()-1){
        dy = -1;
    }
    else if(y == 5){
        dy = 1;
    }
    bool DistanceX = abs(x - game->getPlayerShip()->getX()) >= abs(y - game->getPlayerShip()->getY());
    if(DistanceX){
        newx += dx * speed;
    }
    else{
        newy += dy * speed;
    }
    if(! game->isObstacle(newx, newy)){
        x = newx;
        y = newy;
    }
    else {
        int newdx = dx;
        int newdy = dy;
        while( game->isObstacle(newx, newy) ) {
            int choice = rand()%2;
            if( choice == 0 ) {
                newdx = -dx;
                newdy = dy;
            }
            else {
                newdx = dx;
                newdy = -dy;
            }
            newx = x + newdx * speed;
            newy = y + newdy * speed;
        }
        x = newx;
        y = newy;
    }
}

void GunBoat::draw(){
    game->getGui().drawSomething(game->getGui().getWin(), y, x, symbol, 2);
}