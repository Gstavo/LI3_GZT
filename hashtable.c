#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hashtable.h"

/*static AVL REMOVED = malloc(sizeof(struct avl_node));*/

static int codigo_produto_usado = 0;


static int remakes = 0;

static int colisions = 0;

static int noncolisions = 0;

static int firstcolisions = 0;

int getCodigosProdutosUsados() 
{return codigo_produto_usado;}

int getColisions()
{return colisions;}

int getNoncolisions()
{return noncolisions;}

int getFirstcolisions()
{return firstcolisions;}

int getRemakes(){return remakes;}


/* cria uma avl de max_size n */
HashTable initHashTable(int n)
{
	HashTable ht;
	int i;
	ht = malloc(sizeof(struct hashtable));
	ht->table = calloc(n,sizeof(AVL));
	for(i=0;i<n;i++) ht->table[i] = NULL;
	ht->max_size = n;
	ht->size = 0;
	return ht;
}

/*
 *	Realloc a 30 % de ocupação
 */

HashTable insertHashTable( HashTable ht, AVL a,int* cresceu)
{
	unsigned int hash_code;
	int i;
	float ocupacao = (float)ht->size / ht->max_size;

	if( ocupacao > 0.3)
	{
		ht = remakeHash(ht,1.5*ht->max_size);
		remakes++;
	}
	
	if(a)
	{	
	Comp compra = (Comp)a->info;
	Comp casted;
	hash_code = hash(compra->codigo_produto) % ht->max_size;
	i = hash_code;
	do
	{
	/*	if(ht->table[i] != REMOVED)
		{*/
		if(ht->table[i] == NULL)
		{
			ht->table[i] = insert(ht->table[i],compra,cresceu,Compras_Ord_CC);
			codigo_produto_usado++;
			ht->size++;
			if(i==hash_code) noncolisions++; else colisions++;
                
			return ht;
		}
		casted = (Comp) ht->table[i]->info;
		if(strcmp(casted->codigo_produto,compra->codigo_produto) == 0)	
		{	
	/* Considerar mudar o tipo de AVL ordenada por cc para ordenado
		por quanidade vendidada */

			ht->table[i] = insert(ht->table[i],compra,cresceu,Compras_Ord_CC);
			if(i == hash_code) noncolisions++; else colisions++;

			return ht;
		}
	/*	}*/
		if(i == hash_code) firstcolisions++;
		i = (i + 1) % ht->max_size;
		
	}while(i!=hash_code);
	
	}	
	return ht;
}

/*
AVL searchHash(HashTable ht,char* code)
{
	int i = hash(code);
	for(; ht->table[i] ; i = (i+1) % ht->max_size) 
		if(strcmp(code,ht->table[i]->codigo_produto)==0)
		return ht->table[i];
	return NULL;
}
*/

/* da hash à primeira avl e depois insere as avls todas ligadas no new */
void insertRemake(HashTable new,AVL a)
{
	int hash_code,i;
	Comp compra = (Comp) a->info;
	hash_code = hash(compra->codigo_produto) % new->max_size;
	i = hash_code;
	
	do
	{
		if(new->table[i] == NULL)
		{
			new->table[i] = a;
			break;
		}
		i = (i + 1) % new->max_size;
	}while(i!=hash_code);
}

HashTable remakeHash(HashTable ht,int N){
	int i;
	HashTable new = initHashTable(N);
	new->size = ht->size;
	for(i=0;i<ht->max_size;i++)
		if(ht->table[i]) insertRemake(new,ht->table[i]);
	free(ht->table);
	free(ht);
	return new;
}



void freeAVL(AVL p)
{
	if(p)
	{
		freeAVL(p->left);
		freeAVL(p->right);
		free(p->info);
		free(p);
	}
}
/* PRODUTOS: 195 584 */

double powM(int x,int y)
{
	if(y==0) return (double)1;
	return (double)x*powM(x,--y);
}

/* Alterar algoritmo de hash, este é horrivel */
/*
int hash(char* code,int max)
{
	int i,n=6;
	double result = 0;
	for(i=0;code[i]!='\0';i++)
		{
		result+=code[i] * powM(10,n-i);
		if(i==0) n--;
		}
	return (int) result % max;	
}
*/


/* hash PJWHash algoritmo */

unsigned int hash(char* str)
{
   int length = strlen(str);
   unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
   unsigned int ThreeQuarters     = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
   unsigned int OneEighth         = (unsigned int)(BitsInUnsignedInt / 8);
   unsigned int HighBits          = (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
   unsigned int hash              = 0;
   unsigned int test              = 0;
   int i; 
   
   for( i = 0; i < length; i++)
   {
      hash = (hash << OneEighth) + str[i];
 
      if((test = hash & HighBits)  != 0)
      {
         hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
      }
   }
 
   return (hash & 0x7FFFFFFF);
}
