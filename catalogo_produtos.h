#ifndef CATALOGO_PRODUTOS_H

#define CATALOGO_PRODUTOS_H

#include "avl.h"

void initCatalogo_Produtos();

void insertCatalogo_Produtos(AAVL pl,char* code,int* cresceu);

int codigos_Produto();

/* A alterar ta a dar printf */
void codProdutos(AVL array[]);

int existeProd(char produto[], AAVL pl);

#endif