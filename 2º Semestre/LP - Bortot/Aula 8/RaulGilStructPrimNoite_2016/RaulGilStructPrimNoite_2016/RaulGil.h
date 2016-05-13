#pragma once

//Declarações do programa raul Gil com struct e menu
#include <iostream>
#include <Windows.h>
using namespace std;

//definicoes
#define PAUSA							system("PAUSE")
#define LIMPAR_TELA						system("cls")
#define QTDE_MINIMA_CALOUROS			4
#define QTDE_MAXIMA_CALOUROS			30
#define MASCULINO						'M'
#define FEMININO						'F'
#define NOTA_MINIMA						0
#define NOTA_MAXIMA						10
#define EXTENSAO_NOME					30

//definicoes do menu
#define INCLUIR_CALOURO					'I'
#define EXIBIR_VENCEDOR					'V'
#define LISTAR_CALOUROS					'L'
#define SAIR_DO_PROGRAMA				'S'

//struct do calouro
typedef struct tagCALOURO {
	int nNota;							//nota do calouro
	char cSexo,							//sexo do calouro
		cNome[EXTENSAO_NOME + 1];		//nome do calouro
}CALOURO;								//struct do calouro

//Prototipos
int InserirCalouro(CALOURO *ptrStCalouro, CALOURO *ptrVetCalouros, int *ptrProx, int *ptrTrono, int *ptrVenc);
void ExibeVencedor(CALOURO *ptrVetCalouros, int *ptrVencedor);
void ListarCalouros(CALOURO *ptrvetCalouros, int *ptrProximo, SYSTEMTIME *ptrTime);