#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hashtable.h"

/*static AVL REMOVED = malloc(sizeof(struct avl_node));*/

static int codigo_produto_usado = 0;


static int remakes = 0;

int getRemakes(){return remakes;}


/* cria uma avl de max_size n */
HashTable initHashTable( HashTable ht,int n)
{
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

int insertHashTable( HashTable ht, AVL a,int* cresceu)
{
	unsigned int hash_code;
	int i;
	float ocupacao = (float)ht->size / ht->max_size;
	if( ocupacao > 0.3)
	{
		puts("Remaking hash");
		remakeHash(ht,1.5*ht->max_size,cresceu);
		puts("Remake done");
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
			return 0;
		}
		casted = (Comp) ht->table[i]->info;
		if(strcmp(casted->codigo_produto,compra->codigo_produto) == 0)	
		{	
	/* Considerar mudar o tipo de AVL ordenada por cc para ordenado
		por quanidade vendidada */

			ht->table[i] = insert(ht->table[i],compra,cresceu,Compras_Ord_CC);
			return 0;
		}
	/*	}*/
		i = (i + 1) % ht->max_size;
		
	}while(i!=hash_code);
	
	}	
	return 1;
}

void remakeHash(HashTable ht,int N,int* cresceu){
	int i;
	HashTable new,tmp;
	new = malloc(sizeof(struct hashtable));
	new->table = calloc(N,sizeof(struct avl_node));
	new->max_size = N;
	new->size = ht->size;
	
	for(i=0;i<N;i++) new->table[i] = NULL;
	
	for(i=0;i<ht->max_size;i++)
		if(ht->table[i]) 
			{
				insertHashTable(new,ht->table[i],cresceu);
				freeAVL(ht->table[i]);
			}
	tmp = ht;
	ht = new;
	free(tmp->table);
	free(tmp);
	
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
