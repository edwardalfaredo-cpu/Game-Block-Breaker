#include <iostream>
#include <ncurses.h>
#include <unistd.h>

using namespace std;

int main() {
    initscr();
    noecho();
    curs_set(0);

    char balok [3][10] = {
        {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
        {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
        {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_'}
    };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 10; j++) {
            mvprintw(i, j, "%c", balok[i][j]);
        }
    }
    refresh();
    getch();
    endwin();
    return 0;
}