#include <stdio.h>
#include <assert.h>

#define ERRO -1
#define true 1
#define false 0
#define MAX 50

typedef int bool;
typedef int TIPOCHAVE;

typedef struct
{
    TIPOCHAVE chave;
} REGISTRO;

typedef struct
{
    REGISTRO A[MAX];
    int inicio;
    int nroElem;
} FILA;

void inicializarFila(FILA* f)
{
    f->inicio=0;
    f->nroElem=0;
}

void exibirFila(FILA* f)
{
    printf("Fila: \" ");
    int i = f->inicio;
    int temp;
    for (temp = 0; temp < f->nroElem; temp++)
    {
        printf("%i ", f->A[i].chave);
        i = (i + 1) % MAX;
    }
    printf("\"\n");
}

bool inserirElementoFila(FILA* f,REGISTRO reg)
{
    if (f->nroElem >= MAX)
        return false;
    f->A[(f->inicio + f->nroElem)%MAX] = reg;
    f->nroElem++;
    return true;
}

void exibirFilaFim(FILA* f)
{
    printf("Fila: \" ");
    int i = f->nroElem - 1;
    int temp;
    for (temp = f->nroElem; temp > 0; temp--)
    {
        printf("%i ", f->A[i].chave);
        i = (i - 1) % MAX;
    }
    printf("\"\n");
}

int main()
{
    REGISTRO reg0;  reg0.chave  =  0;
    REGISTRO reg10; reg10.chave = 10;
    REGISTRO reg20; reg20.chave = 20;
    REGISTRO reg30; reg30.chave = 30;

    FILA minhaFila;

    inicializarFila(&minhaFila);

    inserirElementoFila(&minhaFila, reg10);
    inserirElementoFila(&minhaFila, reg30);
    inserirElementoFila(&minhaFila, reg0);
    inserirElementoFila(&minhaFila, reg20);

    assert(minhaFila.A[0].chave == reg10.chave);
    assert(minhaFila.A[1].chave == reg30.chave);
    assert(minhaFila.A[2].chave == reg0.chave);
    assert(minhaFila.A[3].chave == reg20.chave);

    printf("Do inicio para o fim:\n");
    exibirFila(&minhaFila);
    printf("Do fim para o inicio:\n");
    exibirFilaFim(&minhaFila);

    return 0;
}
