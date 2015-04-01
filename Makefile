CFLAGS= -ansi -Wall -pedantic -O2
OBJS = avl.o compras.o catalogo_clientes.o catalogo_produtos.o leitura_aux.o contabilidade.o

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
	gcc $(CFLAGS) -c leitura_aux.c 


leitura: $(OBJS)
	gcc $(CFLAGS) leitura.c -o leitura $(OBJS)

all: avl.c leitura_aux.c leitura.c catalogo_clientes.c catalogo_produtos.c contabilidade.c compras.c
	make avl
	make catalogo_clientes
	make catalogo_produtos
	make compras
	make contabilidade
	make leitura_aux
	make leitura
clean:
	rm -f *.o
