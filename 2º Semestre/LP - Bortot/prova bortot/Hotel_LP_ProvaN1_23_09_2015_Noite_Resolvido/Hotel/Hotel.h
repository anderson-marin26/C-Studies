// Hotel.h - Defini��es do programa de Hotel para prova
#include <iostream>
#include <windows.h>
using namespace std;
#define PAUSA							system("pause")
#define LIMPAR_TELA						system("cls")
#define EXTEN_NOME						30			// extens�o do nome do h�spede
// op��es do menu
#define FAZER_CHECK_IN					'I'			// fazer o check-in do h�spede
#define FAZER_CHECK_OUT					'O'			// fazer o check-out do h�spede
#define LISTAR_UM_QUARTO				'L'			// listar os dados de um dado quarto
#define LANCAR_SERVICO					'S'			// lan�ar um servi�o no quarto
#define LANCAR_DIARIA					'D'			// lan�ar di�rias nos quartos que est�o ocupados
#define SAIR_DO_PROGRAMA				'X'			// sair do programa		

// Valores das di�rias para cada quarto de acordo com o andar em que est�
#define DIARIA_QUARTO_SIMPLES			88.00		// Di�ria do quarto simples
#define DIARIA_QUARTO_MEDIO				120.00		// Di�ria do quarto do tipo m�dio
#define DIARIA_QUARTO_SUPER				400.00		// Di�ria do quarto do tipo super
#define DIARIA_QUARTO_SUITE				990.00		// Di�ria do quarto do tipo suite
// Observa��es:
// 1 - Os quartos dos andares 1� ao 2� - s�o quartos do tipo simples
// 2 - Os quartos dos andares 3� ao 4� - s�o quartos do tipo m�dio
// 3 - Os quartos dos andares 5� ao 8� - s�o quartos do tipo super
// 4 - Os quartos dos andares 9� e acima - s�o quartos do tipo suite

// Limita��es do programa
#define QUANTIDADE_MAXIMA_ANDARES		30			// quantidade m�xima de andares do hotel
#define QUANTIDADE_MAXIMA_QUARTOS		25			// quantidade m�xima de quartos por andar
#define QTDE_MINIMA_ANDARES				10			// quantidade m�nima de andares
#define QTDE_MINIMA_QUARTOS_ANDAR		10			// quantidade m�nima de quartos por andar

// defini��es de tipos de servi�os
#define DIARIA							1			// transa��o de di�ria
#define RESTAURANTE						2			// transa��o de restaurante
#define BAR								3			// transa��o de bar
#define PISCINA							4			// transa��o de bar da piscina
#define BOATE							5			// transa��o de bar da boate
// prot�tipos das fun��es
bool	PedirAndarQuarto(int *ptrAndar, int *ptrQuarto, int nQtAndares, int nQtQuartos, char *ptrTransacao);
int CalcularIndice(int nAndar, int nQuarto, int nQtQuartoPorAndar);
