#ifndef HASHTABLE_H

#define HASHTABLE_H

typedef struct cpinfolist{
        char* cliente;
        char tipo;
	int mes;
	double fact;
        struct cpinfolist *next;
}cpinfolist;

typedef cpinfolist* CpInfoList;

typedef struct cpinfo{
        int vendas;
        int clientes;
        char* produto;
        CpInfoList first;
        CpInfoList last;
}cpinfo;

typedef cpinfo* CpInfo;

typedef struct hashtable{
        CpInfo* table;
        int max_size;
        int size;
} Hashtable;

typedef Hashtable* HashTable;

typedef CpInfo Elem;

typedef struct {
  int size;
  int used;
  Elem *values;
} Heap;


#include "heap.h"

#include "avl.h"

#include "compras.h"

int getCodigosProdutosUsados();

int getColisions();

int getNoncolisions();

float getColisionsRate();

int getRemakes();

HashTable initHashTable(int n);

HashTable insertHashTable( HashTable ht, Comp compra);

CpInfo searchHash(HashTable ht,char* code);

HashTable remakeHash(HashTable ht,int N);


unsigned int hash(char* str);


#endif
