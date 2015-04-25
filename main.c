#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include "leitura.h"

void menu();
void query1(int valid[]);
void query2(CatalogoClientes clnt, CatalogoProdutos prod);
void query3(HashTable ht);
void query4(HashTable ht, CatalogoProdutos cp);
void query5(Contabilidade contClnt);
void query6(CatalogoClientes clnt);
void query7();
void query8(HashTable ht);
void query9(CatalogoClientes clnt, Contabilidade contClnt);
void query10();
void query11();
void query12(HashTable ht);
void query13(CatalogoClientes clnt, Contabilidade contClnt);
void query14();

int main(){
	int query, valid[5];			/*valid guarda os resultados da leitura para posterior impressao na query1*/
	char comprastxt[20];
	double time_spent, qTime_spent;
	CatalogoClientes clnt;
	CatalogoProdutos prod;
	Contabilidade contClnt;
	HashTable ht;
	Comp compra;
	clock_t begin,qBegin,qEnd, end;
	
	begin=clock();

	/*Inicializa as estruturas*/
	compra=initCompra();
	ht=initHashCompras();
	initCatalogo_Clientes(clnt);
	initCatalogo_Produtos(prod);
	initContabilidade(contClnt);
	
	puts("\nINSIRA O NOME DO FICHEIRO DE COMPRAS");
	if(!scanf("%s",comprastxt)) puts("ERRO");

	if(strcmp(comprastxt,"compras.txt")==0 || strcmp(comprastxt,"compras1.txt")==0 || strcmp(comprastxt,"compras3.txt")==0) {
	puts("\nA CARREGAR ESTRUTURAS DE DADOS...");
	
	/*Preenchimento e leitura das estruturas de dados*/
	leitura(clnt, prod, contClnt, ht, compra, valid,comprastxt);
	
	gatherData(clnt, contClnt);

	while(1) {
		char c;
		menu();
        	printf ("\nESCOLHA UMA QUERY: ");
	
		if(scanf("%d", &query) && query > 0 && query < 15) {
			qBegin=clock();
			switch(query) {
				case 1: query1(valid); break;			
				case 2: query2(clnt, prod); break;		
				case 3: query3(ht); break;			
				case 4: query4(ht,prod); break;			
				case 5: query5(contClnt); break;		
				case 6: query6(clnt); break;			
				case 7: query7(); break;			
				case 8: query8(ht); break;			
				case 9: query9(clnt, contClnt);	break;		
				case 10: query10(); break;			
				case 11: query11(); break;			
				case 12: query12(ht); break;			
				case 13: query13(clnt, contClnt); break;	
				case 14: query14(); 				
			}	
			qEnd=clock();
			qTime_spent=(double)(qEnd-qBegin)/CLOCKS_PER_SEC;
			qTime_spent*=1000;
			printf("\nTEMPO DE EXECUCAO DA QUERY %d: %.2f ms\n\n", query, qTime_spent);

		}
		puts("PARA SAIR 'N', PARA CONTINUAR 'S'");
		if(scanf(" %c",&c) && (c=='n' || c == 'N')) break; 
	}

	end=clock();
	time_spent=(double)(end-begin)/CLOCKS_PER_SEC ;
	printf("\nTEMPO DE EXECUCAO TOTAL: %.2f segundos\n\n", time_spent);
	return 0;
	}
	else {
		printf("Nome incorrecto!!!\n");
		return 0;
	}

}

void menu () {
        printf ("\n\n--------------------------------MENU----------------------------------------\n\n");
        printf ("1 - INFORMACOES;\n");
        printf ("2 - NUMERO DE CLIENTES E DE PRODUTOS POR LETRA / LISTA DE PRODUTOS POR LETRA;\n");
        printf ("3 - NUMERO DE VENDAS DE UM PRODUTO NUM MES;\n");
        printf ("4 - LISTA DOS PRODUTOS NAO COMPRADOS;\n");
        printf ("5 - COMPRAS MENSAIS DE CADA CLIENTE;\n");
        printf ("6 - LISTA DE CLIENTES INICIADOS POR DADA LETRA;\n");
        printf ("7 - TOTAL DE COMPRAS REALIZADAS DENTRO DE UM INTERVALO DE MESES;\n");
        printf ("8 - CLIENTES QUE COMPRARAM DETERMINADO PRODUTO;\n");
        printf ("9 - PRODUTOS COMPRADOS POR CLIENTE NUM DADO MES;\n");
        printf ("10 - CLIENTES QUE FIZERAM COMPRAS EM TODOS OS MESES DO ANO;\n");
        printf ("11 - FICHEIRO (EXCEL) COM COMPRAS E CLIENTES MENSAIS;\n");
        printf ("12 - PRODUTOS MAIS VENDIDOS DO ANO;\n");
        printf ("13 - OS 3 PRODUTOS MAIS COMPRADOS POR CLIENTE;\n");
        printf ("14 - CLIENTES E PRODUTOS INATIVOS;\n\n");
        printf ("----------------------------------------------------------------------------\n\n");
  }


void query1(int valid[]) {
	printf("\nPRODUTOS: %d\n", codigos_Produto());
	printf("CLIENTES: %d\n", codigos_Cliente());
	printf("LINHAS DE COMPRAS: %d\n", valid[0]);
	printf("CODIGOS DE CLIENTE INEXISTENTES: %d\n", valid[1]);
	printf("CODIGOS DE PRODUTO INEXISTENTES: %d\n", valid[2]);
	printf("TOTAL DE COMPRAS INVALIDAS: %d\n", valid[3]);
	printf("--------------------------------------------\n");
	printf("COMPRAS VALIDAS: %d\n", valid[4]);
	printf("FATURACAO ANUAL TOTAL: %.2f Euros\n\n", returnFactTotal());
}

void query2(CatalogoClientes clnt, CatalogoProdutos prod) {
	int i=0, optn;
	char aux[1], escolha;
	printf("\nESCOLHA A OPCAO:\n1-NUMERO DE CLIENTES POR LETRA\n2-NUMERO DE PRODUTOS POR LETRA\n3-LISTA PRODUTOS\n");
	if(scanf("%d", &optn)) {
		if(optn==1) {
			printf("\n-- CODIGOS DE CLIENTES POR LETRA NO CATALOGO --\n");
			for(i=0; i<MAX_LETTERS; i++) printf("%c: %d\n", i+65, contarNodos(devolveAVL(clnt, i+65)));
			printf("\n");
		}
		else if(optn==2) {
			printf("\n-- CODIGOS DE PRODUTOS POR LETRA NO CATALOGO --\n");
			for(i=0;i<MAX_LETTERS;i++) printf("%c: %d\n",i+65,contarNodos(devolveAVL(prod, i+65)));
			printf("\n");
		}
		else {
			int intervalo, res;
        		GrowingArray ga = initGrowingArray(10000,ArrayString);
        		printf("\nINSIRA A LETRA QUE INICIA OS CODIGOS DE PRODUTOS QUE DESEJA SABER:\n");
			if(scanf("%s", aux)) {
				escolha=aux[0];
				if((escolha>=97 && escolha<=122)) guardArrayAVL(prod[escolha-97],ga,ArrayString);
				else guardArrayAVL(prod[escolha-65],ga,ArrayString);
				printf("\nINSIRA O NUMERO DE CODIGOS QUE DESEJA VER POR PAGINA:\n");
				if(scanf("%d", &res)) {
					intervalo=ga->size/res;
					printf("\n**AJUDA** INSIRA PRIMEIRO O NUMERO DA PAGINA ANTES DE VIZUALIZAR A LISTA\n");
					do {
						printf("\nSAIR-0\nESCOLHER PAGINA-1/%d\n", intervalo+1);
						if(scanf("%d", &optn)) {
							if(optn==intervalo+1) {	/*ultima pagina tem sempre res ou menos codigos*/
								for(i=(optn-1)*res; i<(optn-1)*res+(ga->size-(intervalo*res)); i++) 
									printf("%s\n",(char*)ga->Elems[i]);
							}
							else if(optn>0 && optn<=intervalo+1) {
								for(i=(optn-1)*res; i<(optn-1)*res+res; i++) 
									printf("%s\n",(char*)ga->Elems[i]);
							}
						}
						if(optn<0 || optn>intervalo+1) printf("\nINSIRA UM VALOR CORRETO!\n");
					} while(optn!=0);
				}
			}
		}
	}
}
        			

void query3(HashTable ht) {
	int mes, compModeN, compModeP;
	double fact=0;
	char *code=(char*) malloc(10*sizeof(char*));  
	compModeN = compModeP = 0;
	printf("\nINSIRA UM MES: "); 
	if(scanf("%d", &mes)) {
		printf("INSIRA UM CODIGO DE PRODUTO: ");
		if(scanf("%s", code)) {
			CpInfo cpinfo = searchHash(ht,code);
			if(validaMes(mes)==FALSE || cpinfo==NULL) printf("\nARGUMENTOS INVALIDOS!!!\n");
			else {
				CpInfoList tmp;				
				for(tmp = cpinfo->first ; tmp ; tmp = tmp->next) {
					if(tmp->mes == mes) {
						fact += tmp->fact;
						if(tmp->tipo == 'N') compModeN++; else compModeP++;
					}
				}
				printf("\nTOTAL DE COMPRAS EM MODO N: %d\n",compModeN);
				printf("TOTAL DE COMPRAS EM MODO P: %d\n",compModeP);
				printf("TOTAL FATURADO PELO PRODUTO NESSE MES: %.2f Euros\n",fact);
				printf("\n**NOTA** A LISTA ESTA APRESENTADA POR COMPRAS, NAO POR QUANTIDADE COMPRADA\n");
			}
		}
	}
}


void query4(HashTable ht, CatalogoProdutos cp) {
        int i, res, total=0, intervalo, optn;
        int booleano=0;
	char prodNComp[200000][10];	/*guarda os produtos nao comprados*/
        GrowingArray ga = initGrowingArray(10,ArrayString);
        for(i=0;i<MAX_LETTERS;i++) guardArrayAVL(cp[i],ga,ArrayString);
        for(i=0;booleano!=1 && i < ga->size;i++) {
		if(!searchHash(ht,ga->Elems[i])) {
			strncpy(prodNComp[total], (char*)ga->Elems[i], 6);
			total++;
		}
	}
	printf("\nINSIRA O NUMERO DE CODIGOS QUE DESEJA VER POR PAGINA:\n");
	if(scanf("%d", &res)) {
		intervalo=total/res;
		printf("\n**AJUDA** INSIRA PRIMEIRO O NUMERO DA PAGINA ANTES DE VIZUALIZAR A LISTA\n");
		do {
			printf("\nSAIR-0\nESCOLHER PAGINA-1/%d\n", intervalo+1);
			if(scanf("%d", &optn)) {
				if(optn==intervalo+1) {	/*ultima pagina tem sempre res ou menos codigos*/
					for(i=(optn-1)*res; i<(optn-1)*res+(total-(intervalo*res)); i++) printf("%s\n", prodNComp[i]);
				}
				else if(optn>0 && optn<=intervalo+1) {
					for(i=(optn-1)*res; i<(optn-1)*res+res; i++) printf("%s\n", prodNComp[i]);
				}
			}
			if(optn<0 || optn>intervalo+1) printf("\nINSIRA UM VALOR CORRETO!\n");
		} while(optn!=0);
	}
	printf("\nNUMERO DE PRODUTOS QUE NINGUEM COMPROU: %d\n",total);
}

void query5(Contabilidade contClnt) {
	int i, comprasMes[12], optn;
	char *code=(char*) malloc(10*sizeof(char*));  
	FILE *compras_cliente;
	printf("\nINSIRA UM CLIENTE: ");
	if(scanf("%s", code)) {	
		compMes(contClnt, code, comprasMes);
		printf("DESEJA GUARDAR O RESULTADO NUM FICHEIRO DE TEXTO OU IMPRIMIR NO ECRA?\n0 - FICHEIRO, 1 - ECRA: ");
		if(scanf("%d", &optn)) {
			if(optn==1) {
				printf("\n");
				printf("COMPRAS DE "); for(i=0; i<5; i++) printf("%c", code[i]); printf(" POR MES:\n");
				printf("  ____________________________\n");
				printf(" |      #Mes   "); printf("     |# Compras|\n");
				printf(" |__________________|_________|\n");
				for(i=0; i<9; i++){
					printf(" |        %d         |   %d     |\n", (i+1), comprasMes[i]);
					printf(" |__________________|_________|\n");
				}
				for(i=9; i<12; i++){
					printf(" |        %d        |   %d     |\n", (i+1), comprasMes[i]);
					printf(" |__________________|_________|\n");
				}
				printf("\n**NOTA** A TABELA ESTA APRESENTADA POR COMPRAS, NAO POR QUANTIDADE COMPRADA\n");
			} 
			else {
				compras_cliente=fopen("compras_cliente.txt", "w");
				fprintf(compras_cliente, "COMPRAS DE ");  
				for(i=0; i<5; i++) fprintf(compras_cliente, "%c", code[i]);
				fprintf(compras_cliente, " POR MES:\n");
				for(i=0; i<12; i++) fprintf(compras_cliente, "%d: %d\n", (i+1), comprasMes[i]);
				fprintf(compras_cliente, "\n**NOTA** A TABELA ESTA APRESENTADA POR COMPRAS, NAO POR QUANTIDADE COMPRADA\n");
				printf("\nFICHEIRO \"compras_cliente.txt\" CRIADO COM SUCESSO!\n");
				fclose(compras_cliente);
			}
		}
	}
}

void query6(CatalogoClientes clnt) {
	char aux[1], escolha;
	int i,res, optn, intervalo;
        GrowingArray ga = initGrowingArray(20000,ArrayString);
        printf("\nINSIRA A LETRA QUE INICIA OS CODIGOS DE CLIENTES QUE DESEJA SABER:\n");
	if(scanf("%s", aux)) {
		escolha=aux[0];
		if((escolha>=97 && escolha<=122)) guardArrayAVL(clnt[escolha-97],ga,ArrayString);
		else guardArrayAVL(clnt[escolha-65],ga,ArrayString);
        	printf("\nINSIRA O NUMERO DE CODIGOS QUE DESEJA VER POR PAGINA:\n");
		if(scanf("%d", &res)) {
			intervalo=ga->size/res;
			printf("\n**AJUDA** INSIRA PRIMEIRO O NUMERO DA PAGINA ANTES DE VIZUALIZAR A LISTA\n");
			do {
				printf("\nSAIR-0\nESCOLHER PAGINA-1/%d\n", intervalo+1);
				if(scanf("%d", &optn)) {
					if(optn==intervalo+1) {	/*ultima pagina tem sempre res ou menos codigos*/
						for(i=(optn-1)*res; i<(optn-1)*res+(ga->size-(intervalo*res)); i++) 
							printf("%s\n",(char*)ga->Elems[i]);
					}
					else if(optn>0 && optn<=intervalo+1) {
						for(i=(optn-1)*res; i<(optn-1)*res+res; i++) printf("%s\n",(char*)ga->Elems[i]);
					}
				}
				if(optn<0 || optn>intervalo+1) printf("\nINSIRA UM VALOR CORRETO!\n");
			} while(optn!=0);
		}
	}
}

void query7() {
	int i, prim, ult;
	double fact=0;
	VENDAS_MES vendas=0;
	printf("\nINSIRA UM INTERVALO DE MESES:\n");
	printf("MES INICIAL: "); 
	if(scanf("%d", &prim)) {
		printf("MES FINAL: "); 
		if(scanf("%d", &ult)) {
			for(i=prim-1; i<ult; i++) {
				fact+=returnFact(i);
				vendas+=returnVendas(i);
			}
			printf("\n");
			printf("TOTAL DE VENDAS EFETUADAS NESSE INTERVALO: %d\n", vendas);
			printf("FATURACAO TOTAL NESSE INTERVALO: %.2f Euros\n\n", fact);
		}
	}
}

void query8(HashTable ht) {
	int i;
	char cp[10], sn;
	printf("\nINSIRA UM CODIGO DE PRODUTO: ");
	if(scanf("%s", cp)) {
		CpInfoList tmp=query8Aux(ht,cp);
		if(!tmp) puts("O PRODUTO NAO EXISTE!");
		else {
			putchar('\n');
			for(i=0;tmp && i<25; i++) {
				printf("CLIENTE %s | TIPO %c\n", tmp->cliente, tmp->tipo);
				tmp=tmp->next;
				if(i==24 && tmp) {
					puts("DESEJA ACEDER A MAIS INFORMACAO? SIM-s/S, NAO-n/N\n");
					if(scanf("%c", &sn)) if(sn=='s'||sn=='S') i=-1;
				}
			}
		}
	}
}

void query9(CatalogoClientes clnt, Contabilidade contClnt) {
	int i, mes, **arrayAux=malloc(200000*sizeof(int*)), index;
	char *code=(char*) malloc(10*sizeof(char));
	GrowingArray ga=initGrowingArray(200000, ArrayCompProduto);		
	printf("\nINSIRA UM MES: "); 
	if(scanf("%d", &mes)) {
		printf("INSIRA UM CODIGO DE CLIENTE: ");
		if(scanf("%s", code)) {
			if(validaMes(mes)==FALSE || existeClnt(code, clnt)==FALSE) printf("\nARGUMENTOS INVALIDOS!!!\n");
			else {
				guardOcurrencesAVL(contClnt[mes-1][indexL(code)], ga, ArrayCompProduto, code);
				if(ga->size == 0) puts("\nNADA ENCONTRADO");
				else {
					for(i=0; i<ga->size; i++) {
						CompProduto aux=ga->Elems[i];
						arrayAux[i]=malloc(2*sizeof(int));
						arrayAux[i][0]=aux->quantidade;
						arrayAux[i][1]=i;
					}
					ordenaArrayAux(arrayAux, ga->size);
					putchar('\n');
					for(i=0; i<ga->size; i++) {
						CompProduto aux;
						index=arrayAux[i][1];
						aux=(CompProduto) ga->Elems[index];
						printf("PRODUTO: %s | QUANTIDADE: %d\n", aux->codigo_produto, aux->quantidade);
					}
				}
			}
		}
	}
}

void query10() {
	GrowingArray ga=getClientesMensais();
	int i, res, intervalo, optn;
	printf("\nINSIRA O NUMERO DE CODIGOS QUE DESEJA VER POR PAGINA:\n");
	if(scanf("%d", &res)) {
		intervalo=ga->size/res;
		printf("\n**AJUDA** INSIRA PRIMEIRO O NUMERO DA PAGINA ANTES DE VIZUALIZAR A LISTA\n");
		do {
			printf("\nSAIR-0\nESCOLHER PAGINA-1/%d\n", intervalo+1);
			if(scanf("%d", &optn)) {
				if(optn==intervalo+1) {	/*ultima pagina tem sempre res ou menos codigos*/
					for(i=(optn-1)*res; i<(optn-1)*res+(ga->size-(intervalo*res)); i++) 
						printf("%s\n",(char*)ga->Elems[i]);
				}
				else if(optn>0 && optn<=intervalo+1) {
					for(i=(optn-1)*res; i<(optn-1)*res+res; i++) printf("%s\n",(char*)ga->Elems[i]);
				}
			}
			if(optn<0 || optn>intervalo+1) printf("\nINSIRA UM VALOR CORRETO!\n");
		} while(optn!=0);
	}
	printf("\nTOTAL DE CLIENTES QUE REALIZARAM COMPRAS EM TODOS OS MESES DO ANO: %d\n", ga->size);
}

void query11() {
	int compras_mes[12], clientes_mes[12];
	preenchecmp(compras_mes);
	preencheclientes(clientes_mes);
	create_csv(compras_mes, clientes_mes);
	printf("\nFICHEIRO \"query11.csv\" CRIADO COM SUCESSO!\n");
}

void query12(HashTable ht) {
	int i, N;
	puts("\nINSIRA N PARA OBTER OS N PRODUTOS MAIS VENDIDOS: ");
	if(scanf("%d", &N)) {
		Heap* h=initHeap(ht);
		putchar('\n');
		if(N<=10) {
			for(i=0;i < N;i++) {
				printf("PRODUTO: %s | ", h->values[i]->produto);
				printf("VENDAS: %d | CLIENTES: %d\n", h->values[i]->vendas, h->values[i]->clientes);
			}
		}
		else {
			int res, intervalo, optn;
			printf("\nINSIRA O NUMERO DE CODIGOS QUE DESEJA VER POR PAGINA:\n");
			if(scanf("%d", &res)) {
				intervalo=N/res;
				printf("\n**AJUDA** INSIRA PRIMEIRO O NUMERO DA PAGINA ANTES DE VIZUALIZAR A LISTA\n");
				do {
					printf("\nSAIR-0\nESCOLHER PAGINA-1/%d\n", intervalo+1);
					if(scanf("%d", &optn)) {
						putchar('\n');
						if(optn==intervalo+1) {	/*ultima pagina tem sempre res ou menos codigos*/
							for(i=(optn-1)*res; i<(optn-1)*res+(N-(intervalo*res)); i++) {
								printf("PRODUTO: %s | ", h->values[i]->produto);
								printf("VENDAS: %d | CLIENTES: %d\n", h->values[i]->vendas, h->values[i]->clientes);
							}
						}
						else if(optn>0 && optn<=intervalo+1) {
							for(i=(optn-1)*res; i<(optn-1)*res+res; i++) {
								printf("PRODUTO: %s | ", h->values[i]->produto);
								printf("VENDAS: %d | CLIENTES: %d\n", h->values[i]->vendas, h->values[i]->clientes);
							}
						}
					}
					if(optn<0 || optn>intervalo+1) printf("\nINSIRA UM VALOR CORRETO!\n");
				} while(optn!=0);
			}
		}
	}
}



void query13(CatalogoClientes clnt, Contabilidade contClnt) {
	int i, mes, max1=0, max2=0, max3=0;
	char *m1=malloc(10*sizeof(char)), *m2=malloc(10*sizeof(char)), *m3=malloc(10*sizeof(char));
	char *code=(char*) malloc(10*sizeof(char));
	GrowingArray ga=initGrowingArray(200000, ArrayCompProduto);		
	printf("INSIRA UM CODIGO DE CLIENTE: ");
	if(scanf("%s", code)) {
		if(existeClnt(code, clnt)==FALSE) printf("\nARGUMENTOS INVALIDOS!!!\n");
		else {
			for(mes=0; mes<11; mes++) guardOcurrencesAVL(contClnt[mes][indexL(code)], ga, ArrayCompProduto, code);
			if(ga->size==0) puts("\nNADA ENCONTRADO");
			else {
				putchar('\n');
				for(i=0; i<ga->size; i++) {
					CompProduto aux=ga->Elems[i];
					if(aux->quantidade>max1 || aux->quantidade>max2 || aux->quantidade>max3) {
						if(aux->quantidade>max1 && (max2>max1 || max3>max1)) {
							max1=aux->quantidade; 
							strncpy(m1, aux->codigo_produto, 6);
						}
						else if(aux->quantidade>max2 && (max1>max2 || max3>max2)) {
							max2=aux->quantidade;
							strncpy(m2, aux->codigo_produto, 6);
						}
						else {
							max3=aux->quantidade;
							strncpy(m3, aux->codigo_produto, 6);
						}
					}
				}
				if(strlen(m1)>0) printf("PRODUTO: %s | QUANTIDADE: %d\n", m1, max1);
				if(strlen(m2)>0) printf("PRODUTO: %s | QUANTIDADE: %d\n", m2, max2);
				if(strlen(m3)>0) printf("PRODUTO: %s | QUANTIDADE: %d\n", m3, max3);

			}
		}
	}
}

void query14() {
	int clientes_inativos = getClientesInativos();
	int produtos_inativos = codigos_Produto() - getCodigosProdutosUsados();
	printf("\nCLIENTES QUE NAO REALIZARAM COMPRAS: %d\nPRODUTOS QUE NINGUEM COMPROU: %d\n",clientes_inativos, produtos_inativos);

}
