// Agencia banc�ria - Trapalho para entrega na P2
// FATEC - MC - RVC - 20/04/2016 - vers�o 0.0.0
#include "Agencia.h"	

//entry point do programa

void main(void)
{
	int i,		//indice de contador
		nCodCliente;		//recebe o c�digo do cliente
	double valor;
	char cOpcao,			//op��o do operador
		szOperador[] = "Raul Victor Coan",		//nome do operador
		cTrabalho[200];		//sprintf_s
	CLIENTE stCliente;		//para conter os dados de um cliente
	SYSTEMTIME stTime;		//para data e hora do sistema
	FILE *fdCadastro;		//file descriptor do cadastro do cliente

	setlocale(LC_ALL, "portuguese_brazil");		//acentua��o brasileira

												//abrir o arquivo em modo leitura/grava�ao e bin�rio - precisa exixtir
	if (fopen_s(&fdCadastro, CAMINHO_ARQUIVO, "r+b") != 0)		//erro de abertura
	{//o arquivo n�o existe porque � a primeira vez que o programa � executado
		if (fopen_s(&fdCadastro, CAMINHO_ARQUIVO, "w+b") != 0)		//erro de abertura
		{//erro irrecuper�vel
			cout << "Erro de abertura do arquivo: " << CAMINHO_ARQUIVO << endl;
			PAUSA;
			return;		//volta ao sistema operacional
		}
		//aberto com sucesso - vamos "inicializar o arquivo com todos os clientes inativos
		for (i = 0; i < QTDE_CLIENTES; i++)
		{
			stCliente.nCodigo = i + 1;
			stCliente.cAtivo = INATIVO;
			//gravar esse cliente em modo sequencial
			if (fwrite(&stCliente, sizeof(CLIENTE), 1, fdCadastro) == 0)//erro grava��o
			{//erro irrecuper�vel
				fclose(fdCadastro);		//fechar com o que est� gravado
				cout << "Erro na inicializa��o de cadastro de clientes!" << endl;
				PAUSA;
				return;
			}
		}
	}//arquivo n�o existe
	 //arquivo existe ou foi criado outro
	 //loop infinito
	while (true)
	{
		LIMPAR_TELA;
		GetLocalTime(&stTime);		//data e hora do sistema
		sprintf_s(cTrabalho, sizeof(cTrabalho), "\n\tFATEC-MC - Agencia Bancaria %02d/%02d/%04d �s %02d:%02d:%02d \n\tOperador %s", stTime.wDay, stTime.wMonth, stTime.wYear, stTime.wHour, stTime.wMinute, stTime.wSecond, szOperador);
		cout << cTrabalho << endl;

		cout << CADASTRAR_CLIENTE << " - Cadastrar novo cliente" << endl;
		cout << EXCLUIR_CLIENTE << " - Excluir Cliente exixtente" << endl;
		cout << MOSTRAR_CLIENTE << " - Mostrar dados do cliente" << endl;
		cout << DEBITAR_CHEQUE << " - Debitar um cheque de cliente" << endl;
		cout << CREDITAR_DEPOSITO << " - Creditar dep�sito do cliente" << endl;
		cout << LISTAR_CADASTRO << " - Listar cadastro a partir de um cliente" << endl;
		cout << EXIBIR_SALDO_TOTAL << " - Exibir o total das contas" << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do Programa" << endl;
		cout << "\tSelecione: ";
		cin >> cOpcao;
		cOpcao = toupper(cOpcao);

		switch (cOpcao)		//avaliar a op��o escolhica
		{
		case CADASTRAR_CLIENTE:
			nCodCliente = PedirCodigoCliente("\tCadastrar Cliente");
			if (nCodCliente == 0)		//cancelar?
				break;		//volta ao menu
							//ler um cliente posicional
			if (!LerClientePosicional(nCodCliente, &stCliente, fdCadastro))			//erro de leitura?
			{
				cout << " Erro de Leitura do CLiente: " << nCodCliente << endl;
				PAUSA;
				break;		//volta ao menu
			}
			//o cliente foi lido
			if (stCliente.cAtivo == ATIVO)		//cliente ja existe?
			{//cliente ja existe
				cout << "cliente: " << stCliente.nCodigo << " Nome: " << stCliente.cNome << endl << " J� foi cadastrado!" << endl;
				PAUSA;
				break;
			}
			//cliente vai ser cadstrado
			cin.ignore(1, EOF);
			cout << "Nome: ";
			cin.getline(stCliente.cNome, EXTENSAO_NOME, '\n');
			cout << " Saldo: ";
			cin >> stCliente.dSaldo;
			stCliente.dTotalCreditos = stCliente.dTotalDebitos = 0.0;
			stCliente.stDataUltimoAcesso.nDia = stTime.wDay;
			stCliente.stDataUltimoAcesso.nMes = stTime.wMonth;
			stCliente.stDataUltimoAcesso.nAno = stTime.wYear;
			stCliente.cAtivo = ATIVO;
			//gravar o cliente posicional
			if (!GravarClientePosicional(nCodCliente, &stCliente, fdCadastro))
			{
				cout << "Erro de grava��o do cliente: " << nCodCliente << endl;
				PAUSA;
			}
			break;
		case EXCLUIR_CLIENTE:
			nCodCliente = PedirCodigoCliente("Excluir Cliente");
			if (nCodCliente == 0)		//cancelar?
				break;		//volta ao menu
			//ler um cliente posicional
			if (!LerClientePosicional(nCodCliente, &stCliente, fdCadastro))			//erro de leitura?
			{
				cout << " Erro de Leitura do CLiente: " << nCodCliente << endl;
				PAUSA;
				break;		//volta ao menu
			}
			if (stCliente.cAtivo == INATIVO) {
				cout << "O cliente n�o est� cadastrado!" << endl;
				PAUSA;
				break;
			} else {
				stCliente.cAtivo = INATIVO;
				if (!GravarClientePosicional(nCodCliente, &stCliente, fdCadastro))
				{
					cout << "Erro na exclus�o do cliente: " << nCodCliente << endl;
				}
			}
			break;
		case MOSTRAR_CLIENTE:
			nCodCliente = PedirCodigoCliente("\tExcluir Cliente");
			if (nCodCliente == 0)		//cancelar?
				break;		//volta ao menu

			if (!LerClientePosicional(nCodCliente, &stCliente, fdCadastro))			//erro de leitura?
			{
				cout << " Erro de Leitura do CLiente: " << nCodCliente << endl;
				PAUSA;
				break;		//volta ao menu
			}
			if (stCliente.cAtivo == INATIVO) {
				cout << "N�o h� nenhum cliente cadastrado com o c�digo: " << nCodCliente << endl;
				PAUSA;
				break;
			}
			else
			{
				sprintf_s(cTrabalho, sizeof(cTrabalho), "C�digo: %4d Nome: %-40s Ultimo acesso: %02d/%02d/%04d",
					stCliente.nCodigo, stCliente.cNome, stCliente.stDataUltimoAcesso.nDia, stCliente.stDataUltimoAcesso.nMes, stCliente.stDataUltimoAcesso.nAno);
				cout << cTrabalho << endl;
				PAUSA;
			}
			
			break;
		case DEBITAR_CHEQUE:
			nCodCliente = PedirCodigoCliente("\tDebitar Cheque");
			if (nCodCliente == 0)		//cancelar?
				break;		//volta ao menu

			if (!LerClientePosicional(nCodCliente, &stCliente, fdCadastro))			//erro de leitura?
			{
				cout << " Erro de Leitura do CLiente: " << nCodCliente << endl;
				PAUSA;
				break;		//volta ao menu
			}
			if (stCliente.cAtivo == INATIVO) {
				cout << "N�o h� nenhum cliente cadastrado com o c�digo: " << nCodCliente << endl;
				PAUSA;
				break;
			}

			//Inser��o do valor a ser debitado
			do {
				cout << "Insira o valor a ser debitado (Valor positivo): ";
				cin >> valor;
			} while (valor < 0);
			//verifica��o se o valor pode ser descontado do cliente
			if (valor > stCliente.dSaldo) {
				cout << "Saldo R$"<< stCliente.dSaldo <<" insuficiente!"<<endl;
				PAUSA;
				break;
			}

			stCliente.dTotalDebitos += valor;
			stCliente.dSaldo -= valor;
			stCliente.stDataUltimoAcesso.nDia = stTime.wDay;
			stCliente.stDataUltimoAcesso.nMes = stTime.wMonth;
			stCliente.stDataUltimoAcesso.nAno = stTime.wYear;

			if (!GravarClientePosicional(nCodCliente, &stCliente, fdCadastro))
			{
				cout << "Erro ao debitar do cliente: " << nCodCliente << endl;
			}

			break;
		case CREDITAR_DEPOSITO:
			nCodCliente = PedirCodigoCliente("\tCreditar Dep�sito");
			if (nCodCliente == 0)		//cancelar?
				break;		//volta ao menu

			if (!LerClientePosicional(nCodCliente, &stCliente, fdCadastro))			//erro de leitura?
			{
				cout << " Erro de Leitura do CLiente: " << nCodCliente << endl;
				PAUSA;
				break;		//volta ao menu
			}
			if (stCliente.cAtivo == INATIVO) {
				cout << "N�o h� nenhum cliente cadastrado com o c�digo: " << nCodCliente << endl;
				PAUSA;
				break;
			}

			//Inser��o do valor a ser creditado
			do {
				cout << "Insira o valor a ser creditado (Valor positivo): ";
				cin >> valor;
			} while (valor < 0);

			stCliente.dTotalCreditos += valor;
			stCliente.dSaldo += valor;
			stCliente.stDataUltimoAcesso.nDia = stTime.wDay;
			stCliente.stDataUltimoAcesso.nMes = stTime.wMonth;
			stCliente.stDataUltimoAcesso.nAno = stTime.wYear;

			if (!GravarClientePosicional(nCodCliente, &stCliente, fdCadastro))
			{
				cout << "Erro ao creditar o cliente: " << nCodCliente << endl;
			}

			break;
		case LISTAR_CADASTRO:
			nCodCliente = PedirCodigoCliente("\tExcluir Cliente\nDigite um c�digo para exibirmos apartir dele:");
			if (nCodCliente == 0)		//cancelar?
				break;		//volta ao menu
			//for para listar os cadastros
			for (i = nCodCliente; i < QTDE_CLIENTES;) {
				if (!LerClientePosicional(nCodCliente, &stCliente, fdCadastro))			//erro de leitura?
				{
					cout << " Erro de Leitura do CLiente: " << nCodCliente << endl;
					PAUSA;
					break;		//volta ao menu
				}
				if (stCliente.cAtivo == INATIVO) {
					nCodCliente = ++i;		//incrementa o indice e altera nCodigo
					continue;
				}
					sprintf_s(cTrabalho, sizeof(cTrabalho), "C�digo: %4d Nome: %-40s Ultimo acesso:  %02d/%02d/%04d",
						stCliente.nCodigo, stCliente.cNome, stCliente.stDataUltimoAcesso.nDia, stCliente.stDataUltimoAcesso.nMes, stCliente.stDataUltimoAcesso.nAno);
					cout << cTrabalho << endl;
					
					nCodCliente = ++i;		//incrementa o indice e altera nCodigo
			}
			PAUSA;
			break;
		case EXIBIR_SALDO_TOTAL:
			nCodCliente = PedirCodigoCliente("\Exibir saldo do Cliente");
			if (nCodCliente == 0)		//cancelar?
				break;		//volta ao menu

			if (!LerClientePosicional(nCodCliente, &stCliente, fdCadastro))			//erro de leitura?
			{
				cout << " Erro de Leitura do CLiente: " << nCodCliente << endl;
				PAUSA;
				break;		//volta ao menu
			}
			if (stCliente.cAtivo == INATIVO) {
				cout << "N�o h� nenhum cliente cadastrado com o c�digo: " << nCodCliente << endl;
				PAUSA;
				break;
			}
			else
			{
				sprintf_s(cTrabalho, sizeof(cTrabalho), "C�digo: %4d Nome: %-40s Saldo: %.2f  Ultimo acesso: %02d/%02d/%04d",
					stCliente.nCodigo, stCliente.cNome, stCliente.dSaldo,stCliente.stDataUltimoAcesso.nDia, stCliente.stDataUltimoAcesso.nMes, stCliente.stDataUltimoAcesso.nAno);
				cout << cTrabalho << endl;
				PAUSA;
			}
			break;
		case SAIR_DO_PROGRAMA:
			cout << "Sair Realmente? (S ou N): ";
			cin >> cOpcao;
			if (cOpcao == 's' || cOpcao == 'S')
			{
				fclose(fdCadastro);
				return;
			}
			break;
		default:
			cout << "Op��o Inv�lida!" << endl;
			PAUSA;
		}

	}
}//main