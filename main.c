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
/*void query3o(Contabilidade contProd, AAVL prod);*/
void query3(HashTable ht);
void query4(HashTable ht, AAVL cp);
void query5(Contabilidade contClnt);
void query6(AAVL clnt);
void query7();
void query8(HashTable ht);
void query9(AAVL clnt, Contabilidade contClnt);
void query10();
void query11();
void query12(HashTable ht);
void query13(AAVL clnt, Contabilidade contClnt);
void query14();


void imprimeQuantos(GrowingArray ga,int index,int quantos) {
	int i=0,resposta,conta=0,paginas;
	while(conta<quantos && (index + i) < ga->size) {
		printf("%s\n",(char*)ga->Elems[index+i]);
		conta++;
		i++;
		if(conta==quantos){
			printf("\nDESEJA CONTINUAR?\n1-SAIR\n2-PROXIMA\n3-ANTERIOR\n\n");
			if(scanf("%d", &resposta)){
				if(resposta==1) break;
				if(resposta==2) conta=0;
				if(resposta==3){
					printf("ESCREVA QUANTAS PAGINAS QUER VOLTAR A ATRAS?\n");
					if(scanf("%d", &paginas)) if(paginas>0) {
						conta=0;
						i-=(paginas*quantos);
					}
				}
			}
		}
	}
}

int main(){
	int query, valid[5];			/*valid guarda os resultados da leitura para posterior impressao na query1*/
	double time_spent;
	AAVL clnt, prod;
	Contabilidade contClnt;	
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

	/*Preenchimento e leitura das estruturas de dados*/
	leitura(clnt, prod, contClnt, ht, compra, valid);

	/*Faz uma travessia a todos os codigos de cliente recolhendo informaçoes sobre a atividade de cada um*/
	gatherData(clnt, contClnt);

	puts("\nESCOLHA UMA QUERY: ");
	if(scanf("%d", &query)) {
		switch(query) {
			case 1: query1(valid); break;			/*Funcional*/
			case 2: query2(clnt, prod); break;		/*Funcional*/
			case 3: query3(ht); break;			/*Funcional*/
			case 4: query4(ht,prod); break;			/*Funcional*/
			case 5: query5(contClnt); break;		/*Funcional*/
			case 6: query6(clnt); break;			/*Funcional*/
			case 7: query7(); break;			/*Funcional*/
			case 8: query8(ht); break;			/*Funcional*/
			case 9: query9(clnt, contClnt);	break;		/*Falta ordenar resultados*/
			case 10: query10(); break;			/*Funcional*/
			case 11: query11(); break;			/*Funcional*/
			case 12: query12(ht); break;			/*Funcional*/
			case 13: query13(clnt, contClnt); break;	/*Funcional*/
			case 14: query14(); 				/*Funcional*/
		}
	}

	end=clock();
	time_spent=(double)(end-begin)/CLOCKS_PER_SEC ;
	printf("\nTEMPO DE EXECUCAO: %.2f segundos\n\n", time_spent);
	/*system clear*/
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
		else{
			int quantos;
			GrowingArray ga = initGrowingArray(10000,ArrayString);
        	printf("\nINSIRA A LETRA QUE INICIA OS CODIGOS DE PRODUTOS QUE DESEJA SABER:\n");
        	if(scanf("%s", aux)){
        		escolha=aux[0];
				if((escolha>97 && escolha<122)) escolha-=32;
				printf("\nLISTA DE PRODUTOS INICIADOS PELA LETRA %c:\n", escolha);
				guardArrayAVL(prod[escolha-65],ga,ArrayString);
				printf("QUANTOS RESULTADOS PRETENDE VER AGORA?\n");
				if(scanf("%d", &quantos)){
					imprimeQuantos(ga,0,quantos);
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
			}
		}
	}
}

void guardaNComp(HashTable ht,GrowingArray ga,GrowingArray resultado){
	int j,r=0;
	for(j=0;j<ga->size;j++){
		if(!searchHash(ht,ga->Elems[j])){
			resultado->Elems[r]=ga->Elems[j];
			r++;
		}
	}
}

void query4(HashTable ht, AAVL cp) {
   		int i,resposta,conta=0,paginas,total=0,quantos,index=0;
        GrowingArray ga = initGrowingArray(200000,ArrayString);
        GrowingArray resultado = initGrowingArray(200000,ArrayString);
		printf("\nLISTA DE PRODUTOS NAO COMPRADOS: \n");
        for(i=0;i<MAX_LETTERS;i++) guardArrayAVL(cp[i],ga,ArrayString);
        for(i=0;i < ga->size;i++) if(!searchHash(ht,ga->Elems[i])) {total++;}
        guardaNComp(ht,ga,resultado);
		printf("QUANTOS RESULTADOS PRETENDE VER AGORA?\n");
		if(scanf("%d", &quantos));
        for(i=0;(index + i) < ga->size && conta<quantos;) 
        { 
			printf("%s\n",(char*)resultado->Elems[index+i]);
			conta++;
			i++;
			if(conta==quantos){
				printf("\nESCOLHA UMA OPCAO?\n1-SAIR\n2-PROXIMO\n3-ANTERIOR\n\n");
				if(scanf("%d", &resposta)) {
					if(resposta==1) break;
					if(resposta==2) conta=0;
					if(resposta==3) {
						printf("ESCREVA QUANTAS PAGINAS QUER VOLTAR A ATRAS?\n");
						if(scanf("%d", &paginas)) if(paginas>0) {
							conta=0;
							i-=(paginas*quantos);
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
	char aux[1], escolha;
	int quantos;
    GrowingArray ga = initGrowingArray(20000,ArrayString);
    printf("\nINSIRA A LETRA QUE INICIA OS CODIGOS DE CLIENTES QUE DESEJA SABER:\n");
	if(scanf("%s", aux)) {
		escolha=aux[0];
		if((escolha>97 && escolha<122)) escolha-=32;
		printf("\nLISTA DE CLIENTES INICIADOS PELA LETRA %c:\n", escolha);
		guardArrayAVL(clnt[escolha-65],ga,ArrayString);
		printf("QUANTOS RESULTADOS PRETENDE VER AGORA?\n");
		if(scanf("%d", &quantos)){
			imprimeQuantos(ga,0,quantos);
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
	int quantos;
	printf("QUANTOS RESULTADOS PRETENDE VER AGORA?\n");
	if(scanf("%d", &quantos)){
		imprimeQuantos(cm,0,quantos);
	}
	printf("\nCLIENTES QUE NAO REALIZARAM COMPRAS: %d\n",cm->size);
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

void query13(AAVL clnt, Contabilidade contClnt) {
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
