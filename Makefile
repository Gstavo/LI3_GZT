CFLAGS= -ansi -Wall -pedantic -O2 
OBJS = avl.o hashtable.o compras.o catalogo_clientes.o catalogo_produtos.o contabilidade.o leitura.o main.o

avl: avl.c avl.h compras.h  
	gcc $(CFLAGS) -c avl.c  

hashtable: hashtable.c avl.h compras.h 
	gcc $(CFLAGS) -c hashtable.c

catalogo_clientes: catalogo_clientes.c avl.h compras.h
	gcc $(CFLAGS) -c catalogo_clientes.c 

catalogo_produtos: catalogo_produtos.c avl.h compras.h
	gcc $(CFLAGS) -c catalogo_produtos.c 


compras: compras.c avl.h catalogo_produtos.h catalogo_clientes.h
	gcc $(CFLAGS) -c compras.c


contabilidade: contabilidade.c avl.h compras.h catalogo_produtos.h catalogo_clientes.h
	gcc $(CFLAGS) -c contabilidade.c

leitura: leitura.c compras.h catalogo_produtos.h catalogo_clientes.h compras.h hashtable.h contabilidade.h
	gcc $(CFLAGS) -c leitura.c

main : main.c leitura.h compras.h catalogo_produtos.h catalogo_clientes.h compras.h hashtable.h contabilidade.h
	gcc $(CFLAGS) -c main.c 

gesthip: $(OBJS)
	gcc $(OBJS) -o gesthip

all: avl.c leitura.c catalogo_clientes.c catalogo_produtos.c contabilidade.c compras.c hashtable.c main.c
	make avl
	make hashtable
	make catalogo_clientes
	make catalogo_produtos
	make compras
	make contabilidade
	make leitura
	make main
	make gesthip
clean:
	rm -f *.o
