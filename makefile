CC = gcc
CFLAGS = -Wall -std=c99
LIBS = -lncurses

all: buscaminas

buscaminas: main.o buscaminas.o
	$(CC) -o buscaminas main.o buscaminas.o $(LIBS)

main.o: main.c buscaminas.h
	$(CC) $(CFLAGS) -c main.c

buscaminas.o: buscaminas.c buscaminas.h
	$(CC) $(CFLAGS) -c buscaminas.c

clean:
	rm -f *.o buscaminas
