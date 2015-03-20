#define MAX_LINE 40
#define MAX 500000

typedef struct compras {
	char codigo_Produto[10];
	double preco_unitario;
	int unidades_compradas;
	char tipo;	/*promoção-P;normal-N*/
	char codigo_cliente[10];
	int mes_compra;
} Compras;

typedef Compras *Comp;

typedef enum balancefactor {LH, EH, RH} BalanceFactor;

typedef struct prodTree {
	BalanceFactor bf;	/*Fator de balanceamento da arvore*/
	char code[10];
	struct prodTree *left, *right;
} ProdTree;

typedef ProdTree *ProdList;

typedef ProdList Slist[MAX];

void printCompras(Compras a);
int validaMes(int mes);
int validaTipo(char a);
int validaUnidades(int unidade);
int validaPreco(double p);
int isdigitN(char a);
int validaCC(char cc[], ProdList c);
int validaCP(char cc[], ProdList p);
int existeClnt(char cliente[], ProdList c);
int existeProd(char produto[], ProdList p);
int validateCompras(Compras a, ProdList p, ProdList c);
void tokenizer(Comp a, int j, char linha[MAX_LINE]);
void printTree(ProdList p);
ProdList insert(ProdList p, char produto[], int *cresceu);
ProdList insertRight(ProdList p, char produto[], int *cresceu);
ProdList insertLeft(ProdList p, char produto[], int *cresceu);
ProdList balanceRight(ProdList p);
ProdList balanceLeft(ProdList p);
ProdList rotateRight(ProdList p);
ProdList rotateLeft(ProdList p);
int length(char s[]);
