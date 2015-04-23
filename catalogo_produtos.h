#ifndef CATALOGO_PRODUTOS_H

#define CATALOGO_PRODUTOS_H

#include "growingArray.h"
#include "avl.h"
#include "boolean.h"

typedef AAVL CatalogoProdutos;

void initCatalogo_Produtos();

void insertCatalogo_Produtos(CatalogoProdutos pl,char* code,int* cresceu);

int removeCatalogo_Produtos(CatalogoProdutos pl,char* code);

int codigos_Produto();

BOOLEAN existeProd(char* produto, CatalogoProdutos pl);

void imprimir_produto(GrowingArray ga, CatalogoProdutos array, char letra);

#endif
