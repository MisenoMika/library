#include "Game.h"
#include "Grass.h"
#include "Rabbit.h"
#include "Wolf.h"
#include "Tiger.h"
#include <stdlib.h>
#include <ctime>


Game::Game(int tigersnum, int wolvesnum, int rabbitsnum) {
    winH = 30;
    winW = 85;

    for(int i=0; i<rabbitsnum; i++)addRabbit(rand() % (winW-5) + 5, rand() % (winH-5) + 5, 4);
    for(int i=0; i<wolvesnum; i++)addWolf(rand() % (winW-5) + 5, rand() % (winH-5) + 5, 10, 2);
    for(int i=0; i<tigersnum; i++)addTiger(rand() % (winW-5) + 5, rand() % (winH-5) + 5, 15, 3);
    //srand(time(nullptr));
    // 初始化草地
    for (size_t i = 5; i < winW; ++i) {//竖
        for(size_t j = 5; j < winH; ++j){//横
            int x = i;
            int y = j;
            grasses.push_back(new Grass(x, y, this));
        }
    }

}

void Game::addRabbit(int x, int y, int Maxhunger) {
    for(int i = 0; i<1; i++)rabbits.push_back(new Rabbit(x, y, this, Maxhunger));
}

void Game::addWolf(int x, int y, int Maxhunger, int Huntrage) {
        wolves.push_back(new Wolf(x, y , this, Maxhunger, Huntrage));
    } 

void Game::addTiger(int x, int y, int Maxhunger, int Huntrage) {
        tigers.push_back(new Tiger(x, y , this, Maxhunger, Huntrage));
    }


Game::~Game() {
    for (vector<Grass*>::iterator it = grasses.begin(); it != grasses.end(); ++it) {
        delete (*it);  
    }

    for (list<Animal*>::iterator it = rabbits.begin(); it != rabbits.end(); ++it) {
        delete (*it);  
    }
    gui.end();
}

void Game::update(int& key, int&day){
        
    
    
    // 更新草地
    for (vector<Grass*>::iterator it = grasses.begin(); it != grasses.end(); ++it) {
        (*it)->update();
    }

    // 更新动物
   for (list<Animal*>::iterator it = rabbits.begin(); it != rabbits.end(); ++it) {
        (*it)->update();
    }

    for (list<Animal*>::iterator it = wolves.begin(); it != wolves.end(); ++it) {
        (*it)->update();
    }

    for (list<Animal*>::iterator it = tigers.begin(); it != tigers.end(); ++it) {
        (*it)->update();
    }

    // 按d添加兔子（随机位置）
    if (key == 'd' || key == 'D') {
        int x = rand() % (winW-5) + 5 ;
        int y = rand() % (winH-5) + 5 ;
        addRabbit(x, y, 4);
    }
    //按a添加捕食者（随机位置）
    if (key == 'a' || key == 'A') {
        int dice = rand() % 2;
        if(dice == 0){
            int x = rand() % (winW-5) + 5 ;
            int y = rand() % (winH-5) + 5 ;
            int Maxhunger = 10;
            int Huntrange = 2;
            addWolf(x, y, Maxhunger, Huntrange);
        }
        else if(dice == 1){
            int x = rand() % (winW-5) + 5 ;
            int y = rand() % (winH-5) + 5 ;
            int Maxhunger = 15;
            int Huntrange = 3;
            addTiger(x, y, Maxhunger, Huntrange);
        }
    }


    // 动物死亡
    for (list<Animal*>::iterator it = rabbits.begin(); it != rabbits.end(); ++it) {
        if( (*it)-> alive() ){
            continue;
        }
        else if(!( (*it)-> alive() )){
            it = rabbits.erase(it);
        }
        
    }

    for (list<Animal*>::iterator it = wolves.begin(); it != wolves.end(); ++it) {
        if( (*it)-> alive() ){
            continue;
        }
        else if(!( (*it)-> alive() ) )
        {
            it = wolves.erase(it);
        }
        
    }

    for (list<Animal*>::iterator it = tigers.begin(); it != tigers.end(); ++it) {
        if( (*it)-> alive() ){
            continue;
        }
        else if(!( (*it)-> alive() ) )
        {
            it = tigers.erase(it);
        }
        
    }

    wclear(gui.getWin());          // 清空窗口
    Gui::drawBorder(gui.getWin()); // 绘制边框
    day++;
    mvwprintw(gui.getWin(), 2, 25, " DAY %d", day);
    // 绘制草
    for (vector<Grass*>::iterator it = grasses.begin(); it != grasses.end(); ++it) {
        (*it)->draw();
    }

    // 绘制动物
    size_t rabbitnumber= rabbits.size();
    for (list<Animal*>::iterator it = rabbits.begin(); it != rabbits.end(); ++it) {
        (*it)->draw();
        if(rabbitnumber != 0)mvwprintw(gui.getWin(), 1, 5, " Rabbits: %d", static_cast<int>(rabbitnumber));
    }

    size_t wolfnumber= wolves.size();
    for (list<Animal*>::iterator it = wolves.begin(); it != wolves.end(); ++it) {
        (*it)->draw();
        if(wolfnumber != 0)mvwprintw(gui.getWin(), 2, 5, " Wolves: %d", static_cast<int>(wolfnumber));
    }

    size_t tigernumber= tigers.size();
    for (list<Animal*>::iterator it = tigers.begin(); it != tigers.end(); ++it) {
        (*it)->draw();
        if(tigernumber != 0)mvwprintw(gui.getWin(), 3, 5, " Tigers: %d", static_cast<int>(tigernumber));
    }

    wrefresh(gui.getWin());  // 刷新窗口，显示绘制内容


}