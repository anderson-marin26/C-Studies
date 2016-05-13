// Hotel.cpp - Programa de Hotel para prova de Linguagem de Programação - 23/09/2015
// FATEC - Mogi das Cruzes
//
#include "Hotel.h"
//
// Função principal
//
void main(void)
{
	int  i,										// indice genérico
		iIndQuarto,								// para calcular o índice do quarto em função do
												//  andar e o quarto dentro do andar
		nQtdeAndares,							// para receber a quantidade de andares do hotel
		nQtdeQuartosPorAndar,					// para receber a quantidade de quartos por andar
		nAndarHotel,							// para receber o número do andar
		nQuartoHotel;							// para receber o número do quarto dentro do andar

	char cOpcaoOper,							// local para receber a opção escolhida do menu
		cWork[200],								// para formatação de sprintf
		cNomeAluno[] = "Marco Aurélio Macei Duarte";

	double dValor = 0;							// local para receber o valor dos serviços do hotel

	// vetores do sistema de hotel
	//
	// o vetor abaixo indica quando o quarto dentro de um andar  está livre ou ocupado
	//		true - indica que o quarto está ocupado
	bool vetLivreOcupado[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS];

	// o vetor bi-dimensional abaixo indica o nome do hospede que está ocupando o quarto
	char vetNomeHospede[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS][EXTEN_NOME];

	// o vetor abaixo indica o valor da diária do quarto
	double vetVlrDiaria[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS];

	// o vetor abaixo indica o valor total de diárias do quarto
	double vetTotalDiarias[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS];

	SYSTEMTIME stTime;						// para buscar data e hora

	setlocale(LC_ALL, "portuguese_brazil");					//Caracteres especiais e acentuação PT - BR

	// comandos para estabelecer o numero de casas decimais
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);						// duas casas decimais

	//Loop para pedir a qtde de andares do hotel
	do
	{
		cout << "Informe a quantidade de andares do hotel entre " << QTDE_MINIMA_ANDARES << " e " 
			<< QUANTIDADE_MAXIMA_ANDARES << endl
			<< "Ou zero para cancelar: ";
		cin >> nQtdeAndares;			//Recebendo a qtde de andares

		if(nQtdeAndares == 0)			//Vai cancelar?
		{
			cout << endl << "\t\t\tOperação cancelada!" << endl << endl;
			PAUSA;
			return;							//Retorna ao Sistema Operacional
		}//Fim do if de canceelamneto de execução

	}while(nQtdeAndares < QTDE_MINIMA_ANDARES || nQtdeAndares > QUANTIDADE_MAXIMA_ANDARES);

	//Loop para pedir a qtde de quartos do hotel
	do
	{
		cout << endl << "Informe a quantidade de quartos do hotel entre " << QTDE_MINIMA_QUARTOS_ANDAR << " e " 
			<< QUANTIDADE_MAXIMA_QUARTOS << endl
			<< "Ou zero para cancelar: ";
		cin >> nQtdeQuartosPorAndar;			//Recebendo a qtde de quartos

		if(nQtdeQuartosPorAndar == 0)			//Vai cancelar?
		{
			cout << endl << "\t\t\tOperação cancelada!" << endl << endl;
			PAUSA;
			return;							//Retorna ao Sistema Operacional
		}//Fim do if de canceelamneto de execução

	}while(nQtdeQuartosPorAndar < QTDE_MINIMA_QUARTOS_ANDAR || nQtdeQuartosPorAndar > QUANTIDADE_MAXIMA_QUARTOS);

	//Indicar que todos os quartos estão desocupados
	//False - indica desocupado
	//Associar diária com o quarto e andar correspondente
	for(i = 0; i < nQtdeAndares * nQtdeQuartosPorAndar; i++)
	{	
		vetLivreOcupado[i] = false;				//Indicando quarto desocupado

		//Inicializando os valores dos quartos
		if(i >= (nQtdeQuartosPorAndar * 8))					//Do 9º a qtde de andares
			vetVlrDiaria[i] = DIARIA_QUARTO_SUITE;
		if(i < (nQtdeQuartosPorAndar * 8))					//Do 5º ao 8º andar
			vetVlrDiaria[i] = DIARIA_QUARTO_SUPER;
		if(i < (nQtdeQuartosPorAndar * 4))					//Do 3º ao 4º andar
			vetVlrDiaria[i] = DIARIA_QUARTO_MEDIO;
		if(i < (nQtdeQuartosPorAndar * 2))					//Do 1º ao 2º andar
			vetVlrDiaria[i] = DIARIA_QUARTO_SIMPLES;
	}//Fim do for valores quartos

	while(true)							// loop infinito
	{
		LIMPAR_TELA;					//Limpar a tela

		GetLocalTime(&stTime);			//Obtendo data e hora do sistema

		sprintf_s(cWork, sizeof(cWork), 
			"\tFATEC-MC - Sistema de Hotel %02d/%02d/%04d às %02d:%02d:%02d\n\tOperador: %s Turma: Noite",
			stTime.wDay, stTime.wMonth, stTime.wYear, stTime.wHour, stTime.wMinute, stTime.wSecond,
			cNomeAluno);
		
		cout << cWork << endl << endl;				//Exibir o sprintf

		// Mostrar o menu de opções para o operador
		cout << "I - Check-in de um hospede" << endl;
		cout << "O - Check-out de um hospede" << endl;
		cout << "S - Lancar servicos" << endl;
		cout << "D - Lancar diarias em todos os quartos ocupados" << endl;
		cout << "L - Listar um quarto" << endl;
		cout << "X - Sair do programa" << endl;
		cout << "\tSelecione: ";

		cin	 >> cOpcaoOper;					// opção escolhida pelo operador

		cOpcaoOper = toupper(cOpcaoOper);	// converte para upper case a opção escolhida

		switch(cOpcaoOper)					// avaliar a opção que foi escolhida pelo operador
		{
			case FAZER_CHECK_IN:

				//Pedir quarto e andar
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, nQtdeAndares, nQtdeQuartosPorAndar, "Check-in de Hóspede"))
				{
					cout << endl << "\t\t\tOperação cancelada!" << endl << endl;
					PAUSA;
					break;					//Retorna ao menu
				}//Fim de verificação de andar e quarto

				//Se true
				//Calcular o iIndQuarto em função do andar e quarto no andar informados.
				iIndQuarto = nQuartoHotel + ((nAndarHotel - 1) * nQtdeQuartosPorAndar) - 1;		

				//Quarto está ocupado?
				if(vetLivreOcupado[iIndQuarto] == true)
				{
					cout << endl << "\t\t\tQuarto ocupado!" << endl << endl
						<< "Nome do hóspede: " << vetNomeHospede[iIndQuarto] << endl;
					PAUSA;
					break;					//Retorna ao Menu
				}

				//Quarto está desocupado
				//Recebendo o nome do hóspede
				cin.ignore(1, EOF);
				cout << endl << "Informe o nome completo do hóspede: ";
				cin.getline(vetNomeHospede[iIndQuarto], EXTEN_NOME, '\n');

				//Zerando o total de diárias do quarto
				vetTotalDiarias[iIndQuarto] = 0;

				//Indicar que o quarto agora está ocupado, ou seja, true
				vetLivreOcupado[iIndQuarto] = true;

				break;						// para sair do switch e voltar ao menu

			case FAZER_CHECK_OUT:

				//Pedir quarto e andar
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, nQtdeAndares, nQtdeQuartosPorAndar, "Check-out de Hóspede"))
				{
					cout << endl << "\t\t\tOperação cancelada!" << endl << endl;
					PAUSA;
					break;					//Retorna ao menu
				}//Fim de verificação de andar e quarto

				//Calcular o iIndQuarto em função do andar e quarto no andar informados.
				iIndQuarto = nQuartoHotel + ((nAndarHotel - 1) * nQtdeQuartosPorAndar) - 1;

				//Quarto está ocupado?
				if(vetLivreOcupado[iIndQuarto] == true)
				{
					cout << endl << "\t\t\tQuarto ocupado!" << endl << endl
						<< "Nome do hóspede: " << vetNomeHospede[iIndQuarto] << endl;
					PAUSA;

					vetLivreOcupado[iIndQuarto] = false;			//Quarto desocupado

					cout << endl << "\t\tCheck-out realizado com sucesso!" << endl << endl;
					PAUSA;
					break;					//Retorna ao Menu
				}

				//Quarto desocupado
				cout << endl << "\t\t\tQuarto desocupado!" << endl << endl;
				PAUSA;
				break;						// para sair do switch e voltar ao menu

			case LANCAR_SERVICO:
				// <<<< 04 >>>> -
				// @@@@@@@@ Não Codificar este item @@@@@@@@@@@@@@


				// 1 - Pedir o Andar e Quarto da mesma forma que foi feito nos itens anteriores
				// 2 - Verificar se o quarto está ocupado e se não estiver avisar ao operador e
				//		voltar ao menu.
				//			Utilizar a função:  VerificarSeQuartoLivreOuOcupado
				// 3 - Pedir o tipo de serviço que tem que ser um dos que estão no arquivo hotel.h
				//		exceto a diária que lançada de outra forma.
				//		Se não for informado um serviço válido, pedir novamente ao operador
				// 4 - Pedir o valor do serviço 
				// 5 - Chamar a função que lança o serviço no quarto informado
				break;						// para sair do switch e voltar ao menu
			case LANCAR_DIARIA:
				// <<<< 05 >>>> 

				// @@@@@@@@@@@@@@ não codificar está transação @@@@@@@@@@@
				// 1 - Pedir a data e hora do sistema e apresentar ao operador
				// 2 - Confirmar com o operador se ele realmente deseja lançar as diárias no horário
				//		apresentado
				// 3 - Se o operador confirmar percorrer o vetor de quartos livres e ocupados e 
				//			somar uma diária a mais no total de diárias deste quarto.
				// 4 - Caso o operador não confirme voltar ao menu.
				//		Lançar diária significa pegar o valor da diária que foi associada ao quarto e
				//			somar no total das diárias e do quarto.
				// Para buscar a data e hora do sistema utilizar o seguinte comando:
				//		GetLocalTime(&stTime);
				//		stTime.wDay, stTime.wHour e etc. tem o valores correspondentes a data e hora

				break;						// para sair do switch e voltar ao menu

			case LISTAR_UM_QUARTO:

				//Pedir quarto e andar
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, nQtdeAndares, nQtdeQuartosPorAndar, "Listar um Quarto"))
				{
					cout << endl << "\t\t\tOperação cancelada!" << endl << endl;
					PAUSA;
					break;					//Retorna ao menu
				}//Fim de verificação de andar e quarto

				//Calcular o iIndQuarto em função do andar e quarto no andar informados.
				iIndQuarto = nQuartoHotel + ((nAndarHotel - 1) * nQtdeQuartosPorAndar) - 1;

				//Quarto está ocupado?
				if(vetLivreOcupado[iIndQuarto] == true)		//Quarto ocupado
				{
					cout << endl << "Nome do Hóspede: " << vetNomeHospede[iIndQuarto] << endl
						<< "Valor da diária do quarto: " << vetVlrDiaria[iIndQuarto] << endl << endl;
					PAUSA;
					break;					//Retorna ao Menu
				}

				//Quarto desocupado
				cout << endl << "\t\t\tQuarto desocupado!" << endl << endl;
				PAUSA;

				break;						// para sair do switch e voltar ao menu

			case SAIR_DO_PROGRAMA:
				cout << endl << "\t\t\tDeseja sair realmente? (S ou N): ";
				cin >> cOpcaoOper;

				if(cOpcaoOper == 'S' || cOpcaoOper == 's')		// sair realmente?
				{
					cout << endl << "\t\t\tSistema encerrado!" << endl << endl;
					PAUSA;
					return;					//Retorna ao sistema operacional
				}

				break;						// para sair do switch e decidir se vai sair realmente

			default:
				// Avisar que foi escolhida uma opção errada
				cout << "\nOpcao errada!!!\nDigite Enter para continuar.......";
				system("pause > NULL");
		} // switch
	} // while(true)
} // main
