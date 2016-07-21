// Hotel.h - Defini��es do programa de Hotel para prova
#include <iostream>
#include <windows.h>
// defines comuns
#define PAUSA							system("pause")
#define LIMPAR_TELA						system("cls")
// op��es do menu
#define FAZER_CHECK_IN					'I'			// fazer o check-in do h�spede
#define FAZER_CHECK_OUT					'O'			// fazer o check-out do h�spede
#define LISTAR_UM_QUARTO				'L'			// listar os dados de um dado quarto
#define LANCAR_SERVICO					'S'			// lan�ar um servi�o no quarto
#define LANCAR_DIARIA					'D'			// lan�ar di�rias nos quartos que est�o ocupados
#define SAIR_DO_PROGRAMA				'X'			// sair do programa	
// caminhos dos arquivos
#define CAMINHO_QUARTOS					"..\\Quartos.dat"
#define CAMINHO_QUANTIDADES				"..\\Quantidades.dat"

// Tabela de valores das di�rias
#define VALOR_DIARIA_SIMPLES			110.00		// valor da di�ria dos quartos do andar 1 at� o 3
#define VALOR_DIARIA_REGULAR			150.00		// di�ria dos quartos do andar 4 at� o 7
#define VALOR_DIARIA_LUXO				230.00		// di�ria dos quartos do andar 8 at� o 10
#define VALOR_DIARIA_SUITE				380.00		// di�ria dos quartos do andar 11 para cima.

// Limita��es do programa
#define QUANTIDADE_MAXIMA_ANDARES		30			// quantidade m�xima de andares
#define QUANTIDADE_MINIMA_ANDARES		15			// quantidade m�nima de andares
#define QUANTIDADE_MAXIMA_QUARTOS		20			// quantidade m�xima de quartos por andar
#define QUANTIDADE_MINIMA_QUARTOS		10			// quantidade m�nima de quartos por andar

// defini��es de tipos de servi�os
#define RESTAURANTE						1			// transa��o de restaurante
#define BAR								2			// transa��o de bar
#define PISCINA							3			// transa��o de bar da piscina
#define BOATE							4			// transa��o de bar da boate
#define FRIGO_BAR						5			// despesa de bebidas do frigo-bar

//define de estados
#define OCUPADO							true
#define LIVRE							false

// layout da struct de cada quarto do hotel
typedef struct tagQUARTO							// struct de cada quarto
{
	bool flgLivreOuOcupado;							// true - indica que o quarto est� ocupado
	int	nAndar,										// n�mero do andar
		nQuarto;									// n�mero do quarto dentro do andar
	char	cNomeHospede[41];						// nome do h�spede
	double	dValorTotalDespesas,					// valor total das despesas do quarto
		dValorTotalDiarias,							// valor total das di�rias do quarto
		dValorTotalServicos,						// valor total dos servi�os
		dValorDiaria;								// valor da di�ria do quarto
} QUARTO;

// layout da struct para conter as quantidades
//		configuradas para este hotel
typedef struct tagQUANTIDADES
{
	int nQtdeAndares,								// quantidade de andares
		nQtdeQuartos;								// quantidade de quartos por andar
} QUANTIDADES;

// Prot�tipos das fun��es
int		PedirAndar(int nQtAndares, char *ptrTransacao);
int		PedirQuarto(int nQtQuartos, char *ptrTransacao);
bool	LerQuarto(int nAndar, int nQuarto, int nQtQuartoPorAndar, FILE *fdQuarto, QUARTO *ptrStQuarto);
bool	GravarQuarto(int nAndar, int nQuarto, int nQtQuartoPorAndar, FILE *fdQuarto, QUARTO *ptrStQuarto);
double PedirValorServi�o();
