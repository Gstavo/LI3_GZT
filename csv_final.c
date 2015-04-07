#include <stdio.h>
#include <string.h>

#include "csv_final.h"

/*12 linhas que representam os 12 meses e so tem 1 coluna com o respectivo valor total*/
void preenchecmp(int compras_mes[12][1]) {
	int i;
	for(i=0; i<12; i++) {
		compras_mes[i][1]=returnVendas(i);
	}
}

void preencheclientes(int clientes_mes[12][1]){
	int i;
	for(i=0; i<12; i++){
		clientes_mes[i][1]=returnClientes(i);/*Só falta fazer esta funçao e fica a funcionar a 100%*/
	}
}

void create_csv(char *nome_ficheiro, int compras_mes[12][1], int clientes_mes[12][1]) {
	int i;
	FILE *aux;
	printf("\nCriar Ficheiro %s.csv", nome_ficheiro);
	nome_ficheiro=strcat(nome_ficheiro,".csv");
	aux=fopen(nome_ficheiro,"w+");
	fprintf(aux, "%s %s %s\n", "Mes\0", "#Compras\0", "#Clientes\0");
	
	for(i=0;i<12;i++) fprintf(aux,"%d %d %d\n", (i+1), compras_mes[i][1], clientes_mes[i][1]);/*Dá o mês*/
	fclose(aux);
	printf("\n%s :Ficheiro Criado com Sucesso!!!\n",nome_ficheiro);
}

