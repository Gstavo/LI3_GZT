#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include "leitura.h"

/*Executa a leitura das estruturas de dados*/
void leitura(AAVL clnt, AAVL prod, Contabilidade contClnt, HashTable ht, Comp compra, int valid[],char* comprastxt) {
	int i, *cresceu=(int*) malloc(sizeof(int)), clntInv=0, prodInv=0;	
	BOOLEAN validaClnt=FALSE, validaProd=FALSE, validaCmpr=FALSE;
	int countCompras=0, compras_invalidas=0;
	char linha[MAX_LINE];
	FILE *clientes, *produtos, *fcompras;

	clientes=fopen("clientes.txt","r"); 
	produtos=fopen("produtos.txt","r");
	fcompras=fopen(comprastxt,"r");

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
			if(validaClnt==FALSE) clntInv++;
			if(validaProd==FALSE) prodInv++;
			if(validaClnt==FALSE || validaProd==FALSE || validaCmpr==FALSE) compras_invalidas++;
			else {
				insertContabilidade(contClnt, compra, cresceu);
				ht = insertHashTable(ht,compra);	
			}
			countCompras++;
	}

	fclose(clientes);
	fclose(produtos);
	fclose(fcompras);

	valid[0]=countCompras;
	valid[1]=clntInv;
	valid[2]=prodInv;
	valid[3]=compras_invalidas;
	valid[4]=countCompras-compras_invalidas;
}

/*Valida o mes*/
BOOLEAN validaMes(int mes){
	if(mes>=1 && mes<=12) return TRUE;		
	else return FALSE;				
}

/*Valida o tipo da compra*/
BOOLEAN validaTipo(char a){
	if(a=='P' || a=='N') return TRUE;		
	else return FALSE;				
}

/*Valida o numero de unidades compradas*/
BOOLEAN validaUnidades(int unidade){
	if(unidade>0 && unidade<200000) return TRUE;	
	else return FALSE;					
}

/*Valida o preco do produto*/
BOOLEAN validaPreco(double p){
	if(p>=0.0) return TRUE;		
	else return FALSE;			
}

/*Verifica se e um digito*/
BOOLEAN isdigitN(char a) {
	return ((a >= 48) && (a<=57));
}

/*Verifica se um cliente existe no catalogo de clientes*/
BOOLEAN validateClnt(Compras a, AAVL cl) {
        if(existeClnt(a.codigo_cliente, cl)==FALSE) return FALSE;
        else return TRUE;
}

/*Verifica se um produto existe no catalogo de produtos*/
BOOLEAN validateProd(Compras a, AAVL pl) {
	if(existeProd(a.codigo_produto, pl)==FALSE) return FALSE;
	else return TRUE;
}

/*Valida a compra*/
BOOLEAN validateCompras(Compras a) {
	if(validaMes(a.mes)==FALSE || validaTipo(a.tipo)==FALSE || validaUnidades(a.quantidade)==FALSE || validaPreco(a.preco)==FALSE)
		return FALSE;
	else return TRUE;
} 

/*Parte uma linha do ficheiro de compras*/
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

/*Comprimento de uma string*/
COMPRIMENTO length(char s[]) {
       int i;
       for(i=0; s[i]!='\0'; i++);
       return i;
}

/*Move a linha para a esquerda desde um determinado indice*/
void shiftleft(char* s,int i)
{
        while(s[i]!='\0')
        {
                s[i] = s[i+1];
                i++;
        }
}

/*Retira os espacos em excesso numa linha de compras*/
void trim(char* s)
{
        int i;
        for(i = 0;s[i] == ' ';) shiftleft(s,i);
        for(i = 0;s[i] != '\0';)
                if(s[i] == ' ' && s[i+1] == ' ') shiftleft(s,i);
                else i++;
        if(i > 0 && s[i-1] == ' ') s[i-1] = '\0';
}
