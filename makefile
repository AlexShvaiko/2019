myprog: read.o symtab.o asembler.o dc.o	readb.o 											
	gcc -g -Wall -pedantic -ansi read.o symtab.o dc.o readb.o asembler.o -lm -o myprog
read.o: read.c	read.h
	gcc -c -Wall -pedantic -ansi read.c -o read.o
symtab.o: symtab.c symtab.h	
	gcc -c -Wall -pedantic -ansi symtab.c -o symtab.o
asembler.o: asembler.c asembler.h
	gcc -c -Wall -pedantic -ansi asembler.c -o asembler.o
dc.o: dc.c
	gcc -c -Wall -pedantic -ansi dc.c -o dc.o	
readb.o: readb.c	
	gcc -c -Wall -pedantic -ansi readb.c -o readb.o
   
