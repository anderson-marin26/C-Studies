// Hotel.cpp - Programa de Hotel para prova de Linguagem de Programação - 23/09/2015
// FATEC - Mogi das Cruzes
#include "Hotel.h"
// Função principal
void main(void)
{
	int  i, j,								// indices genéricos
		iIndQuarto,							// para calcular o índice do quarto em função do
											//  andar e o quarto dentro do andar
		nQtdeAndares,						// para receber a quantidade de andares do hotel
		nQtdeQuartosPorAndar,				// para receber a quantidade de quartos por andar
		nQtdeTotal,							// quantidade total de quartos do hotel
		nAndarHotel,						// para receber o número do andar
		nQuartoHotel;						// para receber o número do quarto dentro do andar
	char cOpcaoOper,						// local para receber a opção escolhida do menu
		cNomeHospede[41],					// local para receber o nome do hóspede do hotel
		cWork[200],							// para formatação de sprintf
		cNomeAluno[] = "Preencher o seu nome";
	double dValor;							// local para receber o valor dos serviços do hotel
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
	setlocale(LC_ALL, "portuguese_brazil");
	// comandos para estabelecer o numero de casas decimais
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);						// duas casas decimais

	// <<<< 01 >>>>
	// Pedir a quantidade de andares e quartos por andares do hotel ou zeros para cancelar a
	//	execução do programa
	// A quantidade de andares não pode ser menor que QTDE_MINIMA_ANDARES e não pode ser maior
	//	que a QUANTIDADE_MAXIMA_ANDARES
	// A quantidade de quartos por andar não pode ser menor que QTDE_MINIMA_QUARTOS_ANDAR
	//  ou maior que QUANTIDADE_MAXIMA_QUARTOS.
	//
	// Inicializar o vetor vetLivreOcupado fazendo com que todos os quartos estejam livres e 
	//		associar a cada quarto o valor correspondente da diária de acordo com o andar do
	//		mesmo de acordo com que foi definido no Hotel.h
	// loop para solicitação de quantidade de andares
	do
	{
		cout << "Informe a quantidade de andares entre " << QTDE_MINIMA_ANDARES 
			<< " e " << QUANTIDADE_MAXIMA_ANDARES << endl
			<< "ou zeros para cancelar a execução do programa: ";
		cin >> nQtdeAndares;
		if(nQtdeAndares <= 0)				// vai abortar?
			return;							// retorna ao Sistema Operacional
	} while(nQtdeAndares < QTDE_MINIMA_ANDARES ||
		nQtdeAndares > QUANTIDADE_MAXIMA_ANDARES);
	// foi informado uma quantidade de andares válida
	// loop para solicitação da quantidade de quartos por andar
	do
	{
		cout << "Informe a quantidade de quartos por andar entre " << QTDE_MINIMA_QUARTOS_ANDAR
			<< " e " << QUANTIDADE_MAXIMA_QUARTOS << endl
			<< "Ou zeros para cancelar a execução do programa: ";
		cin >> nQtdeQuartosPorAndar;
		if(nQtdeQuartosPorAndar <= 0)			// abortar?
			return;								// volta ao Sistema Operacional
	}while(nQtdeQuartosPorAndar < QTDE_MINIMA_QUARTOS_ANDAR ||
		nQtdeQuartosPorAndar > QUANTIDADE_MAXIMA_QUARTOS);
	// loop para iniciar o vetor de quartos livres e ocupados e indicar a diária de cada quarto
	//	dependendo do seu andar 
	nQtdeTotal = nQtdeAndares * nQtdeQuartosPorAndar;
	for(i = 0, nAndarHotel = 1; i < nQtdeTotal; )			// loop total do hotel
	{
		for(j = 0; j < nQtdeQuartosPorAndar; j++, i++)		// loop por andar
		{
			vetLivreOcupado[i] = false;						// todos os quartos são livres
			switch(nAndarHotel)								// avalia o andar
			{
				case 1:										// primeiro andar
				case 2:										// segundo andar
					vetVlrDiaria[i] = DIARIA_QUARTO_SIMPLES; // diária de quarto simples
					break;
				case 3:
				case 4:
					vetVlrDiaria[i] = DIARIA_QUARTO_MEDIO;	// diária de quarto médio
					break;
				case 5:
				case 6:
				case 7:
				case 8:
					vetVlrDiaria[i] = DIARIA_QUARTO_SUPER;	// diaria de quarto super
					break;
				default:
					vetVlrDiaria[i] = DIARIA_QUARTO_SUITE;  // os demais são suites
					break;									// obrigatório em outras linguagens
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
			"\tFATEC-MC - Sistema de Hotel %02d/%02d/%04d às %02d:%02d:%02d\n\t\tOperador: %s Turma: noite",
			stTime.wDay, stTime.wMonth, stTime.wYear,
			stTime.wHour, stTime.wMinute, stTime.wSecond,
			cNomeAluno);
		cout << cWork << endl;
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
				// <<<< 02 >>>>
				// 1 - Chamar a função PedirAndarQuarto passando os endereço de nAndarHotel para receber
				//		o número do andar e o endereço de nQuartoHotel para receber o número do quarto no
				//			andar, quantidade de andares e quartos por andar que foram configurados e
				//			indicar que a transação é "Check-in de hóspede"
				//		Se retornar false cancelar a transação e voltar ao menu
				// 2 - Se retornou true indicando que foram informados andar e quarto no andar válido
				//		calcular o iIndQuarto em função do andar e quarto no andar informados.
				// 3 - Verificar se o quarto já está ocupado e se estiver exibir ao operador que o
				//		quarto está ocupado e o nome do hóspede que está ocupando o quarto, dar uma
				//		pausa para o operador puder ler e voltar ao menu.
				// 4 - Pedir o nome do hóspede considerando que tem nome e sobrenome
				// 5 - Zerar o total de diárias do quarto que está sendo ocupado
				// 6 - Indicar que este quarto está ocupado e voltar ao menu

				// pedir o andar e quarto
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, nQtdeAndares, nQtdeQuartosPorAndar,
					"Check_in de hóspede"))							// cancelou a transação
					break;											// sai do switch e vai ao menu
				iIndQuarto = CalcularIndice(nAndarHotel, nQuartoHotel, nQtdeQuartosPorAndar);
				if(vetLivreOcupado[iIndQuarto])				// ocupado?
				{	// quarto está ocupado
					cout << "Andar: " << nAndarHotel << " Quarto: " << nQuartoHotel 
						<< " Hóspede: " << vetNomeHospede[iIndQuarto] << endl
						<< "Já está ocupado!" << endl;
					PAUSA;
					break;									// volta ao menu
				}
				cout << "Nome do hóspede: ";
				cin.ignore(1, EOF);			// ignorar a tecla Enter de uma int anterior
				cin.getline(vetNomeHospede[iIndQuarto], EXTEN_NOME, '\n');
				vetTotalDiarias[iIndQuarto] = 0.0;			// zerar o total de diárias do quarto
				vetLivreOcupado[iIndQuarto] = true;			// indica que o quarto está ocupado
				break;						// para sair do switch e voltar ao menu

			case FAZER_CHECK_OUT:
				// <<<< 03 >>>>
				// 1 - Pedir o andar e o quarto da mesma forma que no item anterior indicando que a transação 
				//		é "Check-out"
				// 2 - Verificar se a transação foi cancelada e voltar ao menu
				// 3 - Verificar se o quarto está ocupado e se estiver indicar o nome o hóspede que está
				//		ocupando e indicar que o quarto foi desocupado 
				//		dar uma pausa para o operador poder verificar e
				//		indicar que o quarto está livre
				// 4 - Se o quarto não estiver ocupado avisar ao operador e voltar ao menu
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
				// <<<< 06 >>>> 
				// 1 - Pedir Andar e Quarto conforme itens anteriores
				// 2 - Verificar se o quarto está ocupado e se não estiver, avisar ao operador e voltar ao menu
				// 3 - Se estiver ocupado listar os dados do quarto indicando nome do hóspede e valor da
				//		diária do quarto
				// pedir o andar e quarto
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, nQtdeAndares, nQtdeQuartosPorAndar,
					"Exibir dados do quarto"))						// cancelou a transação
					break;											// sai do switch e vai ao menu
				iIndQuarto = CalcularIndice(nAndarHotel, nQuartoHotel, nQtdeQuartosPorAndar);
				if(vetLivreOcupado[iIndQuarto])				// ocupado?
				{	// quarto está ocupado
					cout << "Andar: " << nAndarHotel << " Quarto: " << nQuartoHotel 
						<< " Hóspede: " << vetNomeHospede[iIndQuarto] << endl
						<< "Diária: " << vetVlrDiaria[iIndQuarto] << endl;
				}
				else
					cout << "Andar: " << nAndarHotel << "Quarto: " << nQuartoHotel << endl
					<< "Não está ocupado!" << endl;
				PAUSA;
				break;						// para sair do switch e voltar ao menu
			case SAIR_DO_PROGRAMA:
				cout << "Deseja sair realmente? (S ou N): ";
				cin >> cOpcaoOper;
				if(cOpcaoOper == 'S' || cOpcaoOper == 's')		// sair realmente?
					return;
				break;						// para sair do switch e decidir se vai sair realmente
			default:
				// Avisar que foi escolhida uma opção errada
				cout << "\nOpcao errada!!!\nDigite Enter para continuar.......";
				PAUSA;
		} // switch
	} // while(true)
} // main
