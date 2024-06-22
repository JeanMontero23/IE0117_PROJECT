#include <ncurses.h>
#include "game.h"

#define MENU_HEIGHT 10
#define MENU_WIDTH 40

int main() {
    WINDOW *menu_win;
    int startx, starty;
    int ch;

    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);

    startx = (COLS - MENU_WIDTH) / 2;
    starty = (LINES - MENU_HEIGHT) / 2;

    menu_win = newwin(MENU_HEIGHT, MENU_WIDTH, starty, startx);
    keypad(menu_win, TRUE);
    refresh();

    mvprintw(0, 0, "Bienvenido a Buscaminas!");
    mvprintw(1, 0, "Usa las flechas para navegar y Enter para seleccionar una opción.");
    mvprintw(2, 0, "Presiona 'q' para salir.");
    refresh();

    char *choices[] = {
        "Iniciar Juego",
        "Instrucciones",
        "Salir"
    };
    int n_choices = sizeof(choices) / sizeof(char *);
    int choice = 0;

    while (1) {
        for (int i = 0; i < n_choices; ++i) {
            if (i == choice) {
                wattron(menu_win, A_REVERSE);
            }
            mvwprintw(menu_win, i + 1, 1, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        }
        wrefresh(menu_win);

        ch = wgetch(menu_win);
        switch (ch) {
            case KEY_UP:
                if (choice > 0) choice--;
                break;
            case KEY_DOWN:
                if (choice < n_choices - 1) choice++;
                break;
            case 10:  // Enter key
                if (choice == 0) {
                    start_game(menu_win);
                } else if (choice == 1) {
                    show_instructions(menu_win);
                } else if (choice == 2) {
                    endwin();
                    return 0;
                }
                break;
            case 'q':
                endwin();
                return 0;
        }
    }

    endwin();
    return 0;
}
