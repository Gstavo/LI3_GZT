#ifndef GROWINGARRAY_H

#define GROWINGARRAY_H

#define ArrayString 1
#define ArrayCompProduto 2

typedef struct compras_prod {
        char* codigo_produto;
        int quantidade;
} ComprasProd;

typedef struct compras_prod *CompProduto;

typedef void* Objeto;

typedef struct growingarray{
        Objeto* Elems;
        int size;
        int max_size;
} growingarray;

typedef growingarray* GrowingArray;

GrowingArray initGrowingArray(int max_size, int tipo);
void insertGrowingArray(GrowingArray a, Objeto o, int tipo);
void resizeGrowingArray(GrowingArray a, int tipo);
void ordenaGrowingArray(GrowingArray a,int tipo);

#endif

	


