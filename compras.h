
#ifndef COMPRAS_H

#define COMPRAS_H



typedef struct compras{
	char* codigo_produto;
	double preco;
	int quantidade;
	char tipo;
	char* codigo_cliente;
	int mes;
}Compras;

typedef struct compras* Comp;

#include "avl.h"
#include "hashtable.h"
#include "heap.h"
#include "catalogo_clientes.h"
#include "catalogo_produtos.h"

Comp initCompra();

HashTable initHashCompras();

Heap* initHeap(HashTable ht);
/*
HashTable insertComprasHashCP(HashTable ht,Comp compra);
*/
void insertComprasCP(AAVL a,Comp compra,int* cresceu);

CpInfoList query8(HashTable ht,char* cp);

void compracpy(Comp dest,Comp src);

int compracmpCC(Comp c1,Comp c2);

int compracmpCP(Comp c1,Comp c2);

#endif
