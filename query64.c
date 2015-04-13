#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 500000

void imprime30(char **lista,int index){
    int i;
    for(i=0;i<30;i++){
        printf("%s\n", lista[index+i]);
    }
}




int main(){
    int i=0, j;
    int seguintes=0,anteriores=0;
    char escolha=' ';
    char **lista_letra=(char**) malloc(MAX*sizeof(char**));
   
    for(i=0;i<MAX/2;i++){
        lista_letra[i]="ola";
    }

    for(i=(MAX/2)+1;i<MAX;i++){
        lista_letra[i]="hello";
    }

    i=0;
    printf("\nOS PRIMEIROS RESULTADOS:\n");
    imprime30(lista_letra,i);
    printf("SE DESEJAR SAIR ESCREVA S.\n");
    printf("SE DESEJAR CONTINUAR ESCREVA P.\n");
    printf("SE DESEJAR VER OS RESULTADOS ANTERIORES ESCREVA A.\n");
    do {
	scanf("%c", &escolha);
	if(escolha=='S' || escolha=='s') break;
        else if(escolha=='P'|| escolha=='p') {
		seguintes++;
		i+=(30*seguintes);
		imprime30(lista_letra, i);
	}
        else if(escolha=='A'|| escolha=='a') {
		anteriores++;
		i-=(30*anteriores);
		imprime30(lista_letra,i);
	}
    } while(escolha!='s'|| escolha!='S');
    return 0;
}

