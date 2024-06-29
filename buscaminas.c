#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "buscaminas.h"

#define FILAS 10
#define COLUMNAS 10
#define MINAS 10

int tablero[FILAS][COLUMNAS];
int mostrado[FILAS][COLUMNAS];

void inicializar_tablero() {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            tablero[i][j] = 0;
            mostrado[i][j] = 0;
        }
    }
}

void colocar_minas() {
    srand(time(NULL));
    for (int i = 0; i < MINAS; ) {
        int fila = rand() % FILAS;
        int columna = rand() % COLUMNAS;
        if (tablero[fila][columna] == 0) {
            tablero[fila][columna] = -1;
            i++;
        }
    }
}

void contar_minas() {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j] == -1) continue;
            int count = 0;
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    int ni = i + di, nj = j + dj;
                    if (ni >= 0 && ni < FILAS && nj >= 0 && nj < COLUMNAS && tablero[ni][nj] == -1) {
                        count++;
                    }
                }
            }
            tablero[i][j] = count;
        }
    }
}

void mostrar_tablero(WINDOW *game_win, int cursor_y, int cursor_x) {
    int x = 2, y = 1;
    box(game_win, 0, 0);
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (cursor_y == i && cursor_x == j) {
                wattron(game_win, A_REVERSE);
                if (mostrado[i][j]) {
                    if (tablero[i][j] == -1) {
                        mvwprintw(game_win, y + i, x + j * 2, "*");
                    } else {
                        mvwprintw(game_win, y + i, x + j * 2, "%d", tablero[i][j]);
                    }
                } else {
                    mvwprintw(game_win, y + i, x + j * 2, "#");
                }
                wattroff(game_win, A_REVERSE);
            } else {
                if (mostrado[i][j]) {
                    if (tablero[i][j] == -1) {
                        mvwprintw(game_win, y + i, x + j * 2, "*");
                    } else {
                        mvwprintw(game_win, y + i, x + j * 2, "%d", tablero[i][j]);
                    }
                } else {
                    mvwprintw(game_win, y + i, x + j * 2, "#");
                }
            }
        }
    }
    wrefresh(game_win);
}

void descubrir_casilla(int fila, int columna) {
    if (fila < 0 || fila >= FILAS || columna < 0 || columna >= COLUMNAS || mostrado[fila][columna]) return;
    mostrado[fila][columna] = 1;
    if (tablero[fila][columna] == 0) {
        for (int di = -1; di <= 1; di++) {
            for (int dj = -1; dj <= 1; dj++) {
                descubrir_casilla(fila + di, columna + dj);
            }
        }
    }
}

void iniciar_juego() {
    inicializar_tablero();
    colocar_minas();
    contar_minas();

    int cursor_y = 0, cursor_x = 0;
    WINDOW *game_win = newwin(FILAS + 2, COLUMNAS * 2 + 2, (24 - (FILAS + 2)) / 2, (80 - (COLUMNAS * 2 + 2)) / 2);
    keypad(game_win, TRUE);

    while (1) {
        clear();
        mostrar_tablero(game_win, cursor_y, cursor_x);
        int c = wgetch(game_win);
        switch (c) {
            case KEY_UP:
                if (cursor_y > 0) cursor_y--;
                break;
            case KEY_DOWN:
                if (cursor_y < FILAS - 1) cursor_y++;
                break;
            case KEY_LEFT:
                if (cursor_x > 0) cursor_x--;
                break;
            case KEY_RIGHT:
                if (cursor_x < COLUMNAS - 1) cursor_x++;
                break;
            case '\n':
                descubrir_casilla(cursor_y, cursor_x);
                if (tablero[cursor_y][cursor_x] == -1) {
                    clear();
                    mvprintw(0, 0, "Game Over! Press any key to return to the menu.");
                    refresh();
                    getch();
                    return;
                }
                break;
            case 'q':
                return;
        }
    }
}

void mostrar_instrucciones() {
    clear();
    printw("Instrucciones del juego:\n");
    printw("1. Use las flechas para moverse por el tablero.\n");
    printw("2. Presione Enter para descubrir una casilla.\n");
    printw("3. Evite las minas para ganar el juego.\n");
    printw("Presione cualquier tecla  para volver al menú principal en cualquier momento.\n");
    refresh();
    getch();
}

void print_menu(WINDOW *menu_win, int highlight) {
    int x, y, i;
    char *options[] = {
        "Iniciar juego",
        "Instrucciones",
        "Salir del juego"
    };
    int num_options = sizeof(options) / sizeof(options[0]);

    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    for (i = 0; i < num_options; ++i) {
        if (highlight == i + 1) {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%d. %s", i + 1, options[i]);
            wattroff(menu_win, A_REVERSE);
        } else {
            mvwprintw(menu_win, y, x, "%d. %s", i + 1, options[i]);
        }
        ++y;
    }
    wrefresh(menu_win);
}
