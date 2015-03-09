#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define MAX_LINE 40

int main () {
	int i=0, countC=0, countP=0,countCompras =0;
	FILE *clientes, *produtos, *fcompras;
	char linha[MAX_LINE];
	char** compras;
	char** clnt;
	char** prod;
	
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
	
	i=0;
	while(!feof(clientes)) {
		while(fgets(linha, MAX_LINE, clientes)!=NULL) {
			strcpy(clnt[i], linha);
			i++;
			countC++;
		}
	}
	fclose(clientes);
	i=0;
	while(!feof(produtos)) {
		while(fgets(linha, MAX_LINE, produtos)!=NULL) {
			strcpy(prod[i], linha);
			i++;
			countP++;
		}
	}
	fclose(produtos);
	i=0;
	while(!feof(fcompras)){
		while(fgets(linha, MAX_LINE,fcompras)!=NULL){
			strcpy(compras[i],linha);
			i++;
			countCompras++;
		}
	}
	fclose(fcompras);
	printf("\nClientes=%d, Produtos=%d, Compras=%d\n\n", countC, countP,countCompras);
	/* Imprime as primeiras 5 linhas da matriz*/
	for(i=0; i<5; i++) {
		printf("Cliente %d: %s\nProduto %d: %s\nCompra %d: %s\n\n", (i+1), clnt[i], (i+1), prod[i],i+1,compras[i]);
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

	
	
