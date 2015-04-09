#ifndef CONTABILIDADE_H

#define CONTABILIDADE_H

#include "avl.h"
#include "compras.h"

#define MAX_MONTHS 12

typedef double FACTORACAO_TOTAL;
typedef double FACTORACAO_MES;
typedef int VENDAS_MES;
typedef int CLIENTES_MES;
typedef int COMPRAS_MES;
typedef int INDICE_MES;



typedef AAVL Contabilidade[MAX_MONTHS];

INDICE_MES indexM(Comp c);

void initContabilidade(Contabilidade c);

void insertContabilidade(Contabilidade c,Comp compra,int* cresceu);

FACTORACAO_TOTAL returnFactTotal();

FACTORACAO_TOTAL returnFact(int mes);

VENDAS_MES returnVendas(int mes);

CLIENTES_MES returnClientes(int mes);

COMPRAS_MES compras_Mes(int mes);

void compMes(Contabilidade c, char* cliente, int resultado[]);

void preenchecmp(int compras_mes[12][1]);
void preencheclientes(int clientes_mes[12][1]);
void create_csv(char *nome_ficheiro,int compras_mes[12][1],int clientes_mes[12][1]);




#endif
