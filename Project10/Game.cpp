#include "Game.h"
#include "PlayerShip.h"
#include "EnemyShip.h"
#include "Bomber.h"
#include "Destroyer.h"
#include "GunBoat.h"
#include "Cruiser.h"
#include "Weapon.h"
#include "Shell.h"
#include "Missile.h"
#include "Item.h"
#include "MedicalPack.h"
#include "WeaponPack.h"
#include "Explosion.h"
#include "Obstacle.h"
#include <fstream>

Game::Game(string mapfilePath){
    winH = HEIGHT;//留4行给Bomber
    winW = LENGTH-20;//这些是游戏需要的主要战场尺寸
    running = true;
    playership = new PlayerShip(winW/2, winH/2, this);
    Gui::drawBorder(gui.getWin());  // 先画边框
    playership->draw();
    wrefresh(gui.getWin());  // 刷新屏幕，立即显示
    level = 0;
    lastlevel = 0;
    delaytime = 0;
    BomberCount = 0;
    GunBoatCount = 0;
    DestroyerCount = 0;
    CruiserCount = 0;
    MedicalPackCount = 0;
    WeaponPackCount = 0;
    maxGunBoatCount = level + 2;
    maxBomberCount = (level+1)/3 + 1;
    maxDestroyerCount = level + 1;
    maxCruiserCount = (level/2) + 1;
    maxMedicalPackCount = 2+(level/3);
    maxWeaponPackCount = 2+(level/3);
    delaytime_2 = 0;
    mapfile = mapfilePath;
    if(!mapfile.empty()){
        loadMap(mapfile);
    }
}   

Game::~Game(){
    for(list<Weapon*>::iterator it = weapons.begin(); it != weapons.end(); ++it){
        delete (*it);
    }
    for(list<EnemyShip*>::iterator it = enemies.begin(); it != enemies.end(); ++it){
        delete (*it);
    }
    for(list<Explosion*>::iterator it = explosions.begin(); it != explosions.end(); ++it){
        delete (*it);
    }
    for(list<Item*>::iterator it = items.begin(); it != items.end(); ++it){
        delete (*it);
    }
    delete playership;
}


void Game::addGunBoat(){
    int dice = rand()%3;
    if(dice == 0){
        int x = rand() % (winW - 20) + 20;
        int y = winH - 1 - rand()%2;
        GunBoat* gunboat = new GunBoat(x, y, this);
        enemies.push_back(gunboat);
    }
    else if(dice == 1){
        int x = rand()%3 + 5;
        int y = rand() % (winH - 10) + 5;
        GunBoat* gunboat = new GunBoat(x, y, this);
        enemies.push_back(gunboat);
    }
    else if(dice == 2){
        int x = winW - 2 - rand()%2;;
        int y = rand() % (winH - 10) + 5;
        GunBoat* gunboat = new GunBoat(x, y, this);
        enemies.push_back(gunboat);
    }
}

void Game::addBomber(){
    int x = rand() % (winW - 10) + 5;
    int y = 1+rand()%2;
    Bomber* bomber = new Bomber(x, y, this);
    enemies.push_back(bomber);
}

void Game::addDestroyer(){
    int dice = rand()%3;
    if(dice == 0){
        int x = rand() % (winW - 20) + 20;
        int y = winH - 1 - rand()%2;
        Destroyer* destroyer = new Destroyer(x, y, this);
        enemies.push_back(destroyer);
    }
    else if(dice == 1){
        int x = rand()%3 + 5;
        int y = rand() % (winH - 10) + 5;
        Destroyer* destroyer = new Destroyer(x, y, this);
        enemies.push_back(destroyer);
    }
    else if(dice == 2){
        int x = winW - 2 - rand()%2;;
        int y = rand() % (winH - 10) + 5;
        Destroyer* destroyer = new Destroyer(x, y, this);
        enemies.push_back(destroyer);
    }
}
void Game::addCruiser(){
    int dice = rand()%2;
    if(dice == 0){
        int x = rand()%3 + 5;
        int y = 7+rand() % (winH - 10);
        Cruiser* cruiser = new Cruiser(x, y, this);
        enemies.push_back(cruiser);
    }
    else if(dice == 1){
        int x = winW - 2 - rand()%2;;
        int y = 7+rand() % (winH - 10);
        Cruiser* cruiser = new Cruiser(x, y, this);
        enemies.push_back(cruiser);
    }
}

void Game::addObstacle(int x, int y, int selection, string sym, int color){
    if(selection == 0){
        Obstacle* obstacle0 = new Obstacle(x, y, this);
        Obstacle* obstacle1 = new Obstacle(x+1, y, this);
        Obstacle* obstacle2 = new Obstacle(x-1, y, this);
        Obstacle* obstacle3 = new Obstacle(x, y+1, this);
        obstacles.push_back(obstacle0);
        obstacles.push_back(obstacle1);
        obstacles.push_back(obstacle2);
        obstacles.push_back(obstacle3);
    }
    else if(selection == 1){
        Obstacle* obstacle0 = new Obstacle(x, y, this);
        Obstacle* obstacle1 = new Obstacle(x+1, y, this);
        Obstacle* obstacle2 = new Obstacle(x, y+1, this);
        Obstacle* obstacle3 = new Obstacle(x, y+2, this);
        obstacles.push_back(obstacle0);
        obstacles.push_back(obstacle1);
        obstacles.push_back(obstacle2);
        obstacles.push_back(obstacle3);
    }
    else if(selection == 2){
        Obstacle* obstacle0 = new Obstacle(x, y, this);
        Obstacle* obstacle1 = new Obstacle(x-1, y, this);
        Obstacle* obstacle2 = new Obstacle(x, y+1, this);
        Obstacle* obstacle3 = new Obstacle(x+1, y+1, this);
        Obstacle* obstacle4 = new Obstacle(x+1, y, this);
        Obstacle* obstacle5 = new Obstacle(x+1, y, this);
        Obstacle* obstacle6 = new Obstacle(x+1, y+1, this);
        obstacles.push_back(obstacle0);
        obstacles.push_back(obstacle1);
        obstacles.push_back(obstacle2);
        obstacles.push_back(obstacle3);
        obstacles.push_back(obstacle4);
        obstacles.push_back(obstacle5);
        obstacles.push_back(obstacle6);
    }
    else if(selection == 3){
        Obstacle* obstacle0 = new Obstacle(x, y, this, sym, color);
        obstacles.push_back(obstacle0);
    }
    else if(selection == 4){
        int colonPos = sym.rfind(':');
        if(colonPos != string::npos){
            string character = sym.substr(0, colonPos);
            int color = stoi(sym.substr(colonPos + 1));
            Obstacle* obstacle0 = new Obstacle(x, y, this, character, color);
            obstacles. push_back(obstacle0);
        }
    }
}


void Game::update(){
    if(lastlevel != level){
        clearScreen();
        lastlevel = level;
    }
    delaytime++;
    maxGunBoatCount = level + 2;
    maxBomberCount = (level+1)/3 + 1;
    maxDestroyerCount = level + 1;
    maxCruiserCount = (level/2) + 1;
    maxMedicalPackCount = 2+(level/3);
    maxWeaponPackCount = 2+(level/3);

    int key = Gui::getKey(gui.getWin());
    if (key == 'q' || key == 'Q') {
        running = false;  // 按q退出
    }

    if(delaytime == 1 && mapfile.empty()){
        int dice2 = rand()%9 + 4;
        for(int i = 0; i < dice2; i++){
            int dice = rand()%3;
            int x = rand() % (winW - 10) + 6;
            int y = rand() % (winH - 10) + 6;
            addObstacle(x, y, dice);
        }
    }
    int dice = rand() % 10;
    if(dice > 2 && dice < 9 && delaytime % 5 == 0 && GunBoatCount < maxGunBoatCount){
        addGunBoat();
        GunBoatCount++;
    }
    if(dice == 1 && delaytime % 5 == 0 && BomberCount < maxBomberCount){
        addBomber();
        BomberCount++;
    }
    if(dice > 3 && dice < 8 && delaytime % 5 == 0 && DestroyerCount < maxDestroyerCount){
        addDestroyer();
        DestroyerCount++;
    }
    if(dice > 4 && dice < 7 && delaytime % 5 == 0 && CruiserCount < maxCruiserCount){
        addCruiser();
        CruiserCount++;
    }
    if(delaytime%200 == 0 && delaytime != 0 && MedicalPackCount < maxMedicalPackCount){
        int x = rand() % (winW - 10) + 5;
        int y = rand() % (winH - 10) + 5;
        MedicalPack* medpack = new MedicalPack(x, y, this);
        items.push_back(medpack);
        MedicalPackCount++;
    }
    if(delaytime%200 == 0 && delaytime != 0 && WeaponPackCount < maxWeaponPackCount){
        int x = rand() % (winW - 10) + 5;
        int y = rand() % (winH - 10) + 5;
        WeaponPack* weapack = new WeaponPack(x, y, this);
        items.push_back(weapack);
        WeaponPackCount++;
    }

    for(list<Weapon*>::iterator it = weapons.begin(); it != weapons.end(); ){
        if(!(*it)->getAlive()){
        delete (*it);        // 先释放内存！
        it = weapons.erase(it);  // erase返回下一个迭代器，不要++
        }
        else{
        ++it;  
        }
    }

    for(list<EnemyShip*>::iterator it = enemies.begin(); it != enemies.end(); ){
        if(!(*it)->getAlive()){
            if(dynamic_cast<GunBoat*>(*it) != nullptr){
                GunBoatCount--;
            }   
            else if(dynamic_cast<Bomber*>(*it) != nullptr){
                BomberCount--;
            }
            else if(dynamic_cast<Destroyer*>(*it) != nullptr){
                DestroyerCount--;
            }
            else if(dynamic_cast<Cruiser*>(*it) != nullptr){
                CruiserCount--;
            }
            delete (*it);        // 先释放内存！
            it = enemies.erase(it);  // erase返回下一个迭代器，不要++
        }
        else{
        ++it;  
        }
    }
    for(list<Explosion*>::iterator it = explosions.begin(); it != explosions.end(); ){
        if(!(*it)->getAlive()){
            delete (*it);        // 先释放内存！
            it = explosions.erase(it);  // erase返回下一个迭代器，不要++
        }
        else{
        ++it;
        }
    }
    for(list<Item*>::iterator it = items.begin(); it != items.end(); ){
        if(!(*it)->getAlive()){
            delete (*it);        // 先释放内存！
            it = items.erase(it);  // erase返回下一个迭代器，不要++
        }
        else{
        ++it;
        }
    }
    for(list<Obstacle*>::iterator it = obstacles.begin(); it != obstacles.end(); ){
        if(!(*it)->isObstacle((*it)->getX(), (*it)->getY())){
            delete (*it);        // 先释放内存！
            it = obstacles.erase(it);  // erase返回下一个迭代器，不要++
        }
        else{
        ++it;
        }
    }


    playership->update(key);
    for(list<EnemyShip*>::iterator it = enemies.begin(); it != enemies.end(); ++it){
        (*it)->update();
    }
    for(list<Weapon*>::iterator it = weapons.begin(); it != weapons.end(); ++it){
        (*it)->update();
    }
    for(list<Explosion*>::iterator it = explosions.begin(); it != explosions.end(); ++it){
    (*it)->update();
    }
    for(list<Item*>::iterator it = items.begin(); it != items.end(); ++it){
        (*it)->update();
    }

    werase(gui.getWin());        
    Gui::drawBorder(gui.getWin()); 
    
    playership->draw();
    for(list<EnemyShip*>::iterator it = enemies.begin(); it != enemies.end(); ++it){
        (*it)->draw();
    }
    for(list<Weapon*>::iterator it = weapons.begin(); it != weapons.end(); ++it){
        (*it)->draw();
    }
    for(list<Explosion*>::iterator it = explosions.begin(); it != explosions.end(); ++it){
        (*it)->draw();
    }
    for(list<Item*>::iterator it = items.begin(); it != items.end(); ++it){
        (*it)->draw();
    }
    for(list<Obstacle*>::iterator it = obstacles.begin(); it != obstacles.end(); ++it){
        (*it)->draw();
    }

    if(!playership->getAlive()){
        running = false;
    }
    wattron(gui.getWin(), COLOR_PAIR(2));
    mvwprintw(gui.getWin(), 1, LENGTH-17, "Health: %d/%d", playership->getHealth(), playership->getMaxHealth());
    wattroff(gui.getWin(), COLOR_PAIR(2));
    wattron(gui.getWin(), COLOR_PAIR(6));
    mvwprintw(gui.getWin(), 2, LENGTH-17, "Shells: %d", playership->getShellCount());
    mvwprintw(gui.getWin(), 3, LENGTH-17, "Missiles: %d", playership->getMissileCount());
    wattroff(gui.getWin(), COLOR_PAIR(6));
    wattron(gui.getWin(), COLOR_PAIR(1));
    mvwprintw(gui.getWin(), 4, LENGTH-17, "Coins: %d/%d", playership->getCoins(), playership->getMaxCoins());
    wattroff(gui.getWin(), COLOR_PAIR(1));
    wattron(gui.getWin(), COLOR_PAIR(5));
    mvwprintw(gui.getWin(), 5, LENGTH-17, "Levels: %d", level);
    wattroff(gui.getWin(), COLOR_PAIR(5));
    mvwprintw(gui.getWin(), 7, LENGTH-17, "GunBoats: %d", GunBoatCount);
    mvwprintw(gui.getWin(), 8, LENGTH-17, "Bombers: %d", BomberCount);
    mvwprintw(gui.getWin(), 9, LENGTH-17, "Destroyers: %d", DestroyerCount);
    mvwprintw(gui.getWin(), 10, LENGTH-17, "Cruisers: %d", CruiserCount);
    mvwprintw(gui.getWin(), 11, LENGTH-17, "MaxGunBoats: %d", maxGunBoatCount);
    mvwprintw(gui.getWin(), 12, LENGTH-17, "MaxBombers: %d", maxBomberCount);
    mvwprintw(gui.getWin(), 13, LENGTH-17, "MaxDestroyers: %d", maxDestroyerCount);
    mvwprintw(gui.getWin(), 14, LENGTH-17, "MaxCruisers: %d", maxCruiserCount);
    mvwprintw(gui.getWin(), 15, LENGTH-17, "MedicalPacks: %d", MedicalPackCount);
    mvwprintw(gui.getWin(), 16, LENGTH-17, "WeaponPacks: %d", WeaponPackCount);

    //wrefresh(gui.getWin());  
    wnoutrefresh(gui.getWin());
    doupdate();
    
}

void Game::reset() {
    for(list<Weapon*>::iterator it = weapons.begin(); it != weapons.end(); ++it){
        delete (*it);
    }
    weapons.clear();
    
    for(list<EnemyShip*>::iterator it = enemies.begin(); it != enemies.end(); ++it){
        delete (*it);
    }
    enemies.clear();
    for(list<Explosion*>::iterator it = explosions.begin(); it != explosions.end(); ++it){
        delete (*it);
    }
    for(list<Item*>::iterator it = items.begin(); it != items.end(); ++it){
        delete (*it);
    }
    items.clear();
    explosions.clear();
    for(list<Obstacle*>::iterator it = obstacles.begin(); it != obstacles.end(); ++it){
        delete (*it);
    }
    obstacles.clear();
    delete playership;

    running = true;
    playership = new PlayerShip(winW/2, winH/2, this);
    Gui::drawBorder(gui.getWin()); 
    playership->draw();
    level = 0;
    delaytime = 0;
    BomberCount = 0;
    GunBoatCount = 0;
    DestroyerCount = 0;
    CruiserCount = 0;
    MedicalPackCount = 0;
    WeaponPackCount = 0;
    maxGunBoatCount = level + 2;
    maxBomberCount = (level+1)/3 + 1;
    maxDestroyerCount = level + 1;
    maxCruiserCount = (level/2) + 1;
    maxMedicalPackCount = 2+(level/3);
    maxWeaponPackCount = 2+(level/3);
    delaytime_2 = 0;
    if(!mapfile.empty()){
        loadMap(mapfile);
    }
}

bool Game::isObstacle(int checkx, int checky){
    for(list<Obstacle*>::iterator it = obstacles.begin(); it != obstacles.end(); ++it){
        if((*it)->getX() == checkx && (*it)->getY() == checky){
            return true;
        }
    }
    return false;
}

void Game::clearScreen(){
    for(list<Weapon*>::iterator it = weapons.begin(); it != weapons.end(); ++it){
        delete (*it);
    }
    weapons.clear();
    
    for(list<EnemyShip*>::iterator it = enemies.begin(); it != enemies.end(); ++it){
        delete (*it);
    }
    enemies.clear();

    delaytime = 2;
    BomberCount = 0;
    GunBoatCount = 0;
    DestroyerCount = 0;
    CruiserCount = 0;
    MedicalPackCount = 0;
    WeaponPackCount = 0;
    maxGunBoatCount = level + 2;
    maxBomberCount = (level+1)/3 + 1;
    maxDestroyerCount = level + 1;
    maxCruiserCount = (level/2) + 1;
    maxMedicalPackCount = 2+(level/3);
    maxWeaponPackCount = 2+(level/3);
    delaytime_2 = 0;

    int prex = playership->getX();
    int prey = playership->getY();
    if(!mapfile.empty()){
        loadMap(mapfile);
        playership->setX(prex);
        playership->setY(prey);
    }

    werase(gui.getWin());        
    Gui::drawBorder(gui.getWin()); 
    playership->draw();
    wrefresh(gui.getWin());
}

void Game::loadMap(string& mapfile){
    std::ifstream file(mapfile);
    if (!file.is_open()) {
        return;
    }
    std::string line;
    int y = 0;
    while(getline(file, line) && y < winH){
        for(size_t x = 0; x < line.length() && x < (size_t)winW; x++){
            char ch = line[x];
            string sym(1, ch);
            switch (ch)
            {
            case '#':
                addObstacle(x, y+5, 3, sym);
                break;
            
            case 'B': 
                addObstacle(x, y+5, 4, sym +":3");
                break;
            case 'C':
                addObstacle(x, y+5, 4, sym +":5");
                break;
            
            // Ubuntu 橙色/黄色 (COLOR_PAIR 1 = YELLOW)
            case 'o':
            case 's':
            case '+':
            case '-':
            case '/':
            case '.':
            case ':':
            case '`':
            case 'y':
            case 'd':
            case 'm':
            case 'h':
                addObstacle(x, y+5, 4, sym +":1");
                break;
                
            case 'O':
            case '@':
                addObstacle(x, y+5, 4, sym +":4");
                break;
            
            case 'G':
                addObstacle(x, y+5, 4, sym +":2");
                break;
            
            // 洋红色障碍物 (COLOR_PAIR 6 = MAGENTA)
            case 'M': 
                addObstacle(x, y+5, 4, sym+":6");
                break;
            
            // 白色障碍物 (COLOR_PAIR 0 = WHITE)
            case 'W':
                addObstacle(x, y+5, 4, sym+":0");
                break;

            case 'P':
                playership->setX(x);
                playership->setY(y+5);
                break;
            default:
                break;
            }
        }
        y++;
    }

    file.close();

}