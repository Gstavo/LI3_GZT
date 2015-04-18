#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compras.h"

#define N_Codigos_Produto 200000

/*! \brief Procura o índice de um caracter numa string
*
*	Percorre a string, incrementando uma variável, retornando essa variável se o target corresponder ao caracter nessa posição na string.
*	Se o caracter não for encontrado retorna -1.
*
* \param target O caracter a procurar
* \param s A string sobre a qual se calcula o tamanho
* \return O índice do caracter na string
*/



/*
 *
 * 	VARIAVEIS GLOBAIS
 *
*/

/*static AVL REMOVED = malloc(sizeof(struct avl_node));*/

static int codigo_produto_usado = 0;


static int remakes = 0;

static int noncolisions = 0;

static int colisions = 0;

/*
 *
 * 	FUNÇOES DE ACESSO ÀS VARIAVEIS GLOBAIS
 *
*/


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



/*
 *
 * 	INICIALIZAR AS ESTRUTURAS DE DADOS
 *
*/

/*! \brief Inicializa uma Compra.
*
*       Alloca memória para a struct compras, para o codigo de produto e cliente dentro da struct.
*
* \return Comp O endereço da struct compras.
*/

Comp initCompra() {
	Comp compra=malloc(sizeof(struct compras));
	compra->codigo_produto = malloc(10*sizeof(char));
	compra->codigo_cliente = malloc(10*sizeof(char));
	return compra;
}

HashTable initHashCompras() {
        HashTable ht;
        int HT_SIZE = 4 * N_Codigos_Produto ;
        ht = malloc(sizeof(struct hashtable));
        ht->table = calloc( HT_SIZE ,sizeof(CpInfo));
	ht->max_size = HT_SIZE;
        ht->size = 0;
	return ht;
}


/*! \brief Inicializa uma Heap e insere os objetos da HashTable.
*
*       Alloca memória para uma Heap de Objetos a qual vai ser preenchida 
com endereços do tipo CpInfoList que representam um conjunto de listas ligadas com o codigo
de cada cliente e tipo P/N de cada compra do produto. As CpInfoList de cada produto estam guardadas
na HashTable.
*
* \param ht HashTable com a informaçao de cada produto.
* \return h Heap* gerada.
*/


Heap* initHeap(HashTable ht){
	int i;
	Heap* h = newHeap( ht->size );
	for(i = 0; i < ht->max_size ; i++)
		if(ht->table[i]) insertHeap(h,ht->table[i]);
	heapSort(h->values,h->used);
	return h;
}


/*
 *
 * 	FUNÇÕES DE INSERÇÃO
 *
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
 /*      if(ht->table[i] != REMOVED)
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
        /*      }*/
         if(i == hash_code) colisions++;
                i = (i + 1) % ht->max_size;

        }while(i!=hash_code);

        return ht;
}

/*
 *
 *	OUTRAS FUNÇÕES DA ESTRUTURA HASH & CPINFO
 *
*/

CpInfo searchHash(HashTable ht,char* code)
{
        int i = hash(code) % ht->max_size;

        if(ht)
        for(; ht->table[i] ; i = (i+1) % ht->max_size)
                if(strcmp(code,ht->table[i]->produto)==0) return ht->table[i];

        return NULL;
}

HashTable remakeHash(HashTable ht,int N){
        int i;
        HashTable new;

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
                        			break;
                			 }
                			 i = (i + 1) % new->max_size;

        			 }while(i!=hash_code);

			}
        free(ht->table);
        free(ht);
        return new;
}

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

/*
 *
 *	FUNÇÕES PARA QUERIES ESPECÍFICAS 
 *
*/

/*
	Query 8: show lista de CC distiguindo N/P
		de um dado CP
*/

CpInfoList query8Aux(HashTable ht,char* cp){
	CpInfo cpinfo = searchHash(ht,cp);
	if(!cpinfo) return NULL;
	return cpinfo->first;			
	}


/*
 *
 *	BASIC COMPRAS STRUCT CODE
 *
*/


void compracpy(Comp dest,Comp src){
	strcpy(dest->codigo_produto,src->codigo_produto);
	strcpy(dest->codigo_cliente,src->codigo_cliente);
        dest->preco = src->preco;
        dest->quantidade = src->quantidade;
        dest->tipo = src->tipo;
        dest->mes = src->mes;
}

int compracmpCC(Comp c1,Comp c2) {
        return (strncmp(c1->codigo_cliente,c2->codigo_cliente,5));
}

int compracmpCP(Comp c1,Comp c2) {
        return (strncmp(c1->codigo_produto,c2->codigo_produto,6));
}

