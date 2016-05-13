// declarações do programa Raul Gil

#include "iostream"
#include "windows.h"
using namespace std;

//defines do programa

#define PAUSA						system("pause")
#define LIMPAR_TELA					system("cls")
#define ACENTUACAO_BRASILEIRA		setlocale(LC_ALL, "portuguese_brazil")
#define SAIR_DO_PROGRAMA			system("exit")

//limitações do programa
#define QTDE_MINIMA_CALOUROS		1
#define QTDE_MAXIMA_CALOUROS		30
#define NOTA_MINIMA					0
#define NOTA_MAXIMA					10
#define EXTENSAO_NOME				30
#define MASCULINO					'M'
#define FEMININO					'F'

//Prototipos

void ListarCalouros(char vetNomes[][EXTENSAO_NOME], char vetSexo[], int vetNotas[], int nQtdeCalouros);

void BubbleSortAlfabetico(char vetNomes[][EXTENSAO_NOME], char vetSexo[], int vetNota[], int nQtdeCalouros);

// Struct
typedef struct tagCALOURO {
	int nNota[QTDE_MAXIMA_CALOUROS];
	char cSexo[QTDE_MAXIMA_CALOUROS],
		cNome[QTDE_MAXIMA_CALOUROS][EXTENSAO_NOME + 1];
}CALOURO;