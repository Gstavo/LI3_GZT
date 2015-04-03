#ifndef CSV_H

#define CSV_H

#include "avl.h"
#include "compras.h"
#include "contabilidade.h"

#define MAX_LINE 12  /*numero de meses*/


void preenchecmp(int compras_mes[12][1]);
void preencheclientes(int clientes_mes[12][1]);
void create_csv(char *nome_ficheiro,int compras_mes[12][1],int clientes_mes[12][1]);


#endif