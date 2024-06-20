/*
 * Se incluye evitar duplicaciones y errores al compilar
 * Al incluirse por primera vez GAME_H en las siguientes veces no se incluira el contenido
 */ 
#ifndef GAME_H
#define GAME_H

// Proporciona lo necesario mediante funciones de control de pantalla
#include <ncurses.h>

// Estas dos constantes son para definir el tamano del tablero de juego
#define WIDTH 10
#define HEIGHT 10

/*
 * void start_game(WINDOW *win) es para iniciar el juego
 * win es un puntero hacia WINDOW de ncurses que sirve para la ventana en la terminal
 * void show_instructions(WINDOW *win) es para mostrar las instrucciones en la ventana win
 */
void start_game(WINDOW *win);
void show_instructions(WINDOW *win);

// Final del contenido protegido contra inclusion repetida
#endif
