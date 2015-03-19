#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "leitura_aux.h"

typedef enum balancefactor {LH, EH, RH} BalanceFactor;

typedef struct prodTree {
	BalanceFactor bf;	/*Fator de balanceamento da arvore*/
	char code[3];
	struct prodTree *left, *right;
} ProdTree;

typedef ProdTree *ProdList;

typedef ProdList Slist[3];

void printTree(ProdList p);
ProdList insert(ProdList p, char produto[], int *cresceu);
ProdList insertRight(ProdList p, char produto[], int *cresceu);
ProdList insertLeft(ProdList p, char produto[], int *cresceu);
ProdList balanceRight(ProdList p);
ProdList balanceLeft(ProdList p);
ProdList rotateRight(ProdList p);
ProdList rotateLeft(ProdList p);

int main() {
	int i, index, *cresceu=(int*) malloc(sizeof(int*));
	char list[3][3]={{'A','B','A'},{'B','A','B'},{'C','A','B'}};
	Slist s;
	for(i=0; i<3; i++) s[i]=NULL;
	for(i=0; i<3; i++) {
		index=list[i][0]-65;
		s[index]=insert(s[index], list[i], cresceu);
	}
	for(i=0; i<3; i++) {
		printf("Nova arvore:\n");
		printTree(s[i]);
		printf("\n");
	}
	return 0;
}

void printTree(ProdList p) {
	int i;
	if(p==NULL) printf("NULL\n");
	else {
		for(i=0; i<3; i++) printf("%c", p->code[i]);
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
	else if(strcmp(p->code, produto)<0) p=insertLeft(p, produto, cresceu);
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
	ProdList aux;
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
	ProdList aux;
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


	
