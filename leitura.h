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

void leitura(AAVL clnt, AAVL prod, Contabilidade cont, HashTable ht, Comp compra);
void printCompras(Comp a);
int validaMes(int mes);
int validaTipo(char a);
int validaUnidades(int unidade);
int validaPreco(double p);
int isdigitN(char a);
int validateClnt(Compras a, AAVL c);
int validateProd(Compras a, AAVL p);
int validateCompras(Compras a);
void tokenizer(Comp a, char linha[MAX_LINE]);
void printTree(AVL p);
int length(char s[]);
void shiftleft(char* s,int i);
void trim(char* s);

#endif
