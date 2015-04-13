#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compras.h"

#define N_Codigos_Produto 200000

Comp initCompra() {
	Comp compra=malloc(sizeof(struct compras));
	compra->codigo_produto = malloc(10*sizeof(char));
	compra->codigo_cliente = malloc(10*sizeof(char));
	return compra;
}

HashTable initHashCompras() {
	HashTable ht=initHashTable(4*N_Codigos_Produto);
	return ht;
}

Heap* initHeap(HashTable ht){
	int i;
	Heap* h = newHeap( ht->size );
	for(i = 0; i < ht->max_size ; i++)
		if(ht->table[i]) insertHeap(h,ht->table[i]);
	heapSort(h->values,h->used);
	return h;
}

void insertComprasCP(AAVL a,Comp compra,int* cresceu)
{
	insert(a[indexL(compra->codigo_produto)],compra,cresceu,Compras_Ord_CP);
}
/*
HashTable insertComprasHashCP(HashTable ht,Comp compra)
{
	ht = insertHashTable(ht,compra);
	return ht;
}
*/

/*
	Query 8: show lista de CC distiguindo N/P
		de um dado CP
*/

CpInfoList query8(HashTable ht,char* cp){
	CpInfo cpinfo = searchHash(ht,cp);
	if(!cpinfo) return NULL;
	return cpinfo->first;			
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

