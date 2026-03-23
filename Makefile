CC = gcc
CFLAGS = -Wall -Wextra

all: rate edf

rate: main.c escalonador.c
	$(CC) $(CFLAGS) main.c escalonador.c -o rate

edf: main.c escalonador.c
	$(CC) $(CFLAGS) -D ALGO_EDF main.c escalonador.c -o edf

clean:
	rm -f rate edf *.out
