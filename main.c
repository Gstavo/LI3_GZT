#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include "leitura.h"


int main() {
	int comprasMes[12], optn, prim, ult, vendas=0,i, compras_mes[12][1], clientes_mes[12][1];
	double time_spent, fact=0;
	char *cl=(char*) malloc(5*sizeof(char*)), escolha, **lista_letra=(char**) malloc(MAX*sizeof(char**)), nome[100];
	FILE *compras_cliente;
	AAVL clnt, prod;
	Contabilidade cont;
	HashTable ht;
	Comp compra;
	clock_t begin, end;
	char scanmenu;

	begin=clock();

	/*Inicializa as estruturas*/
	compra=initCompra();
	ht=initHashCompras();
	initCatalogo_Clientes(clnt);
	initCatalogo_Produtos(prod);
	initContabilidade(cont);

	/*Query 1*/
	leitura(clnt, prod, cont, ht, compra);

	puts("Deseja ir para as queries?? s/n");
	if(scanf("%c",&scanmenu) && (scanmenu == 's' || scanmenu == 'S'))
	{	

	/*Query 2*/
	printf("-- CODIGOS DE CLIENTES POR LETRA NO CATALOGO --\n\n");
	codClientes(clnt);
	printf("\n-- CODIGOS DE PRODUTOS POR LETRA NO CATALOGO --\n\n");
	codProdutos(prod);
	printf("\n");

	/*Query 5*/
	printf("INSIRA UM CLIENTE: ");
	if(gets(cl));
	compMes(cont, cl, comprasMes);
	printf("DESEJA GUARDAR O RESULTADO NUM FICHEIRO DE TEXTO OU IMPRIMIR NO ECRA?\n0 - FICHEIRO, 1 - ECRA: ");
	if(scanf("%d", &optn));
	if(optn==1) {
		printf("\n");
		printf("COMPRAS DE "); for(i=0; i<5; i++) printf("%c", cl[i]); printf(" POR MES:\n");
		for(i=0; i<12; i++) printf("%d: %d\n", (i+1), comprasMes[i]);
	} 
	else {
		compras_cliente=fopen("compras_cliente.txt", "w");
		fprintf(compras_cliente, "COMPRAS DE ");  
		for(i=0; i<5; i++) fprintf(compras_cliente, "%c", cl[i]);
		fprintf(compras_cliente, " POR MES:\n");
		for(i=0; i<12; i++) fprintf(compras_cliente, "%d: %d\n", (i+1), comprasMes[i]);
		fclose(compras_cliente);
	}

	/*Query 6*/
	printf("\nINSIRA A LETRA QUE INICIA OS CODIGOS DE CLIENTES QUE DESEJA SABER:\n");
	if(scanf("%c", &escolha));
	if((escolha>65 && escolha<90) || (escolha>97 && escolha<122)) {	
		imprimir_cliente(lista_letra, clnt, escolha);	
	}

	/*Query 7*/
	printf("\nINSIRA UM INTERVALO DE MESES:\n");
	printf("MES INICIAL: "); if(scanf("%d", &prim));
	printf("MES FINAL: "); if(scanf("%d", &ult));
	for(i=prim-1; i<ult; i++) {
		fact+=returnFact(i);
		vendas+=returnVendas(i);
	}
	printf("\n");
	printf("TOTAL DE VENDAS EFETUADAS NESSE INTERVALO: %d\n", vendas);
	printf("FATURACAO TOTAL NESSE INTERVALO: %.2f\n\n", fact);

	/*Query 11*/
	printf("\n INSIRA O NOME DO FICHEIRO .CSV QUE PRETENDE CRIAR: ");
	/*if(gets(nome));*/
	preenchecmp(compras_mes);
	preencheclientes(clientes_mes);
	create_csv(nome,compras_mes,clientes_mes);

	}
	end=clock();
	time_spent=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("Tempo de execucao: %.2f segundos\n\n", time_spent);
	
	return 0;
}
	
