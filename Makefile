CFLAGS= -ansi -Wall -pedantic -O2

avl: avl.c 
	gcc $(CFLAGS) -c avl.c 

catalogo_clientes: catalogo_clientes.c avl.c
	gcc $(CFLAGS) -c catalogo_clientes.c avl.c

catalogo_produtos: catalogo_produtos.c avl.c
	gcc $(CFLAGS) -c catalogo_produtos.c avl.c

leitura_aux: leitura_aux.c 
	gcc $(CFLAGS) -c leitura_aux.c 

leitura: leitura.o leitura_aux.o
	gcc $(CFLAGS) -o leitura leitura.o leitura_aux.o avl.o

all: avl.c leitura_aux.c leitura.c catalogo_clientes.c catalogo_produtos.c
	gcc $(CFLAGS) -o leitura avl.c leitura_aux.c leitura.c catalogo_clientes.c catalogo_produtos.c

clean:
	rm -f *.o
