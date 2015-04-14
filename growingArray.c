#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "growingArray.h"


GrowingArray initGrowingArray(int max_size,int tipo)
{
	GrowingArray novo = malloc(sizeof(struct growingarray));
	novo->size = 0;
	novo->max_size = max_size;
	if(tipo == ArrayString)
	{
		int i;
		novo->Elems = calloc(max_size,sizeof(char *));
		for(i=0;i < max_size;i++)
			novo->Elems[i] = malloc(10*sizeof(char));
	}	
	return novo;
}

void insertGrowingArray(GrowingArray a, Objeto o,int tipo)
{
	if(a->size == a->max_size) resizeGrowingArray(a,tipo);
	
	a->Elems[a->size++] = o;

}

void resizeGrowingArray(GrowingArray a,int tipo)
{ 
	int i = a->max_size;
	a->max_size*= 1.5; 
	a->Elems = realloc(a->Elems,a->max_size);
	
	for(;i<a->max_size;i++)
	{
		if(tipo==ArrayString) a->Elems[i] = malloc(10*sizeof(char));
	}

}


