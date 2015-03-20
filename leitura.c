#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "leitura_aux.h"

int main () {
	int i=0, countC=0, countP=0, countCompras=0,compras_invalidas=0, index;
	FILE *clientes, *produtos, *fcompras;
	char **compras;
	char linha[MAX_LINE];
	int *cresceu=(int*) malloc(sizeof(int*));	/*Verifica se a AVL cresceu*/
	Slist cl, pd;	/*cl - array com AVL's de clientes, pd - array com AVL's de produtos*/
	Comp array=(Comp)malloc(MAX*sizeof(Compras));

	for(i=0; i<20000; i++) {
		cl[i]=(ProdList) malloc(sizeof(struct prodTree));
		cl[i]=NULL;
	}
	for(i=0; i<200000; i++) {
		pd[i]=(ProdList) malloc(sizeof(struct prodTree));
		pd[i]=NULL;
	}
	
	compras = calloc(500000,sizeof(char*));
	for(i=0;i<500000;i++)
		compras[i] = calloc(MAX_LINE,sizeof(char));
	
	clientes=fopen("clientes.txt","r"); 
	produtos=fopen("produtos.txt","r");
	fcompras=fopen("compras.txt","r");
	
	for(i=0;fgets(linha, MAX_LINE, clientes);i++) 
	{
			linha[strlen(linha)-1] = '\0';
			index=linha[0]-65;
			cl[index]=insert(cl[index], linha, cresceu);
			countC++;
	}
	fclose(clientes);
	
	for(i=0;fgets(linha, MAX_LINE, produtos);i++)
	{ 
			linha[strlen(linha)-1] = '\0';
			index=linha[0]-65;
			pd[index]=insert(pd[index], linha, cresceu);
			countP++;
	}
	fclose(produtos);
	
	for(i=0;fgets(linha, MAX_LINE,fcompras);i++)
	{
			int valido;
			linha[strlen(linha)-1] = '\0';
			strcpy(compras[i],linha);
			tokenizer(array, i, compras[i]);
			valido = validateCompras(array[i]);
			if(!valido) {   
           				compras_invalidas++;}
			countCompras++;
	}
	fclose(fcompras);
	
	/*Codigo imprime compras*/
	printf("\nCompras:\n\n");
	for(i=0;i<5;i++){
		printf("Compra n %d\n\n",i+1);
		printCompras(array[i]);
		putchar('\n');
	}
	printf("\n");

	printf("N compras invalidas %d de %d compras\n",compras_invalidas,countCompras);

	for(i=0;i<500000;i++)
		free(compras[i]);
	free(compras);
	
	return 0;
}
	

	
	
