#include "Predator.h"

Predator::Predator(int x, int y, Game* game, int Maxhunger, int Huntrange):
Animal(x, y, game, Maxhunger)
{
    huntrange = Huntrange;
}