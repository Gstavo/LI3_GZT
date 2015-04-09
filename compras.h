
#ifndef COMPRAS_H

#define COMPRAS_H

#include "hashtable.h"
#include "avl.h"
#include "catalogo_clientes.h"
#include "catalogo_produtos.h"
#include "boolean.h"

typedef struct compras{
	char* codigo_produto;
	double preco;
	int quantidade;
	char tipo;
	char* codigo_cliente;
	int mes;
}Compras;

typedef struct compras* Comp;

Comp initCompra();
HashTable initHashCompras();

HashTable insertComprasHashCP(HashTable ht,Comp compra,int* cresceu);

void insertComprasCP(AAVL a,Comp compra,int* cresceu);

void compracpy(Comp dest,Comp src);

BOOLEAN compracmpCC(Comp c1,Comp c2);

BOOLEAN compracmpCP(Comp c1,Comp c2);

#endif
