#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

void start_game(WINDOW *win) {
    int x = 0, y = 0;
    int ch;
    char board[HEIGHT][WIDTH];
    int revealed[HEIGHT][WIDTH] = {0};
    int mines = 10;
    int game_over = 0;
    initialize_board(board, revealed, mines);

    clear();
    refresh();
    wclear(win);
    wrefresh(win);

    mvprintw(LINES - 2, 0, "Usa las flechas para moverte. Presiona espacio para revelar una celda. Presiona 'q' para salir.");
    refresh();

    while ((ch = wgetch(win)) != 'q' && !game_over) {
        switch (ch) {
            case KEY_UP:
                if (y > 0) y--;
                break;
            case KEY_DOWN:
                if (y < HEIGHT - 1) y++;
                break;
            case KEY_LEFT:
                if (x > 0) x--;
                break;
            case KEY_RIGHT:
                if (x < WIDTH - 1) x++;
                break;
            case ' ':
                if (board[y][x] == 'M') {
                    game_over = 1;
                    reveal_cell(revealed, x, y);
                    mvprintw(LINES - 3, 0, "Game Over! Has revelado una mina.");
                    refresh();
                } else {
                    reveal_cell(revealed, x, y);
                }
                break;
        }
        wclear(win);
        draw_board(win, board, revealed, x, y);
    }

    if (game_over) {
        mvprintw(LINES - 3, 0, "Game Over! Has revelado una mina.");
        refresh();
        wgetch(win);
    }

    wclear(win);
    mvwprintw(win, HEIGHT / 2, (WIDTH * 3) / 2 - 6, "Game Over!");
    wrefresh(win);
    wgetch(win);
}

void show_instructions(WINDOW *win) {
    int startx = 2, starty = 2;
    wclear(win);
    mvwprintw(win, starty, startx, "Instrucciones:");
    mvwprintw(win, starty + 2, startx, "Usa las flechas para moverte.");
    mvwprintw(win, starty + 3, startx, "Presiona espacio para revelar una celda.");
    mvwprintw(win, starty + 4, startx, "Presiona 'q' para salir.");
    wrefresh(win);
    wgetch(win);
}

void initialize_board(char board[HEIGHT][WIDTH], int revealed[HEIGHT][WIDTH], int mines) {
    srand(time(NULL));
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            board[i][j] = '0';
            revealed[i][j] = 0;
        }
    }

    for (int i = 0; i < mines; ++i) {
        int x, y;
        do {
            x = rand() % WIDTH;
            y = rand() % HEIGHT;
        } while (board[y][x] == 'M');
        board[y][x] = 'M';
    }
}

void reveal_cell(int revealed[HEIGHT][WIDTH], int x, int y) {  // Actualización de la firma
    if (revealed[y][x] == 1) return;
    revealed[y][x] = 1;
    // Aquí iría la lógica adicional para revelar las celdas adyacentes
}

void draw_board(WINDOW *win, char board[HEIGHT][WIDTH], int revealed[HEIGHT][WIDTH], int cursor_x, int cursor_y) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (i == cursor_y && j == cursor_x) {
                wattron(win, A_REVERSE); // Resaltar la posición del cursor
            }
            if (revealed[i][j]) {
                mvwprintw(win, i, j * 3, "%c", board[i][j]);  // Ajuste del espaciado
            } else {
                mvwprintw(win, i, j * 3, "#");  // Ajuste del espaciado
            }
            wattroff(win, A_REVERSE);
        }
    }
    wmove(win, cursor_y, cursor_x * 3);  // Ajuste del espaciado
    wrefresh(win);
} 
