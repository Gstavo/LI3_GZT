CFLAGS= -ansi -Wall -pedantic -O2

avl: avl.c 
	gcc $(CFLAGS) -c avl.c 

leitura_aux: leitura_aux.c 
	gcc $(CFLAGS) -c leitura_aux.c 

leitura: leitura.o leitura_aux.o
	gcc $(CFLAGS) -o leitura leitura.o leitura_aux.o avl.o

clean:
	rm -f *.o
