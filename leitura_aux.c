#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "leitura_aux.h"
/*
#include "avl.h"
redundante
*/

/*Funcao util para imprimir as compras*/
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

int validaCC(char cc[], AVL c) {
	int i;
	for(i=0;i<2;i++)
		if (!isalpha(cc[i]) && !isupper(cc[i])) return 0;
	for(;i<5;i++)
		if (!isdigitN(cc[i])) return 0;
	if(!existeClnt(cc, c)) return 0;
	else return 1;
}

int validaCP(char cc[], AVL p) {
	int i;
	for(i=0;i<2;i++)
		if (!isalpha(cc[i]) && !isupper(cc[i])) return 0;
	for(;i<6;i++)
		if (!isdigitN(cc[i])) return 0;
	if(!existeProd(cc, p)) return 0;
	else return 1;
}

int existeClnt(char cliente[], AVL c) {
	int res;
	if(c==NULL) res=0;
	else{
		char* code = c->info;
		 if(strncmp(cliente, code, 5)<0) res=existeClnt(cliente, c->left);
	     else if(strncmp(cliente, code, 5)>0) res=existeClnt(cliente, c->right);
		  else res=1;
		}
	return res;
}

int existeProd(char produto[], AVL p) {
	int res;
	if(p==NULL) res=0;
	else {
		char* code = p->info;
		if(strncmp(produto,code, 6)<0) res=existeProd(produto, p->left);
	     else if(strncmp(produto, code, 6)>0) res=existeProd(produto, p->right);
		  else res=1;
	}
	return res;
}

int validateClnt(Compras a, AVL c) {
	if(existeClnt(a.codigo_cliente, c)==0) return 0;
	else return 1;
}

int validateProd(Compras a, AVL p) {
	if(existeProd(a.codigo_Produto, p)==0) return 0;
	else return 1;
}

int validateCompras(Compras a) {
	if(validaMes(a.mes_compra)==0 || validaTipo(a.tipo)==0 || validaUnidades(a.unidades_compradas)==0 || validaPreco(a.preco_unitario)==0)
		return 0;
	else return 1;
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

void codClientes(AVL array[]){
	int i;
  for (i=0;i<MAX_LETTERS;i++){
     printf("%c : %d\n",i+65,contarNodos(devolveAVL(array, i+65)));
	}
} 

void codProdutos(AVL array[]){
	int i;
  for (i=0;i<MAX_LETTERS;i++){
     printf("%c : %d\n",i+65,contarNodos(devolveAVL(array, i+65)));
	}
} 

int length(char s[]) {
       int i;
       for(i=0; s[i]!='\0'; i++);
       return i;
}


