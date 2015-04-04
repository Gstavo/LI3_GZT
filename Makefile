CFLAGS= -ansi -Wall -pedantic -O2 
OBJS = avl.o hashtable.o compras.o catalogo_clientes.o catalogo_produtos.o contabilidade.o leitura.o 

avl: avl.c compras.c 
	gcc $(CFLAGS) -c avl.c  

hashtable: avl.c compras.c hashtable.c
	gcc $(CFLAGS) -c hashtable.c

catalogo_clientes: catalogo_clientes.c avl.c compras.c
	gcc $(CFLAGS) -c catalogo_clientes.c 

catalogo_produtos: catalogo_produtos.c avl.c compras.c
	gcc $(CFLAGS) -c catalogo_produtos.c 


compras: compras.c avl.c catalogo_produtos.c catalogo_clientes.c
	gcc $(CFLAGS) -c compras.c


contabilidade: avl.c compras.c catalogo_produtos.c catalogo_clientes.c
	gcc $(CFLAGS) -c contabilidade.c

leitura: avl.c compras.c catalogo_produtos.c catalogo_clientes.c compras.c hashtable.c contabilidade.c
	gcc $(CFLAGS) -c leitura.c

main : $(OBJS)
	gcc $(CFLAGS) main.c -o main $(OBJS)

all: avl.c leitura.c catalogo_clientes.c catalogo_produtos.c contabilidade.c compras.c hashtable.c main.c
	make avl
	make hashtable
	make catalogo_clientes
	make catalogo_produtos
	make compras
	make contabilidade
	make leitura
	make main
clean:
	rm -f *.o
