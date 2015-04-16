#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include "leitura.h"

void query1(int valid[]);
void query2(AAVL clnt, AAVL prod);
void query3(Contabilidade contProd, AAVL prod);
void query4(HashTable ht, AAVL cp);
void query5(Contabilidade contClnt);
void query6(AAVL clnt);
void query7();
void query8(HashTable ht);
void query9(AAVL clnt, Contabilidade contClnt);
void query10();
void query11();
void query12(HashTable ht);
void query14();

void imprime30(GrowingArray ga,int index) {
	int i;
	for(i=0; i<30 && (index + i) < ga->size ; i++) printf("%s\n",(char*)ga->Elems[index+i]);
}

int main(){
	int query, valid[5];			/*valid guarda os resultados da leitura para posterior impressao na query1*/
	double time_spent;
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

	/*Preenchimento e leitura das estruturas de dados*/
	leitura(clnt, prod, contClnt, contProd, ht, compra, valid);

	/*Faz uma travessia a todos os codigos de cliente recolhendo informaçoes sobre a atividade de cada um*/
	gatherData(clnt, contClnt);

	puts("\nESCOLHA UMA QUERY: ");
	if(scanf("%d", &query)) {
		switch(query) {
			case 1: query1(valid); break;			/*Funcional*/
			case 2: query2(clnt, prod); break;		/*Funcional, mas nao volta para tras*/
			case 3: query3(contProd, prod);	break;		/*Fact da resultado inteiro*/
			case 4: query4(ht,prod); break;			/*Funcional, mas nao volta para tras*/
			case 5: query5(contClnt); break;		/*Funcional*/
			case 6: query6(clnt); break;			/*Funcional, mas nao volta para tras*/
			case 7: query7(); break;			/*Funcional*/
			case 8: query8(ht); break;			/*Funcional*/
			case 9: query9(clnt, contClnt);	break;		/*Falta ordenar resultados*/
			case 10: query10(); break;			/*Funcional, mas falta a navegacao*/
			case 11: query11(); break;			/*Funcional*/
			case 12: query12(ht); break;			/*Funcional*/
			case 14: query14(); 				/*Funcional*/
		}
	}

	end=clock();
	time_spent=(double)(end-begin)/CLOCKS_PER_SEC ;
	printf("\nTEMPO DE EXECUCAO: %.2f segundos\n\n", time_spent);

	return 0;

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

void query2(AAVL clnt, AAVL prod) {
	int i=0, optn;
	char escolha='A';
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
			int j,res,counter=0;
        		int booleano=0;
       			int quantas;
        		GrowingArray ga = initGrowingArray(10000,ArrayString);
        		printf("\nINSIRA A LETRA QUE INICIA OS CODIGOS DE PRODUTOS QUE DESEJA SABER:\n");
			/*escolha=getchar();*/
			guardArrayAVL(prod[escolha-65],ga,ArrayString);
        		for(j=0;booleano!=1 && j < ga->size;j++) {
				printf("%s\n",(char*)ga->Elems[j]);
				counter++;
				if(counter%30==0) {
					printf("\nDESEJA CONTINUAR?\n1-SAIR\n2-PROXIMA\n3-ANTERIOR\n\n");
					if(scanf("%d", &res)) {
						if(res==1) booleano=1;
						if(res==3) {
							printf("ESCREVA QUANTAS PAGINAS QUER VOLTAR A ATRAS?\n");
							if(scanf("%d", &quantas)) if(quantas>0) j-=(j*quantas);
						}
					}
				}
			}
		}
	}
}

void query3(Contabilidade contProd, AAVL prod) {
	int mes, compModeN, compModeP;
	double fact=0;
	char *code=(char*) malloc(10*sizeof(char*));  
	printf("\nINSIRA UM MES: "); 
	if(scanf("%d", &mes)) {
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
}

void query4(HashTable ht, AAVL cp) {
        int i,res,counter=0,total=0;
        int booleano=0;
        int quantas;
        GrowingArray ga = initGrowingArray(200000,ArrayString);
	printf("\nLISTA DE PRODUTOS NAO COMPRADOS: \n");
        for(i=0;i<MAX_LETTERS;i++) guardArrayAVL(cp[i],ga,ArrayString);
        for(i=0;booleano!=1 && i < ga->size;i++) if(!searchHash(ht,ga->Elems[i])) {total++;}
        for(i=0;booleano!=1 && i < ga->size;i++) {
                if(!searchHash(ht,ga->Elems[i])) {
			printf("%s\n",(char*)ga->Elems[i]);
			counter++;
			if(counter%30==0){
				printf("\nESCOLHA UMA OPCAO?\n1-SAIR\n2-PROXIMO\n3-ANTERIOR\n\n");
				if(scanf("%d", &res)) {
					if(res==1) booleano=1;
					if(res==3) {
						printf("ESCREVA QUANTAS PÁGINAS QUER VOLTAR A ATRÁS?\n");
						if(scanf("%d", &quantas)){
							if(quantas>0) i-=(counter*quantas);
						}
					}
				}
			}
		}
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
				for(i=0; i<12; i++) printf("%d: %d\n", (i+1), comprasMes[i]);
			} 
			else {
				compras_cliente=fopen("compras_cliente.txt", "w");
				fprintf(compras_cliente, "COMPRAS DE ");  
				for(i=0; i<5; i++) fprintf(compras_cliente, "%c", code[i]);
				fprintf(compras_cliente, " POR MES:\n");
				for(i=0; i<12; i++) fprintf(compras_cliente, "%d: %d\n", (i+1), comprasMes[i]);
				printf("\nFICHEIRO \"compras_cliente.txt\" CRIADO COM SUCESSO!\n");
				fclose(compras_cliente);
			}
		}
	}
}

void query6(AAVL clnt) {
	char escolha='A';
	int j,res,counter=0,booleano=0,quantas;
        GrowingArray ga = initGrowingArray(10000,ArrayString);
        printf("\nINSIRA A LETRA QUE INICIA OS CODIGOS DE CLIENTES QUE DESEJA SABER:\n");
	/*escolha=getchar();*/
	printf("\nLISTA DE CLIENTES INICIADOS PELA LETRA %c:\n", escolha);
	guardArrayAVL(clnt[escolha-65],ga,ArrayString);
        for(j=0;booleano!=1 && j < ga->size;j++) {
		printf("%s\n",(char*)ga->Elems[j]);
		counter++;
		if(counter%30==0) {
			printf("\nESCOLHA UMA OPCAO:\n1-SAIR\n2-PROXIMA\n3-ANTERIOR\n\n");
			if(scanf("%d", &res)) {
				if(res==1) booleano=1;
				if(res==3) {
					printf("ESCREVA QUANTAS PAGINAS QUER VOLTAR A ATRAS?\n");
					if(scanf("%d", &quantas)) if(quantas>0) j-=(j*quantas);
				}	
			}
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
		if(getRemakes()) puts("A HASH TABLE FOI REALOCADA E NAO IRA FUNCIONAR DEVIDAMENTE!");
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

void query9(AAVL clnt, Contabilidade contClnt) {
	int i, mes;
	char *code=(char*) malloc(10*sizeof(char));
	GrowingArray ga=initGrowingArray(200000, ArrayCompProduto);		
	printf("\nINSIRA UM MES: "); if(scanf("%d", &mes));
	printf("INSIRA UM CODIGO DE CLIENTE: ");
	if(scanf("%s", code)) {
		if(validaMes(mes)==FALSE || existeClnt(code, clnt)==FALSE) printf("\nARGUMENTOS INVALIDOS!!!\n");
		else{

			guardOcurrencesAVL(contClnt[mes-1][indexL(code)], ga, ArrayCompProduto, code);
			if(ga->size == 0) puts("\nNADA ENCONTRADO");
			else {
				ordenaGrowingArray(ga,ArrayCompProduto);
				putchar('\n');
				for(i=0; i<ga->size; i++) {
					CompProduto aux=(CompProduto) ga->Elems[i];
					printf("PRODUTO: %s | QUANTIDADE: %d\n", aux->codigo_produto, aux->quantidade);
				}
			}
		}
	}
}

void query10() {
	GrowingArray cm=getClientesMensais();
	int i;
	for(i=0; i<cm->size; i++) printf("%s\n", (char*) cm->Elems[i]);
	printf("\n%d CODIGOS\n",cm->size);
}

void query11() {
	int compras_mes[12][1], clientes_mes[12][1];
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
		for(i=0;i < N;i++) {
			printf("PRODUTO: %s | ", h->values[i]->produto);
			printf("VENDAS: %d | CLIENTES: %d\n", h->values[i]->vendas, h->values[i]->clientes);
		}
	}
}

void query14() {
	int clientes_inativos = getClientesInativos();
	int produtos_inativos = codigos_Produto() - getCodigosProdutosUsados();
	printf("\nCLIENTES QUE NAO REALIZARAM COMPRAS: %d\nPRODUTOS QUE NINGUEM COMPROU: %d\n",clientes_inativos, produtos_inativos);

}
