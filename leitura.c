#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include "leitura.h"

void leitura(AAVL clnt, AAVL prod, Contabilidade cont, HashTable ht, Comp compra) {
	int i, *cresceu=(int*) malloc(sizeof(int)), validaClnt=0, validaProd=0, validaCmpr=0, clntInv=0, prodInv=0;	
	int countCompras=0, compras_invalidas=0;
	char linha[MAX_LINE];
	FILE *clientes, *produtos, *fcompras;

	compra=malloc(sizeof(struct compras));
	compra->codigo_produto = malloc(10*sizeof(char));
	compra->codigo_cliente = malloc(10*sizeof(char));

	/*Inicializa as estruturas*/
	initCatalogo_Clientes(clnt);
	initCatalogo_Produtos(prod);
	initContabilidade(cont);
	ht=NULL; /* necessario pois bug estranho de compilaçao */
	initCompras(ht);

	clientes=fopen("clientes.txt","r"); 
	produtos=fopen("produtos.txt","r");
	fcompras=fopen("compras1.txt","r");

	for(i=0; fgets(linha, MAX_LINE, clientes); i++) {
			linha[strlen(linha)-1]='\0';
			trim(linha);
			insertCatalogo_Clientes(clnt, linha, cresceu);
	}
	for(i=0; fgets(linha, MAX_LINE, produtos); i++) { 
			linha[strlen(linha)-1]='\0';
			trim(linha);
			insertCatalogo_Produtos(prod, linha, cresceu);
	}
	for(i=0; fgets(linha, MAX_LINE, fcompras); i++) {
			linha[strlen(linha)-1] = '\0';
			trim(linha);
			tokenizer(compra, linha);
			validaClnt=validateClnt((*compra), clnt);
			validaProd=validateProd((*compra), prod);
			validaCmpr=validateCompras((*compra));
			if(validaClnt==0) clntInv++;
			if(validaProd==0) prodInv++;
			if(validaClnt==0 || validaProd==0 || validaCmpr==0) compras_invalidas++;
			else {
				insertContabilidade(contabilidade,compra,cresceu);
				insertComprasHashCP(ht,compra,cresceu);	
			/* Futuramente vai inserir a compra nas estruturas de dados em compras.c tambemaqui */
			}
			countCompras++;
	}

	fclose(clientes);
	fclose(produtos);
	fclose(fcompras);

	/* Hash - Compras (TESTE) */
	printf("Numero de vezes de realocaçao da hash : %d\n",getRemakes());
	printf("Tamanho da hash : %d\n",ht->size);

	printf("\nPRODUTOS: %d\n", codigos_Produto());
	printf("CLIENTES: %d\n", codigos_Cliente());
	printf("LINHAS DE COMPRAS: %d\n", countCompras);
	printf("CODIGOS DE CLIENTE INEXISTENTES: %d\n", clntInv);
	printf("CODIGOS DE PRODUTO INEXISTENTES: %d\n", prodInv);
	printf("TOTAL DE COMPRAS INVALIDAS: %d\n", compras_invalidas);
	printf("--------------------------------------------\n");
	printf("COMPRAS VALIDAS: %d\n", (countCompras-compras_invalidas));
	printf("FATURACAO ANUAL TOTAL: %.2f Euros\n\n", returnFactTotal());
}

/*Funcao util para imprimir as compras*/
void printCompras(Comp a){
	printf("Codigo Produto = %s\n",a->codigo_produto);
	printf("Preco Unitario = %f\n",a->preco);
	printf("Unidades Compradas = %d\n",a->quantidade);
	printf("Tipo = %c\n",a->tipo);
	printf("Codigo Cliente = %s\n",a->codigo_cliente);
	printf("Mes = %d\n",a->mes);
}

int validaMes(int mes){
	if(mes>=1 && mes<=12) return 1;		/*Verdadeiro*/
	else return 0;				/*Falso*/
}

int validaTipo(char a){
	if(a=='P' || a=='N') return 1;		/*Verdadeiro*/
	else return 0;				/*Falso*/
}

int validaUnidades(int unidade){
	if(unidade>0 && unidade<200000) return 1;	/*Verdadeiro*/
	else return 0;					/*Falso*/
}

int validaPreco(double p){
	if(p>=0.0) return 1;		/*Verdadeiro*/
	else return 0;			/*Falso*/
}

int isdigitN(char a) {return ((a >= 48) && (a<=57));}

int validateClnt(Compras a, AAVL cl) {
        if(existeClnt(a.codigo_cliente, cl)==0) return 0;
        else return 1;
}

int validateProd(Compras a, AAVL pl) {
	if(existeProd(a.codigo_produto, pl)==0) return 0;
	else return 1;
}

int validateCompras(Compras a) {
	if(validaMes(a.mes)==0 || validaTipo(a.tipo)==0 || validaUnidades(a.quantidade)==0 || validaPreco(a.preco)==0)
		return 0;
	else return 1;
} 

void tokenizer(Comp a, char linha[MAX_LINE]){
	char* t; 
	int x=0, n;
	double m;
	t=strtok(linha, " ");
	while (t!=NULL) 
	{
        	if(x == 0) strcpy(a->codigo_produto, t);
        	if(x == 1) {
			m=atof(t);
			a->preco=m;
		}
        	if(x == 2) {
			n=atoi(t);
			a->quantidade=n;
		}
        	if(x == 3) a->tipo = t[0];
        	if(x == 4) strcpy(a->codigo_cliente, t); 
        	if(x == 5) {
			n=atoi(t);
			a->mes=n;
		}
        	x++;
        	t=strtok(NULL, " ");
	}	
}

void printTree(AVL p) {
	int i;
	if(p==NULL) printf("NULL\n");
	else {
		char* code = p->info;
		for(i=0; i<6; i++) printf("%c", code[i]);
		printf("\n");
		printTree(p->left);
		printTree(p->right);
	}
}
int length(char s[]) {
       int i;
       for(i=0; s[i]!='\0'; i++);
       return i;
}

void shiftleft(char* s,int i)
{
        while(s[i]!='\0')
        {
                s[i] = s[i+1];
                i++;
        }
}

void trim(char* s)
{
        int i;
        for(i = 0;s[i] == ' ';) shiftleft(s,i);
        for(i = 0;s[i] != '\0';)
                if(s[i] == ' ' && s[i+1] == ' ') shiftleft(s,i);
                else i++;
        if(i > 0 && s[i-1] == ' ') s[i-1] = '\0';
}
