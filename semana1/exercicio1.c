#include <stdio.h>;
#include <assert.h>;

typedef struct
{
    int dia;
    int mes;
    int ano;
} DATA;

void atualizar(DATA* pontData, int dia, int mes, int ano)
{
	pontData->dia = dia;
	pontData->mes = mes;
	pontData->ano = ano;
}

int main()
{
    DATA meuAniversario;

    atualizar(&meuAniversario, 7, 9, 1981);

    printf("Nasci em %d/%d/%d.", meuAniversario.dia, meuAniversario.mes, meuAniversario.ano);
    scanf("");

    assert(meuAniversario.dia == 7);
    assert(meuAniversario.mes == 9);
    assert(meuAniversario.ano == 1981);

	return 0;
}
