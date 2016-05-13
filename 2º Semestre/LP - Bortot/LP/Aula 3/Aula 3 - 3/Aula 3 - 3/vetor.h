// declarações do programa de ensaio de vetores

#include "iostream"
#include "windows.h"
using namespace std;

//defines do programa

#define PAUSA						system("pause")
#define LIMPAR_TELA					system("cls")
#define QTDE_INTEIRAS				1000
#define QTDA_POR_LINHA				9			//quantidade da listagem por linha

//prototipos das funcoes
void BubbleSort(int vetInt[], int nQtde, bool flgOrdem);
