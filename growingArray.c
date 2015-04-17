#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
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
	if(a->size==a->max_size) 
		{
			a->max_size*=1.5; 
			a->Elems=realloc(a->Elems,sizeof(void*) *  a->max_size);
		}	
	a->Elems[a->size]=o;
	a->size+=1;
}
	

/*
void ordenaGrowingArray(GrowingArray a,int tipo){
	int i;
	GrowingArray aux=initGrowingArray(200000, ArrayCompProduto);
	if(tipo==ArrayCompProduto){
		for(i=0;i+1<a->size;i++){
			CompProduto o=(CompProduto) aux->Elems[i];
			CompProduto p=(CompProduto) a->Elems[i];
			CompProduto q=(CompProduto) a->Elems[i+1];
			if((p->quantidade)>(q->quantidade)){
				o->quantidade =p->quantidade;
				p->quantidade = q->quantidade;
				q->quantidade = o->quantidade;
			}
		}
	}
	*else if(tipo==ArrayString){....}*
}
*/

void swapCP(ComprasProd a[],int i,int j)
{	
	ComprasProd tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;

}
/*
void ordenaGrowingArray(GrowingArray a,int tipo)
{
	int i;
	int i2;
	int j = a->size - 1;
	
	if(tipo==ArrayCompProduto)

	for(i=2; i <= a->size ;i++)
		for(j= i - 1,i2 = j -1 ; i2 >= 0 ; i2--)
		{
			CompProduto elem = a->Elems[j];
			CompProduto comp = a->Elems[i2];
			if(elem->quantidade > comp->quantidade)
			{
				swapCP((ComprasProd*)a->Elems,i2,j);
				j=i2;
			}
		}

}
*/

int partition(ComprasProd a[],int N)
{
	int j,i;
	int pivo = a[0].quantidade;
	for(i=1,j=N;j>i+1;)
		if(pivo < a[i].quantidade)
		{
			swapCP(a,i,--j);
		}
		else i++;
	swapCP(a,0,--i);
	return i;	
}

void qSortGrowingArray(ComprasProd a[],int N)
{
	int p;
	if(N > 1)
	{
		p = partition(a,N);
		qSortGrowingArray(a,p);
		qSortGrowingArray(a + p,N-p); 
	}
}


void ordenaGrowingArray(GrowingArray a,int tipo)
{
	qSortGrowingArray((ComprasProd*)a->Elems,a->size);
}
