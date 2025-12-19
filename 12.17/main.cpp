#include <ncurses.h>
#include "Gui.h"
#include <sys/time.h>
#include <stdlib.h>
#include <ctime>
#include <unistd.h>
#include <iostream>
#include <cstddef>
#include "Game.h"
using namespace std;
int main()
{
    srand(time(0));
    struct timeval time_now;
    gettimeofday(&time_now, NULL);
    time_t oldTime = (time_now.tv_sec*1000)+(time_now.tv_usec/1000);
    time_t currentTime =  oldTime;
    Game game;
    int day;
    //game.update();
    while (true) {
        
        gettimeofday(&time_now, NULL);
        currentTime =(time_now.tv_sec*1000)+(time_now.tv_usec/1000);
        if (currentTime - oldTime < 100) {usleep(40);continue;}
        oldTime = currentTime;
        int key = Gui::getKey(game.getGui().getWin());
        if (key == 'q' || key == 'Q') {
            break;  // 按q退出
        }
        game.update(key, day);

        /*在main.cpp的主循环中，按键获取与游戏更新的时机不同步，导致d键输入可能被忽略：
        原逻辑先获取按键，再判断是否到更新时间（每隔 100ms 更新一次）。
        若按下d键时未到更新时间，会执行usleep(22); continue;，此时按键已被flushinp()清空，下一次循环获取的按键可能为无效值（ERR），导致game.update(key)未处理d键。*/
    }
    return 0;
}