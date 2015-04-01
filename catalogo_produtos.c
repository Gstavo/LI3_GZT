#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "catalogo_produtos.h"

static int Codigos_Produto = 0;

void initCatalogo_Produtos(AAVL pl){
        int i;
        for(i=0; i<MAX_LETTERS; i++)
        {
                pl[i]=NULL;
        }
}

/* guardar o resultado do insert em cl faz alguma cena util???? */

void insertCatalogo_Produtos(AAVL pl,char* code,int* cresceu)
        {
                pl[indexL(code)] = insert(pl[indexL(code)],code,cresceu,Catalogo_P);
                Codigos_Produto++;
        }

/*
int removeCatalogo_Clientes(AVL c,char* code)
*/

int codigos_Produto(){return Codigos_Produto;}

/* funçao a alterar n pode printf*/

void codProdutos(AVL array[]){
        int i;
  for (i=0;i<MAX_LETTERS;i++){
     printf("%c : %d\n",i+65,contarNodos(devolveAVL(array, i+65)));
        }
}

int existeP_aux(char* produto,AVL p)
{
        int res;
        if(p==NULL) res=0;
        else {
                if(strncmp(produto,(char*)p->info, 6)<0) res=existeP_aux(produto, p->left);
             else if(strncmp(produto,(char*)p->info, 6)>0) res=existeP_aux(produto, p->right);
                  else res=1;
        }
        return res;
}

int existeProd(char* produto, AAVL pl) 
{
	return existeP_aux(produto,pl[indexL(produto)]);
}




