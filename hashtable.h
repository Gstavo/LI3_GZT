#ifndef HASHTABLE_H

#define HASHTABLE_H

#include "avl.h"

#include "compras.h"

int getRemakes();

HashTable initHashTable( HashTable ht,int n);

int insertHashTable( HashTable ht, AVL a,int* cresceu);

void remakeHash(HashTable ht,int N,int* cresceu);

void freeAVL(AVL p);

unsigned int hash(char* str);

/*

int hash(char* code,int max);
*/

#endif
