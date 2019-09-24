all: main.o ds_memory.o
	gcc -Wall -ansi -pedantic main.o ds_memory.o -o a1

main.o: main.c
	gcc -Wall -ansi -pedantic -c main.c -o main.o

ds_memory.o: ds_memory.c ds_memory.h
	gcc -Wall -ansi -pedantic -c ds_memory.c -o ds_memory.o
