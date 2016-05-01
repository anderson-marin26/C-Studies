//Programa Raul Gil com struct e menu
//30/03/2016 - Anderson Marin de Ramos - Fatec Mogi das Cruzes

#include "RaulGil.h"

//Entry point
void main(void) {
	int nQtdeCalouros,						//quantidade de calouros que ira cantar hoje
		nIndProx = 0,						//indice do proximo calouro
		nIndVencedor = 0,					//indice do calouro vencedor
		nNotaTrono = -1;					//nota do melhor calouro até o momento
	char cOpcao,							//opcao de escolha do operador
		cWork[200];							//formatacao do sprintf_s
	CALOURO stCalouro,						//struct para conter os dados de um calouro
		vetCalouros[QTDE_MAXIMA_CALOUROS];	//vetor para conter todos os calouros
	SYSTEMTIME stTime;						//para obter a data e hora do sistema
	setlocale(LC_ALL, "portuguese_brazil"); //acentuacao brasileira
	
	// pedir uma quantidade valida de calouros que ira cantar hoje
	do
	{
		cout << "Quantidade de calouros entre " << QTDE_MINIMA_CALOUROS << " e " << QTDE_MAXIMA_CALOUROS << endl << "Ou zero para cancelar a execucao do programa: ";
		cin >> nQtdeCalouros;				//quantidade de calouros
		if (nQtdeCalouros == 0) {
			return;							//retorna ao sistema operacional
		}
	} while (nQtdeCalouros < QTDE_MINIMA_CALOUROS && nQtdeCalouros > QTDE_MINIMA_CALOUROS);

	//loop infinito
	while (true) {
		LIMPAR_TELA;
		GetLocalTime(&stTime);				//obtem a data e hora do sistema
		sprintf_s(cWork, sizeof(cWork), "Programa Raul Gil em %02d/%02d/%04d às %02d:%02d:%02d", stTime.wDay, stTime.wMonth, stTime.wYear, stTime.wHour, stTime.wMinute, stTime.wSecond);
		cout << "\n\t" << cWork << endl;
		//exibir o menu de opções
		cout << INCLUIR_CALOURO << " - Incluir o calouro" << endl;
		cout << EXIBIR_VENCEDOR << " - Vencedor até o momento" << endl;
		cout << LISTAR_CALOUROS << " - Listar os calouros que cantaram até agora" << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do Programa" << endl;
		cout << "\tSelecione: ";
		cin >> cOpcao;						//opcao do operador
		cOpcao = toupper(cOpcao);			//converte para maiuscula
		switch (cOpcao) {					//avaliar a opcao escolhida
			case INCLUIR_CALOURO:
				if (nIndProx == nQtdeCalouros) {
					cout << "Todos os calouros ja cantaram!" << endl;
					PAUSA;
					break;					//volta ao menu
				}
				cin.ignore(1, EOF);			//ignora a tecla enter perdida no buffer do teclado
				cout << "Nome: ";
				cin.getline(stCalouro.cNome, EXTENSAO_NOME, '\n');
				//pedir o sexo valido
				do
				{
					cout << "Sexo (" << MASCULINO << "-Masculino ou " << FEMININO << "Feminino): ";
					cin >> stCalouro.cSexo;
					stCalouro.cSexo = toupper(stCalouro.cSexo);
				} while (stCalouro.cSexo != MASCULINO && stCalouro.cSexo != FEMININO);
				//break;						//cai fora do switch e volta ao menu

				//pedir uma nota valida
				do
				{
					cout << "Nota entre " << NOTA_MINIMA << " e " << NOTA_MAXIMA << ": ";
					cin >> stCalouro.nNota;
				} while (stCalouro.nNota<NOTA_MINIMA || stCalouro.nNota>NOTA_MAXIMA);

				//chamar funcao que insere o calouro no vetor
				nIndProx = InserirCalouro(&stCalouro, vetCalouros, &nIndProx, &nNotaTrono, &nIndVencedor);
			case EXIBIR_VENCEDOR:
				// testar se alguem cantou
				if (nIndProx == 0) {		//ninguem cantou?
					cout << "Ninguem cantou ainda!" << endl;
					PAUSA;
					break;
				}
				ExibeVencedor(vetCalouros, &nIndVencedor);
				break;

			case LISTAR_CALOUROS:
				// testar se alguem cantou
				if (nIndProx == 0) {		//ninguem cantou?
					cout << "Ninguem cantou ainda!" << endl;
					PAUSA;
					break;
				}
				ListarCalouros(vetCalouros, &nIndProx, &stTime);
				break;

			case SAIR_DO_PROGRAMA:
				cout << "Sair realmente? (S ou N): ";
				cin >> cOpcao;				//vai sair ou nao
				if (cOpcao == 's' || cOpcao == 'S'){
					return;
				}
				break;
			default:
				cout << "Opção invalida!" << endl;
				PAUSA;
		}//switch
	}//loop infinito


}// main