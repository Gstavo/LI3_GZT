#include <stdio.h>

int main () {
	int escolha;
	printf ("\n\n------------------------------------------------------MENU-----------------------------------------------------\n\n");
	printf ("1 - Ler ficheiros;\n");
	printf ("2 - Lista e total de produtos;\n");
	printf ("3 - Numero total de vendas de um produto num dado mes;\n");
	printf ("4 - Lista de codigos de produtos;\n");
	printf ("5 - Numero de produtos comprados por cliente;\n");
	printf ("6 - ???;\n");
	printf ("7 - Total de compras registadas entre dois meses;\n");
	printf ("8 - Clientes que compraram determinado produto;\n");
	printf ("9 - Produtos comprados por cliente;\n");
	printf ("10 - Clientes que realizaram compras neste ano;\n");
	printf ("11 - Criar ficheiro (em Excel) com o numero de compras realizadas e o numero de compradores por mes;\n");
	printf ("12 - Produtos mais vendidos no ano;\n");
	printf ("13 - Os tres produtos mais comprados por cada cliente;\n");
	printf ("14 - Clientes que nao compraram nada, assim como os produtos que nao foram adquiridos;\n\n");
	printf ("---------------------------------------------------------------------------------------------------------------\n\n");
	printf ("Intruduza a sua escolha: ");
	scanf ("%d", &escolha);
	printf ("\n");
	return 0;
}

