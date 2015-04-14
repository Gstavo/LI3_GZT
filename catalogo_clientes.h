#ifndef CATALOGO_CLIENTES_H

#define CATALOGO_CLIENTES_H

#include "avl.h"
#include "boolean.h"

typedef struct compras_prod {
	char* codigo_produto;
	int quantidade;
} ComprasProd;

typedef struct compras_prod *CompProduto;

typedef CompProduto listaProdutos[MAX_PROD];

void initCatalogo_Clientes();

void insertCatalogo_Clientes(AAVL cl,char* code,int* cresceu);

int codigos_Cliente();

/* funçao a alterar(esta a fazer printf) */
void codClientes(AVL array[]);

BOOLEAN existeClnt(char* cliente, AAVL cl);

void imprimir_cliente(char **lista, AAVL array, char letra);


#endif
