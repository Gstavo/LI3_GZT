CFLAGS= -ansi -Wall -pedantic -O2 
OBJS = avl.o heap.o compras.o catalogo_clientes.o catalogo_produtos.o contabilidade.o leitura.o main.o growingArray.o

gesthip: $(OBJS)
	gcc $(OBJS) -o gesthip
	make clean

growingArray: growingArray.c 
	gcc $(CFLAGS) -c growingArray.c

avl: avl.c compras.h  growingArray.h
	gcc $(CFLAGS) -c avl.c  

heap: heap.c compras.h
	gcc $(CFLAGS) -c heap.c


catalogo_clientes: catalogo_clientes.c avl.h compras.h growingArray.h
	gcc $(CFLAGS) -c catalogo_clientes.c 

catalogo_produtos: catalogo_produtos.c avl.h compras.h growingArray.h
	gcc $(CFLAGS) -c catalogo_produtos.c 

compras: compras.c avl.h heap.h catalogo_produtos.h catalogo_clientes.h
	gcc $(CFLAGS) -c compras.c


contabilidade: contabilidade.c avl.h compras.h catalogo_produtos.h catalogo_clientes.h
	gcc $(CFLAGS) -c contabilidade.c

leitura: leitura.c catalogo_produtos.h catalogo_clientes.h compras.h contabilidade.h
	gcc $(CFLAGS) -c leitura.c

main : main.c leitura.h 
	gcc $(CFLAGS) -c main.c 


clean:
	rm -f *.o

cleanall:
	rm -f *.o
	rm -f *.csv
	rm compras_cliente.txt
