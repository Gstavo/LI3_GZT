#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "catalogo_produtos.h"

static int Codigos_Produto = 0;

/*Inicializa a estrutura de dados do catalogo de produtos*/
void initCatalogo_Produtos(CatalogoProdutos pl){
        int i;
        for(i=0; i<MAX_LETTERS; i++)
        {
                pl[i]=NULL;
        }
}

/*Insere um codigo de produto no catalogo*/
void insertCatalogo_Produtos(CatalogoProdutos pl,char* code,int* cresceu)
        {
                pl[indexL(code)] = insert(pl[indexL(code)],code,cresceu,Catalogo_P);
                Codigos_Produto++;
        }

/*Remove um produto do catalogo*/
int removeCatalogo_Produtos(CatalogoProdutos pl,char* code)
{
	int i = indexL(code),r;
        r = removeAVL(pl[i],code,Catalogo_C);
        if(r==0) Codigos_Produto--;
        return r;
}

/*Retorna o numero de codigos de produto*/
int codigos_Produto(){return Codigos_Produto;}

/*Funcao auxiliar da existeProd*/
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

/*Verifica se um produto existe no catalogo*/
BOOLEAN existeProd(char* produto, CatalogoProdutos pl) 
{
	return existeP_aux(produto,pl[indexL(produto)]);
}

/*Guarda no growing array todos os produto iniciados por dada letra*/
void imprimir_produto(GrowingArray ga, CatalogoProdutos array, char letra) {
    if((letra>97 && letra<122)) letra-=32;  /*Se for minuscula passa para maiuscula*/
    guardArrayAVL(array[letra-65], ga, ArrayString);  /*Coloca na matriz todos os clientes iniciados pela letra dada*/
}




