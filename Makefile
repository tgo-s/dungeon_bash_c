all: exercicio
exercicio: main.o
	gcc -o exercicio main.o
main.o: main.c
	gcc -o main.o -c main.c -W -Wall -ansi -pedantic
clean:
	rm -rf *.o
mrpropper: clean
	rm -rf exercicio