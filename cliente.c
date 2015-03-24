void codClientes(ProdList array[],int Max){
  for (i=0;i<Max;i++){
     printf("Códigos de Clientes %c : %d\n",i+65,contarNodos(array[i],Max,i+65));
	}
} 

void codProdutos(ProdList array[],int Max){
  for (i=0;i<Max;i++){
     printf("Códigos de Produtos %c : %d\n",i+65,contarNodos(array[i],Max,i+65));
	}
} 

/*ou*/

ProdList devolveAVL(ProdList array[],int MAX,char a){
  int pos=a-65;
  ProdList aux=(ProdList) malloc (sizeof (struct prodTree));
  aux=array[pos];
  return aux;
}


int contarNodos(ProdList aux){
   if(aux == NULL)
        return 0;
   else
        return 1 + contarNodos(aux->esquerda) + contarNodos(aux->direita);
}