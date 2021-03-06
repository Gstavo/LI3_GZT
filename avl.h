
#ifndef AVL_H

#define AVL_H

#define MAX_LETTERS 26
#define MAX_PROD 200000
#define Catalogo_C 1
#define Catalogo_P 2
#define Compras_Ord_CP 3
#define Compras_Ord_CC 4 

typedef int INDICE_CODIGOS;
typedef int NUM_NODOS;
typedef int NUM_OCORRENCIAS_CODE;
typedef enum balancefactor {LH, EH, RH} BalanceFactor;

typedef struct avl_node {
        BalanceFactor bf;       /*Fator de balanceamento da arvore*/
       /* char code[10]; */
        void* info; 
        struct avl_node *left, *right;
} AVL_node;

typedef struct avl_node* AVL;

typedef AVL AAVL[MAX_LETTERS];

#include "compras.h"
#include "growingArray.h"
#include "boolean.h"

AVL insert(AVL p, void* unc_info, int *cresceu,int tipo_AVL);
AVL devolveAVL(AVL array[], char a);
int removeAVL(AVL p,void* info,int tipo);
NUM_NODOS contarNodos(AVL aux);
INDICE_CODIGOS indexL(char* code);
NUM_OCORRENCIAS_CODE avl_count(AVL c, char* code, int tipo, char mode);
void guardArrayAVL(AVL aux,GrowingArray array,int tipo);
void guardOcurrencesAVL(AVL avl,GrowingArray array,int tipo,char* codigo);
void limpaLista(char **buf);
double avl_countFact(AVL c, char* code);
BOOLEAN countainAVL(AVL a,char* code);


#endif
