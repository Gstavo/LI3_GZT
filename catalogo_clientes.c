#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "catalogo_clientes.h"


static int Codigos_Cliente = 0;

/*Inicializa o catalogo de clientes*/
void initCatalogo_Clientes(CatalogoClientes cl){
	int i;
	for(i=0; i<MAX_LETTERS; i++) 
	{
                cl[i]=NULL;
        }
}

/*Insere um cliente no catalogo*/
void insertCatalogo_Clientes(CatalogoClientes cl,char* code,int* cresceu)
	{
		int i = indexL(code);
		cl[i] = insert(cl[i],code,cresceu,Catalogo_C);
		Codigos_Cliente++;
	}

/*Remove um cliente do catalogo*/
int removeCatalogo_Clientes(CatalogoClientes cl,char* code){
	int i = indexL(code),r;
	r = removeAVL(cl[i],code,Catalogo_C);
	if(r==0) Codigos_Cliente--;
	return r;
}

/*Devolve o numero de clientes*/
int codigos_Cliente(){return Codigos_Cliente;}

/*Funcao auxiliar da existeClnt*/
BOOLEAN existeC_aux(char* cliente, AVL c)	{
        int res;
        if(c==NULL) res = FALSE;
	else {

		if(strncmp(cliente,(char*)c->info, 5)<0) res=existeC_aux(cliente, c->left);
             else if(strncmp(cliente,(char*)c->info, 5)>0) res=existeC_aux(cliente, c->right);
                  else res=TRUE;
        	}
	return res;
}

/*Verifica se existe um cliente no catalogo*/
BOOLEAN existeClnt(char* cliente, CatalogoClientes cl)
{
	return existeC_aux(cliente,cl[indexL(cliente)]);
} 

/*Coloca todos os clientes iniciados por dada letra no growingArray*/
void imprimir_cliente(GrowingArray ga, CatalogoClientes array, char letra) {
	if((letra>97 && letra<122)) letra-=32;	/*Se for minuscula passa para maiuscula*/
	guardArrayAVL(array[letra-65], ga, ArrayString);	/*Coloca na matriz todos os clientes iniciados pela letra dada*/
}






