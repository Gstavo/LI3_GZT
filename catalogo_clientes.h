#ifndef CATALOGO_CLIENTES_H

#define CATALOGO_CLIENTES_H

#include "avl.h"

void initCatalogo_Clientes();

void insertCatalogo_Clientes(AAVL cl,char* code,int* cresceu);

int codigos_Cliente();

/* funçao a alterar(esta a fazer printf) */
void codClientes(AVL array[]);

int existeClnt(char cliente[], AAVL cl);

#endif
