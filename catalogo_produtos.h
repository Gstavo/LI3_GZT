#ifndef CATALOGO_PRODUTOS_H

#define CATALOGO_PRODUTOS_H

#include "avl.h"
#include "boolean.h"

typedef int CODIGOS_PROD;

void initCatalogo_Produtos();

void insertCatalogo_Produtos(AAVL pl,char* code,int* cresceu);

CODIGOS_PROD codigos_Produto();

/* A alterar ta a dar printf */
void codProdutos(AVL array[]);

BOOLEAN existeProd(char* produto, AAVL pl);

#endif
