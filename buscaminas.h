// Se hace una proteccion para evitar la inclusion multiple
#ifndef BUSCAMINAS_H
#define BUSCAMINAS_H

// Se declaran las funciones utilizadas en buscaminas.c
void iniciar_juego();
void mostrar_instrucciones();
void print_menu(WINDOW *menu_win, int highlight);

// Se cierra la proteccion, esto asegura que el contenido del archivo solo se incluya una vez por compilacion
#endif
