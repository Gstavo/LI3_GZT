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

/*index corresponde ao endereco da AVL onde vai ser intruduzida a linha*/

/* guardar o resultado do insert em cl faz alguma cena util???? */

void insertCatalogo_Clientes(AAVL cl,char* code,int* cresceu)
	{
		int i = index(code);
		cl[i] = insert(cl[i],code,cresceu,Catalogo_C);
		Codigos_Cliente++;
	}
/*
int removeCatalogo_Clientes(AVL c,char* code)
*/

int codigos_Cliente(){return Codigos_Cliente;}

/* Mudem esta funçao depois, Nao pode imprimir nada neste modulo */

void codClientes(AVL array[]){
        int i;
  for (i=0;i<MAX_LETTERS;i++){
     printf("%c : %d\n",i+65,contarNodos(devolveAVL(array, i+65)));
        }
}


int existeC_aux(char cliente[], AVL c)	{
        int res;
        if(c==NULL) res = 0;
	else {

		if(strncmp(cliente,(char*)c->info, 5)<0) res=existeC_aux(cliente, c->left);
             else if(strncmp(cliente,(char*)c->info, 5)>0) res=existeC_aux(cliente, c->right);
                  else res=1;
        	}
	return res;
}


int existeClnt(char cliente[], AAVL cl)
{
	return existeC_aux(cliente,cl[index(cliente)]);
} 









