#include <stdio.h>
#include <assert.h>;

#define MAX 50
#define ERRO -1
#define true 1
#define false 0

typedef int bool;

typedef int TIPOCHAVE;

typedef struct
{
    TIPOCHAVE chave;
    // outros campos...
} REGISTRO;

typedef struct
{
    REGISTRO A[MAX+1];
    int nroElem;
} LISTA;

void inicializarLista(LISTA* l)
{
    l->nroElem = 0;
}

void exibirLista(LISTA* l)
{
    int i;
    printf("Lista: \" ");
    for (i=0; i < l->nroElem; i++)
        printf("%i ", l->A[i].chave);
    printf("\"\n");
}

bool inserirNovo(LISTA* l, REGISTRO reg)
{
    if (l->nroElem >= MAX)
        return false;
    l->A[l->nroElem] = l->A[0];
    l->A[0] = reg;
    l->nroElem++;
    return true;
}

int main()
{
    LISTA listaTesteExercicio;

    inicializarLista(&listaTesteExercicio);

    REGISTRO r1;
    r1.chave = 10;
    inserirNovo(&listaTesteExercicio, r1);
    exibirLista(&listaTesteExercicio);

    REGISTRO r2;
    r2.chave = 20;
    inserirNovo(&listaTesteExercicio, r2);
    exibirLista(&listaTesteExercicio);

    REGISTRO r3;
    r3.chave = 30;
    inserirNovo(&listaTesteExercicio, r3);
    exibirLista(&listaTesteExercicio);

    REGISTRO r4;
    r4.chave = 40;
    inserirNovo(&listaTesteExercicio, r4);
    exibirLista(&listaTesteExercicio);

    assert(listaTesteExercicio.A[0].chave == 40);
    assert(listaTesteExercicio.A[1].chave == 10);
    assert(listaTesteExercicio.A[2].chave == 20);
    assert(listaTesteExercicio.A[3].chave == 30);

    return 0;
}

