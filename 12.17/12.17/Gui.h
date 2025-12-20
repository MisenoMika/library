#ifndef _GUI_H_
#define _GUI_H_
#include <ncurses.h>

class Gui {
    size_t row;
    size_t col;
    WINDOW* win;
public:
    Gui ():row(85),col(90) {init();}
    ~Gui() {endwin();}
    WINDOW* getWin() { return win;}
    void init();
    int get();
    void paintat(size_t, size_t, char);
    void printMsg(WINDOW* win, int row, int col, const char* prompt);
    void clear();
    void redraw();
    void end() {endwin();}
    void drawSomething(WINDOW* win, int y, int x, char ch, int colorPair);
    // 获取按键
    static int getKey(WINDOW* win) {
        int c = wgetch(win);
        flushinp();//清空输入缓存区(idkwhat is this)
        return c;
    }
    static void drawBorder(WINDOW* win) {
        int maxY, maxX;
        getmaxyx(win, maxY, maxX);
        mvwprintw(win, 1, 18, " Earth Online Simulation. ");
        mvwprintw(win, 1, 50, " Author: BlossilveR ");
        mvwprintw(win, 2, 50, " My animals won't die easily  ");
        mvwprintw(win, 3, 50, " even if they eat nothing ");
        mvwprintw(win, 31, 25, " Press 'A or a ' to add predators ");
        mvwprintw(win, 32, 25, " Press 'D or d ' to add rabbits ");
        mvwprintw(win, 33, 25, " Press 'Q or q ' to exit ");
        //mvwprintw(win, 4, 50, " Sakuraba Kawaii ");
        for(int i = 0; i < 31; i++) {
            mvwaddch(win, i, 4, '|');
            mvwaddch(win, i, 85, '|' );
        }
        for(int i = 5; i < 86; i++) {
            mvwaddch(win, 4, i, '=');
            mvwaddch(win, 30, i, '=' );
        }
    }
};
#endif
