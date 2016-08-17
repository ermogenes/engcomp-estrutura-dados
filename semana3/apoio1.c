#include <stdio.h>
#include <malloc.h>

#define true 1
#define false 0

#define INICIO 1
#define FIM 0

typedef int bool;
typedef int TIPOCHAVE;
typedef int POSICAO_ENTRADA;

typedef struct
{
    TIPOCHAVE chave;
    // outros campos...
} REGISTRO;

typedef struct
{
    POSICAO_ENTRADA posicaoEntrada;
    int valor;
} ITEM_DEQUE;

typedef struct auxElem
{
    REGISTRO reg;
    struct auxElem* ant;
    struct auxElem* prox;
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct
{
    PONT cabeca;
} DEQUE;

/* Inicialização do deque (o deque jah esta criado e eh apontado pelo endereco em d) */
void inicializarDeque(DEQUE* d)
{
    d->cabeca = (PONT) malloc(sizeof(ELEMENTO));
    d->cabeca->prox = d->cabeca;
    d->cabeca->ant = d->cabeca;
}

/* Exibição do DEQUE a partir do inicio1 */
void exibirDequeInicio(DEQUE* d)
{
    PONT end = d->cabeca->prox;
    printf("Deque partindo do início: \" ");
    while (end != d->cabeca)
    {
        printf("%i ", end->reg.chave);
        end = end->prox;
    }
    printf("\"\n");
}

/* Exibição do DEQUE a partir do inicio2 */
void exibirDequeFim(DEQUE* d)
{
    PONT end = d->cabeca->ant;
    printf("Deque partindo do fim: \" ");
    while (end != d->cabeca)
    {
        printf("%i ", end->reg.chave); // soh lembrando TIPOCHAVE = int
        end = end->ant;
    }
    printf("\"\n");
}

/* Retornar o tamanho do deque (numero de elementos) */
int tamanho(DEQUE* d)
{
    PONT end = d->cabeca->prox;
    int tam = 0;
    while (end != d->cabeca)
    {
        tam++;
        end = end->prox;
    }
    return tam;
}

int tamanho2(DEQUE* d)
{
    PONT end = d->cabeca->ant;
    int tam = 0;
    while (end != d->cabeca){
        tam++;
        end = end->ant;
    }
    return tam;
}

/* Retornar o tamanho em bytes da lista. Neste caso, isto depende do numero
de elementos que estao sendo usados.
int tamanhoEmBytes(DEQUE* d) {
return((tamanho(d))*sizeof(ELEMENTO))+sizeof(DEQUE); // sizeof(DEQUE) = 2*sizeof(PONT) pois a "DEQUE" eh composto por ponteiros
}
*/

/* Busca sequencial */
PONT buscaSeq(DEQUE* d, TIPOCHAVE ch)
{
    PONT pos = d->cabeca->prox;
    d->cabeca->reg.chave = ch;
    while (pos->reg.chave != ch)
        pos = pos->prox;
    if (pos != d->cabeca)
        return pos;
    return NULL;
}

/* Exclusão do primeiro elemento, entrada 1 do deque
e colocar o valor da chave do elemento memoria apontada por ch*/
bool excluirElemDequeInicio(DEQUE* d, REGISTRO* reg)
{
    if (d->cabeca->prox == d->cabeca)
        return false;  // deque vazio
    PONT apagar = d->cabeca->prox;
    *reg = apagar->reg;
    d->cabeca->prox = apagar->prox;
    apagar->prox->ant = d->cabeca;
    free(apagar);
    return true;
}

/* Exclusão do primeiro elemento, entrada 2 do deque
e colocar o valor da chave do elemento memoria apontada por ch*/
bool excluirElemDequeFim(DEQUE* d, REGISTRO* reg)
{
    if (d->cabeca->ant == NULL) return false;  // deque vazio
    PONT apagar = d->cabeca->ant;
    *reg = apagar->reg;
    d->cabeca->ant = apagar->ant;
    apagar->ant->prox = d->cabeca;
    free(apagar);
    return true;
}

/* Destruição do deque libera a memoria de todos os elementos do deque*/
void reinicializarDeque(DEQUE* d) {
    PONT end = d->cabeca->prox;
    while (end != d->cabeca)
    {
        PONT apagar = end;
        end = end->prox;
        free(apagar);
    }
    d->cabeca->prox = d->cabeca;
    d->cabeca->ant = d->cabeca;
}

/* Inserção no deque, entrada 1 */
bool inserirDequeInicio(DEQUE* d,REGISTRO reg)
{
    PONT i = (PONT) malloc(sizeof(ELEMENTO));
    i->reg = reg;
    i->ant = d->cabeca;
    i->prox = d->cabeca->prox;
    d->cabeca->prox = i;
    i->prox->ant = i;
    return true;
}

/* Inserção no deque, entrada 2 */
bool inserirDequeFim(DEQUE* d,REGISTRO reg)
{
    PONT i = (PONT) malloc(sizeof(ELEMENTO));
    i->reg = reg;
    i->prox = d->cabeca;
    i->ant = d->cabeca->ant;
    d->cabeca->ant = i;
    i->ant->prox = i;
    return true;
}

/* retornarPrimeiro1 - retorna o endereco do primeiro elemento do deque 1 */
PONT retornarPrimeiro1(DEQUE* d, TIPOCHAVE* ch)
{
    if (d->cabeca->prox != d->cabeca)
        *ch = d->cabeca->prox->reg.chave;
    return d->cabeca->prox;
}

/* retornarPrimeiro2 - retorna o endereco do primeiro elemento do deque 2*/
PONT retornarPrimeiro2(DEQUE* d, TIPOCHAVE* ch)
{
    if (d->cabeca->ant != d->cabeca)
        *ch = d->cabeca->ant->reg.chave;
    return d->cabeca->ant;
}

/*
void exibirDequeInicio(DEQUE* d)
{
    PONT end = d->cabeca->prox;
    printf("Deque partindo do inicio: \" ");
    while(end != d->cabeca)
    {
        printf("%i ", end->reg.chave);
        end = end->prox;
    }
    printf("\"\n");
}
*/

int main()
{
    DEQUE meuDeque;

    ITEM_DEQUE elementosASeremInseridos[] = {
        { INICIO, 1 },
        { FIM,    2 },
        { INICIO, 3 },
        { FIM,    4 },
        { INICIO, 5 },
        { FIM,    6 },
        { INICIO, 7 },
        { FIM,    8 },
        { INICIO, 9 },
        { FIM,   10 },
    };

    inicializarDeque(&meuDeque);

    int i;
    REGISTRO regAtual;
    for(i = 0; i < 10; i++)
    {
        regAtual.chave = elementosASeremInseridos[i].valor;
        if (elementosASeremInseridos[i].posicaoEntrada == INICIO)
            inserirDequeInicio(&meuDeque, regAtual);
        else if (elementosASeremInseridos[i].posicaoEntrada == FIM)
            inserirDequeFim(&meuDeque, regAtual);
        else
            return -1; // Erro: Posicao invalida

        printf("Valor inserido: %d\n", regAtual.chave);
        exibirDequeInicio(&meuDeque);
    }

    printf("\nResultado final:\n");
    exibirDequeInicio(&meuDeque);
}
