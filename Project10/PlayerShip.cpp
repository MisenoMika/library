#include "PlayerShip.h"
#include "Weapon.h"
#include "Game.h"
#include "Shell.h"
#include "Missile.h"
#include "Obstacle.h"
#include <cmath>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
PlayerShip::PlayerShip(int x, int y, Game* game)
    : x(x), y(y), dx(0), dy(0), speed(2), health(1000), maxHealth(1000),coins(0), maxCoins(500),lastdirection(LEFT), 
    burstCount(0), burstdirX(0), burstLeft(0),reloadTime(239), delayTime(60), level(0),
    shellCount(100), missileCount(5), isAlive(1), game(game),
    symbol1(">"), symbol2("="), symbol3("<") {}

void PlayerShip::move(int& key) {
    int newx = x;
    int newy = y;
    switch(key) {
        case 'w':
            dy = -1;
            dx = 0;
            symbol1 = "^";
            symbol2 = "|";
            symbol3 = "V";
            lastdirection = UP;
            break;
        case 's':
            dy = 1;
            dx = 0;
            symbol1 = "^";
            symbol2 = "|";
            symbol3 = "V";
            lastdirection = DOWN;
            break;
        case 'a':
            dx = -1;
            dy = 0;
            symbol1 = ">";
            symbol2 = "=";
            symbol3 = "<";
            lastdirection = LEFT;
            break;
        case 'd':
            dx = 1;
            dy = 0;
            symbol1 = ">";
            symbol2 = "=";
            symbol3 = "<";
            lastdirection = RIGHT;
            break;
        default:
            dx = 0;
            dy = 0;
            break;
    }
    int stepX = dx;
    int stepY = dy;

    for(int i = 0; i < speed; i++) {
        int newx = x + stepX;
        int newy = y + stepY;

        if (newx < 6) newx = 6;
        if (newx > game->getWinW() - 2) newx = game->getWinW() - 2;
        if (newy < 5) newy = 5;
        if (newy > game->getWinH() - 1) newy = game->getWinH() - 1;

        bool canMove = false;
        switch(lastdirection) {
            case UP:
                canMove = !game->isObstacle(newx, newy);
                break;
            case DOWN:
                canMove = !game->isObstacle(newx, newy);
                break;
            case LEFT:
                canMove = !game->isObstacle(newx-2, newy) && 
                          !game->isObstacle(newx-1, newy) && 
                          !game->isObstacle(newx, newy);
                break;
            case RIGHT:
                canMove = !game->isObstacle(newx+2, newy) && 
                          !game->isObstacle(newx+1, newy) && 
                          !game->isObstacle(newx, newy);
                break;
        }
        
        if(canMove) {
            x = newx;
            y = newy;
        } 
        else {
            break;  
        }
    }

}

void PlayerShip::attack(int& key) {
    // Implementation of attack logic
    switch(key){
        case KEY_DOWN:
            if(shellCount <= 0){
                //mvwprintw(game->getGui().getWin(),game->getWinH() + 2, 2, "Out of shells!");
                break;
            }
            else if(shellCount > 0){
                // Fire shell
                int directx = 0;
                int directy = 0;
                int directx2 = 0;
                int directy2 = 0;
                int directx3 = 0;
                int directy3 = 0;
                int newx = 0;
                int newy = 0;
                switch (lastdirection)
                {
                case UP:
                    directx = 0;
                    directy = directy2 = directy3 = -1;
                    directx2 = -1;
                    directx3 = 1;
                    newx = x;
                    newy = y-1;
                    break;
                case DOWN:
                    directx = 0;
                    directy = directy2 = directy3 = 1;
                    directx2 = -1;
                    directx3 = 1;
                    newx = x;
                    newy = y+1;
                    break;
                case LEFT:
                    directx = directx2 = directx3 = -1;
                    directy = 0;
                    directy2 = -1;
                    directy3 = 1;
                    newx = x-2;
                    newy = y;
                    break;
                case RIGHT:
                    directx = directx2 = directx3 = 1;
                    directy = 0;
                    directy2 = -1;
                    directy3 = 1;
                    newx = x+2;
                    newy = y;
                    break;
                default:
                    break;
                }
                Shell* shell = new Shell(newx, newy, game, directx, directy, 2);
                game->getWeapons().push_back(shell);
                shellCount--;
                if(level >= 4){
                    Shell* shell_2 = new Shell(newx, newy, game, directx2, directy2, 2);
                    game->getWeapons().push_back(shell_2);
                    Shell* shell_3 = new Shell(newx, newy, game, directx3, directy3, 2);
                    game->getWeapons().push_back(shell_3);
                    shellCount--;
                }
                
            }
            break;

        case KEY_UP:
            if(missileCount <= 0){
                break;
            }
            else if(missileCount > 0){
                int newx = 0;
                int newy = 0;
                switch (lastdirection)
                {
                case UP:
                    newx = x;
                    newy = y-1;
                    break;
                case DOWN:
                    newx = x;
                    newy = y+1;
                    break;
                case LEFT:
                    newx = x-2;
                    newy = y;
                    break;
                case RIGHT:
                    newx = x+2;
                    newy = y;
                    break;
                default:
                    break;
                }
                Missile* missile = new Missile(newx, newy, game, 2);
                game->getWeapons().push_back(missile);
                missileCount--;
            }
            break;

        case KEY_LEFT:
            if(shellCount <= 0){
                break;
            }
            else if(shellCount > 0){
                burstCount = 2;
                burstLeft = (level <= 4)? 1 + level / 2 : 3;
                switch (lastdirection)
                {
                case LEFT:
                    burstdirX = 0;
                    burstdirY = 1;
                    break;
                case RIGHT:
                    burstdirX = 0;
                    burstdirY = -1;
                    break;
                case UP:
                    burstdirX = -1;
                    burstdirY = 0;
                    break;
                case DOWN:
                    burstdirX = 1;
                    burstdirY = 0;
                    break;
                default:
                    break;
                }
            }
            break;
        
        case KEY_RIGHT:
            if(shellCount <= 0){
                break;
            }
            else if(shellCount > 0){
                burstCount = 2;
                burstLeft = (level <= 4)? 1 + level / 2 : 3;
                switch (lastdirection)
                {
                case LEFT:
                    burstdirX = 0;
                    burstdirY = -1;
                    break;
                case RIGHT:
                    burstdirX = 0;
                    burstdirY = 1;
                    break;
                case UP:
                    burstdirX = 1;
                    burstdirY = 0;
                    break;
                case DOWN:
                    burstdirX = -1;
                    burstdirY = 0;
                    break;
                default:
                    break;
                }
            
            }
            break;
        default:
            break;
    }


    if(burstLeft > 0 && shellCount > 2) {
        burstCount--;
        if(burstCount <= 0) {
            int newx, newy;
            switch (burstdirY)
            {
            case 1://本来写的是y-1/y+1,但是似乎不加这个效果更好
                newy = y;
                break;
            case 0:
                newy = y;
                break;
            case -1:
                newy = y; 
                break;
            default:
                break;
            }
            switch (burstdirX)
            {
            case 1:
                newx = x;
                break;
            case 0:
                newx = x;
                break;
            case -1:
                newx = x;
                break;
            default:
                break;
            }
            game->getWeapons().push_back(new Shell(newx, newy, game, burstdirX, burstdirY, 2));
            game->getWeapons().push_back(new Shell(newx-abs(burstdirY), newy-abs(burstdirX), game, burstdirX, burstdirY, 2));
            game->getWeapons().push_back(new Shell(newx+abs(burstdirY), newy+abs(burstdirX), game, burstdirX, burstdirY, 2));

            int frequency = (level<5)? 6-level : 1;
            int dice = rand()%(frequency);
            if(level >= 2 && dice == 0){
                int directx2 = 0;
                int directy2 = 0;
                int directx3 = 0;
                int directy3 = 0;
                if(burstdirX == 0){
                    directx2 = -1;
                    directx3 = 1;;
                    directy2 = directy3 = burstdirY;
                }
                else if(burstdirY == 0){
                    directy2 = -1;
                    directy3 = 1;
                    directx2 = directx3 = burstdirX;
                }
                game->getWeapons().push_back(new Shell(newx, newy, game, directx2, directy2, 2));
                game->getWeapons().push_back(new Shell(newx, newy, game, directx3, directy3, 2));
            }
            shellCount-=3;
            burstLeft--;
            burstCount = 2;  // 间隔2帧
        }
    }
    else if(burstLeft > 0 && shellCount <= 2){
        while(shellCount>0 && burstLeft > 0){
            game->getWeapons().push_back(new Shell(x, y, game, burstdirX, burstdirY, 2));
            shellCount--;
            burstLeft--;
        }
    }

}

void PlayerShip::hitted(int damage){
    health -= damage;
    if(health <= 0){
        isAlive = 0;
    }
}

void PlayerShip::levelUp(){
    if(abs(maxHealth - health) <= 200){
        health = maxHealth;
    }
    else {
        health += 200;
    }
    if(level%2 == 0)maxHealth += 200;
    shellCount += 50;
    missileCount += 10;
    game->setLevel(game->getLevel() + 1);
    level++;
}

void PlayerShip::update(int& key) {
    move(key);
    attack(key);
        
    if(coins >= maxCoins){
        levelUp();
        coins -= maxCoins;
    }
    if(reloadTime > 0){
        reloadTime--;
    }
    else if(reloadTime <= 0){
        reloadTime = 240;
        shellCount += 20;
        missileCount += 1;
        delayTime = 0;
    }
    if(health <= 0){
        isAlive = 0;
    }
}


void PlayerShip::draw(){
    if(lastdirection == RIGHT || lastdirection == LEFT){
        game->getGui().drawSomething(game->getGui().getWin(), y, x+1, symbol1.c_str(), 1);
        game->getGui().drawSomething(game->getGui().getWin(), y, x, symbol2.c_str(), 1);
        game->getGui().drawSomething(game->getGui().getWin(), y, x-1, symbol3.c_str(), 1);
    }
    else if(lastdirection == UP || lastdirection == DOWN){
        game->getGui().drawSomething(game->getGui().getWin(), y-1, x, symbol1.c_str(), 1);
        game->getGui().drawSomething(game->getGui().getWin(), y, x, symbol2.c_str(), 1);
        game->getGui().drawSomething(game->getGui().getWin(), y+1, x, symbol3.c_str(), 1);
    }

    if(delayTime <= 20){
        game->getGui().drawSomething(game->getGui().getWin(), 20, LENGTH-18, "Weapons reloaded!", 0);
        delayTime++;
    }
    
}