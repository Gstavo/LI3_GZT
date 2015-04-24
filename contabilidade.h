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
void insertContabilidade(Contabilidade contClnt, Comp compra, int* cresceu);
int removeContabilidade(Contabilidade c,Comp compra);
FACTORACAO_TOTAL returnFactTotal();
FACTORACAO_TOTAL returnFact(int mes);
VENDAS_MES returnVendas(int mes);
CLIENTES_MES returnClientes(int mes);
COMPRAS_MES compras_Mes(int mes);
GrowingArray getClientesMensais();
int getClientesInativos();
void compMes(Contabilidade c, char* cliente, int resultado[]);
void preenchecmp(int compras_mes[12]);
void preencheclientes(int clientes_mes[12]);
void create_csv(int compras_mes[12], int clientes_mes[12]);
int comprasModo(Contabilidade contProd, int mes, char *code, char modo);
double totalFactProdMes(Contabilidade contProd, int mes, char *code);
void gatherData(AAVL cl,Contabilidade c);

#endif
