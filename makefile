CC = gcc
CFLAGS = -Wall -std=c99
LIBS = -lncurses

all: buscaminas

buscaminas: main.o buscaminas.o
	$(CC) $(CFLAGS) -o buscaminas main.o buscaminas.o $(LIBS)

main.o: main.c buscaminas.h
	$(CC) $(CFLAGS) -c main.c $(LIBS)

buscaminas.o: buscaminas.c buscaminas.h
	$(CC) $(CFLAGS) -c buscaminas.c $(LIBS)

clean:
	rm -f *.o buscaminas
