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
} REGISTRO;

typedef struct aux
{
    REGISTRO reg;
    struct aux* prox;
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct
{
    PONT topo;
} PILHA;

void inicializarPilha(PILHA* p)
{
    p->topo = NULL;
}

void exibirPilha(PILHA* p)
{
    PONT end = p->topo;
    printf("Pilha: \" ");
    while (end != NULL)
    {
        printf("%i ", end->reg.chave);
        end = end->prox;
    }
    printf("\"\n");
}

bool inserirElemPilha(PILHA* p, REGISTRO reg)
{
    PONT novo = (PONT) malloc(sizeof(ELEMENTO));
    novo->reg = reg;
    novo->prox = p->topo;
    p->topo = novo;
    return true;
}

PONT buscarElementoPilha(PILHA* p, TIPOCHAVE ch)
{
    PONT resultado = NULL;
    PONT posicaoAtual = p->topo;
    while(posicaoAtual != NULL)
    {
        if (posicaoAtual->reg.chave == ch)
            resultado = posicaoAtual;
        posicaoAtual = posicaoAtual->prox;
    }
    return resultado;
}

int main()
{
    REGISTRO reg0;  reg0.chave  =  0;
    REGISTRO reg10; reg10.chave = 10;
    REGISTRO reg15; reg15.chave = 15;
    REGISTRO reg20; reg20.chave = 20;
    REGISTRO reg30; reg30.chave = 30;
    REGISTRO reg35; reg35.chave = 35;

    PILHA minhaPilha;

    inicializarPilha(&minhaPilha);

    exibirPilha(&minhaPilha);

    PONT elemento10listaVazia = buscarElementoPilha(&minhaPilha, reg10.chave);

    assert(elemento10listaVazia == NULL);

    printf("Valor %d nao encontrado.\n", reg10.chave);

    inserirElemPilha(&minhaPilha, reg10);
    inserirElemPilha(&minhaPilha, reg20);
    inserirElemPilha(&minhaPilha, reg30);

    exibirPilha(&minhaPilha);

    PONT elemento0listaPreenchida  = buscarElementoPilha(&minhaPilha, reg0.chave);
    PONT elemento10listaPreenchida = buscarElementoPilha(&minhaPilha, reg10.chave);
    PONT elemento15listaPreenchida = buscarElementoPilha(&minhaPilha, reg15.chave);
    PONT elemento30listaPreenchida = buscarElementoPilha(&minhaPilha, reg30.chave);
    PONT elemento35listaPreenchida = buscarElementoPilha(&minhaPilha, reg35.chave);

    if(elemento0listaPreenchida == NULL)
        printf("Valor %d nao encontrado.\n", reg0.chave);
    if(elemento10listaPreenchida->reg.chave == reg10.chave)
        printf("Valor %d encontrado.\n", reg10.chave);
    if(elemento15listaPreenchida == NULL)
        printf("Valor %d nao encontrado.\n", reg15.chave);
    if(elemento30listaPreenchida->reg.chave == reg30.chave)
        printf("Valor %d encontrado.\n", reg30.chave);
    if(elemento35listaPreenchida == NULL)
        printf("Valor %d nao encontrado.\n", reg35.chave);

    assert(elemento0listaPreenchida == NULL);
    assert(elemento10listaPreenchida->reg.chave == reg10.chave);
    assert(elemento15listaPreenchida == NULL);
    assert(elemento30listaPreenchida->reg.chave == reg30.chave);
    assert(elemento35listaPreenchida == NULL);

    return 0;
}
