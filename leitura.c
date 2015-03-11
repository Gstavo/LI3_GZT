#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define MAX_LINE 40
#define MAX 500000

typedef struct compras {
	char codigo_Produto[10];
	double preco_unitario;
	int unidades_compradas;
	char tipo;	/*promoção-P;normal-N*/
	char codigo_cliente[10];
	int mes_compra;
} Compras;

typedef Compras *Comp;

void printCompras(Compras a){
	printf("CP = %s\n",a.codigo_Produto);
	printf("Preço Unitario = %f\n",a.preco_unitario);
	printf("Unidades Compradas = %d\n",a.unidades_compradas);
	printf("Tipo = %c\n",a.tipo);
	printf("CC = %s\n",a.codigo_cliente);
	printf("Mes = %d\n",a.mes_compra);
}

void tokenizer(Comp a, int j, char linha[MAX_LINE]){
	char* t; 
	int x=0, n;
	double m;
	t=strtok(linha, " ");
	while (t!=NULL) 
	{
        	if(x == 0) strcpy(a[j].codigo_Produto, t);
        	if(x == 1) {
			m=atof(t);
			a[j].preco_unitario=m;
		}
        	if(x == 2) {
			n=atoi(t);
			a[j].unidades_compradas=n;
		}
        	if(x == 3) a[j].tipo = t[0];
        	if(x == 4) strcpy(a[j].codigo_cliente, t); /* No name codigo_cliente */
        	if(x == 5) {
			n=atoi(t);
			a[j].mes_compra=n;/* no name mes_compra em Compras*/
		}
        	x++;
        	t=strtok(NULL, " ");
	}	
}

void init(Comp array) {
	int i;
	for(i=0; i<MAX; i++) {
		strncpy(array[i].codigo_Produto, "", 10);
		array[i].preco_unitario=0.0;
		array[i].unidades_compradas=0;
		array[i].tipo=' ';
		strncpy(array[i].codigo_cliente, "", 10);
		array[i].mes_compra=0;
	}
}

int main () {
	int i=0, countC=0, countP=0, countCompras=0;
	FILE *clientes, *produtos, *fcompras;
	char **compras, **clnt, **prod;
	
	Comp array=(Comp)malloc(MAX*sizeof(Compras));
/*	init(array); desnecessário ????*/
	
	compras = calloc(500000,sizeof(char*));
	for(i=0;i<500000;i++)
		compras[i] = calloc(MAX_LINE,sizeof(char));
	
	prod = calloc(200000,sizeof(char*));
	for(i=0;i<200000;i++)
		prod[i] = calloc(MAX_LINE,sizeof(char));
	
	clnt = calloc(20000,sizeof(char*));
	for(i=0;i<20000;i++)
		clnt[i] = calloc(MAX_LINE,sizeof(char));
	
	clientes=fopen("clientes.txt","r"); 
	produtos=fopen("produtos.txt","r");
	fcompras=fopen("compras.txt","r");
	
	for(i=0;fgets(clnt[i], MAX_LINE, clientes);i++) 
			countC++;
	fclose(clientes);
	
	for(i=0;fgets(prod[i], MAX_LINE, produtos);i++) 
			countP++;
	fclose(produtos);
	
	for(i=0;fgets(compras[i], MAX_LINE,fcompras);i++){
			tokenizer(array, i, compras[i]);
			countCompras++;
		}
	fclose(fcompras);
	/*
	printf("\nClientes=%d, Produtos=%d, Compras=%d\n\n", countC, countP, countCompras);
	* Imprime as primeiras 5 linhas da matriz*
	for(i=0; i<5; i++) {
		printf("Cliente %d: %sProduto %d: %sCompra %d: %s\n\n", (i+1), clnt[i], (i+1), prod[i],i+1,compras[i]);
	}
	*/
	/* Codigo imprime compras */
	for(i=0;i<5;i++){
		printf("Compra n %d\n\n",i+1);
		printCompras(array[i]);
		putchar('\n');
	}

	for(i=0;i<20000;i++)
		free(clnt[i]);
	free(clnt);

	for(i=0;i<200000;i++)
		free(prod[i]);
	free(prod); 
 
	for(i=0;i<500000;i++)
		free(compras[i]);
	free(compras);
	
	return 0;
}
	

	
	
