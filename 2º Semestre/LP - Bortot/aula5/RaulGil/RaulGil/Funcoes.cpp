// funcoes do programa Raul Gil
#include "RaulGil.h"
// funcao que classifica os calouros em ordem alfabetica

//Parametros:
//	Entrada

//char vetNomes[][EXTENSAO_NOME], - endereco do primeiro bytee do primeiro nome do vetor
	//char vetSexo[], - endereco do sexo do primeiro calorou do vetor
		//int vetNota[], - endereço da nota do primeiro calour do vetor
		//int nQtdeCalouros[] - quantidade de calouros que cantaram hoje

void BubbleSortAlfabetico(char vetNomes[][EXTENSAO_NOME],char vetSexo[],	int vetNota[], int nQtdeCalouros) {
	int nAuxiliar,							// para troca de nota
		i;									// contador e indexador
	char cAuxiliar;							// troca de sexo
	char cAuxNome[EXTENSAO_NOME];			// para auxiliar na troca dos nomes
	bool flgHouveTroca;						//true houve troca

	do
	{
		flgHouveTroca = false;				//não houve troca ainda
		//loop de comparação dois a dois nome
		for (i = 0; i < nQtdeCalouros - 1; i++) {
			if (strcmp(vetNomes[i], vetNomes[i + 1]) > 0) {		// Fora de ordem?
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