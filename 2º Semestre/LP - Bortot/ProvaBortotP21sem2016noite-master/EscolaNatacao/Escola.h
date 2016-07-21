// Declara��es do programa Escola de Nata��o
#include <iostream>
#include <windows.h>
using namespace std;
// Defini��es
#define PAUSA				system("pause")
#define LIMPAR_TELA			system("cls")
// Delimita��o do programa
#define QTDE_PERIODOS		3			// quantidade de per�odos (1 - manh�, 2 - tarde e 3 - noite)
#define QTDE_MINIMA_RAIAS_PISCINA	5	// quantidade minima de raias da piscina
#define QTDE_MAXIMA_RAIAS_PISCINA	15	// quantidade m�xima de raias da piscina
#define PERIODO_MANHA		1			// per�odo da manh�
#define PERIODO_TARDE		2			// per�odo da tarde
#define PERIODO_NOITE		3			// per�odo da noite
// op��es do menu
#define MATRICULAR_ALUNO		'M'			
#define CANCELAR_MATRICULA		'C'
#define EXIBIR_DADOS_ALUNO		'E'
#define LISTAR_PERIODO			'P'
#define SAIR_DO_PROGRAMA		'S'
// valores e descontos de mensalidade
#define VALOR_MENSALIDADE			137.50	// valor da mensalidade do primeiro da fam�lia
#define VALOR_DESCONTO_POR_PARENTE	10		// porcentagem de desconto para cada parente com o mesmo sobrenome
#define EXTENSAO_NOME			20			
#define EXTENSAO_SOBRENOME		20
// caminho dos arquivos do programa
#define CAMINHO_QUANTIDADE		"..\\QtdeRaias.arq"
#define CAMINHO_RAIA			"..\\Raia.arq"
//estados das raias
#define OCUPADA					true
#define LIVRE					false

// struct para quantidade de raias da piscina
typedef struct tagQTDE_RAIAS
{
	int nQtdeRaias;							// quantidade de raias da piscina
} QTDE_RAIAS;

// struct para cada aluno da escola
typedef struct tagRAIA
{
	int	nPeriodo,							// per�odos da escola (1, 2 e 3 - manh� tarde e noite
		nRaia;								// raia de 1, 2, 3, .......quantidade de raias da piscina
	bool flgRaiaOcupada;					// true indica que raia ocupada e false raia livre
	char cNome[EXTENSAO_NOME + 1],			// nome do aluno
		cSobreNome[EXTENSAO_SOBRENOME + 1];	// sobrenome do aluno (para dar desconto de fam�lia)
	double dVlrMensalidade;					// valor da mensalidade
} RAIA;										// struct de cada raia da piscina nos tr�s per�odos

// prot�tipos das fun��es
bool PedirPeriodoRaia(int *ptrPeriodo, int *ptrRaia, 
					  int nQtdePeriodos, int nQtRaiasPiscina, char *ptrAcao);
int BuscarRaiaLivreNoPeriodo(int nPeriodo, int nQtRaiasPiscina, RAIA *ptrStRaia, FILE **fdRaia);
int PedirPeriodo(int nQtdePeriodos, char *ptrAcao);
int VerificaParentes(char *ptrSobrenome, FILE **fdRaia);
bool GravaPosicional(int nPosicional, RAIA *ptrStRaia, FILE **fdRaia);
bool LerPosicional(int nPosicional, RAIA *ptrStRaia, FILE **fdRaia);
