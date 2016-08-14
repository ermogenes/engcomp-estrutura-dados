#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#define true 1
#define false 0

typedef int bool;

typedef int TIPOCHAVE;

typedef struct
{
    TIPOCHAVE chave;
    // outros campos...
} REGISTRO;


typedef struct tempRegistro
{
    REGISTRO reg;
    struct tempRegistro* prox;
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct
{
    PONT cabeca;
} LISTA;

void inicializarLista(LISTA* l)
{
    l->cabeca = (PONT) malloc(sizeof(ELEMENTO));
    l->cabeca->prox = l->cabeca;
}

void exibirLista(LISTA* l)
{
    PONT end = l->cabeca->prox;
    printf("Lista: \" ");
    while (end != l->cabeca)
    {
        printf("%d ", end->reg.chave);
        end = end->prox;
    }
    printf("\"\n");
}

PONT buscaSentinelaOrd(LISTA* l, TIPOCHAVE ch)
{
    PONT pos = l->cabeca->prox;
    l->cabeca->reg.chave = ch;
    while (pos->reg.chave < ch)
        pos = pos->prox;
    if (pos != l->cabeca && pos->reg.chave==ch)
        return pos;
    return NULL;
}

PONT buscaSeqExc(LISTA* l, TIPOCHAVE ch, PONT* ant)
{
    *ant = l->cabeca;
    PONT pos = l->cabeca->prox;
    l->cabeca->reg.chave = ch;
    while (pos->reg.chave<ch)
    {
        *ant = pos;
        pos = pos->prox;
    }
    if ((pos != l->cabeca) && (pos->reg.chave == ch))
        return pos;
    return NULL;
}

bool inserirElemListaOrd(LISTA* l, REGISTRO reg)
{
    PONT ant, i;
    i = buscaSeqExc(l,reg.chave,&ant);
    if (i != NULL)
        return false;
    i = (PONT) malloc(sizeof(ELEMENTO));
    i->reg = reg;
    i->prox = ant->prox;
    ant->prox = i;
    return true;
}

int maiorChaveParametroPorValor(LISTA l){
    PONT posicaoAtual = l.cabeca->prox;
    if (posicaoAtual == l.cabeca)
        return -1;
    TIPOCHAVE maiorChave = posicaoAtual->reg.chave;
    while(posicaoAtual != l.cabeca)
    {
        if (maiorChave < posicaoAtual->reg.chave)
            maiorChave = posicaoAtual->reg.chave;
        posicaoAtual = posicaoAtual->prox;
    }
    return maiorChave;
}

int maiorChaveParametroPorReferencia(LISTA* l){
    PONT posicaoAtual = l->cabeca->prox;
    if (posicaoAtual == l->cabeca)
        return -1;
    TIPOCHAVE maiorChave = posicaoAtual->reg.chave;
    while(posicaoAtual != l->cabeca)
    {
        if (maiorChave < posicaoAtual->reg.chave)
            maiorChave = posicaoAtual->reg.chave;
        posicaoAtual = posicaoAtual->prox;
    }
    return maiorChave;
}

int main()
{
    LISTA listaTesteExercicio;

    inicializarLista(&listaTesteExercicio);

    REGISTRO r3;
    r3.chave = 30;
    inserirElemListaOrd(&listaTesteExercicio, r3);
    exibirLista(&listaTesteExercicio);

    REGISTRO r1;
    r1.chave = 10;
    inserirElemListaOrd(&listaTesteExercicio, r1);
    exibirLista(&listaTesteExercicio);

    REGISTRO r4;
    r4.chave = 40;
    inserirElemListaOrd(&listaTesteExercicio, r4);
    exibirLista(&listaTesteExercicio);

    REGISTRO r2;
    r2.chave = 20;
    inserirElemListaOrd(&listaTesteExercicio, r2);
    exibirLista(&listaTesteExercicio);

    printf("\nMaior valor: %d [implementacao com parametro por valor]", maiorChaveParametroPorValor(listaTesteExercicio));
    printf("\nMaior valor: %d [implementacao com parametro por referencia]", maiorChaveParametroPorReferencia(&listaTesteExercicio));

    assert(maiorChaveParametroPorValor(listaTesteExercicio) == 40);
    assert(maiorChaveParametroPorReferencia(&listaTesteExercicio) == 40);

    return 0;
}
