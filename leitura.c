#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "leitura.h"

int main () {
	int i=0,countCompras=0, compras_invalidas=0; 
	double fact=0, time_spent;	/*fact corresponde a faturacao total anual*/
	int validaClnt=0, validaProd=0, validaCmpr=0, clntInv=0, prodInv=0;	
	FILE *clientes, *produtos, *fcompras;
	char **compras;
	char linha[MAX_LINE];
	int *cresceu=(int*) malloc(sizeof(int*));	/*Verifica se a AVL cresceu*/
	AAVL cl, pl;	/*cl - array com AVL's de clientes, pl - array com AVL's de produtos*/
	Comp array=(Comp)malloc(MAX*sizeof(Compras));
	clock_t begin, end;
	
	begin=clock();

	/*Inicializa as estruturas*/
	
	initCatalogo_Clientes(cl);

	initCatalogo_Produtos(pl);
	
	compras = calloc(MAX,sizeof(char*));
	for(i=0;i<MAX;i++)
		compras[i] = calloc(MAX_LINE,sizeof(char));
	
	clientes=fopen("clientes.txt","r"); 
	produtos=fopen("produtos.txt","r");
	fcompras=fopen("compras.txt","r");
	
	for(i=0;fgets(linha, MAX_LINE, clientes);i++) 
	{
			linha[strlen(linha)-1] = '\0';
			trim(linha);
			insertCatalogo_Clientes(cl,linha, cresceu);
	}
	fclose(clientes);
	
	for(i=0;fgets(linha, MAX_LINE, produtos);i++)
	{ 
			linha[strlen(linha)-1] = '\0';
			trim(linha);
			insertCatalogo_Produtos(pl, linha, cresceu);
	}
	fclose(produtos);
	
	for(i=0;fgets(linha, MAX_LINE,fcompras);i++)
	{
			linha[strlen(linha)-1] = '\0';
			trim(linha);
			strcpy(compras[i],linha);
			tokenizer(array, i, compras[i]);
			/*indexProd e indexClnt calculados nos catalagos*/
			validaClnt=validateClnt(array[i], cl);
			validaProd=validateProd(array[i], pl);
			validaCmpr=validateCompras(array[i]);
			if(validaClnt==0) clntInv++;
			if(validaProd==0) prodInv++;
			if(validaClnt==0 || validaProd==0 || validaCmpr==0) compras_invalidas++;
			else fact+=array[i].preco_unitario;
			countCompras++;
	}
	fclose(fcompras);
	printf("\nPRODUTOS: %d\n", codigos_Produto());
	printf("CLIENTES: %d\n", codigos_Cliente());
	printf("LINHAS DE COMPRAS: %d\n", countCompras);
	printf("CODIGOS DE CLIENTE INEXISTENTES: %d\n", clntInv);
	printf("CODIGOS DE PRODUTO INEXISTENTES: %d\n", prodInv);
	printf("TOTAL DE COMPRAS INVALIDAS: %d\n", compras_invalidas);
	printf("--------------------------------------------\n");
	printf("COMPRAS VALIDAS: %d\n", (countCompras-compras_invalidas));
	printf("FATURACAO ANUAL TOTAL: %.2f Euros\n\n", fact);

	printf("-- CODIGOS DE CLIENTES POR LETRA NO CATALOGO --\n\n");
	codClientes(cl);
	printf("\n-- CODIGOS DE PRODUTOS POR LETRA NO CATALOGO --\n\n");
	codProdutos(pl);
	printf("\n");


	for(i=0;i<MAX;i++)
		free(compras[i]);
	free(compras);

	end=clock();
	time_spent=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("Tempo de execucao: %.2f segundos\n\n", time_spent);
	
	return 0;
}
	

	
	
