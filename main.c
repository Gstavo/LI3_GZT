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
	int comprasMes[12], optn, prim, ult, i, j, compras_mes[12][1], clientes_mes[12][1], query, mes;
	int compModeN, compModeP;
	double time_spent;
	VENDAS_MES vendas=0;
	double fact=0;
	char *code=(char*) malloc(10*sizeof(char*)), **lista_letra=(char**) malloc(MAX*sizeof(char**));
	char nome[30]="query11\0";
	char cp[10],sn;/*Q 8*/ 
	char escolha='A';
	FILE *compras_cliente;
	AAVL clnt, prod;
	Contabilidade contClnt, contProd;	/*contProd - contabilidade por codigo de produto*/
	HashTable ht;
	Comp compra;
	clock_t begin, end;

	/*Nome de teste eqnquanto nao se consegue inserir pelo stdin*/
	code="ZC3371\0";
	
	begin=clock();

	/*Inicializa as estruturas*/
	compra=initCompra();
	ht=initHashCompras();
	initCatalogo_Clientes(clnt);
	initCatalogo_Produtos(prod);
	initContabilidade(contClnt);
	initContabilidade(contProd);

	/*Query 1 (Funcional)*/
	leitura(clnt, prod, contClnt, contProd, ht, compra);

	puts("ESCOLHA UMA QUERY: ");
	if(scanf("%d", &query)) {
		if(query==2) {		/*Funcional*/
			printf("-- CODIGOS DE CLIENTES POR LETRA NO CATALOGO --\n\n");
			codClientes(clnt);
			printf("\n-- CODIGOS DE PRODUTOS POR LETRA NO CATALOGO --\n\n");
			codProdutos(prod);
			printf("\n");
		}
		else if(query==3) {	/*Funcional*/
			printf("\nINSIRA UM MES: "); if(scanf("%d", &mes));
			printf("INSIRA UM CODIGO DE PRODUTO: ");
			/*for(i=0; i<6; i++) code[i]=getchar();
			getchar();*/
			if(validaMes(mes)==FALSE || existeProd(code, prod)==FALSE) printf("\nARGUMENTOS INVALIDOS!!!\n");
			else {
				compModeN=comprasModo(contProd, (mes-1), code, 'N');
				compModeP=comprasModo(contProd, (mes-1), code, 'P');
				fact=totalFactProdMes(contProd, (mes-1), code);
				printf("\nTOTAL DE COMPRAS EM MODO N: %d\n", compModeN);
				printf("TOTAL DE COMPRAS EM MODO P: %d\n", compModeP);
				printf("TOTAL FATURADO PELO PRODUTO NESSE MES: %.2f\n", fact);
			}
		}
		else if(query==5) {	/*Funcional*/
			printf("INSIRA UM CLIENTE: ");
			/*for(i=0; i<5; i++) code[i]=getchar();
			getchar();*/	
			compMes(contClnt, code, comprasMes);
			printf("DESEJA GUARDAR O RESULTADO NUM FICHEIRO DE TEXTO OU IMPRIMIR NO ECRA?\n0 - FICHEIRO, 1 - ECRA: ");
			if(scanf("%d", &optn)) {
				if(optn==1) {
					printf("\n");
					printf("COMPRAS DE "); for(i=0; i<5; i++) printf("%c", code[i]); printf(" POR MES:\n");
					for(i=0; i<12; i++) printf("%d: %d\n", (i+1), comprasMes[i]);
				} 
				else {
					compras_cliente=fopen("compras_cliente.txt", "w");
					fprintf(compras_cliente, "COMPRAS DE ");  
					for(i=0; i<5; i++) fprintf(compras_cliente, "%c", code[i]);
					fprintf(compras_cliente, " POR MES:\n");
					for(i=0; i<12; i++) fprintf(compras_cliente, "%d: %d\n", (i+1), comprasMes[i]);
					fclose(compras_cliente);
				}
			}
		}
		else if(query==6) {	/*Seg.Fault na impressao*/
			printf("\nINSIRA A LETRA QUE INICIA OS CODIGOS DE CLIENTES QUE DESEJA SABER:\n");
			/*escolha=getchar();*/
			imprimir_cliente(lista_letra, clnt, escolha);	
			for(i=0; strlen(lista_letra[i])!=0; i++) {
				for(j=0; j<5; j++) printf("%c", lista_letra[i][j]);
				putchar('\n');
			}
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
		else if(query==8){
			printf("\nInsira um codigo de produto\n");
			if(scanf("%s",cp))
				{
				CpInfoList tmp = query8(ht,cp);
				if(getRemakes()) puts("A ht foi realocada n vai funcionar direito");
				if(!tmp) puts("Produto sem actividade");
				else{
					for(i=0;tmp && i<25;i++){
						printf("Cliente %s  Tipo %c\n",tmp->cliente,tmp->tipo);
						tmp = tmp->next;
						if(i==24 && tmp)
						{
							puts("Deseja aceder a mais informação? s/n");
							if(scanf("%c",&sn))
							if(sn=='s'||sn=='S') i=-1;
						}
						}
					}
				}
		}
		else if(query==11) {	/*Funcional (nome sera query11, dado de forma predefinida)*/
			printf("\nINSIRA O NOME DO FICHEIRO .CSV QUE PRETENDE CRIAR: ");
			preenchecmp(compras_mes);
			preencheclientes(clientes_mes);
			create_csv(nome, compras_mes, clientes_mes);
		}
	}
	end=clock();
	time_spent=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("\nTempo de execucao: %.2f segundos\n\n", time_spent);
	
	return 0;
}
	
