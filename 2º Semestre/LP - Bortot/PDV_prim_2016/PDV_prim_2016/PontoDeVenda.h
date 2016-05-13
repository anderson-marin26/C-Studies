// Declarações do programa de Ponto de Venda
#include <iostream>
#include <Windows.h>
using namespace std;

// Definições do programa
#define PAUSA							system("pause")
#define LIMPAR_TELA						system("cls")
#define ATIVO							'A'
#define INATIVO							'I' // inativo ou excluido
#define EXTENSAO_DESCRICAO				40
#define EXTENSAO_RAZAO					40

// Caminho dos Arquivos
#define CAMINHO_CONFIG					"..\\Mercado.ini"
#define CAMINHO_CADASTRO				"..\\Produtos.cad"

// Opções do menu
#define CADASTRAR_PRODUTO				'C'
#define EXCLUIR_PRODUTO					'E'
#define MOSTRAR_PRODUTO					'M'
#define VENDER_PRODUTO					'V'
#define SAIR_DO_PROGRAMA				'S'

// Struct de data
typedef struct tagDATA {
	int nDia, nMes, nAno;
}DATA;

// Struct da configuração
typedef struct tagCONFIGURACAO {
	int nQtdeProdutos;						// quantidade de produtos do mercado
	char cRazaoSocial[EXTENSAO_RAZAO + 1];	// razão social do mercado
	DATA stDtInicio;						// data do inicio
}CONFIGURACAO;

// Struct do cadastro do produto
typedef struct tagPRODUTO {
	int nCodProduto;
	char cAtivo,
		cDescricao[EXTENSAO_DESCRICAO + 1];
	double dPrecoUnit;
}PRODUTO;

//Prototipos das funções do programa

