#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "avl.h"

/*produto nao quer dizer que seja um produto, serve tambem para um cliente*/

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


AVL insert(AVL p,void* unc_info , int *cresceu,int tipo_AVL) {
	
	if(tipo_AVL == Catalogo_C || tipo_AVL == Catalogo_P)
	{
	char* code = (char*)unc_info; 
	if(p==NULL) {
		
		p = (AVL) malloc(sizeof(struct avl_node));
		p->info = malloc(10*sizeof(char));
		strcpy(p->info, code);
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
	else
	{
	Comp compra = (Comp) unc_info;
		if(p==NULL)
		{
		Comp info = (Comp) p->info;
		p = (AVL) malloc(sizeof(struct avl_node));
		p->info = (Comp) malloc(sizeof(struct compras));
		info = p->info;
		info->codigo_produto = malloc(10*sizeof(char));
        	info->codigo_cliente = malloc(10*sizeof(char));
		compracpy(p->info,compra);
		p->right=p->left=NULL;
		p->bf=EH;
		*cresceu=1;
		}
		
		else if(tipo_AVL == Compras_Ord_CP)
		{
			if(compracmpCP(compra,p->info) < 0) p=insertLeft(p,unc_info,cresceu,tipo_AVL);
				else p = insertRight(p,unc_info,cresceu,tipo_AVL);	
			}
		else /* Compras_Ord_CC*/
		{

			if(compracmpCC(compra,p->info) < 0) p=insertLeft(p,unc_info,cresceu,tipo_AVL);
				else p = insertRight(p,unc_info,cresceu,tipo_AVL);	
		}
	
	}

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

AVL insertLeft(AVL p, void* info, int *cresceu,int tipo_AVL) {
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
  AVL aux=(AVL) malloc (sizeof (struct avl_node));
  aux=array[pos];
  return aux;
}


NUM_NODOS contarNodos(AVL aux){
   if(aux == NULL)
        return 0;
   else
        return 1 + contarNodos(aux->left) + contarNodos(aux->right);
}

void guardArray(AVL aux, char **lista, int index) {	/*index corresponde ao indice da matriz onde colocar o cliente*/
	int i;
 	if(aux!=NULL) {
		char *p=(char*) aux->info;
		lista[index]=(char*) malloc(5*sizeof(char*));
		strncpy(lista[index], p, 5);
		for(i=0; i<5; i++) printf("%c", lista[index][i]);
		printf("\n");
		index++;
		/*Insere primeiro na matriz os elementos que estao na AVL esquerda e depois insere os da direita*/
		/*O index vai aumentando em cada chamada recursiva*/
		guardArray(aux->left, lista, index);
		guardArray(aux->right, lista, index);
	}
}

INDICE_CODIGOS indexL(char* code) {return code[0] - 65;}

/*Numero de produtos por cliente ou vice-versa (para ja so funciona para clientes)*/
NUM_OCORRENCIAS_CODE avl_count(AVL c, char* code) {
	NUM_OCORRENCIAS_CODE res;
	if(c==NULL) res=0;
	else {
		Comp info=(Comp) c->info;
		if(strncmp(info->codigo_cliente, code, 5)>0) res=avl_count(c->left, code);
		else if(strncmp(info->codigo_cliente, code, 5)<0) res=avl_count(c->right, code);
		else res=1+avl_count(c->right, code);	/*iguais foram inseridos na AVL direita*/
	}
	return res;
}
		


