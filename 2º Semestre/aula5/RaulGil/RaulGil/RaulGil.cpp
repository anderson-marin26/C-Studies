// Programa de calouros Raul Gil com vetores
// Anderson Marin de Ramos - FATEC MC - 16/03/2016

#include "RaulGil.h"

// entry point
void main(void) {
	int i, j,											// contadores e indexadores
		nQtdeCalouros,									// quantidade de calouros
		nNotaTrono = -1,								// a nota do trono do melhor
		iIndiceMelhor = 0;								// indice do melhor

	// vetores dos calouros
	//int vetNotas[QTDE_MAXIMA_CALOUROS];					//vetor de notas
	//char vetSexos[QTDE_MAXIMA_CALOUROS];				//vetor de sexos
	//char vetNomes[QTDE_MAXIMA_CALOUROS][EXTENSAO_NOME];	//vetor bi-dimensional dos nomes

	CALOURO stCalouros;

	ACENTUACAO_BRASILEIRA;

	do
	{
		cout << "Informe a quantidade de calouros entre " << QTDE_MINIMA_CALOUROS << " e " << QTDE_MAXIMA_CALOUROS << endl
			<< "Ou zero para cancelar a execução do programa: ";
		cin >> nQtdeCalouros;		//recebe quantidade
		if (nQtdeCalouros == 0)		//cancelar?
			return;
	} while (nQtdeCalouros < QTDE_MINIMA_CALOUROS || nQtdeCalouros > QTDE_MAXIMA_CALOUROS);
	// loop para receber cada calouro
	for (i = 0; i < nQtdeCalouros; i++) {
		cin.ignore(1, EOF);								//ignorar a tecla enter
		cout << "Nome do calouro de ordem " << i + 1 << " de " << nQtdeCalouros << ": ";
		cin.getline(stCalouros.cNome[i], EXTENSAO_NOME - 1, '\n');	// nome com sobrenome

		do
		{
			cout << "Sexo de " << stCalouros.cNome[i] << " (" << MASCULINO << "=masculino ou " << FEMININO << " =feminino): ";
			cin >> stCalouros.cSexo[i];							//recebe o sexo
			stCalouros.cSexo[i] = toupper(stCalouros.cSexo[i]);		//converte para maiuscula
		} while (vetSexos[i] != MASCULINO && vetSexos[i] != FEMININO);

		do
		{
			cout << "Nota entre " << NOTA_MINIMA << " e " << NOTA_MAXIMA << ": ";
			cin >> vetNotas[i];					//recebe a nota
		} while (vetNotas[i] < NOTA_MINIMA || vetNotas[i] > NOTA_MAXIMA);

		//verificar se vai para o trono
		if (vetNotas[i] > nNotaTrono) {			//Vai para o trono?
			nNotaTrono = vetNotas[i];			//salva a nota do calouro
			iIndiceMelhor = i;
		}
	}//for i

	//Todos calouros cantaram
	cout << "Vencedor: " << vetNomes[iIndiceMelhor] << " Sexo: " << vetSexos[iIndiceMelhor] << " Nota: " << vetNotas[iIndiceMelhor] << endl;
	PAUSA;
	cout << "\n\tListagem dos calouros que cantaram hoje " << endl;
	ListarCalouros(vetNomes, vetSexos,vetNotas,nQtdeCalouros);

	//classificar em ordem alfabetica os calouros que cantaram hoje
	cout << "\n\tListagem dos calouros que cantaram hoje em ordem alfabetica " << endl;
	BubbleSortAlfabetico(vetNomes, vetSexos, vetNotas, nQtdeCalouros);
	ListarCalouros(vetNomes, vetSexos, vetNotas, nQtdeCalouros);
}//main

// Função que lista os calouros que cantaram hoje.


//Parametros
//	Entrada: char vetNomes[][EXTENSAO_NOME]  - endereço do primeiro byte do primeiro nome do vetor de nomes
//			char vetSexo[]					 - endereço do sexo do primeiro calouro
//			int vetNotas[]					 - endereço da nota do primeiro calouro
//			 int nQtCalouros				 - quantidade de calouros que cantaram hoje

void ListarCalouros(char vetNomes[][EXTENSAO_NOME], char vetSexo[], int vetNotas[] ,int nQtdeCalouros) {
	for (int i = 0; i < nQtdeCalouros; i++) {
		cout << vetNomes[i] << " do sexo:" << vetSexo[i] << " com a nota: " << vetNotas[i] << endl;
		
	}
	PAUSA;
}