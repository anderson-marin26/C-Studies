// Programa Escola de Natação - Prova B1 - 16/09/2015 - Turma da Noite
//
//Biblioteca
#include "Escola.h"
//
//	Entry point do programa
//
void main(void)
{
	int nPeriodo,									// periodo da aula de natação
		nRaia,										// raia da piscina
		iIndRaia,									// indice da raia calculada
		nQtdeParentes,								// quantidade de parentes para desconto
		nQtdeRaiasPiscina,							// para receber a quantidade de raias que a piscina tem
		nQtdeTotalDeRaias,							// qtde total de raias nos três períodos
		i;											// índice genérico

	double dValorMensalidade,						// para calcular a mensalidade
		dSomaMensalidades = 0;						// para somar as mensalidades

	char cOpcao,									// opcao do operador
		cNomeAluno[] = "Marco Aurélio Macei Duarte",
		cRA_Aluno[] = "1840481413018",
		cSobrenome[TAMANHO_SOBRENOME + 1],			// para receber o sobrenome
		cWork[200];									// para sprintf

	SYSTEMTIME stTime;								// para data e hora do sistema

	// vetores dos periodos e raias das piscinas
	char vetNomesPeriodos[QTDE_PERIODOS][7] = {"Manhã", "Tarde", "Noite"};
	
	// vetor que indica se raia livre ou ocupada - true - indica ocupada, false - indica que a raia está livre
	bool vetRaiaLivreOcupada[QTDE_PERIODOS * QTDE_MAXIMA_RAIAS_PISCINA];

	// vetor de sobrenomes dos alunos matriculados
	char vetSobrenomesAlunos[QTDE_PERIODOS * QTDE_MAXIMA_RAIAS_PISCINA][TAMANHO_SOBRENOME + 1];

	double vetMensalidades[QTDE_PERIODOS * QTDE_MAXIMA_RAIAS_PISCINA]; 

	// para duas casas decimais nos valores
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	setlocale(LC_ALL, "portuguese_brazil");		// para acentuação brasileira

	//Loop para pedir a qtde de raias da piscina
	do
	{
		cout << "informe a quantidade de raias da piscina entre " << QTDE_MINIMA_RAIAS_PISCINA << " e " 
			<< QTDE_MAXIMA_RAIAS_PISCINA << endl
			<< "Ou zero para cancelar: ";
		cin >> nQtdeRaiasPiscina;

		if(nQtdeRaiasPiscina == 0)			//Vai cancelar?
		{
			cout << endl << "\t\t\tOperação cancelada!" << endl << endl;
			PAUSA;
			return;							//Retorna ao Sistema Operacional
		}//Fim do if de canceelamneto de execução

	}while(nQtdeRaiasPiscina < QTDE_MINIMA_RAIAS_PISCINA || nQtdeRaiasPiscina > QTDE_MAXIMA_RAIAS_PISCINA);

	//Calculando a qtde total de raias
	nQtdeTotalDeRaias = nQtdeRaiasPiscina * QTDE_PERIODOS;

	//Loop de indicação de raias livres, ou seja, false
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
			"\tFATEC - Escola de Natação %02d/%02d/%04d às %02d:%02d:%02d\n\tOperador: %s Matrícula: %s",
			stTime.wDay, stTime.wMonth, stTime.wYear, stTime.wHour, stTime.wMinute, stTime.wSecond,
			cNomeAluno, cRA_Aluno);

		cout << cWork << endl << endl;

		// exibir o menu
		cout << MATRICULAR_ALUNO << " - Matricular aluno em um período desejado" << endl
			<< CANCELAR_MATRICULA << " - Cancelar a matrícula de um aluno" << endl
			<< LISTAR_PERIODO << " - Listar os alunos de um dado período" << endl
			<< SAIR_DO_PROGRAMA << " - Sair do programa" << endl
			<< "\tSelecione: ";
		cin  >> cOpcao;

		cOpcao = toupper(cOpcao);					// converte para maiúscula

		switch(cOpcao)								// avalia a opção escolhida
		{
			case MATRICULAR_ALUNO:
				//Pedir um período válido (desejado pelo aluno)
				nPeriodo = PedirPeriodo(QTDE_PERIODOS, "Matricular Aluno");
				if(nPeriodo == 0)					// cancelou a ação?
					break;							// cai fora do switch

				//Chamar a função que vê se tem raia livre neste periodo
				nRaia = BuscarRaiaLivreNoPeriodo(vetRaiaLivreOcupada, nPeriodo, nQtdeRaiasPiscina);

				// verificar se não tem raia livre neste periodo
				if(nRaia == -1)					// não tem raia livre?
				{	// não tem raia livre neste período
					cout << "Não tem vaga no periodo da " << vetNomesPeriodos[nPeriodo - 1] << endl << endl;
					PAUSA;
					break;
				}//Fim do if de verificação

				// calcular o indice desta raia para saber a posição dentro dos vetores
				iIndRaia = nRaia + ((nPeriodo - 1) * nQtdeRaiasPiscina);

				//Recebendo o sobrenome do aluno 
				cin.ignore(1, EOF);
				cout << endl << "Informe o sobrenome do aluno: ";
				cin.getline(cSobrenome, TAMANHO_SOBRENOME, '\n');

				cSobrenome[0] = toupper(cSobrenome[0]);			//Convertendo o primeiro caractere em maiúsculo

				// loop para cálculo da mensalidade do aluno
				for(i = nQtdeParentes = 0, dValorMensalidade = VALOR_MENSALIDADE; i < nQtdeTotalDeRaias; i++)
				{
					if(vetRaiaLivreOcupada[i] == true &&
						(strcmp(cSobrenome, &vetSobrenomesAlunos[i][0]) == 0))				// mesmo sobrenome?

						nQtdeParentes++;

					if(nQtdeParentes > 4)			//Só vai contar até 4 parentes com o mesmo nome
						nQtdeParentes = 4;
				} // for

				// sabemos quantos parentes tem
				//  Calcular o valor da mensalidade e armazenar no valor da
				//	mensalidade dentro do vetor de mensalidades
				vetMensalidades[iIndRaia] = VALOR_MENSALIDADE - (VALOR_MENSALIDADE * 
					(nQtdeParentes * VALOR_DESCONTO_POR_PARENTE) / 100);

				//Indicar que a raia no índice calculado está ocupada
				vetRaiaLivreOcupada[iIndRaia] = true;						// indica raia ocupada

				//Copiando o sobrenome para o vetor de sobrenomes de acordo com o índice calculado
				strcpy(&vetSobrenomesAlunos[iIndRaia][0], cSobrenome);

				cout << endl << "Informações da Matrícula" << endl
					<< "Aluno: " << vetSobrenomesAlunos[iIndRaia] << endl
					<< "Período: " << vetNomesPeriodos[nPeriodo - 1] << endl
					<< "Raia: " << nRaia  + 1 << endl
					<< "Mensalidade: " << vetMensalidades[iIndRaia] << endl;
				PAUSA;
				break;								// cai fora do switch

			case CANCELAR_MATRICULA:
				//Pedir período e raia para cancelar a matrícula
				if(!PedirPeriodoRaia(&nPeriodo, &nRaia, QTDE_PERIODOS, nQtdeRaiasPiscina, "Cancelar Matrícula"))
				{
					cout << endl << "\t\t\tOperação Cancelada!" << endl << endl;
					PAUSA;
					break;
				}//Fim do if de verificação de período e raias

				// calcular o indice desta raia para saber a posição dentro dos vetores
				iIndRaia = (nRaia + ((nPeriodo - 1) * nQtdeRaiasPiscina)) - 1;

				//Verificar se a raia está livre
				if(vetRaiaLivreOcupada[iIndRaia] == false)			//Raia está livre?
				{
					//Está livre
					cout << endl << "Raia livre para o período informado. Operação cancelada!" << endl << endl;
					PAUSA;
					break;
				}//Fim da verificação

				//Está ocupada. Exibir dados da matrícula
				sprintf_s(cWork, sizeof(cWork), "Aluno: %s \nPeríodo: %s \nRaia: %d \nMensalidade: %.2f", 
					vetSobrenomesAlunos[iIndRaia], vetNomesPeriodos[nPeriodo - 1],
					nRaia, vetMensalidades[iIndRaia]);
				cout << endl << cWork << endl << endl;

				//Pedir confirmação de cancelamento de matrícula
				cout << "\tDeseja realmente cancelar esta matrícula? (S - sim ou N - não): ";
				cin >> cOpcao;

				if(cOpcao == 'S' || cOpcao == 's')
				{
					vetRaiaLivreOcupada[iIndRaia] = false;				//Matrícula cancelada
					cout << endl << endl << "\t\tMatrícula cancelada com sucesso!" << endl << endl;
					PAUSA;
					break;
				}//Fim do if de cancelamento
				
				//Se não quer cancelar a matrícula
				cout << endl << endl << "\t\t\tOperação cancelada!" << endl << endl;
				PAUSA;

				break;								// cai fora do switch

			case LISTAR_PERIODO:				
				//Pedir um período válido (desejado pelo aluno)
				nPeriodo = PedirPeriodo(QTDE_PERIODOS, "Listar Período");
				if(nPeriodo == 0)					// cancelou a ação?
					break;							// cai fora do switch

				cout << endl << "Listagem do período da "<<  vetNomesPeriodos[nPeriodo - 1] << endl << endl;

				//Exibir dados das matrículas
				for(i = ((nPeriodo - 1) * nQtdeRaiasPiscina); i < nQtdeRaiasPiscina * nPeriodo; i++)
				{
					//Verificar e exibir somente raias ocupadas
					if(vetRaiaLivreOcupada[i] == true)
					{
						sprintf_s(cWork, sizeof(cWork), "Aluno: %s \nPeríodo: %s \nRaia: %d \nMensalidade: %.2f", 
							vetSobrenomesAlunos[i], vetNomesPeriodos[nPeriodo - 1],
							i + 1 - ((nPeriodo - 1) * nQtdeRaiasPiscina), vetMensalidades[i]);
							cout << endl << cWork << endl << endl;

							//Soma de todas as mensalidades do período
							dSomaMensalidades += vetMensalidades[i];
					}//Fim do if de verificação
				}//Fim do for de listar
				
				//Exibir a soma das mensalidades do período informado
				if(dSomaMensalidades > 0)				//Somente terá valor se o período possuir matrículas
				{
					cout << "\tA soma das mensalidades do período informado é: " << dSomaMensalidades << endl << endl;

					//Zerar a soma das mensalidades
					dSomaMensalidades = 0;					//Para ser usado em outra listagem
				}//Fim do if de exibir soma das matrículas
				else
				{
					cout << "\t\tNão há matrículas para o período informado!" << endl << endl;
					PAUSA;
					break;
				}//Sem matrículas

				cout << "\t\t\tFim da listagem do período!" << endl << endl;
				
				PAUSA;
				break;								// cai fora do switch

			case SAIR_DO_PROGRAMA:					
				cout << endl << "\t\t\tVai sair realmente? (S ou N): ";
				cin >> cOpcao;

				if(cOpcao == 's' || cOpcao == 'S')	// sair realmente?
					return;								//Retorna ao Sistema Operacional
				break;								// cai fora do switch

			default:
				cout << endl << "\t\t\tOpção inválida!" << endl;
				PAUSA;
		} // switch
	} // while
} // main
// 
// Funções do Programa
//
// Função que pede um período válido e uma raia da piscina válida
// Parâmetros:
//	Entrada: int *ptrPeriodo - ponteiro para receber o período desejado
//			 int *ptrRaia - ponteiro para receber a raia da piscina desejada
//			 int nQtdePeriodos - quantidade de períodos da Escola de Natação
//			 int nQtRaiasPiscina - quantidade de raias que tem a piscina da Escola de Natação
//			 char *ptrAcao - ponteiro de um string que contém a ação que está sendo executada
//	Retorno: bool - true - indica que foi informado um período e uma raia válidos
//					false - indica que o operador desistiu da ação que iria executar:
bool PedirPeriodoRaia(int *ptrPeriodo, int *ptrRaia, 
					  int nQtdePeriodos, int nQtRaiasPiscina, char *ptrAcao)
{
	
	do
	{
		cout << "\n\t" << ptrAcao << endl;

		cout << "Informe o período desejado " << endl 
			<<"\t1 - Manhã" << endl 
			<< "\t2 - Tarde" << endl 
			<< "\t3 - Noite" << endl
			<< "Ou zero para cancelar está ação: ";
		cin >> *(ptrPeriodo);

		if(*(ptrPeriodo) == 0)				// cancelou a ação
			return false;					// indica que cancelou

	}while(*(ptrPeriodo) < PERIODO_MANHA ||
		*(ptrPeriodo) > nQtdePeriodos);
	do
	{
		cout << endl << "Informe a raia entre 1 e " << nQtRaiasPiscina << endl
			<< "Ou zero para cancelar a execução desta ação: ";
		cin >> *(ptrRaia);

		if(*(ptrRaia) == 0)					// cancelou a ação?
			return false;

	}while(*(ptrRaia) < 1 ||
		*(ptrRaia) > nQtRaiasPiscina);

	return true;							// indica que foi digitado um período e uma raia
}
//
// Função que verifica se tem uma raia livre no período desejado
//	Parâmetros:
//		Entrada: bool *ptrVetLivreOcup - ponteiro do vetor de bool que indica se a raia está 
//										 livre ou ocupada
//				 int nPeriodo - período desejado
//				 int nQtRaiasPiscina - quantidade de raia que a piscina tem
//		Retorno: int - Número da raia que está livre ou zero se não existir nenhuma
//						raia livre no período desejado
int BuscarRaiaLivreNoPeriodo(bool *ptrVetLivreOcup, int nPeriodo, int nQtRaiasPiscina)
{
	int i, j;							// indices genéricos

	for(i = (nPeriodo - 1) * nQtRaiasPiscina, j = 0; j < nQtRaiasPiscina; j++, i++)
	{
		if(!*(ptrVetLivreOcup + i))		// raia livre?
			return j;				// retornar a raia livre
	}
	return -1;							// não tem raia livre no período
}

// Função que pede um período válido ou zero para cancelar a ação
//	Parâmetros:
//		Entrada: int nQtdePeriodos - quantidade de períodos da escola de natação
//				 char *ptrAcao - ponteiro para uma string que contem a ação sendo executada
//		Retorno: int - o período desejado ou zero para cancelar a ação
int PedirPeriodo(int nQtdePeriodos, char *ptrAcao)
{
	int nPeriodo;									//Para receber o periodo

	//Loop para pedir o período
	do
	{
		cout << "\n\t" << ptrAcao << endl;

		cout << "Informe o período desejado " << endl 
			<< "\t1 - Manhã" << endl 
			<< "\t2 - Tarde" << endl 
			<< "\t3 - Noite" << endl
			<< "Ou zero para cancelar está ação: ";
		cin >> nPeriodo;

		if(nPeriodo < 0 || nPeriodo > nQtdePeriodos)
		{
			cout << endl << endl << "\t\t\tPeríodo inválido!" << endl << endl;
			PAUSA;
		}//Fim do if

	}while(nPeriodo < 0 || nPeriodo > nQtdePeriodos);

	// devolver o que foi válido digitado
	return nPeriodo;								// devolve o digitado
}