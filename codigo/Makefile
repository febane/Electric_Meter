all: energie
	
listas: listas.c
	gcc -std=c99 -c listas.c
	
leitura: leitura.c
	gcc -std=c99 -c leitura.c
	
main: main.c
	gcc -std=c99 -c main.c
	
energie: listas.o leitura.o main.o
	gcc -std=c99 -o energie listas.o leitura.o main.o

clear: 
	rm listas.o leitura.o main.o energie saida.txt

