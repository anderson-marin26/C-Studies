// Declarações do Programa Ponto de Venda - Prova P1 - ADS - Linguagem de Programação
#include <iostream>
#include <Windows.h>
using namespace std;
// Definições do programa
#define PAUSA								system("pause")
#define LIMPAR_TELA							system("cls")
#define	QTDE_PRODUTOS						600					// quantidade total de produtos
#define EXTENSAO_DESCRICAO					40					// qtde bytes da descrição do produto
// Opções do menu
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
	char cDescricao[EXTENSAO_DESCRICAO + 1];				// descrição do produto
	double dPrecoUnitario;									// preço unitário do produto
} PRODUTO;
