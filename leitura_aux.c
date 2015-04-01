#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "leitura_aux.h"

/*Funcao util para imprimir as compras*/
void printCompras(Compras a){
	printf("Codigo Produto = %s\n",a.codigo_produto);
	printf("Preco Unitario = %f\n",a.preco);
	printf("Unidades Compradas = %d\n",a.quantidade);
	printf("Tipo = %c\n",a.tipo);
	printf("Codigo Cliente = %s\n",a.codigo_cliente);
	printf("Mes = %d\n",a.mes);
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
	if(p>=0.0) return 1;		/*Verdadeiro*/
	else return 0;			/*Falso*/
}

int isdigitN(char a) {return ((a >= 48) && (a<=57));}

int validateClnt(Compras a, AAVL cl) {
        if(existeClnt(a.codigo_cliente, cl)==0) return 0;
        else return 1;
}

int validateProd(Compras a, AAVL pl) {
	if(existeProd(a.codigo_produto, pl)==0) return 0;
	else return 1;
}

int validateCompras(Compras a) {
	if(validaMes(a.mes)==0 || validaTipo(a.tipo)==0 || validaUnidades(a.quantidade)==0 || validaPreco(a.preco)==0)
		return 0;
	else return 1;
} 

void tokenizer(Comp a, char linha[MAX_LINE]){
	char* t; 
	int x=0, n;
	double m;
	t=strtok(linha, " ");
	while (t!=NULL) 
	{
        	if(x == 0) strcpy(a->codigo_produto, t);
        	if(x == 1) {
			m=atof(t);
			a->preco=m;
		}
        	if(x == 2) {
			n=atoi(t);
			a->quantidade=n;
		}
        	if(x == 3) a->tipo = t[0];
        	if(x == 4) strcpy(a->codigo_cliente, t); 
        	if(x == 5) {
			n=atoi(t);
			a->mes=n;
		}
        	x++;
        	t=strtok(NULL, " ");
	}	
}

void printTree(AVL p) {
	int i;
	if(p==NULL) printf("NULL\n");
	else {
		char* code = p->info;
		for(i=0; i<6; i++) printf("%c", code[i]);
		printf("\n");
		printTree(p->left);
		printTree(p->right);
	}
}
int length(char s[]) {
       int i;
       for(i=0; s[i]!='\0'; i++);
       return i;
}

void shiftleft(char* s,int i)
{
        while(s[i]!='\0')
        {
                s[i] = s[i+1];
                i++;
        }
}

void trim(char* s)
{
        int i;
        for(i = 0;s[i] == ' ';) shiftleft(s,i);
        for(i = 0;s[i] != '\0';)
                if(s[i] == ' ' && s[i+1] == ' ') shiftleft(s,i);
                else i++;
        if(i > 0 && s[i-1] == ' ') s[i-1] = '\0';
}

/* Codigo desnecessario/ n usado???
int validaCC(char cc[], AVL c) {
        int i;
        for(i=0;i<2;i++)
                if (!isalpha(cc[i]) && !isupper(cc[i])) return 0;
        for(;i<5;i++)
                if (!isdigitN(cc[i])) return 0;
        if(!existeClnt(cc, c)) return 0;
        else return 1;
}
*/

/*
int validaCP(char cc[], AVL p) {
	int i;
	for(i=0;i<2;i++)
		if (!isalpha(cc[i]) && !isupper(cc[i])) return 0;
	for(;i<6;i++)
		if (!isdigitN(cc[i])) return 0;
	if(!existeProd(cc, p)) return 0;
	else return 1;
}
*/


