#ifndef CATALOGO_CLIENTES_H

#define CATALOGO_CLIENTES_H

#include "avl.h"
#include "boolean.h"
#include "growingArray.h"

typedef CompProduto listaProdutos[MAX_PROD];

void initCatalogo_Clientes();

void insertCatalogo_Clientes(AAVL cl,char* code,int* cresceu);

int codigos_Cliente();

BOOLEAN existeClnt(char* cliente, AAVL cl);

void imprimir_cliente(GrowingArray ga, AAVL array, char letra);


#endif
