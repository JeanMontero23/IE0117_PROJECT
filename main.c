/*
 * Se incluyen los headers necesarios
 * ncurses.h es necesario para tener funciones que brindan interfases de usuario en modo de texto
 * game.h va a tener las declaraciones de las funciones que va a tener un archivo game.c
 */
#include <ncurses.h>
#include "game.h"

/*
 * Para comenzar, se busca hacer una especie de prototipo de las funciones y variables globales
 * void print_menu(WINDOW *menu_win, int highlight) funciona para imprimir el menu en la pantalla
 * char *choices es un array que contiene las opcione del menu
 * nt n_choices tiene como objetivo el calculo de las opciones del menu
 * Para lograr lo anterior, se divide el tamano total del array mencionado entre un puntero a char
 */
void print_menu(WINDOW *menu_win, int highlight);

char *choices[] = {
    "Iniciar Juego",
    "Instrucciones",
    "Salir",
};

int n_choices = sizeof(choices) / sizeof(char *);

/*
 * La funcion principal va a inicializar ncourses
 * Trae consigo varias funciones
 * initscr va a iniciar la pantalla para ncourses
 * clear es para limpiar la pantalla
 * noecho es para que no haya eco en las teclas presionadas
 * cbreak es para pasar a un cbreak mode (o desactivar modo de linea)
 * curs_set sirve para que no se vea el cursor
 */
int main() {
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);

    //Aqui se define el tamano y posicion de la ventana en el menu
    int height = 10, width = 40, starty = (LINES - height) / 2, startx = (COLS - width) / 2;

    /*
     * newwin crea una ventana a partir de los datos anteriores
     * keypad hace que se habilite el teclado para poder usar las flechas en la ventana que se abre
     * mvprintw muestra un mensaje de ayuda para que el usuario sepa como moverse en la ventana generada
     * refresh hace que se refresque la pantalla para que se vean los cambios
     */
    WINDOW *menu_win = newwin(height, width, starty, startx);
    keypad(menu_win, TRUE);
    mvprintw(0, 0, "Usa las flechas para moverte, Enter para seleccionar");
    refresh();
    
    /*
     * highlight sirve para resaltar la opcion que esta siendo seleccionada
     * choice almancena la opcion que fue elegida por la persona usuaria
     * c es para almacenar la techa que presiono el usuario
     */
    int highlight = 1;
    int choice = 0;
    int c;

    /*
     * Primero se necesita llamar a print_menu para que se dibuje el menu con la opcion resaltada
     * wgetch es para que esperar a que el usuario presiona alguna tecla
     * switch es para que se procese la tecla que ingresa el usuario
     * En switch, con KEY_UP si se presiona la flecha hacia arriba el resultado va a cambiar hacia arriba 
     * En switch, con KEY_DOWN si se presiona la flecha hacia abajo el resultado se va a cambiar hacia abajo
     * En switch, con 10 sirve para que se almacene la opcion seleccionada en choice cuando se presiona enter
     * Cuando choice es distinto de 0 se sale del bucle
     */
    while (1) {
        print_menu(menu_win, highlight);
        c = wgetch(menu_win);
        switch (c) {
            case KEY_UP:
                if (highlight == 1)
                    highlight = n_choices;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if (highlight == n_choices)
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10: // Enter key
                choice = highlight;
                break;
            default:
                break;
        }
        if (choice != 0) // Si se seleccionó una opción
            break;
    }

    /*
     * Ahora hay que tratar con la opcion que fue seleccionada por la persona usuaria, para eso se quiere usar switch(choice)
     * En el primer caso, se llama start_game para que inicie el juego
     * En el caso dos, se trata es con la funcion show_instructions para que se vean las instrucciones
     * En el ultimo caso, se termina la ejecucion del programa y se cierra ncurses
     */
    switch (choice) {
        case 1:
            // Llama a la función que inicia el juego
            start_game(menu_win);
            break;
        case 2:
            // Muestra las instrucciones
            show_instructions(menu_win);
            break;
        case 3:
            // Salir
            endwin();
            return 0;
    }

    //Esta parte es para que se finalice ncurses y la terminal se restaure; ademas que se termina el programa de manera exitosa
    endwin();
    return 0;
}

/*
 * box(menu_win, 0, 0) sirve para crear un borde en la ventana del menu
 * Se hace un recorrido en las opciones del menu y se imprime la ventana
 * En el caso de que la opcion este resaltada "highlight" se va a activar A_REVERSE antes que se imprima y luego se desactiva
 * Para ver los cambios en el menu, se refresca la ventana con wrefresh(menu_win)
 */
void print_menu(WINDOW *menu_win, int highlight) {
    int x = 2, y = 2;
    box(menu_win, 0, 0);
    for (int i = 0; i < n_choices; ++i) {
        if (highlight == i + 1) {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        } else
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        ++y;
    }
    wrefresh(menu_win);
}

/*
 * Este codigo deberia de crear un menu en el que pueda interacturar el usuario
 * Deberian de desplegarse las opciones de iniciar el juego, mostrar las instrucciones del juego y salir del programa
 */
