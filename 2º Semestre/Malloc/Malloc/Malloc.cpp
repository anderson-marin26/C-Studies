// Programa de teste do memory allocation
// FATEC - MC - Anderson Marin de Ramos - 27/04/2016 - Versão 0.0
#include "Meu.h"

// Função que classifica o vetor de doubles em ordem crescente ou decrescente
void BubbleSort(double *ptrVetor, int nQtde, bool flgOrdem) {
	double dWork;
	int i;
	bool flgHouveTroca;
	do {
		flgHouveTroca = false;
		for (i = 0; i < nQtde - 1; i++) {
			if (flgOrdem && *(ptrVetor+i) > *(ptrVetor + i + 1) || !flgOrdem && *(ptrVetor + i) < *(ptrVetor + i + 1)) {
				dWork = *(ptrVetor+i);
				*(ptrVetor+i) = *(ptrVetor+i+1);
				*(ptrVetor+i+1) = dWork;
				flgHouveTroca = true;
			}
		}
	} while (flgHouveTroca);
}

// Função que lista o vetor de doubles
void ListarDoubles(double *ptrVet, int nQtde, char *ptrCabec) {
	char cWork[20];
	int i, j;										// indexadores e contadores
	LIMPAR_TELA;
	cout << "\n\t" << ptrCabec << endl;

	//loop de listagem
	for (i = 0; i < nQtde;) {
		for (j = 0; j < 5; j++, i++) {
			if (i == nQtde) {
				break;
			}
			sprintf_s(cWork, sizeof(cWork), "%12.2f", *ptrVet++);
			cout << cWork << "\t";
		}// for j
		cout << endl;
	}// for i
	cout << "\t\tFim da Listagem" << endl;
	PAUSA;
}

// entry point do programa
void main(void) {
	int i,											// indexador e contador
		nQtdeDoubles = 0;							// recebe a quantidade de doubles
	double *ptrVetor,								// ponteiro do vetor de doubles
		*ptrSalva;									// ponteiro de salva guarda
	setlocale(LC_ALL, "portuguese_brazil");
	cout << "Qtde de doubles desejada ou zero para cancelar a execução: ";
	cin >> nQtdeDoubles;							// recebe a quantidade
	if (nQtdeDoubles <= 0) {
		return;										// retorna ao sistema operacional
	}

	// Alocando memoria dinamicamente
	ptrSalva = ptrVetor = (double *)malloc(nQtdeDoubles * sizeof(double));
	// testando se alocou
	if (ptrVetor == NULL) {
		cout << "Não tem memoria!" << endl << "Encerre programas desnecessarios e abra o programa novamente";
		PAUSA;
		return;										// volta ao sistema operacional
	}
	
	// inicializar doubles de forma random
	srand(200);										// semente random
	for (i = 0; i < nQtdeDoubles; i++, ptrVetor++) {
		*ptrVetor = rand() * 12.4567;
	}
	// restaurar o ponteiro
	ptrVetor = ptrSalva;

	// listar as doubles que foram geradas
	ListarDoubles(ptrVetor, nQtdeDoubles, "Listagem original das doubles");
	// classificar em ordem crescente
	BubbleSort(ptrVetor, nQtdeDoubles, true);
	// listar doubles
	ListarDoubles(ptrVetor, nQtdeDoubles, "Listagem em ordem crescente");
	// classificar em ordem decrescente
	BubbleSort(ptrVetor, nQtdeDoubles, false);
	// listar as doubles
	ListarDoubles(ptrVetor, nQtdeDoubles, "Listagem em ordem decrescente");
	free(ptrSalva);									// libera a memoria alocada
}