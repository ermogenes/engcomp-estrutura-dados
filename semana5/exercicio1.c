#include <stdio.h>
#include <malloc.h>

#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef struct aux{
    TIPOCHAVE chave;
    struct aux *esq, *dir;
} NO;

typedef NO* PONT;

PONT inicializa() {
    return(NULL);
}

PONT adiciona(PONT raiz, PONT no) {
    if (raiz == NULL) return(no);
    if (no->chave < raiz->chave)
        raiz->esq = adiciona(raiz->esq, no);
    else
        raiz->dir = adiciona(raiz->dir, no);
    return(raiz);
}

PONT criaNovoNo(TIPOCHAVE ch) {
    PONT novoNo = (PONT)malloc(sizeof(NO));
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->chave = ch;
    return(novoNo);
}

void exibirArvore(PONT raiz){
    if (raiz != NULL)
    {
        printf("%d",raiz->chave);
        printf("(");
        exibirArvore(raiz->esq);
        exibirArvore(raiz->dir);
        printf(")");
    }
}

void exibirElementosDecrescente(PONT raiz){
    // Se tiver elementos na subarvore
    if (raiz != NULL)
    {
        // Se a subarvore tiver elementos a direita
        if (raiz->dir != NULL)
        {
            // Exibe a subarvore da direita
            exibirElementosDecrescente(raiz->dir);
        }

        // Exibe a chave da raiz da subarvore atual
        printf("%d ", raiz->chave);

        // Se a subarvore tiver elementos a esquerda
        if (raiz->esq != NULL)
        {
            // Exibe a subarvore da esquerda
            exibirElementosDecrescente(raiz->esq);
        }
    }
}

int main()
{
    PONT minhaArvore = inicializa();

    PONT no;
    no = criaNovoNo(8);  minhaArvore = adiciona(minhaArvore, no);
    no = criaNovoNo(5);	 minhaArvore = adiciona(minhaArvore, no);
    no = criaNovoNo(10); minhaArvore = adiciona(minhaArvore, no);
    no = criaNovoNo(3);	 minhaArvore = adiciona(minhaArvore, no);
    no = criaNovoNo(2);	 minhaArvore = adiciona(minhaArvore, no);
    no = criaNovoNo(7);	 minhaArvore = adiciona(minhaArvore, no);
    no = criaNovoNo(1);  minhaArvore = adiciona(minhaArvore, no);
    no = criaNovoNo(4);	 minhaArvore = adiciona(minhaArvore, no);
    no = criaNovoNo(6);	 minhaArvore = adiciona(minhaArvore, no);
    no = criaNovoNo(9);  minhaArvore = adiciona(minhaArvore, no);

    printf("Arvore:\n"); exibirArvore(minhaArvore);

    printf("\nElementos da arvore em ordem decrescente:\n");
    exibirElementosDecrescente(minhaArvore);

    return 0;
}

