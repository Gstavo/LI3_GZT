#include "catalogo_produtos.h"

static int Codigos_Produto = 0;

int index(char* code){return (code[0] - 65);}

AAVL initCatalogo_Produtos(){
        int i;
        AAVL cl;
        for(i=0; i<MAX_LETTERS; i++)
        {
                cl[i]=(AVL) malloc(sizeof(struct AVL_struct));
                cl[i]=NULL;
        }
        return cl;
}

/* guardar o resultado do insert em cl faz alguma cena util???? */

void insertCatalogo_Produtos(AAVL pl,char* code,int* cresceu)
        {
                pl[index(code)] = insert(pl[index(code)],code,cresceu,Catalogo_P);
                Codigos_Produto++;
        }

int codigos_Produto(){return Codigos_Produto;}

/* funçao a alterar n pode printf*/

void codProdutos(AVL array[]){
        int i;
  for (i=0;i<MAX_LETTERS;i++){
     printf("%c : %d\n",i+65,contarNodos(devolveAVL(array, i+65)));
        }
}

int existeProd(char produto[], AAVL pl) 
{
	return existeP_aux(produto,cl[index(produto)]);
}

int existeP_aux(char produto[],AVL p)
{
        int res;
        if(p==NULL) res=0;
        else {
                char* code = p->info;
                if(strncmp(produto,code, 6)<0) res=existeProd(produto, p->left);
             else if(strncmp(produto, code, 6)>0) res=existeProd(produto, p->right);
                  else res=1;
        }
        return res;
}






