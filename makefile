#Primeramente se define el compilador (gcc)
# Luego se definen las opciones del compilador
#Se habilitan todas las alertas, advertecias, se especifica que se quiere usar C11 y  se enlaza la biblioteca ncurses
#Se define el nombre del ejecutable
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -lncurses
TARGET = buscaminas

#Se define que all es dependiente de $(TARGET)
all: $(TARGET)

#Primeramente se define la dependencia a los objetos main.o y game.o
#Luego se hace linking y compila los archivos game.o y main.o para crear el ejecutable
#Seguidamente se define que main.o es dependiente de game.h y main.c y se compila main.c en el archivo object main.o
#Las reglas establecidas para game.o incluye primero una definicion del propio archivo objeto que depende de game.c y game.h
#Luego se compila game.c en game.o
#clean no tiene dependencias por lo que se ejecuta al utilizar makeclean
#Se eliminan los archivos *.o y el ejecutable (buscaminas)

$(TARGET): main.o game.o
    $(CC) -o $(TARGET) main.o game.o $(CFLAGS)

main.o: main.c game.h
    $(CC) -c main.c $(CFLAGS)

game.o: game.c game.h
    $(CC) -c game.c $(CFLAGS)

clean:
    rm -f *.o $(TARGET)
