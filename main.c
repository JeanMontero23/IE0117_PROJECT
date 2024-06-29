#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "buscaminas.h"

#define MENU_HEIGHT 7
#define MENU_WIDTH 40

void main_menu();

int main() {
    initscr();
    clear();
    noecho();
    cbreak();

    main_menu();

    endwin();
    return 0;
}

void main_menu() {
    WINDOW *menu_win;
    int highlight = 1;
    int choice = 0;
    int c;
    int startx, starty;

    startx = (80 - MENU_WIDTH) / 2;
    starty = (24 - MENU_HEIGHT) / 2;

    menu_win = newwin(MENU_HEIGHT, MENU_WIDTH, starty, startx);
    keypad(menu_win, TRUE);

    while (1) {
        clear();
        refresh();
        print_menu(menu_win, highlight);
        while (1) {
            c = wgetch(menu_win);
            switch (c) {
                case KEY_UP:
                    if (highlight == 1)
                        highlight = 3;
                    else
                        --highlight;
                    break;
                case KEY_DOWN:
                    if (highlight == 3)
                        highlight = 1;
                    else
                        ++highlight;
                    break;
                case '\n':
                    choice = highlight;
                    break;
            }
            print_menu(menu_win, highlight);
            if (choice != 0)
                break;
        }
        if (choice == 1) {
            iniciar_juego();
        } else if (choice == 2) {
            mostrar_instrucciones();
        } else if (choice == 3) {
            break;
        }
        choice = 0;
        highlight = 1;
    }
}
