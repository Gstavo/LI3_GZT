#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define ArrayString 1

typedef void* Object;

typedef struct growingarray{
	Object* Elems;
	int size;
	int max_size;
}growingarray;

typedef growingarray* GrowingArray;

GrowingArray initGrowingArray(int max_size,int tipo)
{
	GrowingArray novo;
	novo->size = 0;
	novo->max_size = max_size;
	if(tipo == ArrayString)
	{
		int i;
		novo->Elems = calloc(max_size,sizeof(char *));
		for(i=0;i < max_size;i++)
			Elems[i] = malloc(10*sizeof(char));
	}	
	return novo;
}

void insertGrowingArray(GrowingArray a, Object o,int tipo)
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
		if(tipo==ArrayString) Elems[i] = malloc(10*sizeof(char));
	}

}


