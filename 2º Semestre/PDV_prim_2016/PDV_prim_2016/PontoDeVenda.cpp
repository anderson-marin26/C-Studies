// Programa Ponto de Venda - FATEC - MC - Anderson Marin de Ramos - 04/05/2016 - Vers�o 0.0
#include "PontoDeVenda.h"

// entry point
void main(void) {
	CONFIGURACAO stConfig;						// struct para conter a configura��o
	PRODUTO stProduto;							// para conter os dados de um produto
	int i;
	char cOpcao,
		cWork[200];
	SYSTEMTIME stTime;							// data e hora do sistema
	FILE *fdConfig,								// filde descriptor do arquivo de configura��o
		*fdProduto;	
	setlocale(LC_ALL, "portuguese_brazil");

	// abrir arquivo de configura��o em modo leitura/binario
	if (fopen_s(&fdConfig, CAMINHO_CONFIG, "rb") != 0) {
		// n�o sendo aberto significa que � a primeira vez que o programa � executado
		if (fopen_s(&fdConfig, CAMINHO_CONFIG, "wb") != 0) {
			// Erro irrecuperavel
			cout << "Erro de abertura da configura��o!" << endl;
			PAUSA;
			exit(-1);							// retorna ao sistema em condi��o de erro
		}

		// configurar o programa
		cout << "Informe a quantidade de produtos: ";
		cin >> stConfig.nQtdeProdutos;
		cin.ignore(1, EOF);
		cout << "Raz�o social: ";
		cin.getline(stConfig.cRazaoSocial, EXTENSAO_RAZAO, '\n');
		GetLocalTime(&stTime);					// data e hora do sistema
		stConfig.stDtInicio.nDia = stTime.wDay;
		stConfig.stDtInicio.nMes = stTime.wMonth;
		stConfig.stDtInicio.nAno = stTime.wYear;
		if (fwrite(&stConfig, sizeof(CONFIGURACAO), 1, fdConfig) == 0) {
			// erro irrecuperavel de grava��o
			fclose(fdConfig);					// fecha o arquivo
			cout << "Erro de grava��o da configura��o!" << endl;
			PAUSA;
			exit(-1);
		}

		// abrir o arquivo de produtos em modo grava��o/leitura/binario
		if (fopen_s(&fdProduto, CAMINHO_CADASTRO, "w+b") != 0) {
			fclose(fdConfig);
			cout << "Erro de abertura do cadastro de produtos!" << endl;
			PAUSA;
			exit(-1);
		}

		// "formatar" o arquivo de produtos com todos inativos
		for (i = 0; i < stConfig.nQtdeProdutos; i++) {
			stProduto.nCodProduto = i + 1;
			stProduto.cAtivo = INATIVO;			// produto n�o existe
			stProduto.dPrecoUnit = 0.0;			// zerar pre�o unitario
			stProduto.cDescricao[0] = NULL;
			if (fwrite(&stProduto, sizeof(PRODUTO), 1, fdProduto) == 0) {
				fclose(fdConfig);
				fclose(fdProduto);
				cout << "Erro de grava��o do produto" << endl;
				PAUSA;
				exit(-1);
			}
		}// for i
	}// Primeira vez
	else {
		if (fread_s(&stConfig, sizeof(CONFIGURACAO), sizeof(CONFIGURACAO), 1, fdConfig) == 0) {
			// erro de leitura, irrecuperavel
			fclose(fdConfig);
			cout << "Erro de leitura da configura��o" << endl;
			PAUSA;
			exit(-1);
		}

		// abrir o arquivo de produto em modo leitura/grava��o/binario
		if (fopen_s(&fdProduto, CAMINHO_CADASTRO, "r+b") != 0) {
			// erro irrecuperavel
			fclose(fdConfig);
			cout << "Erro de abertura do cadastro" << endl;
			PAUSA;
			exit(-1);
		}
	}// os dois arquivos foram abertos

	// loop infinito do programa
	while (true) {
		LIMPAR_TELA;
		GetLocalTime(&stTime);
		sprintf_s(cWork, sizeof(cWork), "\n\tPonto de Venda de %s %02d/%02d/%04d �s %02d:%02d:%02d Dt.Inicio %02d/%02d/%04d",
			stConfig.cRazaoSocial,
			stTime.wDay,
			stTime.wMonth,
			stTime.wYear,
			stTime.wHour,
			stTime.wMinute,
			stTime.wSecond,
			stConfig.stDtInicio.nDia,
			stConfig.stDtInicio.nMes,
			stConfig.stDtInicio.nAno
		);
		cout << cWork << endl;
	}// while
}// main