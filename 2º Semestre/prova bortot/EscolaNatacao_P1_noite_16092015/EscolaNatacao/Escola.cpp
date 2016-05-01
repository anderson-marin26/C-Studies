// Programa Escola de Nata��o - Prova B1 - 16/09/2015 - Turma da Noite
//
//Biblioteca
#include "Escola.h"
//
//	Entry point do programa
//
void main(void)
{
	int nPeriodo,									// periodo da aula de nata��o
		nRaia,										// raia da piscina
		iIndRaia,									// indice da raia calculada
		nQtdeParentes,								// quantidade de parentes para desconto
		nQtdeRaiasPiscina,							// para receber a quantidade de raias que a piscina tem
		nQtdeTotalDeRaias,							// qtde total de raias nos tr�s per�odos
		i;											// �ndice gen�rico

	double dValorMensalidade,						// para calcular a mensalidade
		dSomaMensalidades = 0;						// para somar as mensalidades

	char cOpcao,									// opcao do operador
		cNomeAluno[] = "Marco Aur�lio Macei Duarte",
		cRA_Aluno[] = "1840481413018",
		cSobrenome[TAMANHO_SOBRENOME + 1],			// para receber o sobrenome
		cWork[200];									// para sprintf

	SYSTEMTIME stTime;								// para data e hora do sistema

	// vetores dos periodos e raias das piscinas
	char vetNomesPeriodos[QTDE_PERIODOS][7] = {"Manh�", "Tarde", "Noite"};
	
	// vetor que indica se raia livre ou ocupada - true - indica ocupada, false - indica que a raia est� livre
	bool vetRaiaLivreOcupada[QTDE_PERIODOS * QTDE_MAXIMA_RAIAS_PISCINA];

	// vetor de sobrenomes dos alunos matriculados
	char vetSobrenomesAlunos[QTDE_PERIODOS * QTDE_MAXIMA_RAIAS_PISCINA][TAMANHO_SOBRENOME + 1];

	double vetMensalidades[QTDE_PERIODOS * QTDE_MAXIMA_RAIAS_PISCINA]; 

	// para duas casas decimais nos valores
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	setlocale(LC_ALL, "portuguese_brazil");		// para acentua��o brasileira

	//Loop para pedir a qtde de raias da piscina
	do
	{
		cout << "informe a quantidade de raias da piscina entre " << QTDE_MINIMA_RAIAS_PISCINA << " e " 
			<< QTDE_MAXIMA_RAIAS_PISCINA << endl
			<< "Ou zero para cancelar: ";
		cin >> nQtdeRaiasPiscina;

		if(nQtdeRaiasPiscina == 0)			//Vai cancelar?
		{
			cout << endl << "\t\t\tOpera��o cancelada!" << endl << endl;
			PAUSA;
			return;							//Retorna ao Sistema Operacional
		}//Fim do if de canceelamneto de execu��o

	}while(nQtdeRaiasPiscina < QTDE_MINIMA_RAIAS_PISCINA || nQtdeRaiasPiscina > QTDE_MAXIMA_RAIAS_PISCINA);

	//Calculando a qtde total de raias
	nQtdeTotalDeRaias = nQtdeRaiasPiscina * QTDE_PERIODOS;

	//Loop de indica��o de raias livres, ou seja, false
	for(i = 0; i < nQtdeTotalDeRaias; i++)
	{
		vetRaiaLivreOcupada[i] = false;
	}//Fim do for

	//	Loop Infinito
	while(true)
	{
		LIMPAR_TELA;

		GetLocalTime(&stTime);						// data e hora do sistema

		sprintf_s(cWork, sizeof(cWork),
			"\tFATEC - Escola de Nata��o %02d/%02d/%04d �s %02d:%02d:%02d\n\tOperador: %s Matr�cula: %s",
			stTime.wDay, stTime.wMonth, stTime.wYear, stTime.wHour, stTime.wMinute, stTime.wSecond,
			cNomeAluno, cRA_Aluno);

		cout << cWork << endl << endl;

		// exibir o menu
		cout << MATRICULAR_ALUNO << " - Matricular aluno em um per�odo desejado" << endl
			<< CANCELAR_MATRICULA << " - Cancelar a matr�cula de um aluno" << endl
			<< LISTAR_PERIODO << " - Listar os alunos de um dado per�odo" << endl
			<< SAIR_DO_PROGRAMA << " - Sair do programa" << endl
			<< "\tSelecione: ";
		cin  >> cOpcao;

		cOpcao = toupper(cOpcao);					// converte para mai�scula

		switch(cOpcao)								// avalia a op��o escolhida
		{
			case MATRICULAR_ALUNO:
				//Pedir um per�odo v�lido (desejado pelo aluno)
				nPeriodo = PedirPeriodo(QTDE_PERIODOS, "Matricular Aluno");
				if(nPeriodo == 0)					// cancelou a a��o?
					break;							// cai fora do switch

				//Chamar a fun��o que v� se tem raia livre neste periodo
				nRaia = BuscarRaiaLivreNoPeriodo(vetRaiaLivreOcupada, nPeriodo, nQtdeRaiasPiscina);

				// verificar se n�o tem raia livre neste periodo
				if(nRaia == -1)					// n�o tem raia livre?
				{	// n�o tem raia livre neste per�odo
					cout << "N�o tem vaga no periodo da " << vetNomesPeriodos[nPeriodo - 1] << endl << endl;
					PAUSA;
					break;
				}//Fim do if de verifica��o

				// calcular o indice desta raia para saber a posi��o dentro dos vetores
				iIndRaia = nRaia + ((nPeriodo - 1) * nQtdeRaiasPiscina);

				//Recebendo o sobrenome do aluno 
				cin.ignore(1, EOF);
				cout << endl << "Informe o sobrenome do aluno: ";
				cin.getline(cSobrenome, TAMANHO_SOBRENOME, '\n');

				cSobrenome[0] = toupper(cSobrenome[0]);			//Convertendo o primeiro caractere em mai�sculo

				// loop para c�lculo da mensalidade do aluno
				for(i = nQtdeParentes = 0, dValorMensalidade = VALOR_MENSALIDADE; i < nQtdeTotalDeRaias; i++)
				{
					if(vetRaiaLivreOcupada[i] == true &&
						(strcmp(cSobrenome, &vetSobrenomesAlunos[i][0]) == 0))				// mesmo sobrenome?

						nQtdeParentes++;

					if(nQtdeParentes > 4)			//S� vai contar at� 4 parentes com o mesmo nome
						nQtdeParentes = 4;
				} // for

				// sabemos quantos parentes tem
				//  Calcular o valor da mensalidade e armazenar no valor da
				//	mensalidade dentro do vetor de mensalidades
				vetMensalidades[iIndRaia] = VALOR_MENSALIDADE - (VALOR_MENSALIDADE * 
					(nQtdeParentes * VALOR_DESCONTO_POR_PARENTE) / 100);

				//Indicar que a raia no �ndice calculado est� ocupada
				vetRaiaLivreOcupada[iIndRaia] = true;						// indica raia ocupada

				//Copiando o sobrenome para o vetor de sobrenomes de acordo com o �ndice calculado
				strcpy(&vetSobrenomesAlunos[iIndRaia][0], cSobrenome);

				cout << endl << "Informa��es da Matr�cula" << endl
					<< "Aluno: " << vetSobrenomesAlunos[iIndRaia] << endl
					<< "Per�odo: " << vetNomesPeriodos[nPeriodo - 1] << endl
					<< "Raia: " << nRaia  + 1 << endl
					<< "Mensalidade: " << vetMensalidades[iIndRaia] << endl;
				PAUSA;
				break;								// cai fora do switch

			case CANCELAR_MATRICULA:
				//Pedir per�odo e raia para cancelar a matr�cula
				if(!PedirPeriodoRaia(&nPeriodo, &nRaia, QTDE_PERIODOS, nQtdeRaiasPiscina, "Cancelar Matr�cula"))
				{
					cout << endl << "\t\t\tOpera��o Cancelada!" << endl << endl;
					PAUSA;
					break;
				}//Fim do if de verifica��o de per�odo e raias

				// calcular o indice desta raia para saber a posi��o dentro dos vetores
				iIndRaia = (nRaia + ((nPeriodo - 1) * nQtdeRaiasPiscina)) - 1;

				//Verificar se a raia est� livre
				if(vetRaiaLivreOcupada[iIndRaia] == false)			//Raia est� livre?
				{
					//Est� livre
					cout << endl << "Raia livre para o per�odo informado. Opera��o cancelada!" << endl << endl;
					PAUSA;
					break;
				}//Fim da verifica��o

				//Est� ocupada. Exibir dados da matr�cula
				sprintf_s(cWork, sizeof(cWork), "Aluno: %s \nPer�odo: %s \nRaia: %d \nMensalidade: %.2f", 
					vetSobrenomesAlunos[iIndRaia], vetNomesPeriodos[nPeriodo - 1],
					nRaia, vetMensalidades[iIndRaia]);
				cout << endl << cWork << endl << endl;

				//Pedir confirma��o de cancelamento de matr�cula
				cout << "\tDeseja realmente cancelar esta matr�cula? (S - sim ou N - n�o): ";
				cin >> cOpcao;

				if(cOpcao == 'S' || cOpcao == 's')
				{
					vetRaiaLivreOcupada[iIndRaia] = false;				//Matr�cula cancelada
					cout << endl << endl << "\t\tMatr�cula cancelada com sucesso!" << endl << endl;
					PAUSA;
					break;
				}//Fim do if de cancelamento
				
				//Se n�o quer cancelar a matr�cula
				cout << endl << endl << "\t\t\tOpera��o cancelada!" << endl << endl;
				PAUSA;

				break;								// cai fora do switch

			case LISTAR_PERIODO:				
				//Pedir um per�odo v�lido (desejado pelo aluno)
				nPeriodo = PedirPeriodo(QTDE_PERIODOS, "Listar Per�odo");
				if(nPeriodo == 0)					// cancelou a a��o?
					break;							// cai fora do switch

				cout << endl << "Listagem do per�odo da "<<  vetNomesPeriodos[nPeriodo - 1] << endl << endl;

				//Exibir dados das matr�culas
				for(i = ((nPeriodo - 1) * nQtdeRaiasPiscina); i < nQtdeRaiasPiscina * nPeriodo; i++)
				{
					//Verificar e exibir somente raias ocupadas
					if(vetRaiaLivreOcupada[i] == true)
					{
						sprintf_s(cWork, sizeof(cWork), "Aluno: %s \nPer�odo: %s \nRaia: %d \nMensalidade: %.2f", 
							vetSobrenomesAlunos[i], vetNomesPeriodos[nPeriodo - 1],
							i + 1 - ((nPeriodo - 1) * nQtdeRaiasPiscina), vetMensalidades[i]);
							cout << endl << cWork << endl << endl;

							//Soma de todas as mensalidades do per�odo
							dSomaMensalidades += vetMensalidades[i];
					}//Fim do if de verifica��o
				}//Fim do for de listar
				
				//Exibir a soma das mensalidades do per�odo informado
				if(dSomaMensalidades > 0)				//Somente ter� valor se o per�odo possuir matr�culas
				{
					cout << "\tA soma das mensalidades do per�odo informado �: " << dSomaMensalidades << endl << endl;

					//Zerar a soma das mensalidades
					dSomaMensalidades = 0;					//Para ser usado em outra listagem
				}//Fim do if de exibir soma das matr�culas
				else
				{
					cout << "\t\tN�o h� matr�culas para o per�odo informado!" << endl << endl;
					PAUSA;
					break;
				}//Sem matr�culas

				cout << "\t\t\tFim da listagem do per�odo!" << endl << endl;
				
				PAUSA;
				break;								// cai fora do switch

			case SAIR_DO_PROGRAMA:					
				cout << endl << "\t\t\tVai sair realmente? (S ou N): ";
				cin >> cOpcao;

				if(cOpcao == 's' || cOpcao == 'S')	// sair realmente?
					return;								//Retorna ao Sistema Operacional
				break;								// cai fora do switch

			default:
				cout << endl << "\t\t\tOp��o inv�lida!" << endl;
				PAUSA;
		} // switch
	} // while
} // main
// 
// Fun��es do Programa
//
// Fun��o que pede um per�odo v�lido e uma raia da piscina v�lida
// Par�metros:
//	Entrada: int *ptrPeriodo - ponteiro para receber o per�odo desejado
//			 int *ptrRaia - ponteiro para receber a raia da piscina desejada
//			 int nQtdePeriodos - quantidade de per�odos da Escola de Nata��o
//			 int nQtRaiasPiscina - quantidade de raias que tem a piscina da Escola de Nata��o
//			 char *ptrAcao - ponteiro de um string que cont�m a a��o que est� sendo executada
//	Retorno: bool - true - indica que foi informado um per�odo e uma raia v�lidos
//					false - indica que o operador desistiu da a��o que iria executar:
bool PedirPeriodoRaia(int *ptrPeriodo, int *ptrRaia, 
					  int nQtdePeriodos, int nQtRaiasPiscina, char *ptrAcao)
{
	
	do
	{
		cout << "\n\t" << ptrAcao << endl;

		cout << "Informe o per�odo desejado " << endl 
			<<"\t1 - Manh�" << endl 
			<< "\t2 - Tarde" << endl 
			<< "\t3 - Noite" << endl
			<< "Ou zero para cancelar est� a��o: ";
		cin >> *(ptrPeriodo);

		if(*(ptrPeriodo) == 0)				// cancelou a a��o
			return false;					// indica que cancelou

	}while(*(ptrPeriodo) < PERIODO_MANHA ||
		*(ptrPeriodo) > nQtdePeriodos);
	do
	{
		cout << endl << "Informe a raia entre 1 e " << nQtRaiasPiscina << endl
			<< "Ou zero para cancelar a execu��o desta a��o: ";
		cin >> *(ptrRaia);

		if(*(ptrRaia) == 0)					// cancelou a a��o?
			return false;

	}while(*(ptrRaia) < 1 ||
		*(ptrRaia) > nQtRaiasPiscina);

	return true;							// indica que foi digitado um per�odo e uma raia
}
//
// Fun��o que verifica se tem uma raia livre no per�odo desejado
//	Par�metros:
//		Entrada: bool *ptrVetLivreOcup - ponteiro do vetor de bool que indica se a raia est� 
//										 livre ou ocupada
//				 int nPeriodo - per�odo desejado
//				 int nQtRaiasPiscina - quantidade de raia que a piscina tem
//		Retorno: int - N�mero da raia que est� livre ou zero se n�o existir nenhuma
//						raia livre no per�odo desejado
int BuscarRaiaLivreNoPeriodo(bool *ptrVetLivreOcup, int nPeriodo, int nQtRaiasPiscina)
{
	int i, j;							// indices gen�ricos

	for(i = (nPeriodo - 1) * nQtRaiasPiscina, j = 0; j < nQtRaiasPiscina; j++, i++)
	{
		if(!*(ptrVetLivreOcup + i))		// raia livre?
			return j;				// retornar a raia livre
	}
	return -1;							// n�o tem raia livre no per�odo
}

// Fun��o que pede um per�odo v�lido ou zero para cancelar a a��o
//	Par�metros:
//		Entrada: int nQtdePeriodos - quantidade de per�odos da escola de nata��o
//				 char *ptrAcao - ponteiro para uma string que contem a a��o sendo executada
//		Retorno: int - o per�odo desejado ou zero para cancelar a a��o
int PedirPeriodo(int nQtdePeriodos, char *ptrAcao)
{
	int nPeriodo;									//Para receber o periodo

	//Loop para pedir o per�odo
	do
	{
		cout << "\n\t" << ptrAcao << endl;

		cout << "Informe o per�odo desejado " << endl 
			<< "\t1 - Manh�" << endl 
			<< "\t2 - Tarde" << endl 
			<< "\t3 - Noite" << endl
			<< "Ou zero para cancelar est� a��o: ";
		cin >> nPeriodo;

		if(nPeriodo < 0 || nPeriodo > nQtdePeriodos)
		{
			cout << endl << endl << "\t\t\tPer�odo inv�lido!" << endl << endl;
			PAUSA;
		}//Fim do if

	}while(nPeriodo < 0 || nPeriodo > nQtdePeriodos);

	// devolver o que foi v�lido digitado
	return nPeriodo;								// devolve o digitado
}