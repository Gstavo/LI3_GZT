#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include "leitura.h"

void imprime30(char **lista,int index){
    int i;
    for(i=0;i<30;i++){
        printf("%s\n", lista[index+i]);
    }
}

int main(){
	int comprasMes[12], optn, prim, ult, i=0, j, compras_mes[12][1], clientes_mes[12][1], query, mes,N;
	int seguintes=0,anteriores=0,q=0,k;/*Query 6*/
	int compModeN, compModeP;
	double time_spent;
	VENDAS_MES vendas=0;
	double fact=0;
	char *code=(char*) malloc(10*sizeof(char*)), **lista_letra=(char**) malloc(MAX*sizeof(char**)); 
	char nome[30]="query11\0";
	char cp[10],sn;/*Q 8*/ 
	char escolha=' ';
	FILE *compras_cliente;
	AAVL clnt, prod;
	Contabilidade contClnt, contProd;	/*contProd - contabilidade por codigo de produto*/
	HashTable ht;
	Comp compra;
	clock_t begin, end;
	
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
		if(query==2) {		/*Não lê o carater escolha*/
			printf("\nINSIRA:\n1-NUMERO DE CLIENTES POR LETRA\n2-NUMERO DE PRODUTOS POR LETRA\n3-LISTA PRODUTOS\n");
			if(scanf("%d", &optn)) {
				if(optn==1) {
					printf("\n-- CODIGOS DE CLIENTES POR LETRA NO CATALOGO --\n\n");
					codClientes(clnt);
					printf("\n");

				}
				else if(optn==2) {
					printf("\n-- CODIGOS DE PRODUTOS POR LETRA NO CATALOGO --\n\n");
					codProdutos(prod);
					printf("\n");
				}
				else {
					printf("\nINSIRA A LETRA QUE INICIA OS CODIGOS DE PRODUTOS QUE DESEJA SABER:\n");
					if(scanf("%c",&escolha)) {
						imprimir_produto(lista_letra, prod, escolha);
						i=0;
    						printf("\nOS PRIMEIROS RESULTADOS:\n");
    						imprime30(lista_letra,i);
    						printf("SE DESEJAR SAIR ESCREVA S.\n");
    						printf("SE DESEJAR CONTINUAR ESCREVA P.\n");
    						printf("SE DESEJAR VER OS RESULTADOS ANTERIORES ESCREVA A.\n");
						do {
							if(scanf("%c", &escolha)) {
								if(escolha=='S' || escolha=='s') break;
        							else if(escolha=='P'|| escolha=='p') {
									seguintes++;
									i+=(30*seguintes);
									imprime30(lista_letra, i);
								}
        							else if(escolha=='A'|| escolha=='a') {
									anteriores++;
									i-=(30*anteriores);
									imprime30(lista_letra,i);
								}
							}
    						} while(escolha!='s'|| escolha!='S');
					}
				}
			}
		}
		else if(query==3) {	/*Funcional*/
			printf("\nINSIRA UM MES: "); if(scanf("%d", &mes));
			printf("INSIRA UM CODIGO DE PRODUTO: ");
			if(scanf("%s", code)) {
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
		}
		else if(query==5) {	/*Funcional*/
			printf("\nINSIRA UM CLIENTE: ");
			if(scanf("%s", code)) {	
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
		}
		else if(query==6) {	/*Nao lê o carater escolha*/
			printf("\nINSIRA A LETRA QUE INICIA OS CODIGOS DE CLIENTES QUE DESEJA SABER:\n");
			if(scanf("%c", &escolha)) {
				imprimir_cliente(lista_letra, clnt, escolha);
    				printf("\nOS PRIMEIROS RESULTADOS:\n");
    				imprime30(lista_letra, 0);
    				printf("SE DESEJAR SAIR ESCREVA S.\n");
    				printf("SE DESEJAR CONTINUAR ESCREVA P.\n");
    				printf("SE DESEJAR VER OS RESULTADOS ANTERIORES ESCREVA A.\n");
    				do {
					if(scanf("%c", &escolha)) {
						if(escolha=='S' || escolha=='s') break;
        					else if(escolha=='P'|| escolha=='p') {
							seguintes++;
							i+=(30*seguintes);
							imprime30(lista_letra, i);
						}
        					else if(escolha=='A'|| escolha=='a') {
							anteriores++;
							i-=(30*anteriores);
							imprime30(lista_letra,i);
						}
					}
    				} while(escolha!='s'|| escolha!='S');
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
		else if(query==8) {	/*Funcional*/
			printf("\nINSIRA UM CODIGO DE PRODUTO:\n");
			if(scanf("%s", cp)) {
				CpInfoList tmp=query8(ht,cp);
				if(getRemakes()) puts("A HASH TABLE FOI REALOCADA E NAO IRA FUNCIONAR DEVIDAMENTE!");
				if(!tmp) puts("PRODUTO SEM ATIVIDADE");
				else {
					for(i=0;tmp && i<25;i++) {
						printf("CLIENTE %s  TIPO %c\n", tmp->cliente, tmp->tipo);
						tmp=tmp->next;
						if(i==24 && tmp) {
							puts("DESEJA ACEDER A MAIS INFORMACAO?\n");
							if(scanf("%c", &sn)) if(sn=='s'||sn=='S') i=-1;
						}
					}
				}
			}
		}
		else if(query==11) {	/*Funcional*/
			preenchecmp(compras_mes);
			preencheclientes(clientes_mes);
			create_csv(nome, compras_mes, clientes_mes);
		}

		else if(query==12) {	/*Funcional*/
			puts("\nINSIRA N PARA OBTER OS N PRODUTOS MAIS VENDIDOS: ");
			if(scanf("%d", &N)) {
				Heap* h=initHeap(ht);
				for(i=0;i < N;i++) {
					printf("PRODUTO: %s\n", h->values[i]->produto);
					printf("      VENDAS: %d CLIENTES: %d\n", h->values[i]->vendas, h->values[i]->clientes);
				}
			}
		}
	
	}

	end=clock();
	time_spent=(double)(end-begin)/CLOCKS_PER_SEC ;
	printf("\nTempo de execucao: %.2f segundos\n\n", time_spent);

	return 0;

}
