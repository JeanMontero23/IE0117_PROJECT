# Se define el compilador, en este caso es gcc
# CFLAGS tiene las opciones del compilador: -wall que tiene todas las advertencias del compilador y -std=c99 que especifica que se usa estandar C99
# Se definen las bibliotecas necesarias, en este caso es -lncurses para hacer la biblioteca ncurses
CC = gcc
CFLAGS = -Wall -std=c99
LIBS = -lncurses

# Se rige la regla principal, esto indica que el objetivo por defecto es contruir el ejecutable buscaminas. Por esto, al invocar el make sin ningun argumento esta es la regla que se prodera a ejecutar
all: buscaminas

# Esta regla indica como contruir el ejecutable buscaminas, con ayuda de los archivos objeto main.o y buscaminas.o
# $(CC) es el compilador
# Para -o buscaminas va a especificar el nombre del archivo de salida
# En el caso de main.o y buscaminas.o son los archivos objeto para crear el ejecutable
# $(LIBS) se añade para incluir la biblioteca ncurses durante la fase de enlae
buscaminas: main.o buscaminas.o
	$(CC) -o buscaminas main.o buscaminas.o $(LIBS)

# Esta regla inidca como compilar main.c en main.o
# Recordar que hay dependecia de main.o por parte de main.c y buscaminas.h
# El uso de $(CFLAGS) es para contener las opciones del compilador
# -c main.c va a indicar que el compilador debe generar un archivo objeto main.o usando el main.c
main.o: main.c buscaminas.h
	$(CC) $(CFLAGS) -c main.c

# Esta regla es para compilar buscaminas.c en buscaminas.o
# Primeramente se define que buscaminas.o depende de buscaminas.c y buscaminas.h
# $(CFLAGS) contiene las opciones del compilador
# Con -c buscaminas.c se indica que el compilador debe generar un archivo objeto buscaminas.o a partir de buscaminas.c
buscaminas.o: buscaminas.c buscaminas.h
	$(CC) $(CFLAGS) -c buscaminas.c

# Con el uso de rm -f *.o se eliminan todos los archivos objeto (*.o)
# Ademas con el uso de rm -f buscaminas elimina el ejecutable buscaminas
clean:
	rm -f *.o buscaminas
