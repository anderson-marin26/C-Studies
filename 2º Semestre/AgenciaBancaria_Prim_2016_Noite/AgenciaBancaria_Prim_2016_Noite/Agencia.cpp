// Agencia Bancaria - Trabalho para entrega na P2
// FATEC - MC - AMR - 20/04/2016 - Versão 0.0
#include "Agencia.h"

// entry point do programa
void main(void) {
	int i,							// indice e contador
		nCodCliente;				// recebe o codigo do cliente
	char cOpcao,					// opcao do operador
		szOperador[]="Anderson Marin de Ramos",
		cTrabalho[200];				// sprintf_s
	CLIENTE stCliente;				// para conter os dados de um cliente
	SYSTEMTIME stTime;				// para data e hora do sistema
	FILE *fdCadastro;				// file descriptor do cadastro cliente

	setlocale(LC_ALL, "portuguese_brazil");	// acentuacao brasileira
	// abrir o arquivo em modo leitura/gravacao e binario - precisa existir
	if (fopen_s(&fdCadastro, CAMINHO_ARQUIVO, "r+b") != 0) { //erro de abertura
		if (fopen_s(&fdCadastro, CAMINHO_ARQUIVO, "w+b") != 0) {
			// erro irrecuperavel
			cout << "Erro de abertura do arquivo: " << CAMINHO_ARQUIVO << endl;
			PAUSA;
			return;					// volta ao sistema operacional
		}
		// aberto com sucesso - inicializar o arquivo com todos os clientes inativos
		for (i = 0; i < QTDE_CLIENTES; i++) {
			stCliente.nCodigo = i + 1; //cliente 1,2,3....QTDE_CLIENTES
			stCliente.cAtivo = INATIVO;//cliente inativo
			//gravar esse cliente em modo sequencial
			if (fwrite(&stCliente, sizeof(CLIENTE), 1, fdCadastro) == 0) {
				//erro irrecuperavel
				fclose(fdCadastro);	// fechar com o que esta gravado
				cout << "Erro na inicialização do cadastro de clientes!" << endl;
				PAUSA;
				return;				// volta ao sistema operacional
			}
		}// for
	}// arquivo nao existe
	
	 // arquivo existe ou foi criado um novo
	// loop infinito
	while (true) {
		LIMPAR_TELA;
		GetLocalTime(&stTime);		// data e hora do sistema
		sprintf_s(cTrabalho, sizeof(cTrabalho), "\n\tFATEC-MC - Agencia Bancaria %02d/%02d/%04d às %02d:%02d:%02d\n\tOperador: %s", stTime.wDay, stTime.wMonth, stTime.wYear, stTime.wHour, stTime.wMinute, stTime.wSecond, szOperador);
		cout << cTrabalho << endl;

		// editar o menu
		cout << CADASTRAR_CLIENTE << " - Cadastrar novo cliente" << endl;
		cout << EXCLUIR_CLIENTE << " - Excluir cliente existente" << endl;
		cout << MOSTRAR_CLIENTE << " - Mostrar dados do cliente" << endl;
		cout << DEBITAR_CHEQUE << " - Debitar cheque de cliente" << endl;
		cout << CREDITAR_DEPOSITO << " - Creditar o deposito de cliente" << endl;
		cout << LISTAR_CADASTRO << " - Listar o cadastro a partir de um cliente" << endl;
		cout << EXIBIR_SALDO_TOTAL << " - Exibir o total das contas da agencia" << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do Programa" << endl;
		cout << "\tSelecione: ";
		cin >> cOpcao;				// opção do operador
		cOpcao = toupper(cOpcao);
		switch (cOpcao) {				// avaliar a opção escolhida
			case CADASTRAR_CLIENTE:
				nCodCliente = PedirCodigoCliente("Cadastrar cliente");
				if (nCodCliente == 0) {
					break;
				}
				if (!LerClientePosicional(nCodCliente, &stCliente, fdCadastro)) {
					cout << "Erro de leitura do cliente: " << nCodCliente << endl;
					break;
				}
				// o cliente foi lido
				if (stCliente.cAtivo == ATIVO) {
					cout << "Cliente: " << stCliente.nCodigo << " Nome: " << stCliente.cNome << endl << "Ja foi cadastrado!" << endl;
					PAUSA;
					break;
				}

				//cliente vai ser cadastrado
				cin.ignore(1, EOF);		// ignorar a tecla enter
				cout << "Nome: ";
				cin.getline(stCliente.cNome, EXTENSAO_NOME, '\n');
				cout << "Saldo: ";
				cin >> stCliente.dSaldo;
				stCliente.dTotalCreditos = stCliente.dTotalDebitos = 0.0;
				stCliente.stDataUltimoAcesso.nDia = stTime.wDay;
				stCliente.stDataUltimoAcesso.nMes = stTime.wMonth;
				stCliente.stDataUltimoAcesso.nAno = stTime.wYear;
				stCliente.cAtivo = ATIVO;

				// grava o cliente posicional
				if (!GravarClientePosicional(nCodCliente, &stCliente, fdCadastro)) {
					cout << "Erro de gracação do cliente: " << nCodCliente << endl;
					PAUSA;
				}
				break;					// volta ao menu
			case EXCLUIR_CLIENTE:
				break;
			case MOSTRAR_CLIENTE:
				break;
			case DEBITAR_CHEQUE:
				break;
			case CREDITAR_DEPOSITO:
				break;
			case LISTAR_CADASTRO:
				break;
			case EXIBIR_SALDO_TOTAL:
				break;
			case SAIR_DO_PROGRAMA:
				cout << "Sair realmente? (S ou N): ";
				cin >> cOpcao;
				if (cOpcao == 's' || cOpcao == 'S') {
					fclose(fdCadastro);
					return;
				}
				break;
			default:
				cout << "Opção invalida!" << endl;
				PAUSA;
		}//switch
	}// while
		

}// main