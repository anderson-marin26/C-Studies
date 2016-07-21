// Declarações do Programa Ponto de Venda - Prova P1 - ADS - Linguagem de Programação
#include <iostream>
#include <Windows.h>
using namespace std;
// Definições do programa
#define PAUSA								system("pause")
#define LIMPAR_TELA							system("cls")
#define	QTDE_PRODUTOS						1000				// quantidade total de produtos
#define EXTENSAO_DESCRICAO					40					// qtde bytes da descrição do produto
#define CAMINHO_CADASTRO					"..\\Produtos.cad"
// Opções do menu
#define CADASTRAR_PRODUTO					'C'
#define EXCLUIR_PRODUTO						'E'
#define MOSTRAR_PRODUTO						'M'
#define VENDER_PRODUTO						'V'
#define SAIR_DO_PROGRAMA					'S'
// struct do produto
typedef struct tagPRODUTO
{
	bool flgCadastrado;										// true - indica produto cadastrado
															// false - indica produto não cadastrado ou excluido
	int nCodigoProduto;										// codigo 1, 2, 3, .......QTDE_PRODUTOS
	char cDescricao[EXTENSAO_DESCRICAO + 1];				// descrição do produto
	double dPrecoUnit;										// preço unitário do produto
} PRODUTO;

//funcoes
bool GravaPosicional(int nPosicional, PRODUTO *ptrStProduto, FILE **fdProduto);
bool LerPosicional(int nPosicional, PRODUTO *ptrStProduto, FILE **fdProduto);