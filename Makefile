#makefile
#Riesenie UJC-DU1, 16.3.2014
#Autor: Jan Profant, FIT
#Prelozene: gcc 4.8.1

CC=gcc
CFLAGS=-std=c99 -pedantic -g -Wall -Wextra -lm -O2
INLINE=-DUSE_INLINE


all: prvocisla steg-decode prvocisla-inline

error.o: error.c error.h
	$(CC) $(CFLAGS) -c $<

bit-array.o: bit-array.c bit-array.h
	$(CC) $(CFLAGS) -c $<

bit-array-inline.o: bit-array.c bit-array.h
	$(CC) $(INLINE) $(CFLAGS) -c $< -o bit-array-inline.o

eratosthenes-inline.o: eratosthenes.c eratosthenes.h
	$(CC) $(INLINE) $(CFLAGS) -c $< -o eratosthenes-inline.o

eratosthenes.o: eratosthenes.c eratosthenes.h
	$(CC) $(CFLAGS) -c $< -lm

prvocisla.o: prvocisla.c
	$(CC) $(CFLAGS) -c $<

prvocisla-inline.o: prvocisla.c
	$(CC) $(INLINE) $(CFLAGS) -o prvocisla-inline.o -c prvocisla.c

steg-decode.o: steg-decode.c
	$(CC) $(CFLAGS) -c $<

ppm.o: ppm.c ppm.h
	$(CC) $(CFLAGS) -c $<

prvocisla: prvocisla.o bit-array.o error.o eratosthenes.o
	$(CC) $(CFLAGS) -o $@ prvocisla.o bit-array.o error.o eratosthenes.o -lm

prvocisla-inline: prvocisla-inline.o  error.o eratosthenes-inline.o bit-array-inline.o
	$(CC) $(INLINE) $(CFLAGS) -o $@ prvocisla-inline.o bit-array-inline.o error.o eratosthenes-inline.o -lm

steg-decode: steg-decode.o error.o bit-array.o ppm.o eratosthenes.o
	$(CC) $(CFLAGS) -o $@ steg-decode.o error.o bit-array.o ppm.o eratosthenes.o -lm
