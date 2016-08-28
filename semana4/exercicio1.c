#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#define FALSE 0
#define TRUE 1

#define VALOR_ESPARSO 0.0

#define RESULTADO_OK 0
#define RESULTADO_OVERFLOW 1

typedef int bool;
typedef int CodigoResultadoBusca;

typedef struct
{
    CodigoResultadoBusca codigoResultado;
    float valor;
} ResultadoBusca;

typedef struct tempNo
{
    int linha;
    int coluna;
    float valor;
    struct tempNo* prox;
} NO;

typedef NO* PONT;

typedef struct
{
    PONT cabeca;
} MATRIZ;


PONT criarNo(int lin, int col, float valor)
{
    PONT no = (PONT) malloc(sizeof(NO));
    no->linha = lin;
    no->coluna = col;
    no->valor = valor;
    return no;
}

PONT criarNoFinal(int lin, int col, float valor)
{
    PONT no = (PONT) malloc(sizeof(NO));
    no->linha = lin;
    no->coluna = col;
    no->valor = valor;
    no->prox = NULL;
    return no;
}

PONT criarNoFolha(int lin, int col, float valor, PONT pai)
{
    PONT no = criarNoFinal(lin, col, valor);
    pai->prox = no;
    return no;
}

PONT criarNoGalho(int lin, int col, float valor, PONT pai, PONT filho)
{
    PONT no = criarNo(lin, col, valor);
    no->prox = filho;
    pai->prox = no;
    return no;
}

void inicializarMatriz(MATRIZ* m, int lin, int col)
{
    PONT no = criarNo(lin, col, VALOR_ESPARSO);
    no->prox = NULL;
    m->cabeca = no;
}

void excluiElemento(PONT elemento, PONT pai)
{
    pai->prox = elemento->prox;
    free(elemento);
}

bool atribuiElemento(MATRIZ* m, int lin, int col, float valor)
{
    bool obteveSucesso = TRUE;

    if (lin<1 || col<1 || lin>m->cabeca->linha || col>m->cabeca->coluna)
    {
        // Fora dos limites
        obteveSucesso = FALSE;
    }
    else
    {
        // Dentro dos limites da matriz

        PONT elementoAnterior = m->cabeca;
        PONT elementoAtual = m->cabeca->prox;

        if (elementoAtual == NULL) // Matriz vazia
        {
            if (valor != VALOR_ESPARSO)
                criarNoFolha(lin, col, valor, m->cabeca);
        }
        else // Matriz possui elementos
        {
            bool executado = FALSE;

            // Itera elementos da matriz
            while(!executado && elementoAtual != NULL)
            {
                executado = TRUE;

                if(elementoAtual->linha == lin && elementoAtual->coluna == col) // Posição exata
                {
                    if (valor != VALOR_ESPARSO)
                        elementoAtual->valor = valor; // Altera valor atual
                    else
                        excluiElemento(elementoAtual, elementoAnterior); // Exclui elemento atual
                }
                else // Nao esta na posicao exata
                {
                    if(elementoAtual->linha > lin
                            || (elementoAtual->linha == lin) && (elementoAtual->coluna > col))
                        // Passou da posicao onde deveria inserir
                    {
                        if (elementoAtual->prox == NULL) // Ja esta no final, insere no fim
                        {
                            if (valor != VALOR_ESPARSO)
                                criarNoFolha(lin, col, valor, elementoAtual);
                        }
                        else // Nao esta no final, deve inserir no meio
                        {
                            if (valor != VALOR_ESPARSO)
                                criarNoGalho(lin, col, valor, elementoAnterior, elementoAtual);
                        }
                    }
                    else // Ainda nao chegou na posicao desejada
                    {
                        if (elementoAtual->prox == NULL) // Nao ha mais elementos
                        {
                            // Insere no fim
                            if (valor != VALOR_ESPARSO)
                                criarNoFolha(lin, col, valor, elementoAtual);
                        }
                        else
                        {
                            // Busca o proximo elemento e mantem o loop
                            elementoAnterior = elementoAtual;
                            elementoAtual = elementoAtual->prox;
                            executado = FALSE;
                        }
                    }
                }
            }
        }
    }
    return obteveSucesso;
}

ResultadoBusca leValorElemento(MATRIZ* m, int lin, int col)
{
    ResultadoBusca r;
    r.valor = VALOR_ESPARSO;

    if (lin > m->cabeca->linha || col > m->cabeca->coluna || lin <= 0 || col <= 0)
        r.codigoResultado = RESULTADO_OVERFLOW;
    else
    {
        r.codigoResultado = RESULTADO_OK;

        PONT elementoAtual;
        elementoAtual = m->cabeca->prox;

        bool encontrado = FALSE;

        while (!encontrado && elementoAtual != NULL)
        {
            if (elementoAtual->linha == lin && elementoAtual->coluna == col)
            {
                r.valor = elementoAtual->valor;
                encontrado = TRUE;
            }
            else
            {
                if (elementoAtual->linha >= lin && elementoAtual->coluna >= col)
                    encontrado = TRUE; // possui valor padrao
                else
                    elementoAtual = elementoAtual->prox;
            }
        }
    }
    return r;
}

int tamanho(MATRIZ* m)
{
    int numElementos = 0;
    PONT elementoAtual;
    elementoAtual = m->cabeca->prox;
    while (elementoAtual != NULL)
    {
        numElementos++;
        elementoAtual = elementoAtual->prox;
    }
    return numElementos;
}

void exibeMatrizEsparsaPorPosicao(MATRIZ* m)
{
    int l, c;
    for(l = 1; l <= m->cabeca->linha; l++)
    {
        printf("\n");
        for(c = 1; c <= m->cabeca->coluna; c++)
        {
            ResultadoBusca r = leValorElemento(m, l, c);
            if (r.codigoResultado == RESULTADO_OK)
                printf("\t %0.2f", r.valor);
            else
                printf("\t ERRO");
        }
    }
    printf("\nElementos armazenados: %d", tamanho(m));
    printf("\n\n");
}

void testaAtribuicaoElemento(MATRIZ* m, int lin, int col, float valor, bool deveFuncionar, CodigoResultadoBusca deveEncontrar, int tamanhoDepois)
{
    printf("Atribuindo valor %0.2f em [%d][%d]...", valor, lin, col);
    assert(atribuiElemento(m, lin, col, valor) == deveFuncionar);
    ResultadoBusca r = leValorElemento(m, lin, col);
    assert(r.codigoResultado == deveEncontrar);
    assert(tamanho(m) == tamanhoDepois);
    exibeMatrizEsparsaPorPosicao(m);
}

int main()
{
    MATRIZ minhaMatriz;

    printf("Inicializando matriz esparsa 5x3 vazia... ");
    inicializarMatriz(&minhaMatriz, 5, 3);
    assert(minhaMatriz.cabeca->linha == 5);
    assert(minhaMatriz.cabeca->coluna == 3);
    assert(minhaMatriz.cabeca->prox == NULL);
    assert(tamanho(&minhaMatriz) == 0);
    exibeMatrizEsparsaPorPosicao(&minhaMatriz);

    ResultadoBusca r;

    // Insercoes simples, no inicio, no meio e no final
    testaAtribuicaoElemento(&minhaMatriz, 3, 2, 1, TRUE, RESULTADO_OK, 1);
    testaAtribuicaoElemento(&minhaMatriz, 4, 3, 2, TRUE, RESULTADO_OK, 2);
    testaAtribuicaoElemento(&minhaMatriz, 5, 2, 3, TRUE, RESULTADO_OK, 3);
    testaAtribuicaoElemento(&minhaMatriz, 1, 1, 4, TRUE, RESULTADO_OK, 4);
    testaAtribuicaoElemento(&minhaMatriz, 1, 3, 5, TRUE, RESULTADO_OK, 5);
    testaAtribuicaoElemento(&minhaMatriz, 2, 2, 6, TRUE, RESULTADO_OK, 6);

    // Alteracoes de valor
    testaAtribuicaoElemento(&minhaMatriz, 5, 2, 7, TRUE, RESULTADO_OK, 6);
    testaAtribuicaoElemento(&minhaMatriz, 1, 1, 8, TRUE, RESULTADO_OK, 6);

    // Fora da matriz
    testaAtribuicaoElemento(&minhaMatriz, 0, 0, 1, FALSE, RESULTADO_OVERFLOW, 6);
    testaAtribuicaoElemento(&minhaMatriz, 1, 4, 1, FALSE, RESULTADO_OVERFLOW, 6);
    testaAtribuicaoElemento(&minhaMatriz, 6, 1, 1, FALSE, RESULTADO_OVERFLOW, 6);
    testaAtribuicaoElemento(&minhaMatriz, 6, 4, 1, FALSE, RESULTADO_OVERFLOW, 6);

    // Apaga itens com valor esparso
    testaAtribuicaoElemento(&minhaMatriz, 3, 2, 0, TRUE, RESULTADO_OK, 5);
    testaAtribuicaoElemento(&minhaMatriz, 1, 1, 0, TRUE, RESULTADO_OK, 4);

    // Itens com valor esparso, já eram esparsos
    testaAtribuicaoElemento(&minhaMatriz, 1, 1, 0, TRUE, RESULTADO_OK, 4);
    testaAtribuicaoElemento(&minhaMatriz, 4, 1, 0, TRUE, RESULTADO_OK, 4);
    testaAtribuicaoElemento(&minhaMatriz, 5, 3, 0, TRUE, RESULTADO_OK, 4);

}
