#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef struct no {
    TIPOCHAVE chave;
    struct no *primFilho;
    struct no *proxIrmao;
} NO;

typedef NO* PONT;

PONT criaNovoNo(TIPOCHAVE ch)
{
    PONT novo = (PONT)malloc(sizeof(NO));
    novo->primFilho = NULL;
    novo->proxIrmao = NULL;
    novo->chave = ch;
    return(novo);
}

PONT inicializa(TIPOCHAVE ch)
{
    return(criaNovoNo(ch));
}

PONT buscaChave(TIPOCHAVE ch, PONT raiz)
{
    if (raiz == NULL)
        return NULL;
    if (raiz->chave == ch)
        return raiz;
    PONT p = raiz->primFilho;
    while(p)
    {
        PONT resp = buscaChave(ch, p);
        if (resp)
            return(resp);
        p = p->proxIrmao;
    }
    return(NULL);
}

bool insere(PONT raiz, TIPOCHAVE novaChave, TIPOCHAVE chavePai)
{
    PONT pai = buscaChave(chavePai,raiz);
    if (!pai)
        return(false);
    PONT filho = criaNovoNo(novaChave);
    PONT p = pai->primFilho;
    if (!p)
        pai->primFilho = filho;
    else
    {
        while (p->proxIrmao)
            p = p->proxIrmao;
        p->proxIrmao = filho;
    }
    return(true);
}

void exibirArvore(PONT raiz){
    if (raiz == NULL)
        return;
    printf("%d(",raiz->chave);
    PONT p = raiz->primFilho;
    while (p)
    {
        exibirArvore(p);
        p = p->proxIrmao;
    }
    printf(")");
}

int contaElementos(PONT raiz){
    // A contagem da subarvore comeca em 0
    int c = 0;
    // Se houver algum elemento na subarvore
    if (raiz != NULL)
    {
        // Conta a subarvore como um elemento
        c = 1;

        // Se a subarvore tiver filhos
        if (raiz->primFilho != NULL)
        {
            // Soma o a contagem do filho na contagem da subarvore
            c += contaElementos(raiz->primFilho);
        }

        // Se a subarvore tiver irmaos
        if (raiz->proxIrmao != NULL)
        {
            // Soma a contagem do irmao na contagem da subarvore
            c += contaElementos(raiz->proxIrmao);
        }
    }
    return c;
}

int main()
{
    PONT minhaArvore = inicializa(8);
    assert(contaElementos(minhaArvore) == 1);
    insere(minhaArvore,15,8);
    assert(contaElementos(minhaArvore) == 2);
    insere(minhaArvore,23,8);
    assert(contaElementos(minhaArvore) == 3);
    insere(minhaArvore,2,8);
    assert(contaElementos(minhaArvore) == 4);
    insere(minhaArvore,20,15);
    assert(contaElementos(minhaArvore) == 5);
    insere(minhaArvore,10,15);
    assert(contaElementos(minhaArvore) == 6);
    insere(minhaArvore,28,15);
    assert(contaElementos(minhaArvore) == 7);
    insere(minhaArvore,36,2);
    assert(contaElementos(minhaArvore) == 8);
    insere(minhaArvore,7,2);
    assert(contaElementos(minhaArvore) == 9);

    printf("Arvore n-aria:\n");
    exibirArvore(minhaArvore);
    printf("\nNumero de elementos: %d", contaElementos(minhaArvore));

    return 0;
}
