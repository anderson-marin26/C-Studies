// Hotel.cpp - Programa de Hotel para prova de Linguagem de Programa��o - 23/09/2015
// FATEC - Mogi das Cruzes
//
#include "Hotel.h"
//
// Fun��o principal
//
void main(void)
{
	int  i,										// indice gen�rico
		iIndQuarto,								// para calcular o �ndice do quarto em fun��o do
												//  andar e o quarto dentro do andar
		nQtdeAndares,							// para receber a quantidade de andares do hotel
		nQtdeQuartosPorAndar,					// para receber a quantidade de quartos por andar
		nAndarHotel,							// para receber o n�mero do andar
		nQuartoHotel;							// para receber o n�mero do quarto dentro do andar

	char cOpcaoOper,							// local para receber a op��o escolhida do menu
		cWork[200],								// para formata��o de sprintf
		cNomeAluno[] = "Marco Aur�lio Macei Duarte";

	double dValor = 0;							// local para receber o valor dos servi�os do hotel

	// vetores do sistema de hotel
	//
	// o vetor abaixo indica quando o quarto dentro de um andar  est� livre ou ocupado
	//		true - indica que o quarto est� ocupado
	bool vetLivreOcupado[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS];

	// o vetor bi-dimensional abaixo indica o nome do hospede que est� ocupando o quarto
	char vetNomeHospede[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS][EXTEN_NOME];

	// o vetor abaixo indica o valor da di�ria do quarto
	double vetVlrDiaria[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS];

	// o vetor abaixo indica o valor total de di�rias do quarto
	double vetTotalDiarias[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS];

	SYSTEMTIME stTime;						// para buscar data e hora

	setlocale(LC_ALL, "portuguese_brazil");					//Caracteres especiais e acentua��o PT - BR

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
			cout << endl << "\t\t\tOpera��o cancelada!" << endl << endl;
			PAUSA;
			return;							//Retorna ao Sistema Operacional
		}//Fim do if de canceelamneto de execu��o

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
			cout << endl << "\t\t\tOpera��o cancelada!" << endl << endl;
			PAUSA;
			return;							//Retorna ao Sistema Operacional
		}//Fim do if de canceelamneto de execu��o

	}while(nQtdeQuartosPorAndar < QTDE_MINIMA_QUARTOS_ANDAR || nQtdeQuartosPorAndar > QUANTIDADE_MAXIMA_QUARTOS);

	//Indicar que todos os quartos est�o desocupados
	//False - indica desocupado
	//Associar di�ria com o quarto e andar correspondente
	for(i = 0; i < nQtdeAndares * nQtdeQuartosPorAndar; i++)
	{	
		vetLivreOcupado[i] = false;				//Indicando quarto desocupado

		//Inicializando os valores dos quartos
		if(i >= (nQtdeQuartosPorAndar * 8))					//Do 9� a qtde de andares
			vetVlrDiaria[i] = DIARIA_QUARTO_SUITE;
		if(i < (nQtdeQuartosPorAndar * 8))					//Do 5� ao 8� andar
			vetVlrDiaria[i] = DIARIA_QUARTO_SUPER;
		if(i < (nQtdeQuartosPorAndar * 4))					//Do 3� ao 4� andar
			vetVlrDiaria[i] = DIARIA_QUARTO_MEDIO;
		if(i < (nQtdeQuartosPorAndar * 2))					//Do 1� ao 2� andar
			vetVlrDiaria[i] = DIARIA_QUARTO_SIMPLES;
	}//Fim do for valores quartos

	while(true)							// loop infinito
	{
		LIMPAR_TELA;					//Limpar a tela

		GetLocalTime(&stTime);			//Obtendo data e hora do sistema

		sprintf_s(cWork, sizeof(cWork), 
			"\tFATEC-MC - Sistema de Hotel %02d/%02d/%04d �s %02d:%02d:%02d\n\tOperador: %s Turma: Noite",
			stTime.wDay, stTime.wMonth, stTime.wYear, stTime.wHour, stTime.wMinute, stTime.wSecond,
			cNomeAluno);
		
		cout << cWork << endl << endl;				//Exibir o sprintf

		// Mostrar o menu de op��es para o operador
		cout << "I - Check-in de um hospede" << endl;
		cout << "O - Check-out de um hospede" << endl;
		cout << "S - Lancar servicos" << endl;
		cout << "D - Lancar diarias em todos os quartos ocupados" << endl;
		cout << "L - Listar um quarto" << endl;
		cout << "X - Sair do programa" << endl;
		cout << "\tSelecione: ";

		cin	 >> cOpcaoOper;					// op��o escolhida pelo operador

		cOpcaoOper = toupper(cOpcaoOper);	// converte para upper case a op��o escolhida

		switch(cOpcaoOper)					// avaliar a op��o que foi escolhida pelo operador
		{
			case FAZER_CHECK_IN:

				//Pedir quarto e andar
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, nQtdeAndares, nQtdeQuartosPorAndar, "Check-in de H�spede"))
				{
					cout << endl << "\t\t\tOpera��o cancelada!" << endl << endl;
					PAUSA;
					break;					//Retorna ao menu
				}//Fim de verifica��o de andar e quarto

				//Se true
				//Calcular o iIndQuarto em fun��o do andar e quarto no andar informados.
				iIndQuarto = nQuartoHotel + ((nAndarHotel - 1) * nQtdeQuartosPorAndar) - 1;		

				//Quarto est� ocupado?
				if(vetLivreOcupado[iIndQuarto] == true)
				{
					cout << endl << "\t\t\tQuarto ocupado!" << endl << endl
						<< "Nome do h�spede: " << vetNomeHospede[iIndQuarto] << endl;
					PAUSA;
					break;					//Retorna ao Menu
				}

				//Quarto est� desocupado
				//Recebendo o nome do h�spede
				cin.ignore(1, EOF);
				cout << endl << "Informe o nome completo do h�spede: ";
				cin.getline(vetNomeHospede[iIndQuarto], EXTEN_NOME, '\n');

				//Zerando o total de di�rias do quarto
				vetTotalDiarias[iIndQuarto] = 0;

				//Indicar que o quarto agora est� ocupado, ou seja, true
				vetLivreOcupado[iIndQuarto] = true;

				break;						// para sair do switch e voltar ao menu

			case FAZER_CHECK_OUT:

				//Pedir quarto e andar
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, nQtdeAndares, nQtdeQuartosPorAndar, "Check-out de H�spede"))
				{
					cout << endl << "\t\t\tOpera��o cancelada!" << endl << endl;
					PAUSA;
					break;					//Retorna ao menu
				}//Fim de verifica��o de andar e quarto

				//Calcular o iIndQuarto em fun��o do andar e quarto no andar informados.
				iIndQuarto = nQuartoHotel + ((nAndarHotel - 1) * nQtdeQuartosPorAndar) - 1;

				//Quarto est� ocupado?
				if(vetLivreOcupado[iIndQuarto] == true)
				{
					cout << endl << "\t\t\tQuarto ocupado!" << endl << endl
						<< "Nome do h�spede: " << vetNomeHospede[iIndQuarto] << endl;
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
				// @@@@@@@@ N�o Codificar este item @@@@@@@@@@@@@@


				// 1 - Pedir o Andar e Quarto da mesma forma que foi feito nos itens anteriores
				// 2 - Verificar se o quarto est� ocupado e se n�o estiver avisar ao operador e
				//		voltar ao menu.
				//			Utilizar a fun��o:  VerificarSeQuartoLivreOuOcupado
				// 3 - Pedir o tipo de servi�o que tem que ser um dos que est�o no arquivo hotel.h
				//		exceto a di�ria que lan�ada de outra forma.
				//		Se n�o for informado um servi�o v�lido, pedir novamente ao operador
				// 4 - Pedir o valor do servi�o 
				// 5 - Chamar a fun��o que lan�a o servi�o no quarto informado
				break;						// para sair do switch e voltar ao menu
			case LANCAR_DIARIA:
				// <<<< 05 >>>> 

				// @@@@@@@@@@@@@@ n�o codificar est� transa��o @@@@@@@@@@@
				// 1 - Pedir a data e hora do sistema e apresentar ao operador
				// 2 - Confirmar com o operador se ele realmente deseja lan�ar as di�rias no hor�rio
				//		apresentado
				// 3 - Se o operador confirmar percorrer o vetor de quartos livres e ocupados e 
				//			somar uma di�ria a mais no total de di�rias deste quarto.
				// 4 - Caso o operador n�o confirme voltar ao menu.
				//		Lan�ar di�ria significa pegar o valor da di�ria que foi associada ao quarto e
				//			somar no total das di�rias e do quarto.
				// Para buscar a data e hora do sistema utilizar o seguinte comando:
				//		GetLocalTime(&stTime);
				//		stTime.wDay, stTime.wHour e etc. tem o valores correspondentes a data e hora

				break;						// para sair do switch e voltar ao menu

			case LISTAR_UM_QUARTO:

				//Pedir quarto e andar
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, nQtdeAndares, nQtdeQuartosPorAndar, "Listar um Quarto"))
				{
					cout << endl << "\t\t\tOpera��o cancelada!" << endl << endl;
					PAUSA;
					break;					//Retorna ao menu
				}//Fim de verifica��o de andar e quarto

				//Calcular o iIndQuarto em fun��o do andar e quarto no andar informados.
				iIndQuarto = nQuartoHotel + ((nAndarHotel - 1) * nQtdeQuartosPorAndar) - 1;

				//Quarto est� ocupado?
				if(vetLivreOcupado[iIndQuarto] == true)		//Quarto ocupado
				{
					cout << endl << "Nome do H�spede: " << vetNomeHospede[iIndQuarto] << endl
						<< "Valor da di�ria do quarto: " << vetVlrDiaria[iIndQuarto] << endl << endl;
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
				// Avisar que foi escolhida uma op��o errada
				cout << "\nOpcao errada!!!\nDigite Enter para continuar.......";
				system("pause > NULL");
		} // switch
	} // while(true)
} // main
