#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "catalogo_produtos.h"

static int Codigos_Produto = 0;

void initCatalogo_Produtos(CatalogoProdutos pl){
        int i;
        for(i=0; i<MAX_LETTERS; i++)
        {
                pl[i]=NULL;
        }
}

/* guardar o resultado do insert em cl faz alguma cena util???? */

void insertCatalogo_Produtos(CatalogoProdutos pl,char* code,int* cresceu)
        {
                pl[indexL(code)] = insert(pl[indexL(code)],code,cresceu,Catalogo_P);
                Codigos_Produto++;
        }


int removeCatalogo_Produtos(CatalogoProdutos pl,char* code)
{
	int i = indexL(code),r;
        r = removeAVL(pl[i],code,Catalogo_C);
        if(r==0) Codigos_Produto--;
        return r;
}


int codigos_Produto(){return Codigos_Produto;}

BOOLEAN existeP_aux(char* produto,AVL p)
{
        int res;
        if(p==NULL) res=FALSE;
        else {
                if(strncmp(produto,(char*)p->info, 6)<0) res=existeP_aux(produto, p->left);
             else if(strncmp(produto,(char*)p->info, 6)>0) res=existeP_aux(produto, p->right);
                  else res=TRUE;
        }
        return res;
}

BOOLEAN existeProd(char* produto, CatalogoProdutos pl) 
{
	return existeP_aux(produto,pl[indexL(produto)]);
}

void imprimir_produto(GrowingArray ga, CatalogoProdutos array, char letra) {
    if((letra>97 && letra<122)) letra-=32;  /*Se for minuscula passa para maiuscula*/
    guardArrayAVL(array[letra-65], ga, ArrayString);  /*Coloca na matriz todos os clientes iniciados pela letra dada*/
}




