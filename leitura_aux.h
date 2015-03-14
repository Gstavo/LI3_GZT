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

void printCompras(Compras a);
int validaMes(int mes);
int validaTipo(char a);
int validaUnidades(int unidade);
int validaPreco(double p);
int isdigitN(char a);
int validaCC(char cc[]);
int validaCP(char cc[]);
int validateCompras(Compras a);
void tokenizer(Comp a, int j, char linha[MAX_LINE]);
