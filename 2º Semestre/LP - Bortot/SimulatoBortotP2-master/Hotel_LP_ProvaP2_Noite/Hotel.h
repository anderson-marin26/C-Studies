// Hotel.h - Definições do programa de Hotel para prova
#include <iostream>
#include <windows.h>
// defines comuns
#define PAUSA							system("pause")
#define LIMPAR_TELA						system("cls")
// opções do menu
#define FAZER_CHECK_IN					'I'			// fazer o check-in do hóspede
#define FAZER_CHECK_OUT					'O'			// fazer o check-out do hóspede
#define LISTAR_UM_QUARTO				'L'			// listar os dados de um dado quarto
#define LANCAR_SERVICO					'S'			// lançar um serviço no quarto
#define LANCAR_DIARIA					'D'			// lançar diárias nos quartos que estão ocupados
#define SAIR_DO_PROGRAMA				'X'			// sair do programa	
// caminhos dos arquivos
#define CAMINHO_QUARTOS					"..\\Quartos.dat"
#define CAMINHO_QUANTIDADES				"..\\Quantidades.dat"

// Tabela de valores das diárias
#define VALOR_DIARIA_SIMPLES			110.00		// valor da diária dos quartos do andar 1 até o 3
#define VALOR_DIARIA_REGULAR			150.00		// diária dos quartos do andar 4 até o 7
#define VALOR_DIARIA_LUXO				230.00		// diária dos quartos do andar 8 até o 10
#define VALOR_DIARIA_SUITE				380.00		// diária dos quartos do andar 11 para cima.

// Limitações do programa
#define QUANTIDADE_MAXIMA_ANDARES		30			// quantidade máxima de andares
#define QUANTIDADE_MINIMA_ANDARES		15			// quantidade mínima de andares
#define QUANTIDADE_MAXIMA_QUARTOS		20			// quantidade máxima de quartos por andar
#define QUANTIDADE_MINIMA_QUARTOS		10			// quantidade mínima de quartos por andar

// definições de tipos de serviços
#define RESTAURANTE						1			// transação de restaurante
#define BAR								2			// transação de bar
#define PISCINA							3			// transação de bar da piscina
#define BOATE							4			// transação de bar da boate
#define FRIGO_BAR						5			// despesa de bebidas do frigo-bar

//define de estados
#define OCUPADO							true
#define LIVRE							false

// layout da struct de cada quarto do hotel
typedef struct tagQUARTO							// struct de cada quarto
{
	bool flgLivreOuOcupado;							// true - indica que o quarto está ocupado
	int	nAndar,										// número do andar
		nQuarto;									// número do quarto dentro do andar
	char	cNomeHospede[41];						// nome do hóspede
	double	dValorTotalDespesas,					// valor total das despesas do quarto
		dValorTotalDiarias,							// valor total das diárias do quarto
		dValorTotalServicos,						// valor total dos serviços
		dValorDiaria;								// valor da diária do quarto
} QUARTO;

// layout da struct para conter as quantidades
//		configuradas para este hotel
typedef struct tagQUANTIDADES
{
	int nQtdeAndares,								// quantidade de andares
		nQtdeQuartos;								// quantidade de quartos por andar
} QUANTIDADES;

// Protótipos das funções
int		PedirAndar(int nQtAndares, char *ptrTransacao);
int		PedirQuarto(int nQtQuartos, char *ptrTransacao);
bool	LerQuarto(int nAndar, int nQuarto, int nQtQuartoPorAndar, FILE *fdQuarto, QUARTO *ptrStQuarto);
bool	GravarQuarto(int nAndar, int nQuarto, int nQtQuartoPorAndar, FILE *fdQuarto, QUARTO *ptrStQuarto);
double PedirValorServiço();
