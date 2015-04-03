
#ifndef COMPRAS_H

#define COMPRAS_H

#include "hashtable.h"
#include "avl.h"
#include "catalogo_clientes.h"
#include "catalogo_produtos.h"

typedef struct compras{
	char* codigo_produto;
	double preco;
	int quantidade;
	char tipo;
	char* codigo_cliente;
	int mes;
}Compras;

typedef struct compras* Comp;

void initCompras(HashTable ht);

void insertComprasHashCP(HashTable ht,Comp compra,int* cresceu);

void insertComprasCP(AAVL a,Comp compra,int* cresceu);

void compracpy(Comp dest,Comp src);

int compracmpCC(Comp c1,Comp c2);

int compracmpCP(Comp c1,Comp c2);

#endif
