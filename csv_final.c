#include <stdio.h>
#include <string.h>

#include "csv_final.h"


 
 /*12 linhas que representam os 12 meses e so tem 1 coluna com o respectivo valor total*/

void preenchecmp(int compras_mes[12][1]){
	for(int i=0,i<12,i++){
		compras_mes[i][1]=returnVendas(i);
	}
}

void preencheclientes(int clientes_mes[12][1]){
	for(int i=0,i<12,i++){
		compras_mes[i][1]=0;/*Só falta fazer esta funçao e fica a funcionar a 100%*/
	}
}



void create_csv(char *nome_ficheiro,int compras_mes[12][1],int clientes_mes[12][1]){
 
printf("\n Criar Ficheiro %s.csv",nome_ficheiro);
FILE *aux;
int i,j;
nome_ficheiro=strcat(nome_ficheiro,".csv");
aux=fopen(nome_ficheiro,"w+");
fprintf(aux,"Mes,#Compras,#Clientes");

for(i=0;i<MAX_LINE;i++)
{
 
    fprintf(aux,"\n%d",i+1);/*Dá o mês*/
 
    for(j=0;j<1;j++){
        /*max será o máximo entre o numero de vendas e de compras*/
        fprintf(aux,",%d ",compras_mes[i][j]);}

    for(j=0;j<1;j++){   
        fprintf(aux,",%d ",clientes_mes[i][j]);}
}

 
fclose(aux);
printf("\n %sFicheiro Criado com Sucesso!!!",nome_ficheiro);
 
}

