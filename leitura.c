#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "leitura_aux.h"

int main () {
	int i=0, countC=0, countP=0, countCompras=0, compras_invalidas=0, index; 
	double fact=0, time_spent;	/*fact corresponde a faturacao total anual*/
	int validaClnt=0, validaProd=0, validaCmpr=0, clntInv=0, prodInv=0, indexProd, indexClnt;	
	FILE *clientes, *produtos, *fcompras;
	char **compras;
	char linha[MAX_LINE];
	int *cresceu=(int*) malloc(sizeof(int*));	/*Verifica se a AVL cresceu*/
	Slist cl, pd;	/*cl - array com AVL's de clientes, pd - array com AVL's de produtos*/
	Comp array=(Comp)malloc(MAX*sizeof(Compras));
	clock_t begin, end;
	
	begin=clock();

	/*Inicializa as estruturas*/
	for(i=0; i<20000; i++) {
		cl[i]=(ProdList) malloc(sizeof(struct prodTree));
		cl[i]=NULL;
	}
	for(i=0; i<200000; i++) {
		pd[i]=(ProdList) malloc(sizeof(struct prodTree));
		pd[i]=NULL;
	}
	
	compras = calloc(500000,sizeof(char*));
	for(i=0;i<500000;i++)
		compras[i] = calloc(MAX_LINE,sizeof(char));
	
	clientes=fopen("clientes.txt","r"); 
	produtos=fopen("produtos.txt","r");
	fcompras=fopen("compras.txt","r");
	
	for(i=0;fgets(linha, MAX_LINE, clientes);i++) 
	{
			linha[strlen(linha)-1] = '\0';
			/*index corresponde ao endereco da AVL onde vai ser intruduzida a linha*/ 
			index=linha[0]-65;
			cl[index]=insert(cl[index], linha, cresceu);
			countC++;
	}
	fclose(clientes);
	
	for(i=0;fgets(linha, MAX_LINE, produtos);i++)
	{ 
			linha[strlen(linha)-1] = '\0';
			index=linha[0]-65;
			pd[index]=insert(pd[index], linha, cresceu);
			countP++;
	}
	fclose(produtos);
	
	for(i=0;fgets(linha, MAX_LINE,fcompras);i++)
	{
			linha[strlen(linha)-1] = '\0';
			strcpy(compras[i],linha);
			tokenizer(array, i, compras[i]);
			/*indexProd e indexClnt dao o endereco das AVL's onde se vai procurar se existe*/
			indexProd=array[i].codigo_Produto[0]-65;
			indexClnt=array[i].codigo_cliente[0]-65;
			validaClnt=validateClnt(array[i], cl[indexClnt]);
			validaProd=validateProd(array[i], pd[indexProd]);
			validaCmpr=validateCompras(array[i]);
			if(validaClnt==0) clntInv++;
			if(validaProd==0) prodInv++;
			if(validaClnt==0 || validaProd==0 || validaCmpr==0) compras_invalidas++;
			else fact+=array[i].preco_unitario;
			countCompras++;
	}
	fclose(fcompras);

	printf("\nPRODUTOS: %d\n", countP);
	printf("CLIENTES: %d\n", countC);
	printf("LINHAS DE COMPRAS: %d\n", countCompras);
	printf("CODIGOS DE CLIENTE INEXISTENTES: %d\n", clntInv);
	printf("CODIGOS DE PRODUTO INEXISTENTES: %d\n", prodInv);
	printf("TOTAL DE COMPRAS INVALIDAS: %d\n", compras_invalidas);
	printf("--------------------------------------------\n");
	printf("COMPRAS VALIDAS: %d\n", (countCompras-compras_invalidas));
	printf("FATURACAO ANUAL TOTAL: %f\n\n", fact);

	for(i=0;i<500000;i++)
		free(compras[i]);
	free(compras);

	end=clock();
	time_spent=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("Tempo de execucao: %f segundos\n", time_spent);
	
	return 0;
}
	

	
	
