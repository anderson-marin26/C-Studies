// Declarações  do programa Raul Gil do dynamic memory allocation (malloc)
#include <iostream>
#include <Windows.h>
using namespace std;
// Definições do programa
#define PAUSA								system("pause")
#define LIMPAR_TELA							system("cls")
#define QTDE_MINIMA							4
#define QTDE_MAXIMA							40

//struct do calouro
typedef struct tagCALOURO {
	int nNota;
	char cNome[31];
}CALOURO;