CFLAGS= -ansi -Wall -pedantic -O2

avl: avl.c compras.c 
	gcc $(CFLAGS) -c avl.c  

catalogo_clientes: catalogo_clientes.c avl.c compras.c
	gcc $(CFLAGS) -c catalogo_clientes.c 

catalogo_produtos: catalogo_produtos.c avl.c compras.c
	gcc $(CFLAGS) -c catalogo_produtos.c 

compras: compras.c avl.c catalogo_produtos.c catalogo_clientes.c
	gcc $(CFLAGS) -c compras.c


contabilidade: avl.c compras.c catalogo_produtos.c catalogo_clientes.c
	gcc $(CFLAGS) -c contabilidade.c

leitura_aux: leitura_aux.c avl.c catalogo_clientes.c catalogo_produtos.c compras.c contabilidade.c
	gcc $(CFLAGS) -c leitura_aux.c avl.c catalogo_clientes.c catalogo_produtos.c compras.c contabilidade.c

leitura: leitura.o leitura_aux.o catalogo_clientes.o catalogo_produtos.o avl.o compras.o contabilidade.o
	gcc $(CFLAGS) -o leitura leitura.o leitura_aux.o avl.o catalogo_clientes.o catalogo_produtos.o compras.o contabilidade.o

all: avl.c leitura_aux.c leitura.c catalogo_clientes.c catalogo_produtos.c
	gcc $(CFLAGS) -o leitura avl.c leitura_aux.c leitura.c catalogo_clientes.c catalogo_produtos.c

clean:
	rm -f *.o
