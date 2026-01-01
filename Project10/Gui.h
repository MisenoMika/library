#ifndef _GUI_H_
#define _GUI_H_
#include <ncurses.h>
#include <string>

#define LENGTH 165
#define HEIGHT 45

using namespace std;
class Gui {
    size_t row;
    size_t col;
    WINDOW* win;
public:
    Gui ():row(180),col(180) {init();}
    ~Gui() {endwin();}
    WINDOW* getWin() { return win;}
    void init();
    int get();
    void paintat(size_t, size_t, char);
    //void printMsg(WINDOW* win, int row, int col, const char* prompt);
    void clear();
    void redraw();
    void end() {endwin();}
    void drawSomething(WINDOW* win, int y, int x, string ch, int colorPair);
    // 获取按键
    static int getKey(WINDOW* win) {
        int c = wgetch(win);
        flushinp();//清空输入缓存区(idkwhat is this)
        return c;
    }
    static void drawBorder(WINDOW* win) {
        int maxY, maxX;
        getmaxyx(win, maxY, maxX);
        mvwprintw(win, 0, LENGTH-19, " War Thunder AIR. ");
        mvwprintw(win, 38, LENGTH-19, " Author: BlossilveR ");
        //mvwprintw(win, 4, 50, " Sakuraba Kawaii ");
        // y x
        for(int i = 0; i < HEIGHT; i++) {//列
            mvwaddch(win, i, 4, '|');
            mvwaddch(win, i, LENGTH-20, '|' );
            mvwaddch(win, i, LENGTH+3, '|' );
        }
        for(int i = 5; i<LENGTH; i++){
            mvwaddch(win, HEIGHT, i, '=' );
        }
        for(int i = 5; i < LENGTH-20; i++) {//行
            wattron(win, COLOR_PAIR(3));
            mvwaddch(win, 4, i, '~');
            wattroff(win, COLOR_PAIR(3));
        }
        //mvwprintw(win, HEIGHT, 4, "0");
        mvwprintw(win, HEIGHT, LENGTH+3, "0");
        mvwprintw(win, HEIGHT, 4, "0");
        mvwprintw(win, HEIGHT+1, 5, " Higher Level, More enemies ");
        mvwprintw(win, HEIGHT+2, 5, " Level2: Unlock Stronger broadside cannons ");
        mvwprintw(win, HEIGHT+2, 50, " Level4: Unlock Stronger frontside cannons ");
        wattron(win, COLOR_PAIR(4));
        mvwprintw(win, HEIGHT+1, 50, " Before You Started to Play(or mark my project), Read Instructions in README.txt ");
        wattroff(win, COLOR_PAIR(4));
    }

    bool showGameOver() {
        nodelay(win, false);  
        werase(win);
        
        int centerY = 19;
        int centerX = 50;
        
        wattron(win, COLOR_PAIR(4) | A_BOLD);  //红色
        mvwprintw(win, centerY - 2, centerX - 10, "  ____    _    __  __ _____   _____   ___ _____ ____  ");
        mvwprintw(win, centerY - 1, centerX - 10, " / ___|  / \\  |  \\/  | ____| / _ \\ \\ / / | ____|  _ \\ ");
        mvwprintw(win, centerY,     centerX - 10, "| |  _  / _ \\ | |\\/| |  _|  | | | \\ V /| |  _| | |_) |");
        mvwprintw(win, centerY + 1, centerX - 10, "| |_| |/ ___ \\| |  | | |___ | |_| || | | | |___|  _ < ");
        mvwprintw(win, centerY + 2, centerX - 10, " \\____/_/   \\_\\_|  |_|_____| \\___/ |_| |_|_____|_| \\_\\");
        wattroff(win, COLOR_PAIR(4) | A_BOLD);
        
        wattron(win, COLOR_PAIR(1));  // 黄色
        mvwprintw(win, centerY + 5, centerX + 5, "Play again? (Y/N)");
        wattroff(win, COLOR_PAIR(1));
        
        wrefresh(win);
        int key;
        while (true) {
            key = wgetch(win);
            if (key == 'y' || key == 'Y') {
                nodelay(win, true);  
                return true;  
            }
            if (key == 'n' || key == 'N' || key == 'q' || key == 'Q') {
                nodelay(win, true);
                return false;  
            }
        }
    }
};
#endif
