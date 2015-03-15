typedef enum balancefactor {LH, EH, RH} BalanceFactor;

typedef struct prodTree {
	BalanceFactor bf;	/*Fator de balanceamento da arvore*/
	char code[10];
	struct prodTree *left, *right;
} ProdTree;

typedef ProdTree *ProdList;

ProdList rotateRight(ProdList p) {	
	ProdList aux;
	if((!p) || (!p->left)) printf("Erro!\n");
	else {
		aux=p->left;
		p->left=aux->right;
		aux->right=p;
		p=aux;
	}
	return p;
}

ProdList rotateLeft(ProdList p) {
	ProdList aux;
	if((!p) || (!p->right)) printf("Erro!\n");
	else {
		aux=p->right;
		p->right=aux->left;
		aux->left=p;
		p=aux;
	}
	return p;
}

ProdList insert(ProdList p, char produto[], int *cresceu) {
	if(p==NULL) {
		p=(ProdList) malloc(sizeof(struct prodTree));
		strcpy(p->code, produto);
		p->right=p->left=NULL;
		p->bf=EH;
		*cresceu=1;
	}
	else if(strcmp(p->code, produto)<0) p=insertLeft(p, produto, cresceu);
	     else p=insertRight(p, produto, cresceu); 
	return p;
}

ProdList insertRight(ProdList p, char produto[], int *cresceu) {
	p->right=insert(p->right, produto, cresceu);
	if(*cresceu) {
		switch(p->bf) {
		case LH:
			p->bf=EH;
			*cresceu=0;
			break;
		case EH:
			p->bf=RH;
			*cresceu=1;
			break;
		case RH:
			p=balanceRight(p);
			*cresceu=0;
		}
	}
	return p;
}

ProdList insertLeft(ProdList p, char produto[], int *cresceu) {
	p->left=insert(p->left, produto, cresceu);
	if(*cresceu) {
		switch(p->bf) {
		case RH:
			p->bf=EH;
			*cresceu=0;
			break;
		case EH:
			p->bf=LH;
			*cresceu=1;
			break;
		case LH:
			p=balanceLeft(p);
			*cresceu=0;
		}
	}
	return p;
}

ProdList balanceRight(ProdList p) {
	ProdList aux;
	if(p->right->bf==RH) {
		p=rotateLeft(p);
		p->bf=EH;
		p->left->bf=EH;
	}
	else {
		p->right=rotateRight(p->right);
		p=rotateLeft(p);
		switch(p->bf) {
		case EH:
			p->left->bf=EH;
			p->right->bf=EH;
			break;
		case LH:
			p->left->bf=EH;
			p->right->bf=RH;
			break;
		case RH:
			p->left->bf=LH;
			p->right->bf=EH;
		}
		p->bf=EH;
	}
	return p;
}

ProdList balanceLeft(ProdList p) {
	ProdList aux;
	if(p->left->bf==LH) {
		p=rotateRight(p);
		p->bf=EH;
		p->right->bf=EH;
	}
	else {
		p->left=rotateLeft(p->left);
		p=rotateRight(p);
		switch(p->bf) {
		case EH:
			p->left->bf=EH;
			p->right->bf=EH;
			break;
		case RH:
			p->right->bf=EH;
			p->left->bf=LH;
			break;
		case LH:
			p->right->bf=RH;
			p->left->bf=EH;
		}
		p->bf=EH;
	}
	return p;
}


	
