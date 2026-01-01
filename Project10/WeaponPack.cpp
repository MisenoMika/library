#include "WeaponPack.h"
#include "Game.h"
#include <cmath>
WeaponPack::WeaponPack(int x, int y, Game* game)
    : Item(x, y, game)
{
    symbol = "[W]";
    pickRange = 2;
}

void WeaponPack::update(){
    PlayerShip* player = game->getPlayerShip();
    int distX = player->getX() - x;
    int distY = player->getY() - y;
    int distance = sqrt(distX * distX + distY * distY);
    if(distance <= pickRange){
        onPick();
    }
} 

void WeaponPack::onPick(){
    PlayerShip* player = game->getPlayerShip();
    player->addShells(50);   
    player->addMissiles(10); 
    setAlive(false); 
}

void WeaponPack::draw(){
    game->getGui().drawSomething(game->getGui().getWin(), y, x, symbol.c_str(), 6);
}