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
	int factura;
}Mensalidade[MAX_MONTHS];

Mensalidade mDATA;

void initContabilidade(CONTABILIDADE c)
{
	int i;
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
	int i;
	int iM = indexM(compra);
	int iCC = inexCC(compra);
	c[iM][iCC] = insert(c[iM][iCC],compra,cresceu,Compras_Ord_CC);
	/* Aproveitar para retirar informaçoes sobre a compra
	neste mes (iM) , adicionar + variáveis globais caso necessário*/
	/* query 7 feita aqui */
	compras_mes[iM]++;
	mDATA[iM].nvendas+= Comp->quantidade;
	mDATA[iM].factura+= Comp->quantidade * Comp->preco; 
}

/*
int removeContabilidade(Contabilidade c,Comp compra)
*/

int compras_Mes(int mes){return compras_mes[mes];}

/*
	Query 5 : Show numero de compras do cliente em cada mês
*/

int* query5(Contabilidade c,char* cliente)
{
	int resultado[MAX_MONTHS],iM;
	for(iM=0;iM < MAX_MONTHS;iM++)
	{
		int iL = indexL(cliente);
		resultado[iM] = avl_count(c[iM][iL],cliente,Compras_Ord_CC);	
	}
	return resultado;
}

/*
	Query 9 : 
		Recebe um cliente e um mes
		Show lista CP que comprou ordenada por ordem decrescente 
		  de quantidade
*/

char** query9(Contabilidade c,char* cliente,int mes){return NULL;}
{
	/* 
	Prototipo
	1 encontrar a primeira compra do cliente( O resto das compras encontram-se seguidas)
	Retirar os codigos de produto e a respetiva quantidade de cada compra do cliente para uma estrutura nova
	Ordenar a estrutura 
	Filtrar a quantidade de cada um
	Devolver a lista de codigos de produto

	A verificar se a info filtrada é util para outras queries
	*/
}


