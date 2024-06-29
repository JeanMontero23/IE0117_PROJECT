/*
 * Se incluyen las librerias estandar y ncurses
 * Se define el tamano del tablero y el numero de las minas que seran distribuidas por el mismo
 */
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "buscaminas.h"

#define FILAS 10
#define COLUMNAS 10
#define MINAS 10

// Se definen los arreglos del tablero, las casillas mostradas y las banderas
int tablero[FILAS][COLUMNAS];
int mostrado[FILAS][COLUMNAS];
int banderas[FILAS][COLUMNAS];

// Inician los valores del tablero, las casillas mostradas y las banderas a 0
void inicializar_tablero() {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            tablero[i][j] = 0;
            mostrado[i][j] = 0;
            banderas[i][j] = 0;
        }
    }
}

// Se colocan las minas con ayuda de la biblioteca time.h para aleatorizar la posicion de las mismas
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

// Se hace el conteo de las minas que esten alrededor de cada casilla que no sea una mina y se actuliza el tablero
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

/*
 * Se despliega el tablero en la ventana game_win
 * Tambien se resalta la posicion del cursor para que el jugador sepa en que casilla se ubica
 */
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
                } else if (banderas[i][j]) {
                    mvwprintw(game_win, y + i, x + j * 2, "F");
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
                } else if (banderas[i][j]) {
                    mvwprintw(game_win, y + i, x + j * 2, "F");
                } else {
                    mvwprintw(game_win, y + i, x + j * 2, "#");
                }
            }
        }
    }
    wrefresh(game_win);
}

/*
 * Esta funcion descubre la casilla seleccionada
 * Cubre la situacion que, si la casilla es cero se descubre de manera recursiva las celdas adyacentes
 */
void descubrir_casilla(int fila, int columna) {
    if (fila < 0 || fila >= FILAS || columna < 0 || columna >= COLUMNAS || mostrado[fila][columna] || banderas[fila][columna]) return;
    mostrado[fila][columna] = 1;
    if (tablero[fila][columna] == 0) {
        for (int di = -1; di <= 1; di++) {
            for (int dj = -1; dj <= 1; dj++) {
                descubrir_casilla(fila + di, columna + dj);
            }
        }
    }
}

// La siguiente funcion sirve para colocar o quitar una bandera en la casilla actual si todavia no se a seleccionado
void colocar_quitar_bandera(int fila, int columna) {
    if (!mostrado[fila][columna]) {
        banderas[fila][columna] = !banderas[fila][columna];
    }
}

/*
 * La siguiente funcion inicia el juego, de tal modo que se crea una ventana de juego
 * Una vez creada la ventana se maneja la entrada del usuario para moverse por el menu
 * Tambien se contempla la funcion de descubrir las casillas, colocar y quitar las banderas, y salir del juego
 */
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
                    mvprintw(0, 0, "Fin del juego! Presiona cualquier tecla pra volver al menu.");
                    refresh();
                    getch();
                    return;
                }
                break;
            case 'f':
                colocar_quitar_bandera(cursor_y, cursor_x);
                break;
            case 'q':
                return;
        }
    }
}

// La siguiente funcion muestra las instrucciones del juego y espera la entrada de cualquier tecla para volver al menu prinicipal
void mostrar_instrucciones() {
    clear();
    printw("Instrucciones del juego:\n");
    printw("1. Use las flechas para moverse por el tablero.\n");
    printw("2. Presione Enter para descubrir una casilla.\n");
    printw("3. Presione 'f' para colocar o quitar una bandera.\n");
    printw("4. Evite las minas para ganar el juego.\n");
    printw("5. Presione la q en el tablero de juego para volver al menu principal.\n");
    printw("Presione cualquier tecla para volver al menú principal.\n");
    refresh();
    getch();
}

// Esta funcion sirve para se imprima el menu principal y se resalte la opcion actual del usuario para que sepa donde esta 
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
