#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "leitura_aux.h"

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

int validateClnt(Compras *a, AAVL cl) {
        if(existeClnt(a->codigo_cliente, cl)==0) return 0;
        else return 1;
}

int validateProd(Compras *a, AAVL pl) {
	if(existeProd(a->codigo_produto, pl)==0) return 0;
	else return 1;
}

int validateCompras(Compras *a) {
	if(validaMes(a->mes_compra)==0 || validaTipo(a->tipo)==0 || validaUnidades(a->unidades_compradas)==0 || 
           validaPreco(a->preco_unitario)==0) return 0;
	else return 1;
}

void tokenizer(Compras *a, char linha[MAX_LINE]){
	char* t; 
	int x=0, n;
	double m;
	t=strtok(linha, " ");
	while (t!=NULL) 
	{
        	if(x == 0) strcpy(a->codigo_produto, t);
        	if(x == 1) {
			m=atof(t);
			a->preco_unitario=m;
		}
        	if(x == 2) {
			n=atoi(t);
			a->unidades_compradas=n;
		}
        	if(x == 3) a->tipo = t[0];
        	if(x == 4) strcpy(a->codigo_cliente, t); 
        	if(x == 5) {
			n=atoi(t);
			a->mes_compra=n;
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


