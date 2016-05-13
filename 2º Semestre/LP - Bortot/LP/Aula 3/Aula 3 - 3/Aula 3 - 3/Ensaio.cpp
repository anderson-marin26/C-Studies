// programa de ensaio de vetores 
//FATEC-MC - Anderson Marin de Ramos - 02-03-2016
#include "vetor.h"
//funcão que lista
//Parametros:
// Entrada:int vetInt[]  -  endereço do primeiro byte da inteira do vetor
//				int nQtde  -  quantidade de inteiras do vetor
//				int nQtdeLinha  -  quantidade a listar por linha
	
void ListagemDoVetor(int vetInt[], int nQtde, int nQtdeLinha) {
	int i, j;			//indices de contadores
	//loop para listagem
	for (i = 0; i < nQtde; ) {
		for (j = 0; j < nQtdeLinha; j++, i++) {
			if (i == nQtde)			//Listou todas?
				break;
			cout << vetInt[i] << "\t";	//lista uma inteira
		}
		cout << endl;
	}
	PAUSA;
}
//entry point

void main(void) {
	int i, j;						// indices e contadores
	double vetDoubles[] = { 100.42, 312.43, 3123, 412.6, 666.666 };	// vetor iniciado
	char vetChar[] = { 'A', 'B', 'C', '>', 0x27, 0x41, 0x42, 0xB9 }, // vetor iniciado de char
		vetNome[] = "Anderson Marin de Ramos\xb9",	//string
		vetWork[200];
	int vetInteiras[QTDE_INTEIRAS],	//vetor sem inicialização
		vetCopia[QTDE_INTEIRAS],
		nVetInt[] = { 10,56,78,99,203,-44 }; //vetor com valores
	double vet[10];
	setlocale(LC_ALL, "portuguese_brazil");

	cout << "endereço de vetNome = " << &vetNome[1] << " vetNome = " << vetNome << endl;
	PAUSA;
	cout << "endereço de vetDoubles = " << vetDoubles << " vetDoubles[0] = " << vetDoubles[0] << endl;
	PAUSA;
	strcpy_s(vetWork, vetNome);
	cout << "vetWork = " << vetWork << endl;
	PAUSA;
	strcat_s(vetWork, " Estudante de linguagem de programação");
	cout << "vetWork = " << vetWork << endl;
	PAUSA;
	cout << "\tlistagem do vetWork byte a byte " << endl;
	for (i = 0; i < strlen(vetWork); i++) {
		cout << "posição " << i << " é: " << vetWork[i] << endl;
	}
	PAUSA;
	//preencher o vetor de inteiras com valores 
	for (i = 0; i < QTDE_INTEIRAS; i++)
		vetInteiras[i] = i + 15 - 3 * i;
	//listagem do vetor
	LIMPAR_TELA;
	cout << "\n\tListagem do vetor de inteiras com " << QTDA_POR_LINHA << " linha" << endl;
	ListagemDoVetor(vetInteiras, QTDE_INTEIRAS, QTDA_POR_LINHA);
	//preencher o vetor de inteiras com pseudo random inteiras
	srand(240);			//semente random
	for (i = 0; i < QTDE_INTEIRAS; i++) {
		vetInteiras[i] = rand();	//preenche com um random
		if (rand() % 2 == 1)			//negativo?
			vetInteiras[i] *= -1;		//torna negativo

	}
	//listar o vetor
	LIMPAR_TELA;
	cout << "\n\tListagem do vetor com pseudo random" << endl;
	ListagemDoVetor(vetInteiras, QTDE_INTEIRAS, QTDA_POR_LINHA);
	//classificar em ordem crescente
	BubbleSort(vetInteiras, QTDE_INTEIRAS, true);
	LIMPAR_TELA;
	cout << "\n\tListagem do vetor classificado em ordem crescente" << endl;
	ListagemDoVetor(vetInteiras, QTDE_INTEIRAS, QTDA_POR_LINHA);

	//classificar em ordem decrescente
	BubbleSort(vetInteiras, QTDE_INTEIRAS, false);
	LIMPAR_TELA;
	cout << "\n\tListagem do vetor classificado em ordem decrescente" << endl;
	ListagemDoVetor(vetInteiras, QTDE_INTEIRAS, QTDA_POR_LINHA);

	//	1:
	for (i = 0; i < QTDE_INTEIRAS; i++) {
		vetCopia[i] = vetInteiras[i];
	}

	//	2:
	for (i = 0; i < QTDE_INTEIRAS; i++) {
		vetCopia[i] = vetInteiras[i] + vetCopia[i];
	}
	cout << "=================================\n\tvetCopia" << endl;

	// 3:
	ListagemDoVetor(vetCopia, QTDE_INTEIRAS, QTDA_POR_LINHA);

	LIMPAR_TELA;

	//	4:
	for (i = 0, j = QTDE_INTEIRAS; i < QTDE_INTEIRAS; i++, j--) {
		vetCopia[j] = vetInteiras[i];
	}

	cout << "=================================\n\tvetCopia" << endl;
	//	5:
	ListagemDoVetor(vetCopia, QTDE_INTEIRAS, QTDA_POR_LINHA);
	LIMPAR_TELA;
	cout << "=================================\n\t string inversa" << endl;

	//	6:
	for (i = strlen(vetNome), j = 0; i >= 0; i--, j++) {
		vetWork[j] = vetNome[i];
	}

	//	7:
	i = 0;
	for (i = 0; i < strlen(vetWork); i++) {
		cout << vetWork[i] << "\t";
	}
}
}// main
//funcao que classifica em ordem crescente um vetor de inteiras conforme um algoritmo D. Flores
//Parametros:
//	Entrada : int vetInt[]  -  endereço do primeiro byte da primeira inteira do vetor
//			  int nQtde  -  quantidad de inteiras no vetor	
//			  bool flgOrdem  -  True indica ordem crescente e False indica ordem decrescente
void BubbleSort(int vetInt[], int nQtde, bool flgOrdem) {
	int nAuxiliar,		//auxiliar para troca
		i;				//indice e contador
	bool flgHouveTroca; //true - indica troca
	do
	{
		flgHouveTroca = false;		//não houve troca ainda
		//loop de comparação duas a duas
		for (i = 0; i < nQtde - 1; i++) {
			if ((flgOrdem && vetInt[i] > vetInt[i + 1]) || (!flgOrdem && vetInt[i] < vetInt[i+1])) {	//fora de ordem?
				nAuxiliar = vetInt[i]; //salva elem[i]
				vetInt[i] = vetInt[i + 1];	//troca o elem[i+1]
				vetInt[i + 1] = nAuxiliar; //troca elem[i]
				flgHouveTroca = true;
			}
		}
	} while (flgHouveTroca);	//enquanto houver troca



}

//Para casa
//1.Copiar o VetInteiras no vetCopia
//2.Somar cada inteira do vetInteiras com o vetCopia e o resultado em vetcopia
//3.Listar o vetor vetCopia
//4.Copiar o VetInteiras no vetCopia na ordem inversa, isto é, a primeira inteira de vetCopia recebe a ultima de VetInteira
//5.Listar vetCopia
//6.Copiar o cNome em vetWork em ordem inversa
//7.Exibir vetWork mostrando que esta em ordem inversa