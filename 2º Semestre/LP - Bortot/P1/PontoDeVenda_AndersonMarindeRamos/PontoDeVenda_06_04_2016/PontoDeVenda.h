// Declara��es do Programa Ponto de Venda - Prova P1 - ADS - Linguagem de Programa��o
#include <iostream>
#include <Windows.h>
using namespace std;
// Defini��es do programa
#define PAUSA								system("pause")
#define LIMPAR_TELA							system("cls")
#define	QTDE_PRODUTOS						600					// quantidade total de produtos
#define EXTENSAO_DESCRICAO					40					// qtde bytes da descri��o do produto
// Op��es do menu
#define CADASTRAR_PRODUTO					'C'
#define EXCLUIR_PRODUTO						'E'
#define MOSTRAR_PRODUTO						'M'
#define VENDER_PRODUTO						'V'
#define SAIR_DO_PROGRAMA					'S'
// struct do produto
typedef struct tagPRODUTO
{
	bool flgAtivo;											// true - indica produto cadastrado e ativo
	int nCodigoProduto;										// codigo 1, 2, 3, .......QTDE_PRODUTOS
	char cDescricao[EXTENSAO_DESCRICAO + 1];				// descri��o do produto
	double dPrecoUnitario;									// pre�o unit�rio do produto
} PRODUTO;
