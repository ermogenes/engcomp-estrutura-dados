#include <stdio.h>
#include <assert.h>

#define MAX 50
#define true 1
#define false 0

typedef int bool;

typedef int TIPOCHAVE;

typedef struct {
    TIPOCHAVE chave;
} REGISTRO;

typedef struct {
    int topo;
    REGISTRO A[MAX+1];
} PILHA;

void inicializarPilha(PILHA* p){
    p->topo = -1;
}

void exibirPilha(PILHA* p){
    printf("Pilha: \" ");
    int i;
    for (i=p->topo;i>=0;i--){
        printf("%i ", p->A[i].chave);
    }
    printf("\"\n");
}

bool inserirElementoPilha(PILHA* p, REGISTRO reg){
    if (p->topo+1>= MAX)
        return false;
    p->topo = p->topo+1;
    p->A[p->topo] = reg;
return true;
}

int buscarElementoPilhaSentinela(PILHA* p, TIPOCHAVE ch)
{
    int i = 0;
    p->A[p->topo+1].chave = ch;
    while(p->A[i].chave != ch)
        i++;
    if (i == p->topo+1)
        return -1;
    else
        return i;
}

int main()
{
    PILHA pilhaTesteExercicio;

    inicializarPilha(&pilhaTesteExercicio);

    REGISTRO r1;
    r1.chave = 10;
    inserirElementoPilha(&pilhaTesteExercicio, r1);
    exibirPilha(&pilhaTesteExercicio);

    REGISTRO r2;
    r2.chave = 20;
    inserirElementoPilha(&pilhaTesteExercicio, r2);
    exibirPilha(&pilhaTesteExercicio);

    REGISTRO r3;
    r3.chave = 30;
    inserirElementoPilha(&pilhaTesteExercicio, r3);
    exibirPilha(&pilhaTesteExercicio);

    REGISTRO r4;
    r4.chave = 40;
    inserirElementoPilha(&pilhaTesteExercicio, r4);
    exibirPilha(&pilhaTesteExercicio);

    assert(pilhaTesteExercicio.A[0].chave == 10);
    assert(pilhaTesteExercicio.A[1].chave == 20);
    assert(pilhaTesteExercicio.A[2].chave == 30);
    assert(pilhaTesteExercicio.A[3].chave == 40);

    int itensABuscar[] = {5, 10, 15, 20, 30, 40, 50};

    printf("\nTestes de busca:\n");
    int i;
    for (i = 0; i < 7; i++)
        printf("Posicao do valor %d: %d\n", itensABuscar[i], buscarElementoPilhaSentinela(&pilhaTesteExercicio, itensABuscar[i]));

    assert(pilhaTesteExercicio.A[0].chave == 10);
    assert(pilhaTesteExercicio.A[1].chave == 20);
    assert(pilhaTesteExercicio.A[2].chave == 30);
    assert(pilhaTesteExercicio.A[3].chave == 40);

    assert(buscarElementoPilhaSentinela(&pilhaTesteExercicio, 5) == -1);
    assert(buscarElementoPilhaSentinela(&pilhaTesteExercicio, 10) == 0);
    assert(buscarElementoPilhaSentinela(&pilhaTesteExercicio, 30) == 2);
    assert(buscarElementoPilhaSentinela(&pilhaTesteExercicio, 50) == -1);

    return 0;
}
