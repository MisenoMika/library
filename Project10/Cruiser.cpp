#include "Cruiser.h"
#include "Shell.h"
#include "Game.h"
#include "Missile.h"

Cruiser::Cruiser(int x, int y, Game* game)
    : EnemyShip(x, y, game)
{
    health = 90;
    speed = 1;
    shellCount = 200;
    missileCount = 2;
    symbol = "[]";
    symbol1 = "/\\";
    symbol2 = "\\/";
    symbol3 = "<";
    symbol4 = ">";
    reloadTime = 0;
    delayTime = 0;
    delayTime_2 = 0;
}

void Cruiser::update(){
    delayTime++;
    if(delayTime == 10){
        move();
        delayTime = 0;
    }
    attack(0, 0);
    if(delayTime_2 == 150){
        attackMissile();
        delayTime_2 = 0;
    }
    else {
        delayTime_2++;
    }
    draw();
}

void Cruiser::onDeath(){
    game->getPlayerShip()->addcoins(50);
}

void Cruiser::move(){
    int newx = 0;
    int newy = 0;
    int dice = rand()%2;
    if(x< game->getWinW()/2 - 10){
        dice = 0;
    }
    else if(x > game->getWinW()/2 + 10){
        dice = 1;
    }
    switch (dice)
    {
    case 0:
        newx = x+speed;
        newy = y;
        break;
    case 1:
        newx = x-speed;
        newy = y;
        break;
    default:
        break;
    }
    if (newx < 6) newx = 6;
    if (newx > game->getWinW() - 2) newx = game->getWinW() - 2;
    if (newy < 6) newy = 6;
    if (newy > game->getWinH() - 2) newy = game->getWinH() - 2;
    if(!game->isObstacle(newx+2, newy)){
        x = newx;
        y = newy;
    }
    else{
        x -= speed;
    }

}

void Cruiser::attack(int dirX, int dirY){
    if(shellCount > 0 && reloadTime <= 0){
        Shell* shell_1 = new Shell(x, y, game, 1, 0, 1);
        game->getWeapons().push_back(shell_1);
        Shell* shell_2 = new Shell(x, y, game, -1, 0, 1);
        game->getWeapons().push_back(shell_2);
        Shell* shell_3 = new Shell(x, y, game, 0, 1, 1);
        game->getWeapons().push_back(shell_3);
        Shell* shell_4 = new Shell(x, y, game, 0, -1, 1);
        game->getWeapons().push_back(shell_4);
        shellCount-=4;
        reloadTime = 8;
    }
    else if(reloadTime > 0){
        reloadTime--;
    }
}

void Cruiser::attackMissile(){
    if(missileCount > 0){
        Missile* missile = new Missile(x, y, game, 1);
        game->getWeapons().push_back(missile);
        missileCount--;
    }
}

void Cruiser::draw(){
    game->getGui().drawSomething(game->getGui().getWin(), y-1, x, symbol1.c_str(), 4);
    game->getGui().drawSomething(game->getGui().getWin(), y+1, x, symbol2.c_str(), 4);
    game->getGui().drawSomething(game->getGui().getWin(), y, x, symbol.c_str(), 4);
    game->getGui().drawSomething(game->getGui().getWin(), y, x-1, symbol3.c_str(), 4);
    game->getGui().drawSomething(game->getGui().getWin(), y, x+2, symbol4.c_str(), 4);
}
