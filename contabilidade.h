#ifndef CONTABILIDADE_H

#define CONTABILIDADE_H

#include "avl.h"
#include "compras.h"

#define MAX_MONTHS 12

typedef AAVL Contabilidade[MAX_MONTHS];

int indexM(Comp c);

void initContabilidade(Contabilidade c);

void insertContabilidade(Contabilidade c,Comp compra,int* cresceu);

int compras_Mes(int mes);



#endif
