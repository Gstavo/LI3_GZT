#ifndef CATALOGO_CLIENTES_H

#define CATALOGO_CLIENTES_H

#include "growingArray.h"
#include "avl.h"
#include "boolean.h"

void initCatalogo_Clientes();

void insertCatalogo_Clientes(AAVL cl,char* code,int* cresceu);

int codigos_Cliente();

/* funçao a alterar(esta a fazer printf) */
void codClientes(AVL array[]);

BOOLEAN existeClnt(char* cliente, AAVL cl);

void imprimir_cliente(GrowingArray ga, AAVL array, char letra);


#endif
