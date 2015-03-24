#define MAX_LINE 40
#define MAX 500000
#define MAX_LETTERS 26

#include "avl.h"

void printCompras(Compras a);
int validaMes(int mes);
int validaTipo(char a);
int validaUnidades(int unidade);
int validaPreco(double p);
int isdigitN(char a);
int validaCC(char cc[], AVL c);
int validaCP(char cc[], AVL p);
int existeClnt(char cliente[], AVL c);
int existeProd(char produto[], AVL p);
int validateClnt(Compras a, AVL c);
int validateProd(Compras a, AVL p);
int validateCompras(Compras a);
void tokenizer(Comp a, int j, char linha[MAX_LINE]);
void printTree(AVL p);
void codClientes(AVL array[]);
void codProdutos(AVL array[]);
int length(char s[]);
