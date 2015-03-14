#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "leitura_aux.h"

void printCompras(Compras a){
	printf("Codigo Produto = %s\n",a.codigo_Produto);
	printf("Preco Unitario = %f\n",a.preco_unitario);
	printf("Unidades Compradas = %d\n",a.unidades_compradas);
	printf("Tipo = %c\n",a.tipo);
	printf("Codigo Cliente = %s\n",a.codigo_cliente);
	printf("Mes = %d\n",a.mes_compra);
}

int validaMes(int mes){
	if(mes>=1 && mes<=12) return 1;		/*Verdadeiro*/
	else return 0;				/*Falso*/
}

int validaTipo(char a){
	if(a=='P' || a=='N') return 1;		/*Verdadeiro*/
	else return 0;				/*Falso*/
}

int validaUnidades(int unidade){
	if(unidade>0 && unidade<200000) return 1;	/*Verdadeiro*/
	else return 0;					/*Falso*/
}

int validaPreco(double p){
	if(p>0.0) return 1;		/*Verdadeiro*/
	else return 0;			/*Falso*/
}

int isdigitN(char a) {return ((a >= 48) && (a<=57));}

int validaCC(char cc[]){
	int i;
	for(i=0;i<2;i++)
		if (!isalpha(cc[i]) && !isupper(cc[i])) return 0;
	for(;i<5;i++)
		if (!isdigitN(cc[i])) return 0;
	return 1;
}

int validaCP(char cc[]){
	int i;
	for(i=0;i<2;i++)
		if (!isalpha(cc[i]) && !isupper(cc[i])) return 0;
	for(;i<6;i++)
		if (!isdigitN(cc[i])) return 0;
	return 1;
}

int validateCompras(Compras a){
	return ( validaMes(a.mes_compra) && validaTipo(a.tipo) && validaUnidades(a.unidades_compradas) && validaPreco(a.preco_unitario) && validaCP(a.codigo_Produto) && validaCC(a.codigo_cliente) );
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
        	if(x == 4) strcpy(a[j].codigo_cliente, t); 
        	if(x == 5) {
			n=atoi(t);
			a[j].mes_compra=n;
		}
        	x++;
        	t=strtok(NULL, " ");
	}	
}

