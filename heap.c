#include <stdlib.h>
#include <stdio.h>

#include "heap.h"

#define UP(i) (i-1)/2
#define LEFT(i) 2*i+1
#define RIGHT(i) 2*i+2

int minHeapOK (Heap h){
	int i,l,r;
	int used = h.used;
	for(i=0;i<used;i++){
		l = LEFT(i);
		r = RIGHT(i);
		if(l<used && h.values[i] > h.values[l]) return 0; 
		if(r<used && h.values[i] > h.values[r]) return 0; 
	}
	return 1;
}

void swap(Elem h[],int i,int j)
{
	Elem tmp = h[i];
	h[i] = h[j];
	h[j] = tmp;
}

Heap *newHeap (int size){
	Heap *h = (Heap*) malloc(sizeof(Heap));
	h->size = size;
	h->used = 0;
	h->values = (Elem*) calloc(size,sizeof(Elem));
	return h;	
}


void bubbleUp (Elem h[], int i){
	while(i>0){
		if(h[UP(i)]->vendas > h[i]->vendas) swap(h,UP(i),i);
		else break;
		i = UP(i);
	}
}

void bubbleDown(Elem h[], int N){
	int mp,i=0;
	while(LEFT(i)<N){
		if(RIGHT(i)< N)
		{
		if(h[LEFT(i)]->vendas > h[RIGHT(i)]->vendas) mp = RIGHT(i); 
			else mp = LEFT(i);
				} else mp = LEFT(i);
		if(h[i]->vendas <= h[mp]->vendas) break;
		swap(h,i,mp);
		i = mp;	
	}
}


int extractMin(Heap *h, Elem *x){
	if(h->used == 0) return 1;
	*x = h->values[0];
	h->used--;
	h->values[0] = h->values[h->used];
	bubbleDown(h->values,h->used);
	return 0;
}

void heapSort(Elem v[],int N){
	int i;
/*	for(i=0;i<N;i++) bubbleUp(v,i);*/
	for(i=N-1;i>0;i--) {
		swap(v,0,i);
		bubbleDown(v,i);
	}
}


int insertHeap(Heap *h, Elem x){
	if(h->used == h->size) return 1;
	h->values[h->used] = x;
	bubbleUp(h->values,h->used++);
	return 0; 	
}
