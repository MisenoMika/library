#include <ncurses.h>
#include "Gui.h"
#include <string>
using namespace std;

void Gui::init() {
    initscr();          /* Start curses mode*/
    refresh();     /* Print it on to the real screen */
    win = stdscr;
    refresh();
    curs_set(0);
    wrefresh(win);
    noecho();
    cbreak();
    keypad(win, true);
    nodelay(win, true);
    flushinp();
    if (can_change_color()) {
            // Ubuntu 橙色 #E95420 -> RGB(233, 84, 32) -> 缩放到0-1000
            init_color(COLOR_YELLOW, 913, 329, 125);
    }
    if (has_colors()) {
        start_color();
        init_pair(0, COLOR_WHITE, COLOR_BLACK); //子弹 
        init_pair(1, COLOR_YELLOW, COLOR_BLACK); //TrumpShip   
        init_pair(2, COLOR_GREEN, COLOR_BLACK);    
        init_pair(3, COLOR_BLUE, COLOR_BLACK);  //海线
        init_pair(4, COLOR_RED, COLOR_BLACK); //Game Over
        init_pair(5, COLOR_CYAN, COLOR_BLACK); 
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    }
}

int Gui::get() {
    int c = wgetch(win);
    flushinp();
    return c;
}
void Gui::paintat(size_t rw, size_t cl, char c) {
    mvwaddch(win, rw, cl, c);
    return;
}
/*void Gui::printMsg(WINDOW* win, int row, int col, const char* p) {
    mvwprintw(win, row, col, p);
}*/
void Gui::clear() {
    werase(win);
}
void Gui::redraw() {
    wrefresh(win);
}

//绘制实体
void Gui::drawSomething(WINDOW* win, int y, int x, string ch, int colorPair) {
     //mvwprintw(win, y, x, "%c", ch);
    int maxY, maxX;
    getmaxyx(win, maxY, maxX); // 获取窗口实际大小
    // 过滤无效坐标
    if (y < 0 || y >= maxY || x < 0 || x >= maxX) {
        return;
    }
    //mvwprintw(win, 2, 25, "Earth Simulation Online");
    wattron(win, COLOR_PAIR(colorPair));
    mvwprintw(win, y, x, "%s", ch.c_str());
    wattroff(win, COLOR_PAIR(colorPair));
}

    