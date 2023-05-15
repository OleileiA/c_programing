main: main.o test.o
	gcc main.o test.o -o main

main.o: main.c
	gcc -E main.c -o main.i
	gcc -S main.i -o main.s
	gcc -c main.s -o main.o

test.o: test.c
	gcc -E test.c -o test.i
	gcc -S test.i -o test.s
	gcc -c test.s -o test.o