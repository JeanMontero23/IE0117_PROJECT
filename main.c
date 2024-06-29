/*
 * Se incluyen las librerias estandar y ncurses para poder crear una interfaz grafica
 * Tambien se define la altura y ancho del menu
 */
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "buscaminas.h"

#define MENU_HEIGHT 7
#define MENU_WIDTH 40

// Se declara la funcion main_menu
void main_menu();

/*
 * Se desarrolla la propia funcion main
 * Primeramente se inica ncurses
 * Se limpia la pantalla
 * Se desactiva el eco de los caracteres
 * Se establece el modo de "entrada sin buffer"
 * Seguidamente se llama main_menu y se cierra ncurses
 */
int main() {
    initscr();
    clear();
    noecho();
    cbreak();

    main_menu();

    endwin();
    return 0;
}

/*
 * Se crea una ventana nueva para el menu
 * Se activa el uso del teclado para que se puedan captar las flechas y otras teclas que se necesitan para el juego
 */
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

    /*
     * Se establece un bucle principal para el menu
     * Se muestra el menu al usuario y se espera a que elija algun opcion con el uso de las flechas y enter
     * Considerando la eleccion del usuario se llama a iniciar_juego, mostrar_instrucciones o sale del bucle para terminar el programa
     */
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
