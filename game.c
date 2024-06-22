/*
 * Primeramente se incluye el headers game.h ya que contiene HEIGHT y WIDTH junto con otros prototipos y definiciones
 * Seguidamente, stdlib en donde hay bibliotecas comunes
 * Con el uso de time.h se plantea usar para generar numeros aleatorios
 * Se incluye string.h para el uso de memset
 */
#include "game.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Se hace declaracion de prototipos de funciones internas que se van a utilizar a continuacion
void initialize_board(char board[HEIGHT][WIDTH], int revealed[HEIGHT][WIDTH], int mines);
void reveal_cell(WINDOW *win, char board[HEIGHT][WIDTH], int revealed[HEIGHT][WIDTH], int x, int y);
void mark_mine(WINDOW *win, int marked[HEIGHT][WIDTH], int x, int y);
int check_victory(int revealed[HEIGHT][WIDTH], int marked[HEIGHT][WIDTH], char board[HEIGHT][WIDTH]);
int count_adjacent_mines(char board[HEIGHT][WIDTH], int x, int y);

/*
 * La funcion start_game controla flujo del juego por lo que es core para el funcionamiento del programa
 * Luego se inicializa el tablero y otros arrays necesarios (marked, reveled y board)
 * Se hace setup de 10 minas
 * Se cubre el reinicio de las variables de estado de juego (victory y gameover)
 */
void start_game(WINDOW *win) {
    int startx = 0;
    int starty = 0;
    int mines = 10;

    char board[HEIGHT][WIDTH];
    int revealed[HEIGHT][WIDTH];
    int marked[HEIGHT][WIDTH];
    int game_over = 0;
    int victory = 0;

    initialize_board(board, revealed, mines);
    memset(marked, 0, sizeof(marked));

    /*
     * Se mantiene un bucle activo hasta que se de la condicion de victoria o derrota
     * Se forma un tablero en la ventana win, en la misma se muestran las celdas marcadas, reveladas y ocultas
     * Se usa wgetch para obtener lo ingresado por la persona y se toma cierto procedimiento dependiendo de lo recibido
     * Se usa check_victory para verificar la victoria
     * En caso de ganar o perder se muestra un resultado en pantalla para dar feedback al usuario
     */
    int x = 0, y = 0;
    keypad(win, TRUE);
    while (!game_over && !victory) {
        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                if (revealed[i][j]) {
                    mvwprintw(win, starty + i, startx + j * 2, "%c ", board[i][j]);
                } else if (marked[i][j]) {
                    mvwprintw(win, starty + i, startx + j * 2, "M ");
                } else {
                    mvwprintw(win, starty + i, startx + j * 2, "- ");
                }
            }
        }
        wmove(win, starty + y, startx + x * 2);
        wrefresh(win);

        int c = wgetch(win);
        switch (c) {
            case KEY_UP:
                if (y > 0) --y;
                break;
            case KEY_DOWN:
                if (y < HEIGHT - 1) ++y;
                break;
            case KEY_LEFT:
                if (x > 0) --x;
                break;
            case KEY_RIGHT:
                if (x < WIDTH - 1) ++x;
                break;
            case 'r':
                if (!marked[y][x]) {
                    reveal_cell(win, board, revealed, x, y);
                    if (board[y][x] == '*') {
                        game_over = 1;
                    }
                }
                break;
            case 'm':
                mark_mine(win, marked, x, y);
                break;
            default:
                break;
        }
        victory = check_victory(revealed, marked, board);
    }
    if (game_over) {
        mvprintw(LINES - 2, 0, "Has perdido! Presiona cualquier tecla para continuar.");
    } else {
        mvprintw(LINES - 2, 0, "Has ganado! Presiona cualquier tecla para continuar.");
    }
    refresh();
    getch();
}

/*
 * En este bloque se llena el tablero con celdas vacias y las mismas se marcan como no reveladas
 * Se procede a colocar las minas en el tablero hasta el maximo que se fijo anteriormente
 * Por ultimo se hace el calculo del numero de minas adyacentes a cada celda y se almacena en el tablero
 */
void initialize_board(char board[HEIGHT][WIDTH], int revealed[HEIGHT][WIDTH], int mines) {
    srand(time(NULL));
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            board[i][j] = '-';
            revealed[i][j] = 0;
        }
    }

    while (mines > 0) {
        int x = rand() % WIDTH;
        int y = rand() % HEIGHT;
        if (board[y][x] != '*') {
            board[y][x] = '*';
            --mines;
        }
    }

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (board[i][j] != '*') {
                int mines_around = count_adjacent_mines(board, j, i);
                board[i][j] = mines_around + '0';
            }
        }
    }
}

/*
 * La siguiente funcion permite que se revele una celda
 * En caso de que la celda revelada no posea minas adyacentes, se revela de manera recursiva las celdas que estan cerca
 */
void reveal_cell(WINDOW *win, char board[HEIGHT][WIDTH], int revealed[HEIGHT][WIDTH], int x, int y) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT || revealed[y][x]) return;

    revealed[y][x] = 1;

    if (board[y][x] == '0') {
        reveal_cell(win, board, revealed, x - 1, y);
        reveal_cell(win, board, revealed, x + 1, y);
        reveal_cell(win, board, revealed, x, y - 1);
        reveal_cell(win, board, revealed, x, y + 1);
    }
}

// La siguiente funcion cumple que se marque o desmarque una celda como mina
void mark_mine(WINDOW *win, int marked[HEIGHT][WIDTH], int x, int y) {
    marked[y][x] = !marked[y][x];
}

/*
 * La siguiente funcion tiene como proposito que se verifique si la persona usuaria ha ganado
 * La condicion de victoria si todas las minas se marcaron correctamente y las celdas que no tienen minas fueron reveladas
 */
int check_victory(int revealed[HEIGHT][WIDTH], int marked[HEIGHT][WIDTH], char board[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if ((board[i][j] == '*' && !marked[i][j]) || (board[i][j] != '*' && !revealed[i][j])) {
                return 0;
            }
        }
    }
    return 1;
}

// La siguiente funcion hace un conteo de las minas cercanas a una celda en especifico
int count_adjacent_mines(char board[HEIGHT][WIDTH], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int nx = x + j;
            int ny = y + i;
            if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT && board[ny][nx] == '*') {
                ++count;
            }
        }
    }
    return count;
}

// Esta funcion genera en pantalla las instrucciones de juego para ayudar al usuario
void show_instructions() {
    clear();
    mvprintw(0, 0, "Instrucciones del Juego:");
    mvprintw(2, 0, "1. Usa las teclas de flecha para moverte.");
    mvprintw(3, 0, "2. Presiona 'r' para revelar una celda.");
    mvprintw(4, 0, "3. Presiona 'm' para marcar/desmarcar una mina.");
    mvprintw(5, 0, "4. Gana revelando todas las celdas que no sean minas.");
    mvprintw(6, 0, "5. Pierde si revelas una celda con una mina.");
    mvprintw(8, 0, "Presiona cualquier tecla para regresar al menú principal.");
    refresh();
    getch();
}
