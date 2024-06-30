# Objetivo del proyecto

Este proyecto busca implementar el juego clasico de Buscaminas en C con ayuda de la biblioteca ncurses para poder desarrollar una interfaz de usuario por medio del uso de terminal.

## Descripcion del juego

El juego buscaminas es un juego de logicaque tiene como objetivo descubrir todas las casillas de un tablero que no contienen minas. Algunas casillas tienen numeros que indican la cantidad de minas adyacente a la propia casilla seleccionada. El usuario puede marcar las casillas donde cree que hay minas con una bandera.

## Caracteristicas

- Se deslpiega un tablero de juego con casillas ocultas
- Posee la capacidad para marcar casillas con banderas
- Existe una interfaz de usuario en terminal utilizando ncurses

## Requisitos

Para compilar y ejecutar este proyecto, se necesita tener instalados los siguientes componentes:

- Un compilador de C (la persona autora hace uso de gcc)
- La biblioteca ncurses

## Instrucciones de Instalación(Nota: sh indica que el bloque contiene comandos de shell)

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
2. Cuando se ingrese al menú principal,se utilizan las flechas del teclado para seleccionar una opción y presiona `Enter`.
    - **Iniciar Juego**: Se comienza una nueva partida del juego.
    - **Instrucciones**: Se muestran las instrucciones del juego.
    - **Salir del Juego**: Se sale del programa.

### Controles del juego

- Se hace uso de las flechas del teclado para moverse por el tablero.
- Presione `Enter` para descubrir una casilla.
- Presione `F` para marcar una casilla con una bandera.
- Presione `Q` para regresar al menú principal.

## Instrucciones del juego

1. El objetivo del juego es descubrir todas las casillas que no contengan minas.
2. Las casillas que contienen números indican cuántas minas adyacentes hay.
3. Se puede dejar una marca en las casillas donde crees que hay minas con una bandera (`F`).

## Limpieza de los archivos

Para limpiar los archivos generados durante la compilacion y asi mantener un mayor orden se utiliza el siguiente comando:
```sh
make clean
