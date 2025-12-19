#include "Animal.h"

Animal::Animal(int x, int y, Game* game, int Maxhunger)
    : Entity(x, y, game), hunger(0), maxHunger(Maxhunger),isAlive(true) {};

