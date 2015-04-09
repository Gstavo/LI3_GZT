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
	int comprasMes[12], optn, prim, ult, i, compras_mes[12][1], clientes_mes[12][1];
	VENDAS_MES vendas=0;
	double time_spent;
	FACTORACAO_TOTAL fact=0;
	char *cl=(char*) malloc(5*sizeof(char*)), escolha, **lista_letra=(char**) malloc(MAX*sizeof(char**)), nome[100];
	FILE *compras_cliente;
	AAVL clnt, prod;
	Contabilidade cont;
	HashTable ht;
	Comp compra;
	clock_t begin, end;
	clock_t begQue1;begQue2;begQue3;begQue4;begQue5;begQue6;begQue7;begQue8;begQue9;begQue10;begQue11;begQue12;begQue13;begQue14;endQue1;endQue2;endQue3;endQue4;endQue5;endQue6;endQue7;endQue8;endQue9;endQue10;endQue11;endQue12;endQue13;endQue14;
	double time_spent_Q1;time_spent_Q2;time_spent_Q3;time_spent_Q4;time_spent_Q5;time_spent_Q6;time_spent_Q7;time_spent_Q8;time_spent_Q9;time_spent_Q10;time_spent_Q11;time_spent_Q12;time_spent_Q13;time_spent_Q14;
	char scanmenu;

	begin=clock();

	/*Inicializa as estruturas*/
	compra=initCompra();
	ht=initHashCompras();
	initCatalogo_Clientes(clnt);
	initCatalogo_Produtos(prod);
	initContabilidade(cont);

	/*Query 1*/
	begQue1=clock();
	leitura(clnt, prod, cont, ht, compra);
	endQue1=clock();

	puts("Deseja ir para as queries?? s/n");
	if(scanf("%c",&scanmenu) && (scanmenu == 's' || scanmenu == 'S'))
	{	

	/*Query 2*/
	begQue2=clock();
	printf("-- CODIGOS DE CLIENTES POR LETRA NO CATALOGO --\n\n");
	codClientes(clnt);
	printf("\n-- CODIGOS DE PRODUTOS POR LETRA NO CATALOGO --\n\n");
	codProdutos(prod);
	printf("\n");
	endQue2=clock();

	/*Query 5*/
	begQue5=clock();
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
	endQue5=clock();

	/*Query 6*/
	begQue6=clock();
	printf("\nINSIRA A LETRA QUE INICIA OS CODIGOS DE CLIENTES QUE DESEJA SABER:\n");
	if(scanf("%c", &escolha));
	if((escolha>65 && escolha<90) || (escolha>97 && escolha<122)) {	
		imprimir_cliente(lista_letra, clnt, escolha);	
	}
	endQue6=clock();

	/*Query 7*/
	begQue7=clock();
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
	endQue7=clock();

	/*Query 11*/
	begQue11=clock();
	printf("\n INSIRA O NOME DO FICHEIRO .CSV QUE PRETENDE CRIAR: ");
	/*if(gets(nome));*/
	preenchecmp(compras_mes);
	preencheclientes(clientes_mes);
	create_csv(nome,compras_mes,clientes_mes);
	endQue11=clock();

	}
	end=clock();
	time_spent=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("Tempo de execucao: %.2f segundos\n\n", time_spent);
	time_spent_Q1=(double)(endQue1-begQue1)/CLOCKS_PER_SEC;
	printf("Tempo de execucao Query 1: %.2f segundos\n\n", time_spent_Q1);	
	time_spent_Q2=(double)(endQue2-begQue2)/CLOCKS_PER_SEC;
	printf("Tempo de execucao Query 2: %.2f segundos\n\n", time_spent_Q2);
	/*
	time_spent_Q3=(double)(endQue3-begQue3)/CLOCKS_PER_SEC;
	printf("Tempo de execucao Query 3: %.2f segundos\n\n", time_spent_Q3);	
	time_spent_Q4=(double)(endQue4-begQue4)/CLOCKS_PER_SEC;
	printf("Tempo de execucao Query 4: %.2f segundos\n\n", time_spent_Q4);	
	*/
	time_spent_Q5=(double)(endQue5-begQue5)/CLOCKS_PER_SEC;
	printf("Tempo de execucao Query 5: %.2f segundos\n\n", time_spent_Q5);
	time_spent_Q6=(double)(endQue6-begQue6)/CLOCKS_PER_SEC;
	printf("Tempo de execucao Query 6: %.2f segundos\n\n", time_spent_Q6);
	time_spent_Q7=(double)(endQue7-begQue7)/CLOCKS_PER_SEC;
	printf("Tempo de execucao Query 7: %.2f segundos\n\n", time_spent_Q7);	
	/*
	time_spent_Q8=(double)(endQue8-begQue8)/CLOCKS_PER_SEC;
	printf("Tempo de execucao Query 8: %.2f segundos\n\n", time_spent_Q8);
	time_spent_Q9=(double)(endQue9-begQue9)/CLOCKS_PER_SEC;
	printf("Tempo de execucao Query 9: %.2f segundos\n\n", time_spent_Q9);
	time_spent_Q10=(double)(endQue10-begQue10)/CLOCKS_PER_SEC;
	printf("Tempo de execucao Query 10: %.2f segundos\n\n", time_spent_Q10);	
	*/
	time_spent_Q11=(double)(endQue11-begQue11)/CLOCKS_PER_SEC;
	printf("Tempo de execucao Query 11: %.2f segundos\n\n", time_spent_Q11);
	/*
	time_spent_Q12=(double)(endQue12-begQue12)/CLOCKS_PER_SEC;
	printf("Tempo de execucao Query 12: %.2f segundos\n\n", time_spent_Q12);
	time_spent_Q13=(double)(endQue13-begQue13)/CLOCKS_PER_SEC;
	printf("Tempo de execucao Query 13: %.2f segundos\n\n", time_spent_Q13);
	time_spent_Q14=(double)(endQue14-begQue14)/CLOCKS_PER_SEC;
	printf("Tempo de execucao Query 14: %.2f segundos\n\n", time_spent_Q14);	
	*/

	return 0;
}
	
