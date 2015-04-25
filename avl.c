#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "avl.h"

/*Insere um nodo na AVL*/
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

/*Faz a insercao a direita na AVL*/
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

/*Faz a insercao a esquerda na AVL*/
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

/*Balanceamento da AVL a direita*/
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

/*Balanceamento da AVL a esquerda*/
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

/*Rotacao da AVL a direita*/
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

/*Rotacao da AVL a esquerda*/
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

int removeAVL(AVL p,void* info,int tipo)
{
	return 0;
} 

AVL devolveAVL(AVL array[], char a) {
	int pos=a-65;
	AVL aux=(AVL) malloc (sizeof (struct avl_node));
	aux=array[pos];
	return aux;
}

/*Conta o numero de nodos da AVL*/
NUM_NODOS contarNodos(AVL aux) {
	if(aux == NULL) return 0;
	else return 1 + contarNodos(aux->left) + contarNodos(aux->right);
}

/*Guarda a AVL num growingArray*/
void guardArrayAVL(AVL aux, GrowingArray lista, int tipo) {	
	if(aux!=NULL) {
		char* o = malloc(10*sizeof(char));
		strcpy(o,aux->info);
		insertGrowingArray(lista,o,tipo);
		guardArrayAVL(aux->left, lista, tipo);
		guardArrayAVL(aux->right, lista, tipo);
	}
}

/*Guarda as ocurrencias de um codigo na AVL num growingArray*/
void guardOcurrencesAVL(AVL avl, GrowingArray array, int tipo, char* codigo){
	if(avl) {
		Comp compra=(Comp) avl->info;
		char* tmp;
		if(strlen(codigo)==6) tmp=compra->codigo_produto;
		else tmp=compra->codigo_cliente;

		if(strcmp(codigo, tmp)==0) {	
			if(tipo==ArrayString) {
				char* o=malloc(10*sizeof(char));
				strcpy(o,tmp);
				insertGrowingArray(array,o,tipo);
			}
			else if(tipo==ArrayCompProduto) {
				CompProduto p = (CompProduto) malloc(sizeof(struct compras_prod));
				p->quantidade = compra->quantidade;
				p->codigo_produto = malloc(10*sizeof(char));
				strcpy(p->codigo_produto, compra->codigo_produto);
				insertGrowingArray(array, p, tipo);
			}
			guardOcurrencesAVL(avl->left,array,tipo,codigo);
			guardOcurrencesAVL(avl->right,array,tipo,codigo);
		}
		else if(strcmp(codigo,tmp)>0) {
			guardOcurrencesAVL(avl->right,array,tipo,codigo);
		}
		else {
			guardOcurrencesAVL(avl->left,array,tipo,codigo);
		}
	}
}

/*Verifica se o codigo existe na AVL*/
BOOLEAN countainAVL(AVL a,char* code)
{
	if(a == NULL) return FALSE;
	else{
		Comp compra = a->info;
		
		if(strcmp(code,compra->codigo_cliente) == 0) return TRUE;
		else if(strcmp(code,compra->codigo_cliente) < 0) return countainAVL(a->left,code);
		else return countainAVL(a->right,code);
	}
}

/*Limpa uma matriz*/
void limpaLista(char **lista) {
	int i=0;
	for(i=0; i<MAX_PROD;i++) lista[i]=NULL;
}

/*Devolve o indice onde vai ser introduzido um codigo*/
INDICE_CODIGOS indexL(char* code) {
	return code[0]-65;
}

/*Numero de produtos por cliente ou numero de produtos por tipo de compra*/
NUM_OCORRENCIAS_CODE avl_count(AVL c, char* code, int tipo, char mode) {
	NUM_OCORRENCIAS_CODE res;
	if(c==NULL) res=0;
	else if(tipo==Compras_Ord_CC) {
		Comp info=(Comp) c->info;
		if(strncmp(info->codigo_cliente, code, 5)>0) res=avl_count(c->left, code, tipo, mode);
		else if(strncmp(info->codigo_cliente, code, 5)<0) res=avl_count(c->right, code, tipo, mode);
		else res=1+avl_count(c->right, code, tipo, mode) + avl_count(c->left, code, tipo,mode);	
	}
	else {
		Comp info=(Comp) c->info;
		if(strncmp(info->codigo_produto, code, 6)>0) res=avl_count(c->left, code, tipo, mode);
		else if(strncmp(info->codigo_produto, code, 6)<0) res=avl_count(c->right, code, tipo, mode);
		else if(strncmp(info->codigo_produto, code, 6)==0 && mode==info->tipo) res=1+avl_count(c->right, code, tipo, mode)+avl_count(c->left,code,tipo,mode);
		else res=avl_count(c->right, code, tipo, mode)+avl_count(c->left,code,tipo,mode);
	}
	return res;
}

/*Retorna a faturacao de um produto*/
double avl_countFact(AVL c, char* code) {
	double res;
	if(c==NULL) res=0;
	else {
		Comp info=(Comp) c->info;
		if(strncmp(info->codigo_produto, code, 6)>0) res=avl_countFact(c->left, code);
		else if(strncmp(info->codigo_produto, code, 6)<0) res=avl_countFact(c->right, code);
		else res=(info->preco*info->quantidade)+avl_countFact(c->right, code) + avl_countFact(c->left,code);
	}
	return res;
}
		


