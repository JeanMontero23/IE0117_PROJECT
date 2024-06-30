# Objetivo del proyecto

Este proyecto busca implementar el juego clasico de buscaminas en C con ayuda de la biblioteca ncurses para desarrollar una interfaz de usuario por medio del uso de terminal.

## Descripcion del juego

El juego buscaminas es un juego de logica que tiene como objetivo descubrir todas las casillas que no tengan minas de un tablero con determinadas dimensiones. Algunas casillas tienen numeros que indican la cantidad de minas adyacentes a la propia casilla seleccionada. El usuario debe marcar las casillas donde cree que hay minas con una bandera.

## Caracteristicas

- Se despliega un tablero de juego con casillas ocultas.
- Posee la capacidad para marcar casillas con banderas.
- Existe una interfaz de usuario en terminal utilizando ncurses.

## Requisitos

Para compilar y ejecutar este proyecto, se necesitan tener instalados los siguientes componentes:

- Un compilador de C (la persona autora hace uso de gcc).
- La biblioteca ncurses.

## Instrucciones de instalacion

1. Primeramente se clona el repositorio en la maquina local.
    ```sh
    git clone https://github.com/tuusuario/buscaminas.git
    ```
2. Seguidamente se navega al directorio donde se ubica el proyecto.
    ```sh
    cd buscaminas
    ```
3. Por ultimo se compila el proyecto utilizando make.
    ```sh
    make
    ```

## Instrucciones de uso del programa

1. Se ejecuta el programa.
    ```sh
    ./buscaminas
    ```
2. Cuando se ingrese al menu principal se utilizan las flechas del teclado para seleccionar una opcion, luego se presiona `Enter`.
    - **Iniciar Juego**: Se comienza una nueva partida del juego.
    - **Instrucciones**: Se muestran las instrucciones del juego.
    - **Salir del Juego**: Se sale del programa.

### Controles del juego

- Se hace uso de las flechas del teclado para moverse por el tablero.
- Presione `Enter` para descubrir una casilla.
- Presione `F` para marcar una casilla con una bandera.
- Presione `Q` para regresar al menu principal.

## Instrucciones del juego

1. El objetivo del juego es descubrir todas las casillas que no contengan minas.
2. Las casillas que contienen numeros indican cuantas minas adyacentes hay.
3. Se puede dejar una marca en las casillas donde se crea que hay minas mediante el uso de una bandera (`F`).

## Limpieza de los archivos

Para limpiar los archivos generados durante la compilacion y asi mantener un mayor orden se utiliza el siguiente comando:
```sh
make clean
