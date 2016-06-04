// Programa Escola de Nata��o - Prova N2 - 01/06/2016 - Turma da Tarde
//
#include "Escola.h"
//	Entry point do programa
//
void main(void)
{
	int nPeriodo,								// periodo da aula de nata��o
		nRaia,									// raia da piscina
		nPosicionalRaia,						// posicional da raia dentro do arquivo de raias
		nQtdeParentes,							// quantidade de parentes para desconto
		nQtdeTotalDeRaias,						// qtde total de raias nos tr�s per�odos
		i, j;									// �ndices gen�ricos
	FILE *fdQuantidade,							// file descriptor para o arquivo de quantidade de raias da piscina
		*fdRaia;								// file descriptor da raia da piscina
	RAIA stRaia;								// struct para conter os dados de uma raia
	QTDE_RAIAS stQtRaias;						// struct para conter os dados da qtde raias da piscina
	double dValorMensalidade;					// para calcular a mensalidade
	char cOpcao,								// opcao do operador
		cNomeAluno[] = "Preencher com seu nome", // para conter o nome do aluno que est� fazendo a prova
		cWork[200];								// para sprintf_s
	SYSTEMTIME stTime;							// para data e hora do sistema
	char vetNomesPeriodos[QTDE_PERIODOS][7] =
	{"Manh�", "Tarde", "Noite"};
	// para duas casas decimais nos valores
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	setlocale(LC_ALL, "portuguese_brazil");		// para acentua��o brasileira
	// <<<1>>> - Digitar o seu nome na vari�vel cNomeAluno.
	// <<<2>>> - Tratamento inicial dos arquivos de quantidade e raias.
	//	2.1 - Abrir o arquivo de quantidades em modo r+b e testar se ele existe.
	//	2.2 - Se ele n�o existir o arquivo de quantidades:
	//		2.2.1 - Abrir o arquivo de quantidades em modo w+b e testar se foi aberto com sucesso.
	//		2.2.2 - Se o arquivo n�o foi aberto com sucesso:
	//			2.2.2.1 - Avisar o operador e abortar o programa.
	//		2.2.3 - Se o arquivo foi aberto com sucesso
	//			2.2.3.1 - Fazer um loop para obter uma quantidade de raias da piscina v�lida
	//						porque tem um m�nimo e m�ximo no .h. Essa quantidade tem que ser
	//						armazenada na stQtRaias
	//			2.2.3.2 - Gravar stQtRaias no arquivo de quantidades e fechar o arquivo.
	//		2.2.4 - Abrir o arquivo de raias em modo w+b e testar se foi aberto com sucesso
	//			2.2.4.1 - Se houve erro de abertura avisar o operador e abortar o programa
	//			2.2.4.2 - Se o arquivo foi aberto com sucesso fazer um loop para gravar o
	//					  registro de cada raia (stRaia) indicando o per�odo e a raia 
	//						1 e 1 - Manh� raia 1
	//						1 e 2 - Manh� raia 2 .....
	//						1 e qtde raias da piscina - Manh� e raia stQtRaias.nQtdeRaias
	//						2 e 1 - Tarde raia 1
	//						2 e 2 - Tarde raia 2
	//						2 e qtde raias da piscina - Tarde e raia stQtRaias.nQtdeRaias
	//						Idem para o per�odo da noite....
	//					  Para cada raia a ser gravada indicar que a raia n�o est� ocupada.
	//			2.2.4.3 - Se houver erro de grava��o fechar o arquivo de raias, avisar o
	//					  operador e abortar a execu��o do programa
	//	
	//	2.3 - Se o arquivo de quantidades existir:
	//		2.3.1 - Ler a quantidade para stQtRaias e fechar o arquivo.
	//		2.3.2 - Abrir o arquivo de raias em modo r+b e testar se foi aberto com sucesso
	//			2.3.2.1 - Se houve erro de abertura avisar ao operador e abortar a execu��o do programa
	//			2.3.2.2 - Se o arquivo foi aberto com sucesso ir para o menu do operador


	//	Loop Infinito
	while(true)
	{
		LIMPAR_TELA;
		GetLocalTime(&stTime);						// data e hora do sistema
		sprintf_s(cWork, sizeof(cWork), 
			"\n\tFATEC-Escola de Nata��o %02d/%02d/%04d �s %02d:%02d:%02d\n\tOperador: %s",
			stTime.wDay, stTime.wMonth, stTime.wYear, 
			stTime.wHour, stTime.wMinute, stTime.wSecond,
			cNomeAluno);
		cout << cWork << endl;
		// exibir o menu
		cout << MATRICULAR_ALUNO << " - Matricular aluno em um per�odo desejado" << endl
			<< CANCELAR_MATRICULA << " - Cancelar a matr�cula de um aluno" << endl
			<< EXIBIR_DADOS_ALUNO << " - Exibir os dados de um aluno" << endl
			<< LISTAR_PERIODO << " - Listar os alunos de um dado per�odo" << endl
			<< SAIR_DO_PROGRAMA << " - Sair do programa" << endl
			<< "\tSelecione: ";
		cin  >> cOpcao;
		cOpcao = toupper(cOpcao);					// converte para mai�scula
		switch(cOpcao)								// avalia a op��o escolhida
		{
			case MATRICULAR_ALUNO:
				// grande parte j� codificado 

				nPeriodo = PedirPeriodo(QTDE_PERIODOS, "Matricular Aluno");
				if(nPeriodo == 0)					// cancelou a a��o?
					break;							// cai fora do switch
				// chamar a fun��o que v� se tem raia livre neste periodo
				nRaia = BuscarRaiaLivreNoPeriodo(nPeriodo, stQtRaias.nQtdeRaias, &stRaia, &fdRaia);
				// verificar se n�o tem raia livre neste periodo
				if(nRaia == 0)						// n�o tem raia livre?
				{	// n�o tem raia livre neste per�odo
					cout << "N�o tem vaga no periodo da " << vetNomesPeriodos[nPeriodo - 1] << endl;
					PAUSA;
					break;
				}
				cin.ignore(1, EOF);
				cout << "Informe o nome do aluno: ";
				cin.getline(stRaia.cNome, EXTENSAO_NOME, '\n');
				cout << "Informe o sobrenome do aluno: ";
				cin.getline(stRaia.cSobreNome, EXTENSAO_SOBRENOME, '\n');
				// vai calcular o valor da mensalidade em fun��o da quantidade de parentes da
				//	mesma fam�lia
				nQtdeParentes = VerificaParentes(stRaia.cSobreNome, &fdRaia);

				// calcular o valor da mensalidade sabendo que o valor b�sico est� em 
				//		VALOR_MENSALIDADE e a cada parente (nQtdeParentes) � dado um
				// desconto de 10% at� no m�ximo de 40% se tiver 4 parentes com o mesmo
				//	sobrenome). Copiar o valor calculado em stRaia.dVlrMensalidade
				
				//
				// calcular o indice desta raia para saber o posicional da raia dentro do arquivo de
				//	raias - � fun��o do periodo, quantidade de raias da piscina e a raia da piscina
				// armazenar este c�lculo em nPosicionalRaia
				stRaia.flgRaiaOcupada = true;				// indica que a raia est� ocupada
				if(!GravaPosicional(nPosicionalRaia, &stRaia, &fdRaia)) // erro de grava��o?
				{
					cout << "Erro de grava��o!" << endl;
					PAUSA;
				}
				break;								// cai fora do switch e volta ao menu
			case CANCELAR_MATRICULA:				
				// <<<9>>>  Chamar a fun��o que pede o periodo e a raia indicando que a a��o �
				//			Cancelamento de Matr�cula
				//		
				//			Calcular o posicional para est� raia.
				//			Chamar a fun��o que l� posicional
				//			Verificar se a raia est� ocupada
				//			Se n�o estiver ocupada avisar ao operador e voltar ao menu
				//			Se estiver ocupada, exibir todos os dados da raia e
				//				pedir a confirma��o com S ou N.
				//			Se o operador confirmar com S ou s, gravar a raia com a fun��o
				//				gravar posicional.
				//			voltar ao menu principal
				break;								// cai fora do switch e volta ao menu
			case EXIBIR_DADOS_ALUNO:
				// <<<10>>>  Chamar a fun��o que pede o periodo e a raia indicando que a a��o �
				//			Mostrar dados do aluno
				//			Calcular o posicional para est� raia.
				//			Chamar a fun��o que l� posicional
				//			Verificar se a raia est� ocupada
				//			Se n�o estiver ocupada avisar ao operador e voltar ao menu
				//			Se estiver ocupada, exibir todos os dados da raia e dar uma pausa
				break;								// voltar ao menu
			case LISTAR_PERIODO:				
				// <<<15>>> Pedir um per�odo v�lido ou zero para cancelar a a��o de listar
				//			Se foi informado um per�odo v�lido listar todos as raias ocupadas
				//			no seguinte formato:
				//				Listagem das raias do periodo: ppppppp
				//			Raia Sobrenome  Mensalidade 
				//			 RR  SSSSSSSSS  MMMMMM,MM	
				//			.....
				//			.....
				//					       Total das Mensalidades: TTTTTT,TT
				//			Onde: PPPPPPP - periodo: "Manh�", "Tarde" ou "Noite"
				//				  RR - raia ocupada ( 1 a Qtde de Raias da Piscina)
				//				  SSSSSSSSS - sobrenome do aluno
				//				  MMMMM - valor da mensalidade
				//				  TTTTTTT = somat�ria das mensalidades dos alunos matriculados
				//		Para essa listagem considerar o seguinte:
				//		Calcular o posicional para a primeira raia do periodo.
				//		Fazer um looping lendo posicional de cada raia do periodo e
				//			listar no formato acima pedido se a raia estiver ocupada.
				//		Fazer a somat�ria de mensalidades deste per�odo.
				break;								// cai fora do switch
			case SAIR_DO_PROGRAMA:					
				cout << "Vai sair realmente? (S ou N): ";
				cin >> cOpcao;
				if(cOpcao == 's' || cOpcao == 'S')	// sair realmente?
				{
					// fclose(fdRaia);				// ativar quando o programa estiver em 
													// condi��o de testes.
					return;			
				}
				break;								// cai fora do switch
			default:
				cout << "Op��o inv�lida!" << endl;
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
		cout << "Informe o per�odo desejado " << endl <<
			"\t1 - Manh�" << endl << "\t2 - Tarde" << endl << "\t3 - Noite" << endl
			<< "Ou zero para cancelar est� a��o: ";
		cin >> *(ptrPeriodo);
		if(*(ptrPeriodo) == 0)				// cancelou a a��o
			return false;					// indica que cancelou
	}while(*(ptrPeriodo) < PERIODO_MANHA ||
		*(ptrPeriodo) > nQtdePeriodos);
	do
	{
		cout << "Informe a raia entre 1 e " << nQtRaiasPiscina << endl
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
//		Entrada: int nPeriodo - per�odo desejado
//				 int nQtRaiasPiscina - quantidade de raia que a piscina tem
//				 RAIA *ptrStRaia - ponteiro para uma struct a conter os dados da raia 
//									livre.
//				 FILE **fdRaia - file descriptor do arquivo de raias
//		Retorno: int - N�mero da raia que est� livre ou zero se n�o existir nenhuma
//						raia livre no per�odo desejado
int BuscarRaiaLivreNoPeriodo(int nPeriodo, int nQtRaiasPiscina, RAIA *ptrStRaia, FILE **fdRaia)
{
	RAIA stRaia;						// buffer de leitura de cada raia

	// em fun��o do per�odo desejado e a quantidade de raias da piscina
	//	calcular o posicional da primeira raia do periodo desejado.
	// posicionar com o fseek na primeira raia do per�odo ( se der erro - devolve zero)
	// ficar em looping limitado a qtde de raias da piscina
	// lendo sequencialmente at� encontrar uma raia livre
	// Se encontrou uma raia livre devolve o seu n�mero e copie os dados desta raia em
	//		uma struct apontada por ptrStRaia
	// ou devolve zero se n�o encontrou nenhuma livre.
	
	return 0;							// para n�o dar erro
}

// Fun��o que pede um per�odo v�lido ou zero para cancelar a a��o
//	Par�metros:
//		Entrada: int nQtdePeriodos - quantidade de per�odos da escola de nata��o
//				 char *ptrAcao - ponteiro para uma string que contem a a��o sendo executada
//		Retorno: int - o per�odo desejado ou zero para cancelar a a��o
int PedirPeriodo(int nQtdePeriodos, char *ptrAcao)
{
	int nPeriodo;									// para receber o periodo
	do
	{
		cout << "\n\t" << ptrAcao << endl;
		cout << "Informe o per�odo desejado " << endl <<
			"\t1 - Manh�" << endl << "\t2 - Tarde" << endl << "\t3 - Noite" << endl
			<< "Ou zero para cancelar est� a��o: ";
		cin >> nPeriodo;
	}while(nPeriodo < 0 || nPeriodo > nQtdePeriodos);
	// devolver o que foi v�lido digitado
	return nPeriodo;								// devolve o digitado
}
// Fun��o que verifica se tem parentes com o mesmo sobrenome
//	Par�metros:
//		Entrada: char *ptrSobrenome - ponteiro para um string que cont�m o sobrenome
//				 FILE **fdRaia - ponteiro para o file descriptor do arquivo de raias
//		Retorno: int - contendo a quantidade de parentes com o mesmo sobrenome (m�ximo de 4).
int VerificaParentes(char *ptrSobrenome, FILE **fdRaia)
{
	RAIA stRaia;						// buffer de leitura para cada raia do arquivo
	int nContador = 0;					// contador de parentes com mesmo sobrenome
	// posicionar o arquivo de raias na primeira raia do primeiro per�odo (posicional zero).
	// fazer um loop de leitura sequencial at� o fim do arquivo ou at� encontrar 4 parentes
	// com o mesmo sobrenome (o m�ximo de desconto ser� de 40%)
	// a cada raia lida verificar se est� ocupada e se tem o mesmo sobrenome
	// se tiver o mesmo sobrenome somar um no nContador e verificar se chegou a 4.
	// se chegou a 4 retornar este valor.
	// se chegou ao fim do arquivo retornar o nContador.
	return nContador;					// retornar o que foi encontrado
}

// Fun��o que grava uma raia posicional no arquivo de raias
//	Par�metros:
//		Entrada: int nPosicional - posicional para grava��o da raia
//				 RAIA *ptrStRaia - ponteiro para a struct que contem os dados a serem gravados
//				 FILE **fdRaia - file descriptor do arquivo de raias.
//		Retorno: bool - true a grava��o foi realizada OK
//						false - se houve erro de fseek ou fwrite
bool GravaPosicional(int nPosicional, RAIA *ptrStRaia, FILE **fdRaia)
{
	
	// posicionar na raia atrav�s do fseek
	// gravar os dados que foram passados com o fwrite.
	return true;								// para n�o dar erro de compila��o ????????????
}

// Fun��o que l� uma raia posicional do arquivo de raias
//	Par�metros:
//		Entrada: int nPosicional - posicional para leitura da raia
//				 RAIA *ptrStRaia - ponteiro para a struct que receber� os dados a serem lidos
//				 FILE **fdRaia - file descriptor do arquivo de raias.
//		Retorno: bool - true a leitura foi realizada OK e os dados est�o na struct informada
//						false - se houve erro de fseek ou fread_s
bool LerPosicional(int nPosicional, RAIA *ptrStRaia, FILE **fdRaia)
{
	
	// posicionar na raia atrav�s do fseek
	// ler os dados para a struct que foi passada com fread_s
	return true;								// para n�o dar erro de compila��o ????????????
}
