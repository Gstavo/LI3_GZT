#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contabilidade.h"

/* Metade da query 11 */

static int compras_mes[MAX_MONTHS];

/* mDATA Query 7 feita */

typedef struct mensalidade{
	int nvendas;
	double factura;
}Mensalidade[MAX_MONTHS];

Mensalidade mDATA;

int indexM(Comp c){return c->mes-1;}

void initContabilidade(Contabilidade c)
{
	int i,j;
	for(i=0;i < MAX_MONTHS;i++)
	{
		for(j=0;j < MAX_LETTERS;j++)
			c[i][j] = NULL;
		
		compras_mes[i] = 0;
		mDATA[i].nvendas = 0; mDATA[i].factura = 0;
	}
}

void insertContabilidade(Contabilidade c,Comp compra,int* cresceu)
{
	int iM = indexM(compra);
	int iL = indexL(compra->codigo_cliente);
	c[iM][iL] = insert(c[iM][iL],compra,cresceu,Compras_Ord_CC);
	/* Aproveitar para retirar informaçoes sobre a compra
	neste mes (iM) , adicionar + variáveis globais caso necessário*/
	/* query 7 feita aqui */
	compras_mes[iM]++;
	mDATA[iM].nvendas= compra->quantidade;
	mDATA[iM].factura= compra->quantidade * compra->preco; 
}

/*Devolve a faturacao desse mes*/
double returnFact(int mes) {
	return mDATA[mes].factura;
}

/*Devolve o numero de vendas efetuadas nesse mes*/
int returnVendas(int mes) {
	return mDATA[mes].nvendas;
}

/*
int removeContabilidade(Contabilidade c,Comp compra)
*/

int compras_Mes(int mes){return compras_mes[mes-1];}

/*
	Query 5 : Show numero de compras do cliente em cada mês
*/
/*
int* query5(Contabilidade c,char* cliente)
{
	int resultado[MAX_MONTHS],iM;
	int iL = indexL(cliente);
	for(iM=0;iM < MAX_MONTHS;iM++)
		resultado[iM] = avl_count(c[iM][iL],cliente,Compras_Ord_CC);	
	
	return resultado;
}
*/
/*
	Query 9 : 
		Recebe um cliente e um mes
		Show lista CP que comprou ordenada por ordem decrescente 
		  de quantidade
*/
/*
char** query9(Contabilidade c,char* cliente,int mes){return NULL;}
{*/
	/* 
	Prototipo
	1 encontrar a primeira compra do cliente( O resto das compras encontram-se seguidas)
	Retirar os codigos de produto e a respetiva quantidade de cada compra do cliente para uma estrutura nova
	Ordenar a estrutura 
	Filtrar a quantidade de cada um
	Devolver a lista de codigos de produto

	A verificar se a info filtrada é util para outras queries
	*/
/*}*/


