CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -lncurses

all: buscaminas

buscaminas: main.o game.o
	$(CC) main.o game.o -o buscaminas $(CFLAGS)

main.o: main.c game.h
	$(CC) -c main.c $(CFLAGS)

game.o: game.c game.h
	$(CC) -c game.c $(CFLAGS)

clean:
	rm -f *.o buscaminas
