#define MAX_LETTERS 26

#define Catalogo_C 1
#define Catalogo_P 2
#define Compras_Ord_CP 3
#define Compras_Ord_CC 4 


typedef enum balancefactor {LH, EH, RH} BalanceFactor;

typedef struct AVL_struct {
        BalanceFactor bf;       /*Fator de balanceamento da arvore*/
       /* char code[10]; */
	void* info;
        struct AVL_struct *left, *right;
} AVL_struct;

typedef AVL_struct *AVL;

typedef AVL AAVL[MAX_LETTERS];

typedef struct compras {
        char codigo_Produto[10];
        double preco_unitario;
        int unidades_compradas;
        char tipo;      /*promoção-P;normal-N*/
        char codigo_cliente[10];
        int mes_compra;
} Compras;

typedef Compras *Comp;


AVL insert(AVL p, void* unc_info, int *cresceu,int tipo_AVL);
AVL insertRight(AVL p, void* unc_info, int *cresceu,int tipo_AVL);
AVL insertLeft(AVL p, void* unc_info, int *cresceu,int tipo_AVL);
AVL balanceRight(AVL p);
AVL balanceLeft(AVL p);
AVL rotateRight(AVL p);
AVL rotateLeft(AVL p);
AVL devolveAVL(AVL array[], char a);
int contarNodos(AVL aux);
void compracpy(Comp dest,Comp src);
int compracmpCC(Comp c1,Comp c2);
int compracmpCP(Comp c1,Comp c2);

