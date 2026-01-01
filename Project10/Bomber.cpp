#include"Bomber.h"
#include"Game.h"
#include "Torpedo.h"
#include "Shell.h"
Bomber::Bomber(int x, int y, Game* game)
    : EnemyShip(x, y, game)
{
    moveCount = 0;
    health = 99999;
    speed = 1;
    shellCount = 18;
    missileCount = 0;
    symbol = "<==";
    symbol1 = "\\\\";
    symbol2 = "//";
    symbol3 = "==>";
    dy = 0;
    int dice = rand()%2;
    if(dice == 0){
        dx = -1;
    }
    else{
        dx = 1;
    }
    reloadTime = 0;
}

void Bomber::update(){
    move();
    if(reloadTime <= 0){
        attackTorpedo();
        reloadTime = 175;
    }
    else {
        reloadTime--;
    }
    if(reloadTime % 20 == 0 && shellCount >=0){
        attack(0, 0);
    }
    draw();
}

void Bomber::attack(int dirX, int dirY){
    Shell* shell = new Shell(x, y+1, game, 1, 1, 1);
    game->getWeapons().push_back(shell);
    Shell* shell2 = new Shell(x, y+1, game, 0, 1, 1);
    game->getWeapons().push_back(shell2);
    Shell* shell3 = new Shell(x, y+1, game, -1, 1, 1);
    game->getWeapons().push_back(shell3);
    shellCount -= 3;
}

void Bomber::attackTorpedo(){
    int destY = rand() % (game->getWinH()-5) + 5;
    Torpedo* torpedo = new Torpedo(x, y+1, game, destY);
    game->getWeapons().push_back(torpedo);
}


void Bomber::move(){
    if(x == game->getWinW()-2){
        dx = -1;
    }
    else if(x == 5){
        dx = 1;
    }
    if(moveCount % 2 == 0){
        x += dx*speed;
    }
    moveCount++;
}

void Bomber::draw(){
    if(dx == 1){
        game->getGui().drawSomething(game->getGui().getWin(), y-1, x, symbol1.c_str(), 5);
        game->getGui().drawSomething(game->getGui().getWin(), y, x, symbol3.c_str(), 5);
        game->getGui().drawSomething(game->getGui().getWin(), y+1, x, symbol2.c_str(), 5);
    }
    else if(dx == -1){
        game->getGui().drawSomething(game->getGui().getWin(), y-1, x+1, symbol2.c_str(), 5);
        game->getGui().drawSomething(game->getGui().getWin(), y, x, symbol.c_str(), 5);
        game->getGui().drawSomething(game->getGui().getWin(), y+1, x+1, symbol1.c_str(), 5);
    }
}