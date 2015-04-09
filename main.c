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
	int comprasMes[12], optn, prim, ult, i, compras_mes[12][1], clientes_mes[12][1], query;
	double time_spent;
	VENDAS_MES vendas=0;
	FACTORACAO_TOTAL fact=0;
	char *cl=(char*) malloc(10*sizeof(char*)), **lista_letra=(char**) malloc(MAX*sizeof(char**));
	char nome[30]="query11\0";
	char escolha='A';
	FILE *compras_cliente;
	AAVL clnt, prod;
	Contabilidade cont;
	HashTable ht;
	Comp compra;
	clock_t begin, end;

	cl="ET473\0";
	
	begin=clock();

	/*Inicializa as estruturas*/
	compra=initCompra();
	ht=initHashCompras();
	initCatalogo_Clientes(clnt);
	initCatalogo_Produtos(prod);
	initContabilidade(cont);

	/*Query 1 (Funcional)*/
	leitura(clnt, prod, cont, ht, compra);

	puts("ESCOLHA UMA QUERY: ");
	if(scanf("%d", &query)) {
		if(query==2) {		/*Funcional*/
			printf("-- CODIGOS DE CLIENTES POR LETRA NO CATALOGO --\n\n");
			codClientes(clnt);
			printf("\n-- CODIGOS DE PRODUTOS POR LETRA NO CATALOGO --\n\n");
			codProdutos(prod);
			printf("\n");
		}
		else if(query==5) {	/*Funcional, mas falha no gets*/
			printf("INSIRA UM CLIENTE: ");
			/*gets(cl);*/
			compMes(cont, cl, comprasMes);
			printf("DESEJA GUARDAR O RESULTADO NUM FICHEIRO DE TEXTO OU IMPRIMIR NO ECRA?\n0 - FICHEIRO, 1 - ECRA: ");
			if(scanf("%d", &optn)) {
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
			}
		}
		else if(query==6) {	/*Funcional, mas falha no getchar*/
			printf("\nINSIRA A LETRA QUE INICIA OS CODIGOS DE CLIENTES QUE DESEJA SABER:\n");
			/*scanf("%c", &escolha);*/
			if((escolha>65 && escolha<90) || (escolha>97 && escolha<122)) imprimir_cliente(lista_letra, clnt, escolha);	
		}
		else if(query==7) {	/*Funcional*/
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
		}
		else if(query==11) {	/*Funcional, mas falha no gets*/
			printf("\nINSIRA O NOME DO FICHEIRO .CSV QUE PRETENDE CRIAR: ");
			/*gets(nome);*/
			preenchecmp(compras_mes);
			preencheclientes(clientes_mes);
			create_csv(nome, compras_mes,clientes_mes);
		}
	}
	end=clock();
	time_spent=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("\nTempo de execucao: %.2f segundos\n\n", time_spent);
	
	return 0;
}
	
