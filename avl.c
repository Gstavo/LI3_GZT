#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "avl.h"

/*
 * Unc_info pode ser uma estrutura de compras ou um codigo de Cliente/Produto.
Tem de se fazer cast do endereço conforme o tipo_AVL a criar
	
	Tipos disponiveis:
	
	Catalogo_C 1
	Catalogo_P 2
	Compras_Ord_CP 3
	Compras_Ord_CC 4 

 *
 */

AVL insert(AVL p, void* unc_info, int *cresceu, int tipo_AVL) {
	if(tipo_AVL == Catalogo_C || tipo_AVL == Catalogo_P) {
		char* code = (char*)unc_info; 
		if(p==NULL) {
			p = (AVL) malloc(sizeof(struct AVL_struct));
			p->info = (void*)malloc(10*sizeof(char));
			strcpy((char*)p->info, code);
			p->right=p->left=NULL;
			p->bf=EH;
			*cresceu=1;
		}
		else {
			char* info = (char*)p->info;
			if(strncmp(code, info, strlen(code))<0) p=insertLeft(p,unc_info, cresceu,tipo_AVL);
	     		else p=insertRight(p,unc_info, cresceu,tipo_AVL);
		}
	}
	/*else
	{
	Compras compra = unc_info;
	Compras info = p->info;
		if(p==NULL)
		{
		p = (AVL) malloc(sizeof(struct AVL_struct));
		p->info = (Compras) malloc(sizeof(struct compras));
		compracpy(p->info,compra);
		p->right=p->left=NULL;
		p->bf=EH;
		*cresceu=1;
		}
		
		else if(tipo_AVL == Compras_Ord_CP)
		{
			if(compracmpCP(compra,info) < 0) p=insertLeft(p,unc_info,cresceu,tipo_AVL);
				else p = insertRight(p,unc_info,cresceu,tipo_AVL);	
			}
		else 
		{

			if(compracmpCC(compra,info) < 0) p=insertLeft(p,unc_info,cresceu,tipo_AVL);
				else p = insertRight(p,unc_info,cresceu,tipo_AVL);	
		}
	
	}*/

	return p;
}

AVL insertRight(AVL p, void* info, int *cresceu,int tipo_AVL) {
	p->right=insert(p->right, info, cresceu,tipo_AVL);
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

AVL insertLeft(AVL p, void* info, int *cresceu, int tipo_AVL) {
	p->left=insert(p->left, info, cresceu,tipo_AVL);
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

AVL balanceRight(AVL p) {
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
			p->left->bf=EH;
			p->right->bf=EH;
			break;
		case LH:
			p->left->bf=EH;
			p->right->bf=RH;
			break;
		case RH:
			p->left->bf=LH;
			p->right->bf=EH;
		}
		p->bf=EH;
	}
	return p;
}

AVL balanceLeft(AVL p) {
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
			p->left->bf=EH;
			p->right->bf=EH;
			break;
		case RH:
			p->right->bf=EH;
			p->left->bf=LH;
			break;
		case LH:
			p->right->bf=RH;
			p->left->bf=EH;
		}
		p->bf=EH;
	}
	return p;
}

AVL rotateRight(AVL p) {	
	AVL aux;
	if((!p) || (!p->left)) printf("Erro!\n");
	else {
		aux=p->left;
		p->left=aux->right;
		aux->right=p;
		p=aux;
	}
	return p;
}

AVL rotateLeft(AVL p) {
	AVL aux;
	if((!p) || (!p->right)) printf("Erro!\n");
	else {
		aux=p->right;
		p->right=aux->left;
		aux->left=p;
		p=aux;
	}
	return p;
}

AVL devolveAVL(AVL array[], char a){
	int pos=a-65;
	AVL aux=(AVL) malloc (sizeof (struct AVL_struct));
	aux=array[pos];
	return aux;
}


int contarNodos(AVL aux){
	if(aux == NULL) return 0;
	else return 1 + contarNodos(aux->left) + contarNodos(aux->right);
}

int indexL(char* code) { 
	return code[0]-65;
}

void compracpy(Compras *dest, Compras *src) {
	strncpy(dest->codigo_produto, src->codigo_produto,6);
	dest->preco_unitario = src->preco_unitario;
	dest->unidades_compradas = src->unidades_compradas;
	dest->tipo = src->tipo;
	strncpy(dest->codigo_cliente,src->codigo_cliente,5);
	dest->mes_compra = src->mes_compra;
}
int compracmpCC(Compras *c1, Compras *c2) {
	return strncmp(c1->codigo_cliente, c2->codigo_cliente, 5);
}

int compracmpCP(Compras *c1, Compras *c2) {
	return strncmp(c1->codigo_produto, c2->codigo_produto, 6);	
}
