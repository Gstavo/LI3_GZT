#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hashtable.h"

/*static AVL REMOVED = malloc(sizeof(struct avl_node));*/

static int codigo_produto_usado = 0;


static int remakes = 0;

static int noncolisions = 0;

static int colisions = 0;

int getCodigosProdutosUsados() 
{return codigo_produto_usado;}

int getColisions()
{return colisions;}

int getNoncolisions()
{return noncolisions;}

float getColisionsRate()
{return (float)colisions / (noncolisions + colisions) ;}

int getRemakes()
{return remakes;}


/* cria uma avl de max_size n */
HashTable initHashTable(int n)
{
	HashTable ht;
	int i;
	ht = malloc(sizeof(struct hashtable));
	ht->table = malloc(n * sizeof(CpInfo));
	for(i=0;i<n;i++) ht->table[i] = NULL;
	ht->max_size = n;
	ht->size = 0;
	return ht;
}

/*
 *	Realloc a 30 % de ocupação
 */

CpInfo insertCPinfo(CpInfo infoL,Comp compra){
	if(infoL==NULL)
	{
		infoL = malloc(sizeof(cpinfo));
		
		infoL->produto = malloc(10*sizeof(char));
		strcpy(infoL->produto,compra->codigo_produto);	

		infoL->first = malloc(sizeof(cpinfolist));
		infoL->first->cliente = malloc(10*sizeof(char));
		strcpy(infoL->first->cliente,compra->codigo_cliente);
		infoL->first->tipo = compra->tipo;
		infoL->first->mes = compra->mes;
		infoL->first->fact = compra->quantidade * compra->preco;
		infoL->first->next = NULL;

		infoL->clientes = 1;
		infoL->vendas = compra->quantidade;
		infoL->last = infoL->first;
	}
	else{
		CpInfoList new = malloc(sizeof(cpinfolist));
		new->cliente = malloc(10*sizeof(char));
		strcpy(new->cliente,compra->codigo_cliente);
		new->tipo = compra->tipo;
		new->mes = compra->mes;
		new->fact = compra->quantidade * compra->preco;
		new->next = NULL;
		
		infoL->last->next = new;
		infoL->last = new;
		infoL->clientes++;
		infoL->vendas+= compra->quantidade; 
	}
	return infoL;
}

HashTable insertHashTable(HashTable ht, Comp compra)
{
	unsigned int hash_code;
	int i;
	float ocupacao = (float)ht->size / ht->max_size;

	if( ocupacao > 0.3)
	{
		ht = remakeHash(ht,1.5*ht->max_size);
		remakes++;
	}
	
	hash_code = hash(compra->codigo_produto) % ht->max_size;
	i = hash_code;
	do
	{
	/*	if(ht->table[i] != REMOVED)
		{*/
		if(ht->table[i] == NULL)
		{
			ht->table[i] = insertCPinfo(ht->table[i],compra);
			codigo_produto_usado++;
			ht->size++;
			if(i==hash_code) noncolisions++;
                
			return ht;
		}
		if(strcmp(ht->table[i]->produto,compra->codigo_produto) == 0)	
		{	
			ht->table[i] = insertCPinfo(ht->table[i],compra);
			if(i == hash_code) noncolisions++; else colisions++;

			return ht;
		}
	/*	}*/
		if(i == hash_code) colisions++;
		i = (i + 1) % ht->max_size;
		
	}while(i!=hash_code);
	
	return ht;
}


CpInfo searchHash(HashTable ht,char* code)
{
	int i = hash(code) % ht->max_size;
	
	if(ht) 
	for(; ht->table[i] ; i = (i+1) % ht->max_size)
		if(strcmp(code,ht->table[i]->produto)==0) return ht->table[i];
		
	return NULL;
}


/* da hash à primeira avl e depois insere as avls todas ligadas no new */
void insertRemake(HashTable new,CpInfo cpi)
{
	int hash_code,i;
	hash_code = hash(cpi->produto) % new->max_size;
	i = hash_code;
	
	do
	{
		if(new->table[i] == NULL)
		{
			new->table[i] = cpi;
			break;
		}
		i = (i + 1) % new->max_size;
	}while(i!=hash_code);
}

HashTable remakeHash(HashTable ht,int N){
	int i;
	HashTable new = initHashTable(N);
	new->size = ht->size;
	for(i=0;i<ht->max_size;i++) if(ht->table[i]) insertRemake(new,ht->table[i]);
	free(ht->table);
	free(ht);
	return new;
}

/* PRODUTOS: 195 584 */

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
