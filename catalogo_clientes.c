#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "catalogo_clientes.h"

static int Codigos_Cliente = 0;

/* return AAVL ?? bug tipos */
void initCatalogo_Clientes(AAVL cl){
	int i;
	for(i=0; i<MAX_LETTERS; i++) 
	{
                cl[i]=NULL;
        }
}

/*indexL corresponde ao endereco da AVL onde vai ser intruduzida a linha*/

/* guardar o resultado do insert em cl faz alguma cena util???? */

void insertCatalogo_Clientes(AAVL cl,char* code,int* cresceu)
	{
		int i = indexL(code);
		cl[i] = insert(cl[i],code,cresceu,Catalogo_C);
		Codigos_Cliente++;
	}

/*
int removeCatalogo_Clientes(AVL c,char* code){
	int i = indexL(code);
	cl[i] = remove(cl[i],code,Catalogo_C);
	Codigos_Cliente--;
}
*/


int codigos_Cliente(){return Codigos_Cliente;}

/* Mudem esta funçao depois, Nao pode imprimir nada neste modulo */

void codClientes(AVL array[]){
        int i;
  for (i=0;i<MAX_LETTERS;i++){
     printf("%c : %d\n",i+65,contarNodos(devolveAVL(array, i+65)));
        }
}


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


BOOLEAN existeClnt(char* cliente, AAVL cl)
{
	return existeC_aux(cliente,cl[indexL(cliente)]);
} 

void imprimir_cliente(char **lista, AAVL array, char letra) {
	if((letra>97 && letra<122)) letra-=32;	/*Se for minuscula passa para maiuscula*/
	guardArray(array[letra-65], lista, 0);	/*Coloca na matriz todos os clientes iniciados pela letra dada*/
}






