
#ifndef HEAP_H
#define HEAP_H

#include "compras.h"

Heap* newHeap(int size);

void bubbleUp(Elem h[],int i);

void bubbleDown(Elem h[],int N);

int extractMin(Heap *h, Elem *x);

void heapSort(Elem v[],int N);
	
int insertHeap(Heap *h, Elem x);

#endif

