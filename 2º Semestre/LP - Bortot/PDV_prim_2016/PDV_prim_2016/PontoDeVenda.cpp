// Programa Ponto de Venda - FATEC - MC - Anderson Marin de Ramos - 04/05/2016 - Vers�o 0.0
#include "PontoDeVenda.h"

int PedeUmProdutoValido(char *szAcao, CONFIGURACAO stConfig, PRODUTO stProduto)
{                                         
	cout << "\n\tA��o: " << szAcao << endl;
	do
	{
		cout << "Informe o codigo do produto entre 1 e " << stConfig.nQtdeProdutos << endl
			<< "Ou zero para cancelar a transa��o: ";
		cin >> stProduto.nCodProduto;									// pede o c�digo
		if (stProduto.nCodProduto == 0)                               // cancelar a transa��o?
			return 0;                                   // indica que a transa��o foi cancelada
	} while (stProduto.nCodProduto < 1 || stProduto.nCodProduto > stConfig.nQtdeProdutos);
	return stProduto.nCodProduto;                                     // devolve o c�digo que foi digitado
}
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
		cout << CADASTRAR_PRODUTO << " - Cadastrar um novo produto" << endl;
		cout << EXCLUIR_PRODUTO << "- Excluir um produto existente" << endl;
		cout << MOSTRAR_PRODUTO << " - Exibir dados de um produto" << endl;
		cout << VENDER_PRODUTO << " - Vender um produto" << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do programa" << endl;
		cout << "\tSelection:";
		cin >> cOpcao;
		cOpcao = toupper(cOpcao);
		switch (cOpcao) {
			case CADASTRAR_PRODUTO:
				stProduto.nCodProduto = PedeUmProdutoValido("Cadastrar Produto", stConfig, stProduto);
				break;
			case EXCLUIR_PRODUTO:
				break;
			case MOSTRAR_PRODUTO:
				break;
			case VENDER_PRODUTO:
				break;
			case SAIR_DO_PROGRAMA:
				cout << "Sair realmente? (S ou N): ";
				cin >> cOpcao;
				if (cOpcao == 's' || cOpcao == 'S') {
					fclose(fdConfig);
					fclose(fdProduto);
					exit(0);						//retorna ao S.O sem erro
				}
				break;								//volta ao menu
			default:
				cout << "\n\tOp��o invalida!" << endl;
				PAUSA;
		}
	}// while
}// main