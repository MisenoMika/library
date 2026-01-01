#include "Obstacle.h"
#include "Game.h"

Obstacle::Obstacle(int x, int y, Game* game, string sym, int color)
    : x(x), y(y), game(game)
{
    symbol = sym;
    colorPair = color;
}

bool Obstacle::isObstacle(int checkX, int checkY) {
        return (checkX == x && checkY == y);
}

void Obstacle::update() {
    draw();
}

void Obstacle::draw() {
    game->getGui().drawSomething(game->getGui().getWin(), y, x, symbol.c_str(), colorPair);
}