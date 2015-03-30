#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compras.h"

void initCompras(AAVL a)
{
	int i;
	for(i=0;i<MAX_LETTERS;i++)
		a[i] = NULL;
}

void insertComprasCP(AAVL a,Comp compra,int* cresceu)
{
	insert(a,compra,cresceu,Compras_Ord_CP);
}


void compracpy(Comp dest,Comp src){
        dest->codigo_produto = strdup(src->codigo_produto);
        dest->preco = src->preco;
        dest->quantidade = src->unidades_compradas;
        dest->tipo = src->tipo;
        dest->codigo_cliente = strdup(src->codigo_cliente);
        dest->mes_compra = src->mes;
}

int compracmpCC(Comp c1,Comp c2) {
        return strncmp(c1->codigo_cliente,c2->codigo_cliente,5);
}

int compracmpCP(Comp c1,Comp c2) {
        return strncmp(c1->codigo_produto,c2->codigo_produto,6);
}

