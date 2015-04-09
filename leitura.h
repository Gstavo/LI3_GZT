#ifndef LEITURA_H
#define LEITURA_H

#define MAX_LINE 40
#define MAX 500000

#include "avl.h"
#include "hashtable.h"
#include "catalogo_clientes.h"
#include "catalogo_produtos.h"
#include "compras.h"
#include "contabilidade.h"
#include "boolean.h"

typedef int COMPRIMENTO;

void leitura(AAVL clnt, AAVL prod, Contabilidade cont, HashTable ht, Comp compra);
void printCompras(Comp a);
BOOLEAN validaMes(int mes);
BOOLEAN validaTipo(char a);
BOOLEAN validaUnidades(int unidade);
BOOLEAN validaPreco(double p);
BOOLEAN isdigitN(char a);
BOOLEAN validateClnt(Compras a, AAVL c);
BOOLEAN validateProd(Compras a, AAVL p);
BOOLEAN validateCompras(Compras a);
void tokenizer(Comp a, char linha[MAX_LINE]);
void printTree(AVL p);
COMPRIMENTO length(char s[]);
void shiftleft(char* s,int i);
void trim(char* s);

#endif
