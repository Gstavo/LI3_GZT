#ifndef CONTABILIDADE_H

#define CONTABILIDADE_H

#include "avl.h"

#define MAX_MONTH 12
#define MAX_LETTERS 26

typedef struct CONTA_struct {
        AAVL[MAX_LETTERS];
} CONTA_struct;

typedef CONTA_struct *CONTA;

typedef CONTA CONTABILIDADE[MAX_MONTH];


void separaComp(todas_compras,AAVL promo, AAVL normal);
AVL produtosMes(CONTA array[], int mes);
int facturaPromo(CONTA array[], int mes, produtos_todos_comprados_P);
int facturaNormal(CONTA array[], int mes, produtos_todos_comprados_N);
int vendasPromo(Compras);/*percorrer AAVL promo*/
int vendasNormal(Compras);/*percorrer AAVL normal*/

#endif



