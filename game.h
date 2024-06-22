#ifndef GAME_H
#define GAME_H

#define HEIGHT 10
#define WIDTH 10

void start_game(WINDOW *win);
void show_instructions(WINDOW *win);
void initialize_board(char board[HEIGHT][WIDTH], int revealed[HEIGHT][WIDTH], int mines);
void reveal_cell(int revealed[HEIGHT][WIDTH], int x, int y);  // Actualización de la firma
void draw_board(WINDOW *win, char board[HEIGHT][WIDTH], int revealed[HEIGHT][WIDTH], int cursor_x, int cursor_y);

#endif
