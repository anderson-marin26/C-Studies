// Programa Raul Gil com dynamic memory allocation
// FATEC - MC - Anderson Marin de Ramos - 27/04/2016
#include "Raulgil.h"

//Função que lista o vetor de calouros
void ListarCalouros(CALOURO *ptrVetor, int nQtde, char *ptrCabec) {

}

//Função que classifica em ordem alfabetica
void BubbleSort(CALOURO *ptrVetor, int nQtde) {
	int nAuxiliar,							// para troca de nota
		i;									// contador e indexador
	char cAuxiliar;							// troca de sexo
	char cAuxNome[EXTENSAO_NOME];			// para auxiliar na troca dos nomes
	bool flgHouveTroca;						//true houve troca

	do
	{
		flgHouveTroca = false;				//não houve troca ainda
											//loop de comparação dois a dois nome
		for (i = 0; i < nQtde - 1; i++) {
			if (strcmp((ptrVetor+i)->cNome, (ptrVetor + i + 1)->cNome) > 0) {		// Fora de ordem? // continuar
																//troca de nomes
				strcpy_s(cAuxNome, EXTENSAO_NOME, vetNomes[i]);  //salva o elem[i]
				strcpy_s(vetNomes[i], EXTENSAO_NOME, vetNomes[i + 1]);  // troca de posição elem[i + 1]
				strcpy_s(vetNomes[i + 1], EXTENSAO_NOME, cAuxNome);		// troca elem[i]

																		// troca do sexo
				cAuxiliar = vetSexo[i];		//salva eleme[i]
				vetSexo[i] = vetSexo[i + 1];	//troca elem[i+1]
				vetSexo[i + 1] = cAuxiliar;		// troca elem[i]

												//troca de nota
				nAuxiliar = vetNota[i];
				vetNota[i] = vetNota[i + 1];
				vetNota[i + 1] = nAuxiliar;
				flgHouveTroca = true;		//indica que houve troca
			}
		}
	} while (flgHouveTroca);				//enquanto flgHouveTroca == true
}
// Entry point
void main(void) {
	int i,
		nQtde,
		nTrono = -1,
		nIndTrono = 0;
	CALOURO *ptrVetCalouros,							// ponteiro para o vetor de calouros
		*ptrSalva;										// ponteiro de salva guarda
	setlocale(LC_ALL, "portuguese_brazil");
	
	// pedir a quantidade de calouros
	do
	{
		cout << "Quantidade de calouros entre " << QTDE_MINIMA << " e " << QTDE_MAXIMA << endl<<"Ou zero para cancelar a execução: ";
		cin >> nQtde;
		if (nQtde <= 0) {
			return;										// volta ao sistema operacional
		}
	} while (nQtde < QTDE_MINIMA || nQtde > QTDE_MAXIMA);

	// fazer a alocação de memoria para conter nQtde calouros
	ptrSalva = ptrVetCalouros = (CALOURO *) malloc(nQtde * sizeof(CALOURO));
	if (ptrSalva == NULL) {
		cout << "Não tem memoria!" << endl;
		PAUSA;
		return;											// volta ao sistema operacional
	}

	// loop para receber os calouros
	for (i = 0; i < nQtde; i++) {
		cin.ignore(1, EOF);								// ignorar a tecla enter
		cout << "Nome: ";
		cin.getline((ptrVetCalouros + i)->cNome, 30, '\n');
		do
		{
			cout << "Nota entre 0 e 10: ";
			cin >> (ptrVetCalouros + i)->nNota;
		} while ((ptrVetCalouros + i)->nNota < 0 || (ptrVetCalouros + i)->nNota > 10);

		//verificar se vai pro trono
		if ((ptrVetCalouros + i)->nNota > nTrono) {
			nTrono = (ptrVetCalouros + i)->nNota;		// salva a nota do melhor calouro
			nIndTrono = i;
		}
	}// for i
	cout << "O vencedor é: " << (ptrVetCalouros + nIndTrono)->cNome << " Nota: " << (ptrVetCalouros + nIndTrono)->nNota << endl;
	PAUSA;
	// Listagem dos calouros na ordem que cantaram
	// Classificar em ordem alfabetica
	// Listar em ordem alfabetica
	free(ptrSalva);
}// main