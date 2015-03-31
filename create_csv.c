#include <stdio.h>
#include <string.h>

#define MAX_LINE 12  /*numero de meses*/

/*
int compras_mes[][],int clientes_mes[][] são duas matrizes com 12 linhas que dizem respeito aos 12 meses de um ano e com max colunas cada um sendo max
o máximo entre todas as colunas de todas as linhas de cada uma das matrizes.
*/
 
void create_csv(char *nome_ficheiro,int compras_mes[12][2],int clientes_mes[12][2],int maxCp,int maxCl){
 
printf("\n Criar Ficheiro %s.csv",nome_ficheiro);
FILE *aux;
int i,j;
nome_ficheiro=strcat(nome_ficheiro,".csv");
aux=fopen(nome_ficheiro,"w+");
fprintf(aux,"Mês,#Compras,#Clientes");

for(i=0;i<MAX_LINE;i++)
{
 
    fprintf(aux,"\n%d",i+1);/*Dá o mês*/
 
    for(j=0;j<maxCp;j++){
        /*max será o máximo entre o numero de vendas e de compras*/
        fprintf(aux,",%d ",compras_mes[i][j]);}

    for(j=0;j<maxCl;j++){   
        fprintf(aux,",%d ",clientes_mes[i][j]);}
}

 
fclose(aux);
printf("\n %sFicheiro Criado com Sucesso!!!",nome_ficheiro);
 
}
 
int main(){
    
int cp[12][2]={{10,10},{20,20},{30,30},{40,40},{50,50},{60,60},{70,70},{80,80},{90,90},{100,100},{110,110},{120,120}};
int cl[12][2]={{130,130},{140,140},{150,150},{160,160},{170,170},{180,180},{190,190},{200,200},{210,210},{220,220},{230,230},{240,240}};
char nome[100];
printf("\n Insira o nome do ficheiro que pretende criar: ");
gets(nome);
create_csv(nome,cp,cl,2,2);
return 0; 
}