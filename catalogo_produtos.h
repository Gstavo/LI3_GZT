#ifndef CATALOGO_PRODUTOS_H

#define CATALOGO_PRODUTOS_H

#include "growingArray.h"
#include "avl.h"
#include "boolean.h"


void initCatalogo_Produtos();

void insertCatalogo_Produtos(AAVL pl,char* code,int* cresceu);

int codigos_Produto();

BOOLEAN existeProd(char* produto, AAVL pl);

void imprimir_produto(GrowingArray ga, AAVL array, char letra);

#endif
