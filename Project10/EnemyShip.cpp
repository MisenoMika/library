#include "EnemyShip.h"
#include "Game.h"

EnemyShip::EnemyShip(int x, int y, Game* game)
    : x(x), y(y), game(game), isAlive(true) {}

void EnemyShip::hitted(int damage){
    health -= damage;
    if(health <= 0){
        onDeath(); 
        game->getExplosions().push_back( new Explosion(x, y, game) );
        isAlive = false; 
    }
}