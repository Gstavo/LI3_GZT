#ifndef HASHTABLE_H

#define HASHTABLE_H

#include "avl.h"

#include "compras.h"

int getCodigosProdutosUsados();

int getColisions();

int getNoncolisions();

int getFirstcolisions();

int getRemakes();

HashTable initHashTable( HashTable ht,int n);

HashTable insertHashTable( HashTable ht, AVL a,int* cresceu);

HashTable remakeHash(HashTable ht,int N);

void freeAVL(AVL p);

unsigned int hash(char* str);

/*

int hash(char* code,int max);
*/

#endif
