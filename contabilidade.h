#ifndef CONTABILIDADE_H

#define CONTABILIDADE_H

#include "avl.h"
#include "compras.h"

#define MAX_MONTHS 12

typedef AAVL Contabilidade[MAX_MONTHS];

int indexM(Comp c);

void initContabilidade(Contabilidade c);

void insertContabilidade(Contabilidade c,Comp compra,int* cresceu);

double returnFactTotal();

double returnFact(int mes);

int returnVendas(int mes);

int compras_Mes(int mes);

void compMes(Contabilidade c, char* cliente, int resultado[]);



#endif
