
#ifndef COMPRAS_H

#define COMPRAS_H

/* Struct com a informaçao do codigo de compra */

typedef struct compras{
	char* codigo_produto;
	double preco;
	int quantidade;
	char tipo;
	char* codigo_cliente;
	int mes;
}Compras;

typedef struct compras* Comp;

/* Struct HASH & CPINFO */

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

/* Heap Structure */

typedef CpInfo Elem;

typedef struct {
  int size;
  int used;
  Elem *values;
} Heap;

#include "heap.h"
#include "avl.h"
#include "catalogo_clientes.h"
#include "catalogo_produtos.h"

/* FUNÇOES DE ACESSO */

int getHashTableSize(HashTable ht);

int getRemakes();

int getCodigosProdutosUsados();

int getColisions();

int getNoncolisions();

float getColisionsRate();

int getRemakes();



Comp initCompra();

HashTable initHashCompras();

Heap* initHeap(HashTable ht);

void insertComprasCP(AAVL a,Comp compra,int* cresceu);

CpInfo searchHash(HashTable ht,char* code);

HashTable insertHashTable( HashTable ht, Comp compra);



HashTable remakeHash(HashTable ht,int N);

unsigned int hash(char* str);

CpInfoList query8Aux(HashTable ht,char* cp);



void compracpy(Comp dest,Comp src);

int compracmpCC(Comp c1,Comp c2);

int compracmpCP(Comp c1,Comp c2);

#endif
