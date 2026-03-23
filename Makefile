
CC = gcc
CFLAGS = -Wall -Wextra

all: rate edf

rate: main.c
	$(CC) $(CFLAGS) main.c -o rate

edf: main.c
	$(CC) $(CFLAGS) -D ALGO_EDF main.c -o edf

clean:
	rm -f rate edf *.out
