#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <time.h>

#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef struct aux {
	TIPOCHAVE chave;
	struct aux *esq;
	struct aux *dir;
	int h; // altura desse nó
} NO, *PONT;

PONT criaNo(TIPOCHAVE ch){
	PONT novoNo = (PONT)malloc(sizeof(NO));
	novoNo->esq = NULL;
	novoNo->dir = NULL;
	novoNo->chave = ch;
	novoNo->h = 0;
	return(novoNo);
}

PONT inicializa() {
	return(NULL);
}

void exibirArvore(PONT raiz){
  if (raiz != NULL) {
		printf("%d[%d]",raiz->chave,raiz->h);
		printf("(");
		exibirArvore(raiz->esq);
		exibirArvore(raiz->dir);
		printf(")");
	}
}

int max(int a, int b){
	if (a>b) return a;
	return b;
}

int altura (PONT raiz) {
	if (!raiz) return(-1);
	return(raiz->h);
}

PONT direita(PONT r) {
	PONT aux;
	aux = r->esq;
	r->esq = aux->dir;
	aux->dir = r;

	r->h = max(altura(r->dir),altura(r->esq)) +1;
	aux->h = max(altura(aux->esq),r->h) +1;
	return(aux);
}

PONT esquerda(PONT r) {
	PONT aux;
	aux = r->dir;
	r->dir = aux->esq;
	aux->esq = r;

	r->h = max(altura(r->dir),altura(r->esq)) +1;
	aux->h = max(altura(aux->dir),r->h) +1;
	return(aux);
}

PONT esquerdaDireita(PONT r) {
	r->esq = esquerda(r->esq);
	return(direita(r));
}


PONT direitaEsquerda(PONT r) {
	r->dir = direita(r->dir);
	return(esquerda(r));
}

PONT insere(PONT raiz, TIPOCHAVE ch) {
	if (!raiz) return(criaNo(ch));
	// existe uma árvore
	if (ch < raiz->chave) {
		raiz->esq = insere(raiz->esq,ch);
		// verifica se desbalanceou
		if ((altura(raiz->esq) - altura(raiz->dir)) == 2) {
			// se inseriu à esquerda, esq-dir só pode dar +2, se desbalanceado
			if (ch < raiz->esq->chave) {
				// incluiu à esquerda do filho da esquerda
				raiz = direita(raiz);
			}
			else {
				// incluiu à direita do filho da esquerda
				raiz = esquerdaDireita(raiz);
			}
		}
		// se não for 2, está ok, é AVL
	}
	else {
		if (ch > raiz->chave) {
			raiz->dir = insere(raiz->dir, ch);
			if ((altura(raiz->dir) - altura(raiz->esq)) == 2) {
				// se inseriu à direita, dir-esq só pode dar +2, se desbalanceado
				if (ch > raiz->dir->chave) {
					// incluiu à direita do filho da direita
					raiz = esquerda(raiz);
				}
				else {
					// incluiu à esquerda do filho da direita
					raiz = direitaEsquerda(raiz);
				}
			}
		}
		// ignoro se igual a chave
	}
	raiz->h = max(altura(raiz->esq),altura(raiz->dir))+1;
	return(raiz);
}

bool avl(PONT raiz)
{
	bool ehAVL = true;
	if (raiz != NULL)
	{
		int fb = altura(raiz->esq) - altura(raiz->dir);

		// Uma arvore eh AVL se esta balanceada
		// OU desbalanceada somente um nivel E se seus dois filhos sao AVL
		ehAVL = (
			fb == 0
			|| (abs(fb) == 1 && avl(raiz->esq) && avl(raiz->dir))
		);
	}
	return ehAVL;
}

int main() {
	PONT r = inicializa();

	// Arvore vazia eh AVL
	assert(avl(r) == true);

	// Insercoes quaisquer devem manter a arvore AVL
	r = insere(r,15);	assert(avl(r) == true);
	r = insere(r,8);	assert(avl(r) == true);
	r = insere(r,23);	assert(avl(r) == true);
	r = insere(r,12);	assert(avl(r) == true);
	r = insere(r,2);	assert(avl(r) == true);
	r = insere(r,20);	assert(avl(r) == true);
	r = insere(r,18);	assert(avl(r) == true);

	// Insercoes em lote devem manter a arvore AVL
	int k;

	// insere mil nos em ordem crescente
	for(k = 1; k <= 1000; k++)
	{
		r = insere(r, k);		assert(avl(r) == true);
	}

	// insere mil nos em ordem decrescente
	for(k = 1000; k > 0; k--)
	{
		r = insere(r, k);		assert(avl(r) == true);
	}

	// insere mil nos aleatorios
	for(k = 1; k <= 1000; k++)
	{
		r = insere(r, rand());  assert(avl(r) == true);
	}

	exibirArvore(r);
	printf("\n");

	printf("\n\nA arvore tem altura %d. Eh AVL? %s", altura(r), avl(r) ? "S" : "N");
	printf("\n");
}
