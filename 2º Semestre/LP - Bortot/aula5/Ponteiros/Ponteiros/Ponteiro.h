//declaracao do programa que demostra ponteiros
#include "iostream"
#include "windows.h"
using namespace std;

//defines do programa

#define PAUSA						system("pause")
#define LIMPAR_TELA					system("cls")
#define ACENTUACAO_BRASILEIRA		setlocale(LC_ALL, "portuguese_brazil")
#define SAIR_DO_PROGRAMA			system("exit")
#define QTDE_INTEIRAS				500
#define EXTENSAO_NOME				30

//declaracao da struct de clientes

typedef struct tagCLIENTE {
	int nCodigo;									//codigo do cliente
	char cNome[EXTENSAO_NOME + 1];					//nome do cliente
	double dSaldo;									//saldo do cliente
} CLIENTE;