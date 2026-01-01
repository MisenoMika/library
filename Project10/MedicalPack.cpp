#include "MedicalPack.h"
#include "Game.h"
#include <cmath>
MedicalPack::MedicalPack(int x, int y, Game* game)
    : Item(x, y, game)
{
    symbol = "[+]";
    pickRange = 2;
}

void MedicalPack::update(){
    PlayerShip* player = game->getPlayerShip();
    int distX = player->getX() - x;
    int distY = player->getY() - y;
    int distance = sqrt(distX * distX + distY * distY);
    if(distance <= pickRange){
        onPick();
    }
} 

void MedicalPack::onPick(){
    PlayerShip* player = game->getPlayerShip();
    player->addHealth(100);   
    setAlive(false); 
}

void MedicalPack::draw(){
    game->getGui().drawSomething(game->getGui().getWin(), y, x, symbol.c_str(), 6);
}