#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compras.h"

HashTable initCompras(HashTable ht)
{
	int Ncp = codigos_Produto();
/*	for(i=0;i<MAX_LETTERS;i++)
		a[i] = NULL; */
	ht = initHashTable(ht,2*Ncp);
	return ht;
}

void insertComprasCP(AAVL a,Comp compra,int* cresceu)
{
	insert(a[indexL(compra->codigo_produto)],compra,cresceu,Compras_Ord_CP);
}

HashTable insertComprasHashCP(HashTable ht,Comp compra,int* cresceu)
{
	AVL a = malloc(sizeof(struct avl_node));
	Comp casted;
	casted = a->info = malloc(sizeof(struct compras));
	casted->codigo_produto = malloc(10*sizeof(char));	
	casted->codigo_cliente = malloc(10*sizeof(char));	
	a->right = a->left = NULL;
	compracpy(a->info,compra);
	ht = insertHashTable(ht,a,cresceu);
	return ht;
}

void compracpy(Comp dest,Comp src){
	strcpy(dest->codigo_produto,src->codigo_produto);
	strcpy(dest->codigo_cliente,src->codigo_cliente);
        dest->preco = src->preco;
        dest->quantidade = src->quantidade;
        dest->tipo = src->tipo;
        dest->mes = src->mes;
}

int compracmpCC(Comp c1,Comp c2) {
        return (strncmp(c1->codigo_cliente,c2->codigo_cliente,5));
}

int compracmpCP(Comp c1,Comp c2) {
        return (strncmp(c1->codigo_produto,c2->codigo_produto,6));
}

