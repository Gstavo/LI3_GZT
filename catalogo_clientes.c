#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "catalogo_clientes.h"

static int Codigos_Cliente = 0;

int index(char* code) { return code[0] - 65;}

/* return AAVL ?? bug tipos */
AVL* initCatalogo_Clientes(){
	int i;
	AAVL cl;
	for(i=0; i<MAX_LETTERS; i++) 
	{
                cl[i]=(AVL) malloc(sizeof(struct AVL_struct));
                cl[i]=NULL;
        }
	return cl;
}

/*index corresponde ao endereco da AVL onde vai ser intruduzida a linha*/

/* guardar o resultado do insert em cl faz alguma cena util???? */

void insertCatalogo_Clientes(AAVL cl,char* code,int* cresceu)
	{
		cl[index(code)] = insert(cl[index(code)],code,cresceu,Catalogo_C);
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
        if(c==NULL) return 0;
	if(strncmp(cliente,(char*)c->info, 5)<0) res=existeC_aux(cliente, c->left);
             else if(strncmp(cliente,(char*)c->info, 5)>0) res=existeC_aux(cliente, c->right);
                  else res=1;
        
	return res;
}


int existeClnt(char cliente[], AAVL cl)
{
	return existeC_aux(cliente,cl[index(cliente)]);
} 









