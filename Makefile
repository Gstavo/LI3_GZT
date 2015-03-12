CFLAGS= -ansi -Wall -pedantic -O2

leitura: leitura.o leitura_aux.o
	gcc $(CFLAGS) -o leitura leitura.o leitura_aux.o

clean:
	rm -f *.o
