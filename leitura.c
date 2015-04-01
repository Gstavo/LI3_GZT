#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "leitura.h"

int main () {
	int i=0,countCompras=0, compras_invalidas=0, vendas=0; 
	int prim, ult;			/*Utilizados na query 7: prim(primeiro mes), ult(ultimo mes)*/
	double fact=0, time_spent;	
	int validaClnt=0, validaProd=0, validaCmpr=0, clntInv=0, prodInv=0;	
	FILE *clientes, *produtos, *fcompras;
	char linha[MAX_LINE];
	int *cresceu=(int*) malloc(sizeof(int));	/*Verifica se a AVL cresceu*/
	AAVL cl, pl;	/*cl - array com AVL's de clientes, pl - array com AVL's de produtos*/
	Contabilidade contabilidade;
	clock_t begin, end;
	
	Comp compra = malloc(sizeof(struct compras));
	compra->codigo_produto = malloc(10*sizeof(char));
	compra->codigo_cliente = malloc(10*sizeof(char));
	
	begin=clock();

	/*Inicializa as estruturas*/
	initCatalogo_Clientes(cl);
	initCatalogo_Produtos(pl);
	initContabilidade(contabilidade);
	
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
			tokenizer(compra,linha);
			validaClnt=validateClnt((*compra), cl);
			validaProd=validateProd((*compra), pl);
			validaCmpr=validateCompras((*compra));
			if(validaClnt==0) clntInv++;
			if(validaProd==0) prodInv++;
			if(validaClnt==0 || validaProd==0 || validaCmpr==0) compras_invalidas++;
			else {
				insertContabilidade(contabilidade,compra,cresceu);
				fact+=returnFact(indexM(compra));
				/* Futuramente vai inserir a compra nas estruturas de dados em compras.c tambemaqui */
			}
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

	/*Resultados da query 7*/
	fact=0;
	printf("INSIRA UM INTERVALO DE MESES:\n");
	printf("MES INICIAL: "); scanf("%d", &prim);
	printf("MES FINAL: "); scanf("%d", &ult);
	for(i=prim-1; i<ult; i++) {
		fact+=returnFact(i);
		vendas+=returnVendas(i);
	}
	printf("\n");
	printf("TOTAL DE VENDAS EFETUADAS NESSE INTERVALO: %d\n", vendas);
	printf("FATURACAO TOTAL NESSE INTERVALO: %.2f\n\n", fact);
	
	end=clock();
	time_spent=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("Tempo de execucao: %.2f segundos\n\n", time_spent);
	
	return 0;
}
	

	
	
