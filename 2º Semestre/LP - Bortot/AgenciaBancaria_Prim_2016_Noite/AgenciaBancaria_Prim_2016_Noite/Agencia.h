// Declarações do Programa de Agencia Bancaria
#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;
// Definições do programa
#define PAUSA								system("pause")
#define LIMPAR_TELA							system("cls")
#define QTDE_CLIENTES						2000
#define EXTENSAO_NOME						40
#define ATIVO								'A'
#define INATIVO								'I'

//caminho e nome do arquivo
#define CAMINHO_ARQUIVO						"..\\Cadastro.cad"

//menu de opções
#define CADASTRAR_CLIENTE					'C'
#define EXCLUIR_CLIENTE						'E'
#define MOSTRAR_CLIENTE						'M'
#define DEBITAR_CHEQUE						'D'
#define CREDITAR_DEPOSITO					'P'
#define LISTAR_CADASTRO						'L' //listar a partir de um dado cliente
#define EXIBIR_SALDO_TOTAL					'T'
#define SAIR_DO_PROGRAMA					'S'

// teclas
#define BACK_SPACE			0x08
#define ENTER				0x0D
#define BELL				0x07
#define SPACE				0x20

// prototypes
//int TestNumerico(int nExtenMax);

//STRUCT da data
typedef struct tagDATA {
	int nDia, nMes, nAno;					//dia,mes e ano
}DATA;

//STRUCT do cliente
typedef struct tagCLIENTE {
	int nCodigo;							//codigo do cliente 1,2,3,....QTDE_CLIENTES
	char cAtivo,							//'A' - ativo e 'I' - inativo
		cNome[EXTENSAO_NOME + 1];			//nome do cliente
	DATA stDataUltimoAcesso;				//data do ultimo acesso
	double dSaldo,							//saldo do cliente
		dTotalDebitos,						//total dos debitos
		dTotalCreditos;						//total dos creditos
}CLIENTE;

//prototipos das funcoes
int PedirCodigoCliente(char *ptrAcao);
bool GravarClientePosicional(int nCodigo, CLIENTE *ptrCliente, FILE *fdArquivo);
bool LerClientePosicional(int nCodigo, CLIENTE *ptrCliente, FILE *fdArquivo);