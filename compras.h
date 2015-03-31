
#ifndef COMPRAS_H

#define COMPRAS_H

#include "avl.h"
#include "catalogo_clientes.h"
#include "catalogo_produtos.h"

typedef struct compras{
	char codigo_produto[10];
	double preco;
	int quantidade;
	char tipo;
	char codigo_cliente[10];
	int mes;
}Compras;

typedef struct Compras* Comp;

void initCompras(AAVL a);

void insertComprasCP(AAVL a,Comp compra,int* cresceu);

void compracpy(Comp dest,Comp src);

int compracmpCC(Comp c1,Comp c2);

int compracmpCP(Comp c1,Comp c2);

#endif
