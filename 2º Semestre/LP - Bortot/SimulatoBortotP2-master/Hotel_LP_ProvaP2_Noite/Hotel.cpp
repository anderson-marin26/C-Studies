// Hotel.cpp - Programa de Hotel para prova de Linguagem de Programa��o (P2) - 17/06/2015
// FATEC - Mogi das Cruzes - Turma da Noite
#include <iostream>
#include <windows.h>
#include "Hotel.h"
using namespace std;

// Fun��o principal
void main(void)
{
	int  i,									// indice gen�rico
		nAndar,								// para receber o n�mero do andar
		nQuarto;							// para receber o n�mero do quarto dentro do andar
	char cOpcaoOper,						// local para receber a op��o escolhida do menu
		cWork[200],							// para sprintf
		szNomeAluno[] = "Anderson Marin de Ramos";	// nome do aluno
	double dValor;							// local para receber o valor dos servi�os do hotel
	QUARTO stQuarto;						// struct para conter os dados de um quarto
	QUANTIDADES stQuantidades;				// para conter as quantidades deste hotel
	FILE *fdQuartos,						// file descriptor do arquivo de quartos
		*fdQuantidades;						// file descriptor do arquivo de quantidades
	SYSTEMTIME stTime;						// para buscar data e hora
	HANDLE hndConsole = GetStdHandle ( STD_OUTPUT_HANDLE );
	// comandos para estabelecer o numero de casas decimais
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);						// duas casas decimais
	setlocale(LC_ALL, "portuguese_brazil");
	SetConsoleTextAttribute ( hndConsole,  BACKGROUND_GREEN  | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY );	
	SetConsoleTitle("FATEC-MC - Sistema de Hotel - Versao 0.0");
	// <<<< 00 >>>>
	//	Digitar o seu nome em szNomeAluno

	// <<<< 01 >>>>
	//	Abrir o arquivo de quartos em modo "r+b" (precisa existir)
	//		Se o arquivo de quartos existir fazer o seguinte:
	//		. Abrir o arquivo de quantidades em modo "rb"
	//			ler os seus dados para a struct stQuantidades.
	//		. Fechar o arquivo de quantidades  e ir para o menu do operador.
	// ----
	//	Se o arquivo de quartos n�o existir fazer o seguinte:
	//		. fazer um loop pedindo uma quantidade de andares v�lida
	//			indicando o m�nimo e o m�ximo
	//				guardar essa informa��o em stQuantidades.nQtdeAndares
	//		. fazer um loop pedindo uma quantidade de quartos por andar
	//				indicando o m�nimo e o m�ximo
	//				guardar essa informa��o em stQuantidades.nQtdeQuartos
	//		. abrir o arquivo de quantidades em modo "wb" e
	//				gravar os dados que est�o em stQuantidades e
	//				fechar o arquivo. 
	//				Se houver erro abortar o programa.
	// ----------
	//		. abrir o arquivo de quartos em modo "w+b" e 
	//			fazer um loop gravando cada quarto indicando que est� livre e
	//			o n�mero do andar, o n�mero do quarto no andar (lembrando que 
	//				o andar vai de 1 at� a quantidade de andares e quarto vai
	//				de 1 at� a quantidade de quartos por andar sendo que o
	//				n�mero do quarto come�a de 1 no pr�ximo andar) e o valor da di�ria deste
	//				quarto observando a tabela de di�rias no hotel.h.
	//			Se houver erro de abertura abortar o programa
	//		. fechar o arquivo de quartos e
	//			abrir em modo "r+b" e ir para o menu do operador.
	//
	//
	if ((fopen_s(&fdQuartos, CAMINHO_QUARTOS, "r+b") != 0))
	{//arquivo n�o existe
		do // pede quantidade de andares
		{
			cout << "Insira a quantidade de andares do pr�dio, entre " << QUANTIDADE_MINIMA_ANDARES << " e " << QUANTIDADE_MAXIMA_ANDARES << endl
				<< "Ou zero para cancelar: ";
			cin >> stQuantidades.nQtdeAndares;
			if (stQuantidades.nQtdeAndares == 0) {
				return;
			}

		} while (stQuantidades.nQtdeAndares < QUANTIDADE_MINIMA_ANDARES || stQuantidades.nQtdeAndares > QUANTIDADE_MAXIMA_ANDARES);

		do // pede quantidades de quarto por andar
		{
			cout << "Insira a quantidade de quartos por andar do pr�dio, entre " << QUANTIDADE_MINIMA_QUARTOS << " e " << QUANTIDADE_MAXIMA_QUARTOS << endl
				<< "Ou zero para cancelar: ";
			cin >> stQuantidades.nQtdeQuartos;
			if (stQuantidades.nQtdeQuartos == 0) {
				return;
			}
		} while (stQuantidades.nQtdeQuartos < QUANTIDADE_MINIMA_QUARTOS || stQuantidades.nQtdeQuartos > QUANTIDADE_MAXIMA_QUARTOS);

		if ((fopen_s(&fdQuantidades, CAMINHO_QUANTIDADES, "wb")) != 0)	//tenta criar o arquivo
		{//deu merda.
			cout << "Erro ao abrir o arquivo: " << CAMINHO_QUANTIDADES;
			PAUSA;
			return;
		}
		if (fwrite(&stQuantidades, sizeof(stQuantidades), 1, fdQuantidades) == 0)
		{//erro
			cout << "Erro ao criar arquivo de quantidades." << endl;
		}
		fclose(fdQuantidades);

		if ((fopen_s(&fdQuartos, CAMINHO_QUARTOS, "w+b") != 0))//cria o arquivo
		{
			for (i = 1; i = stQuantidades.nQtdeAndares; i++)
			{
				for (int j = 1; j = stQuantidades.nQtdeQuartos ; j++)
				{
					stQuarto.nAndar = i;
					stQuarto.nQuarto = j;
					stQuarto.flgLivreOuOcupado = OCUPADO;
					//seta o status do quarto
					if (i <= 3)
					{
						stQuarto.dValorDiaria = VALOR_DIARIA_SIMPLES;
					}
					else if (i <= 7)
					{
						stQuarto.dValorDiaria = VALOR_DIARIA_REGULAR;
					} 
					else if (i <= 10)
					{
						stQuarto.dValorDiaria = VALOR_DIARIA_LUXO;
					}
					else if (i > 11)
					{
						stQuarto.dValorDiaria = VALOR_DIARIA_SUITE;
					}

					if (!GravarQuarto(i, j, stQuantidades.nQtdeQuartos, fdQuartos, &stQuarto))// erro na grava��o?
					{
						cout << "Erro ao iniciar arquivo de quartos!" << endl;
					}
				}
			}
		}
		fclose(fdQuartos);
		if (fopen_s(&fdQuartos, CAMINHO_QUARTOS, "r+b") != 0)
		{
			cout << "Erro de abertura 0x666" << endl;
		}
	}

	
	
	if ((fopen_s(&fdQuantidades, CAMINHO_QUANTIDADES, "r+b")) != 0)	//tenta criar o arquivo
	{//deu merda.
		cout << "Erro ao abrir o arquivo: " << CAMINHO_QUANTIDADES;
		PAUSA;
		return;
	} 
	else
	{
		if (fseek(fdQuantidades, 0, 0) != 0)	// fseek com erro?
			return;
		if (fread_s(&stQuantidades, sizeof(QUANTIDADES), sizeof(QUANTIDADES), 1, fdQuantidades) == 0)		// erro de leitura?
		{
			cout << "Falha ao abrir arquivos de quantidade!" << endl;
			PAUSA;
			return;
		}
	}
	

	while(true)								// loop infinito
	{
		LIMPAR_TELA;		
		GetLocalTime(&stTime);
		// Mostrar o menu de op��es para o operador
		sprintf_s(cWork, 
			"\n\tFATEC-MC - Sistema de Hotel %02d/%02d/%04d %02d:%02d:%02d\n\tOperador: %s - Turma da Noite\n", 
			stTime.wDay, stTime.wMonth, stTime.wYear,
			stTime.wHour, stTime.wMinute, stTime.wSecond,
			szNomeAluno);
		cout << cWork << endl;
		cout << FAZER_CHECK_IN << " - Check-in de um h�spede" << endl;
		cout << FAZER_CHECK_OUT << " - Check-out de um h�spede" << endl;
		cout << LANCAR_SERVICO << " - Lan�ar servi�o" << endl;
		cout << LANCAR_DIARIA <<  " - Lan�ar di�rias em todos os quartos ocupados" << endl;
		cout << LISTAR_UM_QUARTO << " - Listar um quarto" << endl;
		cout << SAIR_DO_PROGRAMA <<  " - Sair do programa" << endl;
		cout << "\tSelecione: ";
		cin	 >> cOpcaoOper;					// op��o escolhida pelo operador
		cOpcaoOper = toupper(cOpcaoOper);	// converte para upper case a op��o escolhida
		switch(cOpcaoOper)					// avaliar a op��o que foi escolhida pelo operador
		{
			case FAZER_CHECK_IN:
				// <<<< 02 >>>>
				// 1 - Chamar a fun��o que pede o andar e analizar o retorno
				nAndar = PedirAndar(stQuantidades.nQtdeAndares, "Check-in novo h�spede");
				if(nAndar == 0)						// cancelar?
					break;							// volta ao menu
				// 2 - Chamar a fun��o que pede o quarto dentro do andar
				nQuarto = PedirQuarto(stQuantidades.nQtdeQuartos, "Check-in novo h�spede");
				if(nQuarto == 0)					// cancelar?
					break;							// volta ao menu

				// 3 - Chamar a fun��o que l� o quarto que est� dentro do arquivo para stQuarto
				if (!LerQuarto(nAndar, nQuarto, stQuantidades.nQtdeQuartos, fdQuartos, &stQuarto)) //erro?
				{ //erro!
					cout << "Ocorreu um erro ao ler o quarto!" << endl;
					PAUSA;
					break;
				}

				// 4 - verificar se o quarto est� ocupado e se estiver avisar o operador indicando
				//		o nome do h�spede, dar uma pausa para visualiza��o do operador e
				//		voltar ao menu
				if (stQuarto.flgLivreOuOcupado == OCUPADO)
				{
					sprintf_s(cWork, sizeof(cWork), "O quarto est� ocupado por:\n%40s", stQuarto.cNomeHospede);
					cout << cWork << endl;
					PAUSA;
					break;
				}
				// 5 - O quarto est� livre, pedir o nome do h�spede n�o se esquecendo que o
				//		o nome tem sobrenome....
				cin.ignore(1, EOF);
				cout << "Nome do h�spede: ";
				cin.getline(stQuarto.cNomeHospede, '\n');
				// 6 - Zerar os totais e indicar que o quarto est� ocupado.
				stQuarto.dValorTotalDespesas = 0;
				stQuarto.dValorTotalServicos = 0;
				stQuarto.flgLivreOuOcupado = OCUPADO;
				// 7 - Gravar os dados que foram alterados em stQuarto.
				if (!GravarQuarto(nAndar, nQuarto, stQuantidades.nQtdeQuartos, fdQuartos, &stQuarto))
				{
					cout << "erro ao gravar quarto!" << endl;
					PAUSA;
				}
				// 8 - Voltar ao menu.
				break;								// voltar ao menu
			case FAZER_CHECK_OUT:
				// <<<< 03 >>>>
				// 1 - Pedir o andar e o quarto da mesma forma que no item anterior 
				nAndar = PedirAndar(stQuantidades.nQtdeAndares, "Check-in novo h�spede");
				if (nAndar == 0)						// cancelar?
					break;							// volta ao menu
				nQuarto = PedirQuarto(stQuantidades.nQtdeQuartos, "Check-in novo h�spede");
				if (nQuarto == 0)					// cancelar?
					break;
				// 2 - Chamar a fun��o que l� os dados do quarto para stQuarto.
				if (!LerQuarto(nAndar, nQuarto, stQuantidades.nQtdeQuartos, fdQuartos, &stQuarto)) //erro?
				{ //erro!
					cout << "Ocorreu um erro ao ler o quarto!" << endl;
					PAUSA;
					break;
				}
				// 3 - Verificar se o quarto est� livre e se estiver avisar ao operador,
				//		dar uma pausa e voltar ao menu.
				if (stQuarto.flgLivreOuOcupado == LIVRE)
				{
					cout << "O quarto n�o est� ocupado!" << endl;
					PAUSA;
					break;
				}
				// 4 - Se o quarto estiver ocupado exibir os dados do quarto:
				//		Andar, Quarto, H�spede e os totais.
				if (stQuarto.flgLivreOuOcupado == OCUPADO)
				{
					sprintf_s(cWork, sizeof(cWork), "O quarto %2d do andar %4d est� ocupado por:\n%40s\nTotal de di�rias: %3.2f\n Total de servi�os: %3.2f\nTOTAL: %5.2f",
						stQuarto.nQuarto, stQuarto.nAndar, stQuarto.cNomeHospede, 
						stQuarto.dValorTotalDiarias, 
						stQuarto.dValorTotalServicos, 
						stQuarto.dValorTotalServicos + stQuarto.dValorTotalDiarias);
					cout << cWork << endl;
					PAUSA;
					break;
				}
				// 5 - Pedir uma confirma��o do check-out e se for sim indicar que o quarto est� livre
				//		e gravar no arquivo de quarto e voltar ao menu.
				//		Se disser n�o, voltar ao menu.
				cout << "Deseja fazer check-out?(S/N)" << endl;
				cin >> cOpcaoOper;
				cOpcaoOper = toupper(cOpcaoOper);
				if (cOpcaoOper == 'S')
				{
					stQuarto.flgLivreOuOcupado = LIVRE;
					if (!GravarQuarto(nAndar, nQuarto, stQuantidades.nQtdeQuartos, fdQuartos, &stQuarto))
					{
						cout << "erro ao gravar opera��o!" << endl;
						PAUSA;
					}
				}
				break;								// voltar ao menu
			case LANCAR_SERVICO:
				// <<<< 04 >>>>
				// 1 - Pedir o andar e o quarto da mesma forma que no item anterior 
				nAndar = PedirAndar(stQuantidades.nQtdeAndares, "Check-in novo h�spede");
				if (nAndar == 0)						// cancelar?
					break;							// volta ao menu
				nQuarto = PedirQuarto(stQuantidades.nQtdeQuartos, "Check-in novo h�spede");
				if (nQuarto == 0)					// cancelar?
					break;
				// 2 - Chamar a fun��o que l� os dados do quarto para stQuarto.
				if (!LerQuarto(nAndar, nQuarto, stQuantidades.nQtdeQuartos, fdQuartos, &stQuarto)) //erro?
				{ //erro!
					cout << "Ocorreu um erro ao ler o quarto!" << endl;
					PAUSA;
					break;
				}
				// 3 - Verificar se o quarto est� ocupado e se n�o estiver avisar ao operador e
				//		voltar ao menu.
				if (stQuarto.flgLivreOuOcupado == LIVRE)
				{
					cout << "O quarto n�o est� ocupado!" << endl;
					PAUSA;
					break;
				}
				// 4 - Exibir os servi�os poss�veis na seguinte forma:
				//
				//			1 - RESTAURANTE
				//			2 - BAR
				//			3 - PISCINA
				//			4 - BOATE
				//			5 - FRIGO-BAR
				//				Selecione: 
				//
				//		Ficar em looping at� que o operador selecione um tipo de servi�o v�lido
				do
				{
					cout << RESTAURANTE<< " - BAR" << endl;
					cout << PISCINA << " - PISCINA" << endl;
					cout << BOATE << " - BOATE" << endl;
					cout << FRIGO_BAR << " - FRIGO-BAR" << endl;
					cout << SAIR_DO_PROGRAMA << " para cancelar!";
					cout << "\tSelecione: ";
					cin >> cOpcaoOper;

					switch (cOpcaoOper)
					{
					case RESTAURANTE:
						stQuarto.dValorTotalServicos += PedirValorServi�o();
						cOpcaoOper = SAIR_DO_PROGRAMA;
						break;
					case PISCINA:
						stQuarto.dValorTotalServicos += PedirValorServi�o();
						cOpcaoOper = SAIR_DO_PROGRAMA;
						break;
					case BOATE:
						stQuarto.dValorTotalServicos += PedirValorServi�o();
						cOpcaoOper = SAIR_DO_PROGRAMA;
						break;
					case FRIGO_BAR:
						stQuarto.dValorTotalServicos += PedirValorServi�o();
						cOpcaoOper = SAIR_DO_PROGRAMA;
						break;
					case SAIR_DO_PROGRAMA:
						cOpcaoOper = SAIR_DO_PROGRAMA;
						break;
					default:
						cout << "Op��o inv�lida!" << endl;
						PAUSA;
						break;
					}
				} while (cOpcaoOper != SAIR_DO_PROGRAMA);
				// 5 - Pedir o valor do servi�o e adicionar nos totais devidos (total de servi�os e
				//		total de despesas.
				//
				//		Voltar ao menu....

				break;								// voltar ao menu
			case LANCAR_DIARIA:
				// <<<< 05 >>>>
				// 1 - Pedir a data e hora do sistema e apresentar ao operador a seguinte mensagem:
				//		"Confirma o lan�amento de di�rias em dd/mm/aaaa hh:mm (S ou N): "
				//		Se o operador n�o disser sim voltar ao menu
				GetSystemTime(&stTime);
				sprintf_s(cWork,sizeof(cWork), "Corfimar o lan�amento de di�rias em %2d/%2d/4d, �s %2d:%2d? (S/N): ");
				cin >> cOpcaoOper;
				cOpcaoOper = toupper(cOpcaoOper);
				// 2 - Se o operador confirmar fazer o seguinte:
				//		. Ler cada quarto posicionando pelo seu �ndice e verificar se o quarto est�
				//			ocupado. 
				//		. Se o quarto estiver ocupado adicionar o valor da di�ria
				//			que est� no registro do quarto no total de di�rias e no 
				//			total de despesas. Regravar este quarto com os novos valores.
				//		. Se o quarto estiver livre ler o pr�ximo quarto.
				// 3 - No final apresentar os seguintes totais: qtde de di�rias e o valor total das
				//		di�rias. Dar uma pausa.
				//		Voltar ao menu do operador
				break;								// voltar ao menu
			case LISTAR_UM_QUARTO:
				// <<<< 06 >>>>
				// 1 - Pedir Andar e Quarto conforme itens anteriores
				// 2 - Chamar a fun��o que l� os dados do quarto.
				// 3 - Se o quarto estiver livre avisar o operador e voltar ao menu.
				// 4 - Exibir todos os dados do quarto: andar, quarto, h�spede, valor da di�ria e totais
				//	    Dar uma pausa e voltar ao menu
				break;						// para sair do switch e voltar ao menu
			case SAIR_DO_PROGRAMA:
				cout << "Sair realmente? (S ou N): ";
				cin >> cOpcaoOper;			// op��o do operador
				if(cOpcaoOper == 's' || cOpcaoOper == 'S')			// sair realmente
				{	// vai sair realmente
					fclose(fdQuartos);								// fechar o arquivo de quartos
					return;											// volta ao sistema operacional
				}
				break;												// voltar ao menu do operador
			default:
				// Avisar que foi escolhida uma op��o errada
				cout << "\nOp��o errada!!!" << endl;
				PAUSA;
		} // switch
	} // while(true)
} // main
