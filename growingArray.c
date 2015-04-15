#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "growingArray.h"

/*Inicializa o GrowingArray*/
GrowingArray initGrowingArray(int max_size, int tipo) {
	GrowingArray novo=malloc(sizeof(struct growingarray));
	novo->size=0;
	novo->max_size=max_size;
	if(tipo==ArrayString) novo->Elems=calloc(max_size,sizeof(char *));
	else if(tipo==ArrayCompProduto) novo->Elems = calloc(max_size,sizeof(CompProduto));
	return novo;
}

/*Insere um novo CompProduto no GrowingArray*/
void insertGrowingArray(GrowingArray a, Objeto o, int tipo) {
	if(a->size==a->max_size) resizeGrowingArray(a,tipo);
	a->Elems[a->size]=o;
	a->size+=1;
}

/*Aumenta o tamanho do GrowingArray 1.5 vezes, caso este atinja o tamanho maximo*/
void resizeGrowingArray(GrowingArray a,int tipo) { 
	a->max_size*=1.5; 
	a->Elems=realloc(a->Elems, a->max_size);
}
	


