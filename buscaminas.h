#ifndef BUSCAMINAS_H
#define BUSCAMINAS_H

#include <ncurses.h>

void inicializar_tablero();
void colocar_minas();
void mostrar_tablero();
void descubrir_casilla(int fila, int columna);
void iniciar_juego();
void mostrar_instrucciones();
void print_menu(WINDOW *menu_win, int highlight);

#endif /* BUSCAMINAS_H */
