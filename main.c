#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include "leitura.h"

/* Imprime bue codigos depois melhorar o visual */

void query4(HashTable ht, AAVL cp);

void query9(AAVL clnt, Contabilidade contClnt);

void query10();

void query14();

void imprime30(GrowingArray ga,int index) {
	int i;
	for(i=0; i<30 && (index + i) < ga->size ; i++) printf("%s\n",(char*)ga->Elems[index+i]);
}

int main(){
	int comprasMes[12], optn, prim, ult, i=0, compras_mes[12][1], clientes_mes[12][1], query, mes,N;
	int seguintes=0,anteriores=0;/*Query 6*/
	int compModeN, compModeP;
	double time_spent;
	VENDAS_MES vendas=0;
	double fact=0;
	char *code=(char*) malloc(10*sizeof(char*)); 
	char nome[30]="query11\0";
	char cp[10],sn;/*Q 8*/ 
	char escolha='A';
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

	/*
	Faz uma travessia a todos os codigos de cliente recolhendo informaçoes
sobre a atividade de cada -> Query 10 e 14(1/2)
				*/
	gatherData(clnt,contClnt);

	puts("ESCOLHA UMA QUERY: ");
	if(scanf("%d", &query)) {
		if(query==2) {		/*Não lê o carater escolha, imprime resultados errados e anterior=segm.fault*/
			printf("\nESCOLHA A OPCAO:\n1-NUMERO DE CLIENTES POR LETRA\n2-NUMERO DE PRODUTOS POR LETRA\n3-LISTA PRODUTOS\n");
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
					GrowingArray ga = initGrowingArray(10,ArrayString);
					printf("\nINSIRA A LETRA QUE INICIA OS CODIGOS DE PRODUTOS QUE DESEJA SABER:\n");
					/*escolha=getchar();*/
					imprimir_produto(ga, prod, escolha);
    					printf("\nPRIMEIROS RESULTADOS:\n");
    					imprime30(ga, i);
					do {
						printf("\n1-SAIR\n2-PROXIMO\n3-ANTERIOR\n");
						if(scanf("%d", &optn)) {
							if(optn==1) break;
        						else if(optn==2) {
								seguintes++;
								i+=(30*seguintes);
								imprime30(ga, i);
							}
        						else if(optn==3) {
								anteriores++;
								i-=(30*anteriores);
								imprime30(ga,i);
							}
						}
    					} while(optn!=1);
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
					printf("TOTAL FATURADO PELO PRODUTO NESSE MES: %.2f Euros\n", fact);
				}
			}
		}
		else if(query==4) query4(ht,prod);
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
		else if(query==6) {	/*Não lê o carater escolha, imprime resultados errados e anterior=segm.fault*/
			GrowingArray ga = initGrowingArray(10,ArrayString);
			printf("\nINSIRA A LETRA QUE INICIA OS CODIGOS DE CLIENTES QUE DESEJA SABER:\n");
			/*escolha=getchar();*/
			imprimir_cliente(ga, clnt, escolha);
    			printf("\nOS PRIMEIROS RESULTADOS:\n");
    			imprime30(ga, 0);
    			do {
				printf("\n1-SAIR\n2-PROXIMO\n3-ANTERIOR\n");
				if(scanf("%d", &optn)) {
					if(optn==1) break;
        				else if(optn==2) {
						seguintes++;
						i+=(30*seguintes);
						imprime30(ga, i);
					}
        				else if(optn==3) {
						anteriores++;
						i-=(30*anteriores);
						imprime30(ga,i);
					}
				}
    			} while(optn!=1);
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
			printf("FATURACAO TOTAL NESSE INTERVALO: %.2f Euros\n\n", fact);
		}
		else if(query==8) {	/*Funcional*/
			printf("\nINSIRA UM CODIGO DE PRODUTO:\n");
			if(scanf("%s", cp)) {
				CpInfoList tmp=query8(ht,cp);
				if(getRemakes()) puts("A HASH TABLE FOI REALOCADA E NAO IRA FUNCIONAR DEVIDAMENTE!");
				if(!tmp) puts("O PRODUTO NAO EXISTE!");
				else {
					for(i=0;tmp && i<25; i++) {
						printf("CLIENTE %s  TIPO %c\n", tmp->cliente, tmp->tipo);
						tmp=tmp->next;
						if(i==24 && tmp) {
							puts("DESEJA ACEDER A MAIS INFORMACAO? SIM-s/S, NAO-n/N\n");
							if(scanf("%c", &sn)) if(sn=='s'||sn=='S') i=-1;
						}
					}
				}
			}
		}
		else if(query==9) query9(clnt, contClnt);
		else if(query==10) query10();
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
		else if(query==14) query14();
	
	}

	end=clock();
	time_spent=(double)(end-begin)/CLOCKS_PER_SEC ;
	printf("\nTempo de execucao: %.2f segundos\n\n", time_spent);

	return 0;

}

void query4(HashTable ht, AAVL cp)
{
        int i,counter=0;
        GrowingArray ga = initGrowingArray(200000,ArrayString);

        for(i=0;i<MAX_LETTERS;i++)
                guardArrayAVL(cp[i],ga,ArrayString);
        for(i=0;i < ga->size;i++)
                if(!searchHash(ht,ga->Elems[i])) 
			{
			printf("%s\n",(char*)ga->Elems[i]);
			counter++;
			}
	printf("\n %d codigos de produto inativos\n",counter);
}

void query9(AAVL clnt, Contabilidade contClnt) {
	int i, mes;
	char *code=(char*) malloc(10*sizeof(char*));
	GrowingArray ga=initGrowingArray(200000, ArrayCompProduto);		/*Seg.Fault initGrowingArray*/
	printf("\nINSIRA UM MES: "); if(scanf("%d", &mes));
	printf("INSIRA UM CODIGO DE CLIENTE: ");
	if(scanf("%s", code)) {
		if(validaMes(mes)==FALSE || existeClnt(code, clnt)==FALSE) printf("\nARGUMENTOS INVALIDOS!!!\n");
		else {
			guardOcurrencesAVL(contClnt[mes-1][indexL(code)], ga, ArrayCompProduto, code);
			for(i=0; i<ga->size; i++) {
				CompProduto aux=(CompProduto) ga->Elems[i];
				printf("%s\n", aux->codigo_produto);
			}
		}
	}
}

void query10()
{
	GrowingArray cm = getClientesMensais();
	int i;
	for(i=0 ; i < cm->size; i++)
		printf("%s\n",(char*)cm->Elems[i]);
	printf("\n%d codigos\n",cm->size);
}

void query14()
{
	int clientes_inativos = getClientesInativos();
	int produtos_inativos = codigos_Produto() - getCodigosProdutosUsados();
	printf("Clientes inativos = %d\nProdutos inativos = %d",clientes_inativos,produtos_inativos);

}
