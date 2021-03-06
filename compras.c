#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compras.h"

#define N_Codigos_Produto 200000

CpInfo const REMOVED;

static int codigo_produto_usado = 0;
static int noncolisions = 0;
static int colisions = 0;
static int remakes = 0;

HashTable static remakeHash(HashTable ht,int N);

/*Devolve o numero de resizes da tabela de Hash*/
int getRemakes() {
	return remakes;
}

/*Devolve o numero de produtos que foram comprados*/
int getCodigosProdutosUsados() {
	return codigo_produto_usado;
}

/*Devolve o numero de colisoes da tabela de Hash*/
int getColisions() {
	return colisions;
}

/*Devolve o numero de nao colisoes*/
int getNoncolisions() {
	return noncolisions;
}

/*Devolve a percentagem de colisoes da tabela de Hash*/
float getColisionsRate() {
	return (float)colisions / (noncolisions + colisions) ;
}

/*Inicializa a estrutura de compras*/
Comp initCompra() {
	Comp compra=malloc(sizeof(struct compras));
	compra->codigo_produto = malloc(10*sizeof(char));
	compra->codigo_cliente = malloc(10*sizeof(char));
	return compra;
}

/*Inicializa da tabela de Hash*/
HashTable initHashCompras() {
        HashTable ht;
        int HT_SIZE =  8 * N_Codigos_Produto ;
        ht = malloc(sizeof(struct hashtable));
        ht->table = calloc( HT_SIZE ,sizeof(CpInfo));
	ht->max_size = HT_SIZE;
        ht->size = 0;
	return ht;
}

/*Inicializa a heap usada apenas na query 12, insere os elementos e ordena*/
Heap* initHeap(HashTable ht){
	int i;
	Heap* h = newHeap( ht->size );
	for(i = 0; i < ht->max_size ; i++)
		if(ht->table[i]) insertHeap(h,ht->table[i]);
	heapSort(h->values,h->used);
	return h;
}

/*Insere um elemento na estrutura CP Info*/
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

/*Insere na tabela de Hash*/
HashTable insertHashTable(HashTable ht, Comp compra)
{
        unsigned int hash_code;
        int i;

        if( getColisionsRate() > 0.3f && getColisions() > 1000 )
        {
		ht = remakeHash(ht,1.5*ht->max_size);
        }

        hash_code = hash(compra->codigo_produto) % ht->max_size;
        i = hash_code;
        do
        {
                if(ht->table[i] == NULL)
                {
                        ht->table[i] = insertCPinfo(ht->table[i],compra);
                        codigo_produto_usado++;
                        ht->size++;
                        if(i==hash_code) noncolisions++;

                        return ht;
                }
                if(ht->table[i] != REMOVED && strcmp(ht->table[i]->produto,compra->codigo_produto) == 0)
                {
                        ht->table[i] = insertCPinfo(ht->table[i],compra);
                        if(i == hash_code) noncolisions++; else colisions++;

                        return ht;
                }
         if(i == hash_code) colisions++;
         i = (i + 1) % ht->max_size;

        }while(i!=hash_code);

        return ht;
}

/* Remove a informção toda relativamente ao codigo de produto dado na hashtable */
int removeHash(HashTable ht, char *code)
{
	int i = hash(code) % ht->max_size;
	if(ht)
	for(; ht->table[i] ; i = (i+1) % ht->max_size)
                if(strcmp(code,ht->table[i]->produto)==0) 
			{
				ht->table[i] = REMOVED;
				return 0;
			}
	return 1;
}

/*Procura um elemento na tabela de Hash*/
CpInfo searchHash(HashTable ht,char* code)
{
        int i = hash(code) % ht->max_size;

        if(ht)
        for(; ht->table[i] ; i = (i+1) % ht->max_size)
                if(strcmp(code,ht->table[i]->produto)==0) return ht->table[i];

        return NULL;
}

/*Faz o resize da tabela de Hash*/
HashTable static remakeHash(HashTable ht,int N){
        int i;
        HashTable new;

	colisions = 0;
	noncolisions = 0;
	remakes++;

        new = malloc(sizeof(struct hashtable));
        new->table = calloc( N ,sizeof(CpInfo));
	new->max_size = N;
        new->size = ht->size;


        for(i=0;i<ht->max_size;i++) 
		if(ht->table[i]) 
			{
 				 CpInfo cpi = ht->table[i];
       				 int hash_code = hash(cpi->produto) % new->max_size;
       				 i = hash_code;

       				 do
        			 {	
               				 if(new->table[i] == NULL)
                			 {
                        			new->table[i] = cpi;
						if(i == hash_code) noncolisions*=cpi->clientes;
                        			break;
                			 }

					if(i == hash_code) colisions*=cpi->clientes;
                			 i = (i + 1) % new->max_size;

        			 }while(i!=hash_code);

			}

        return new;
}

/* Funcao de Hash (PJWHash) */
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

/*Funcao auxiliar da query8*/
CpInfoList query8Aux(HashTable ht,char* cp){
	CpInfo cpinfo = searchHash(ht,cp);
	if(!cpinfo) return NULL;
	return cpinfo->first;			
}

/*Faz a copia de uma estrutura de compras para outra*/
void compracpy(Comp dest,Comp src){
	strcpy(dest->codigo_produto,src->codigo_produto);
	strcpy(dest->codigo_cliente,src->codigo_cliente);
        dest->preco = src->preco;
        dest->quantidade = src->quantidade;
        dest->tipo = src->tipo;
        dest->mes = src->mes;
}

/*Compara dois codigos de cliente*/
int compracmpCC(Comp c1,Comp c2) {
        return (strncmp(c1->codigo_cliente,c2->codigo_cliente,5));
}

/*Compara dois codigos de produto*/
int compracmpCP(Comp c1,Comp c2) {
        return (strncmp(c1->codigo_produto,c2->codigo_produto,6));
}

