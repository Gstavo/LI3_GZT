#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contabilidade.h"

/* Metade da query 11 */

static int compras_mes[MAX_MONTHS];

typedef struct mensalidade{
	int nvendas;
	int nclientes;
	double factura;
} Mensalidade[MAX_MONTHS];

Mensalidade mDATA;

GrowingArray clientesMensais;  

static int clientes_inativos = 0;

INDICE_MES indexM(Comp c){return c->mes-1;}

void initContabilidade(Contabilidade c)
{
	int i,j;
	for(i=0;i < MAX_MONTHS;i++)
	{
		for(j=0;j < MAX_LETTERS;j++)
			c[i][j] = NULL;
		
		compras_mes[i] = 0;
		mDATA[i].nvendas = 0; mDATA[i].factura = 0; mDATA[i].nclientes=0;
	}
}


void insertContabilidade(Contabilidade contClnt, Contabilidade contProd, Comp compra, int* cresceu) {
	int iM=indexM(compra), iLC=indexL(compra->codigo_cliente), iLP=indexL(compra->codigo_produto);
	contClnt[iM][iLC]=insert(contClnt[iM][iLC], compra, cresceu, Compras_Ord_CC);
	contProd[iM][iLP]=insert(contProd[iM][iLP], compra, cresceu, Compras_Ord_CP);
	compras_mes[iM]++;
	mDATA[iM].nvendas+=compra->quantidade;
	mDATA[iM].nclientes+=1;
	mDATA[iM].factura+=compra->quantidade * compra->preco; 
}

/*Devolve a faturacao desse mes*/
FACTORACAO_TOTAL returnFact(int mes) {
	return mDATA[mes].factura;
}

FACTORACAO_TOTAL returnFactTotal(){
	int i;
	FACTORACAO_TOTAL resultado=0;
	for(i=0;i<MAX_MONTHS;i++)
		resultado+=returnFact(i);
	return resultado;
}

/*Devolve o numero de vendas efetuadas nesse mes*/
VENDAS_MES returnVendas(int mes) {
	return mDATA[mes].nvendas;
}

/*Devolve o numero de clientes nesse mes*/
CLIENTES_MES returnClientes(int mes) {
	return mDATA[mes].nclientes;
}

/*
int removeContabilidade(Contabilidade c,Comp compra)
*/

COMPRAS_MES compras_Mes(int mes){return compras_mes[mes-1];}

/* Retorna o resultado da query 10 */

GrowingArray getClientesMensais()
{
	return clientesMensais;
}

/* Retorna metade do resultado da query 14 */
int getClientesInativos()
{
/*	return clientes_inativos; */
	return clientesMensais->size;
}

/*Devolve o numero de compras de um cliente em cada mes*/
void compMes(Contabilidade c, char* cliente, int resultado[]) {
	int iM;
	int iL=indexL(cliente);
	for(iM=0; iM < MAX_MONTHS; iM++) resultado[iM]=avl_count(c[iM][iL], cliente, Compras_Ord_CC, 'N');	
}

/*12 linhas que representam os 12 meses e so tem 1 coluna com o respectivo valor total*/
void preenchecmp(int compras_mes[12][1]) {
	int i;
	for(i=0; i<12; i++) {
		compras_mes[i][1]=returnVendas(i);
	}
}

void preencheclientes(int clientes_mes[12][1]){
	int i;
	for(i=0; i<12; i++){
		clientes_mes[i][1]=returnClientes(i);/*Só falta fazer esta funçao e fica a funcionar a 100%*/
	}
}

void create_csv(int compras_mes[12][1], int clientes_mes[12][1]) {
	int i;
	char nome_ficheiro[20]="query11.csv\0";
	FILE *aux;
	aux=fopen(nome_ficheiro, "w+");
	fprintf(aux, "%s %s %s\n", "Mes\0", "#Compras\0", "#Clientes\0");
	for(i=0;i<12;i++) fprintf(aux,"%d %d %d\n", (i+1), compras_mes[i][1], clientes_mes[i][1]);	/*Dá o mês*/
	fclose(aux);
}

/*Devolve o numero de compras do tipo modo nesse mes*/
int comprasModo(Contabilidade contProd, int mes, char *code, char modo) {
	int iL=indexL(code), res;
	res=avl_count(contProd[mes][iL], code, Compras_Ord_CP, modo);
	return res;
}

/*Devolve a faturacao total de um produto num dado mes*/
double totalFactProdMes(Contabilidade contProd, int mes, char *code) {
	int iL=indexL(code), res;
	res=avl_countFact(contProd[mes][iL], code);
	return res;
}

void gatherData(AAVL cl,Contabilidade c)
{
	int i;
	GrowingArray clientes = initGrowingArray(20000,ArrayString);
        clientesMensais = initGrowingArray(10000,ArrayString);
	for(i=0;i<MAX_LETTERS;i++)
		guardArrayAVL(cl[i],clientes,ArrayString);
	
	for(i=0;i<clientes->size;i++){
		int im,meses_activos=0;		
		for(im = 0; im < MAX_MONTHS;im++)
		{
			int iL = indexL(clientes->Elems[i]);
			if(countainAVL(c[im][iL],clientes->Elems[i])) meses_activos++;
		}
		if(meses_activos == 0) clientes_inativos++;
		if(meses_activos == 12) {	
			char* insert = malloc(10*sizeof(char));
			strcpy(insert,clientes->Elems[i]);	
			insertGrowingArray(clientesMensais,insert,ArrayString);  
		}
	}
}
