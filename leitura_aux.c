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

int validaCC(char cc[], ProdList c) {
	int i;
	for(i=0;i<2;i++)
		if (!isalpha(cc[i]) && !isupper(cc[i])) return 0;
	for(;i<5;i++)
		if (!isdigitN(cc[i])) return 0;
	if(!existeClnt(cc, c)) return 0;
	else return 1;
}

int validaCP(char cc[], ProdList p) {
	int i;
	for(i=0;i<2;i++)
		if (!isalpha(cc[i]) && !isupper(cc[i])) return 0;
	for(;i<6;i++)
		if (!isdigitN(cc[i])) return 0;
	if(!existeProd(cc, p)) return 0;
	else return 1;
}

/*existeClnt e existeProd verificam se a palavra existe na AVL*/
int existeClnt(char cliente[], ProdList c) {
	int res;
	if(c==NULL) res=0;
	else if(strncmp(cliente, c->code, 5)<0) res=existeClnt(cliente, c->left);
	     else if(strncmp(cliente, c->code, 5)>0) res=existeClnt(cliente, c->right);
		  else res=1;
	return res;
}

int existeProd(char produto[], ProdList p) {
	int res;
	if(p==NULL) res=0;
	else if(strncmp(produto, p->code, 6)<0) res=existeProd(produto, p->left);
	     else if(strncmp(produto, p->code, 6)>0) res=existeProd(produto, p->right);
		  else res=1;
	return res;
}

int validateCompras(Compras a, ProdList p, ProdList c) {
	return ( validaMes(a.mes_compra) && validaTipo(a.tipo) && validaUnidades(a.unidades_compradas) && validaPreco(a.preco_unitario) && validaCP(a.codigo_Produto, p) && validaCC(a.codigo_cliente, c) );
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

void printTree(ProdList p) {
	int i;
	if(p==NULL) printf("NULL\n");
	else {
		for(i=0; i<6; i++) printf("%c", p->code[i]);
		printf("\n");
		printTree(p->left);
		printTree(p->right);
	}
}

ProdList insert(ProdList p, char produto[], int *cresceu) {
	if(p==NULL) {
		p=(ProdList) malloc(sizeof(struct prodTree));
		strcpy(p->code, produto);
		p->right=p->left=NULL;
		p->bf=EH;
		*cresceu=1;
	}
	else if(strncmp(produto, p->code, length(produto))<0) p=insertLeft(p, produto, cresceu);
	     else p=insertRight(p, produto, cresceu);
	return p;
}

ProdList insertRight(ProdList p, char produto[], int *cresceu) {
	p->right=insert(p->right, produto, cresceu);
	if(*cresceu) {
		switch(p->bf) {
		case LH:
			p->bf=EH;
			*cresceu=0;
			break;
		case EH:
			p->bf=RH;
			*cresceu=1;
			break;
		case RH:
			p=balanceRight(p);
			*cresceu=0;
		}
	}
	return p;
}

ProdList insertLeft(ProdList p, char produto[], int *cresceu) {
	p->left=insert(p->left, produto, cresceu);
	if(*cresceu) {
		switch(p->bf) {
		case RH:
			p->bf=EH;
			*cresceu=0;
			break;
		case EH:
			p->bf=LH;
			*cresceu=1;
			break;
		case LH:
			p=balanceLeft(p);
			*cresceu=0;
		}
	}
	return p;
}

ProdList balanceRight(ProdList p) {
	if(p->right->bf==RH) {
		p=rotateLeft(p);
		p->bf=EH;
		p->left->bf=EH;
	}
	else {
		p->right=rotateRight(p->right);
		p=rotateLeft(p);
		switch(p->bf) {
		case EH:
			if(p->left!=NULL) p->left->bf=EH;
			if(p->right!=NULL) p->right->bf=EH;
			break;
		case LH:
			if(p->left!=NULL) p->left->bf=EH;
			if(p->right!=NULL) p->right->bf=RH;
			break;
		case RH:
			if(p->left!=NULL) p->left->bf=LH;
			if(p->right!=NULL) p->right->bf=EH;
		}
		p->bf=EH;
	}
	return p;
}

ProdList balanceLeft(ProdList p) {
	if(p->left->bf==LH) {
		p=rotateRight(p);
		p->bf=EH;
		p->right->bf=EH;
	}
	else {
		p->left=rotateLeft(p->left);
		p=rotateRight(p);
		switch(p->bf) {
		case EH:
			if(p->left!=NULL) p->left->bf=EH;
			if(p->right!=NULL) p->right->bf=EH;
			break;
		case RH:
			if(p->right!=NULL) p->right->bf=EH;
			if(p->left!=NULL) p->left->bf=LH;
			break;
		case LH:
			if(p->right!=NULL) p->right->bf=RH;
			if(p->left!=NULL) p->left->bf=EH;
		}
		p->bf=EH;
	}
	return p;
}

ProdList rotateRight(ProdList p) {	
	ProdList aux;
	if((!p) || (!p->left)) printf("Erro!\n");
	else {
		aux=p->left;
		p->left=aux->right;
		aux->right=p;
		p=aux;
	}
	return p;
}

ProdList rotateLeft(ProdList p) {
	ProdList aux;
	if((!p) || (!p->right)) printf("Erro!\n");
	else {
		aux=p->right;
		p->right=aux->left;
		aux->left=p;
		p=aux;
	}
	return p;
}

int length(char s[]) {
	int i;
	for(i=0; s[i]!='\0'; i++);
	return i;
}


	

