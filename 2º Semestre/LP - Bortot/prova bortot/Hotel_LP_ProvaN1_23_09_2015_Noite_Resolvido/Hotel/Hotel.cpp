// Hotel.cpp - Programa de Hotel para prova de Linguagem de Programa��o - 23/09/2015
// FATEC - Mogi das Cruzes
#include "Hotel.h"
// Fun��o principal
void main(void)
{
	int  i, j,								// indices gen�ricos
		iIndQuarto,							// para calcular o �ndice do quarto em fun��o do
											//  andar e o quarto dentro do andar
		nQtdeAndares,						// para receber a quantidade de andares do hotel
		nQtdeQuartosPorAndar,				// para receber a quantidade de quartos por andar
		nQtdeTotal,							// quantidade total de quartos do hotel
		nAndarHotel,						// para receber o n�mero do andar
		nQuartoHotel;						// para receber o n�mero do quarto dentro do andar
	char cOpcaoOper,						// local para receber a op��o escolhida do menu
		cNomeHospede[41],					// local para receber o nome do h�spede do hotel
		cWork[200],							// para formata��o de sprintf
		cNomeAluno[] = "Preencher o seu nome";
	double dValor;							// local para receber o valor dos servi�os do hotel
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
	setlocale(LC_ALL, "portuguese_brazil");
	// comandos para estabelecer o numero de casas decimais
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);						// duas casas decimais

	// <<<< 01 >>>>
	// Pedir a quantidade de andares e quartos por andares do hotel ou zeros para cancelar a
	//	execu��o do programa
	// A quantidade de andares n�o pode ser menor que QTDE_MINIMA_ANDARES e n�o pode ser maior
	//	que a QUANTIDADE_MAXIMA_ANDARES
	// A quantidade de quartos por andar n�o pode ser menor que QTDE_MINIMA_QUARTOS_ANDAR
	//  ou maior que QUANTIDADE_MAXIMA_QUARTOS.
	//
	// Inicializar o vetor vetLivreOcupado fazendo com que todos os quartos estejam livres e 
	//		associar a cada quarto o valor correspondente da di�ria de acordo com o andar do
	//		mesmo de acordo com que foi definido no Hotel.h
	// loop para solicita��o de quantidade de andares
	do
	{
		cout << "Informe a quantidade de andares entre " << QTDE_MINIMA_ANDARES 
			<< " e " << QUANTIDADE_MAXIMA_ANDARES << endl
			<< "ou zeros para cancelar a execu��o do programa: ";
		cin >> nQtdeAndares;
		if(nQtdeAndares <= 0)				// vai abortar?
			return;							// retorna ao Sistema Operacional
	} while(nQtdeAndares < QTDE_MINIMA_ANDARES ||
		nQtdeAndares > QUANTIDADE_MAXIMA_ANDARES);
	// foi informado uma quantidade de andares v�lida
	// loop para solicita��o da quantidade de quartos por andar
	do
	{
		cout << "Informe a quantidade de quartos por andar entre " << QTDE_MINIMA_QUARTOS_ANDAR
			<< " e " << QUANTIDADE_MAXIMA_QUARTOS << endl
			<< "Ou zeros para cancelar a execu��o do programa: ";
		cin >> nQtdeQuartosPorAndar;
		if(nQtdeQuartosPorAndar <= 0)			// abortar?
			return;								// volta ao Sistema Operacional
	}while(nQtdeQuartosPorAndar < QTDE_MINIMA_QUARTOS_ANDAR ||
		nQtdeQuartosPorAndar > QUANTIDADE_MAXIMA_QUARTOS);
	// loop para iniciar o vetor de quartos livres e ocupados e indicar a di�ria de cada quarto
	//	dependendo do seu andar 
	nQtdeTotal = nQtdeAndares * nQtdeQuartosPorAndar;
	for(i = 0, nAndarHotel = 1; i < nQtdeTotal; )			// loop total do hotel
	{
		for(j = 0; j < nQtdeQuartosPorAndar; j++, i++)		// loop por andar
		{
			vetLivreOcupado[i] = false;						// todos os quartos s�o livres
			switch(nAndarHotel)								// avalia o andar
			{
				case 1:										// primeiro andar
				case 2:										// segundo andar
					vetVlrDiaria[i] = DIARIA_QUARTO_SIMPLES; // di�ria de quarto simples
					break;
				case 3:
				case 4:
					vetVlrDiaria[i] = DIARIA_QUARTO_MEDIO;	// di�ria de quarto m�dio
					break;
				case 5:
				case 6:
				case 7:
				case 8:
					vetVlrDiaria[i] = DIARIA_QUARTO_SUPER;	// diaria de quarto super
					break;
				default:
					vetVlrDiaria[i] = DIARIA_QUARTO_SUITE;  // os demais s�o suites
					break;									// obrigat�rio em outras linguagens
			} // switch
		} // loop por andar
		nAndarHotel++;										// incrementa o andar
	} // for i
	//
	// loop infinito no menu
	//
	while(true)								// loop infinito
	{
		LIMPAR_TELA;
		GetLocalTime(&stTime);
		sprintf_s(cWork, sizeof(cWork), 
			"\tFATEC-MC - Sistema de Hotel %02d/%02d/%04d �s %02d:%02d:%02d\n\t\tOperador: %s Turma: noite",
			stTime.wDay, stTime.wMonth, stTime.wYear,
			stTime.wHour, stTime.wMinute, stTime.wSecond,
			cNomeAluno);
		cout << cWork << endl;
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
				// <<<< 02 >>>>
				// 1 - Chamar a fun��o PedirAndarQuarto passando os endere�o de nAndarHotel para receber
				//		o n�mero do andar e o endere�o de nQuartoHotel para receber o n�mero do quarto no
				//			andar, quantidade de andares e quartos por andar que foram configurados e
				//			indicar que a transa��o � "Check-in de h�spede"
				//		Se retornar false cancelar a transa��o e voltar ao menu
				// 2 - Se retornou true indicando que foram informados andar e quarto no andar v�lido
				//		calcular o iIndQuarto em fun��o do andar e quarto no andar informados.
				// 3 - Verificar se o quarto j� est� ocupado e se estiver exibir ao operador que o
				//		quarto est� ocupado e o nome do h�spede que est� ocupando o quarto, dar uma
				//		pausa para o operador puder ler e voltar ao menu.
				// 4 - Pedir o nome do h�spede considerando que tem nome e sobrenome
				// 5 - Zerar o total de di�rias do quarto que est� sendo ocupado
				// 6 - Indicar que este quarto est� ocupado e voltar ao menu

				// pedir o andar e quarto
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, nQtdeAndares, nQtdeQuartosPorAndar,
					"Check_in de h�spede"))							// cancelou a transa��o
					break;											// sai do switch e vai ao menu
				iIndQuarto = CalcularIndice(nAndarHotel, nQuartoHotel, nQtdeQuartosPorAndar);
				if(vetLivreOcupado[iIndQuarto])				// ocupado?
				{	// quarto est� ocupado
					cout << "Andar: " << nAndarHotel << " Quarto: " << nQuartoHotel 
						<< " H�spede: " << vetNomeHospede[iIndQuarto] << endl
						<< "J� est� ocupado!" << endl;
					PAUSA;
					break;									// volta ao menu
				}
				cout << "Nome do h�spede: ";
				cin.ignore(1, EOF);			// ignorar a tecla Enter de uma int anterior
				cin.getline(vetNomeHospede[iIndQuarto], EXTEN_NOME, '\n');
				vetTotalDiarias[iIndQuarto] = 0.0;			// zerar o total de di�rias do quarto
				vetLivreOcupado[iIndQuarto] = true;			// indica que o quarto est� ocupado
				break;						// para sair do switch e voltar ao menu

			case FAZER_CHECK_OUT:
				// <<<< 03 >>>>
				// 1 - Pedir o andar e o quarto da mesma forma que no item anterior indicando que a transa��o 
				//		� "Check-out"
				// 2 - Verificar se a transa��o foi cancelada e voltar ao menu
				// 3 - Verificar se o quarto est� ocupado e se estiver indicar o nome o h�spede que est�
				//		ocupando e indicar que o quarto foi desocupado 
				//		dar uma pausa para o operador poder verificar e
				//		indicar que o quarto est� livre
				// 4 - Se o quarto n�o estiver ocupado avisar ao operador e voltar ao menu
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
				// <<<< 06 >>>> 
				// 1 - Pedir Andar e Quarto conforme itens anteriores
				// 2 - Verificar se o quarto est� ocupado e se n�o estiver, avisar ao operador e voltar ao menu
				// 3 - Se estiver ocupado listar os dados do quarto indicando nome do h�spede e valor da
				//		di�ria do quarto
				// pedir o andar e quarto
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, nQtdeAndares, nQtdeQuartosPorAndar,
					"Exibir dados do quarto"))						// cancelou a transa��o
					break;											// sai do switch e vai ao menu
				iIndQuarto = CalcularIndice(nAndarHotel, nQuartoHotel, nQtdeQuartosPorAndar);
				if(vetLivreOcupado[iIndQuarto])				// ocupado?
				{	// quarto est� ocupado
					cout << "Andar: " << nAndarHotel << " Quarto: " << nQuartoHotel 
						<< " H�spede: " << vetNomeHospede[iIndQuarto] << endl
						<< "Di�ria: " << vetVlrDiaria[iIndQuarto] << endl;
				}
				else
					cout << "Andar: " << nAndarHotel << "Quarto: " << nQuartoHotel << endl
					<< "N�o est� ocupado!" << endl;
				PAUSA;
				break;						// para sair do switch e voltar ao menu
			case SAIR_DO_PROGRAMA:
				cout << "Deseja sair realmente? (S ou N): ";
				cin >> cOpcaoOper;
				if(cOpcaoOper == 'S' || cOpcaoOper == 's')		// sair realmente?
					return;
				break;						// para sair do switch e decidir se vai sair realmente
			default:
				// Avisar que foi escolhida uma op��o errada
				cout << "\nOpcao errada!!!\nDigite Enter para continuar.......";
				PAUSA;
		} // switch
	} // while(true)
} // main
