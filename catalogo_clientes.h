#ifndef CATALOGO_CLIENTES_H

#define CATALOGO_CLIENTES_H

#include "avl.h"
#include "boolean.h"
#include "growingArray.h"

typedef AAVL CatalogoClientes;

void initCatalogo_Clientes();

void insertCatalogo_Clientes(CatalogoClientes cl,char* code,int* cresceu);

int removeCatalogo_Clientes(CatalogoClientes cl,char* code);

int codigos_Cliente();

BOOLEAN existeClnt(char* cliente, CatalogoClientes cl);

void imprimir_cliente(GrowingArray ga, CatalogoClientes array, char letra);


#endif
