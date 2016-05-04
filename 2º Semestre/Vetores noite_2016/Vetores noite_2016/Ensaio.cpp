//Programa de ensaio de vetores
//FATEC-MC - AA - 02/03/2016 - Versão 0.0

#include "Vetor.h"
//função que lista o vetor
//parâmetros:
//		Entrada:int vetInt[] - endereço do primeiro byte da primeira inteira do vetor
//				int nQtde - quantidade de inteiras do vetor
//				int nQtdeLinha - quantidade a listar por linha
void ListagemDoVetor(int vetInt[], int nQtde, int nQtdeLinha)
{
	int i, j;		//indices de contadores
	//loop para listar
	for (i = 0; i < nQtde;)
	{
		for (j = 0; j < nQtdeLinha; j++, i++)
		{
			if (i == nQtde)
				break;
			cout << vetInt[i] << "\t";		//lista uma inteira
		}//for j
		cout << endl;
	}//for i
	PAUSA;
}
//
//entry point do programa

void main(void)
{
	int i, j;		//indices de contadores
	double vetDoubles[] = { 100.56,300.45,200.99,500.67,600.01 };			//vetor iniciado
	char vetChar[] = { 'A','B','C','>', 0x27, 0x41, 0x42, 0x43, 0xb9 },		//vetor char
		cNome[] = "Alan de Almeida\xb9",		//string
		vetWork[200];

	int vetInteiras[QTDE_INTEIRAS],
		vetCopia[QTDE_INTEIRAS];
	double vet[10];

	setlocale(LC_ALL, "portuguese_brazil");

	cout << "Endereço de cNome=" << &cNome << " cNome =" << cNome << endl;
	PAUSA;
	cout << "Endereço de vetDoubles=" << vetDoubles << " vetDoubles[0]=" << vetDoubles[0] << endl;
	PAUSA;
	strcpy_s(vetWork, cNome);
	cout << "vetWork" << vetWork << endl;
	PAUSA;
	strcat_s(vetWork, " Professor de linguagens de programação");
	cout << "vetWork=" << vetWork << endl;
	PAUSA;
	cout << "\t Listagem do cWork byte a byte" << endl;

	for (i = 0; i < strlen(vetWork); i++)
		cout << vetWork[i];
	cout << endl;
	PAUSA;
	//preencher o vetor de inteiras com pseudo random inteiras

	//preencher o vetor de inteiras com valores
	for (i = 0; i < QTDE_INTEIRAS; i++)
		vetInteiras[i] = i + 15 - 3 * i;
	//listagem do vetor
	LIMPAR_TELA;

	cout << "\ntListagem do vetor de inteiras com " << QTDE_INTEIRAS << " por linha" << endl;
	ListagemDoVetor(vetInteiras, QTDE_INTEIRAS, QTDE_POR_LINHA);

	//preencher o vetor de inteiras com pseudo random inteiras
	srand(240);
	for (i = 0; i < QTDE_INTEIRAS; i++)
	{
		vetInteiras[i] = rand();		//preenche com um random
		if (rand() % 2 == 1)		//negativo?
			vetInteiras[i] *= -1;		//torna negativo

	}
	LIMPAR_TELA;
	cout << "\n\tListagem do vetor com pseudo random" << endl;
	ListagemDoVetor(vetInteiras, QTDE_INTEIRAS, QTDE_POR_LINHA);
	//classifica em ordem crescente
	BubbleSort(vetInteiras, QTDE_INTEIRAS,true);
	//listar o vetor
	LIMPAR_TELA;
	cout << "\n\tListagem do vetor em ordem crescente" << endl;
	ListagemDoVetor(vetInteiras, QTDE_INTEIRAS, QTDE_POR_LINHA);

	BubbleSort(vetInteiras, QTDE_INTEIRAS,false);
	//listar o vetor
	LIMPAR_TELA;
	cout << "\n\tListagem do vetor em ordem decrescente" << endl;
	ListagemDoVetor(vetInteiras, QTDE_INTEIRAS, QTDE_POR_LINHA);
	//para casa
	//1 - Copiar o vetInteiras no vetCopia
	for (i = 0; i < QTDE_INTEIRAS; i++)
		vetCopia[i] = vetInteiras[i];

	//2 - Somar cada vetInteiras com o vetCopia e o resultdo em vetCopia
	for (i = 0; i < QTDE_INTEIRAS; i++)
		vetCopia[i] += vetInteiras[i];
	//3 - Listar o Vetor vetCopia
	LIMPAR_TELA;
	cout << "\n\ tListagem de vetCopia com vetInteira" << endl;
	ListagemDoVetor(vetCopia, QTDE_INTEIRAS, QTDE_POR_LINHA);
	//4 - Copiar o vetInteira no vetCopia na ordem inversa
	for (i = 0, j= QTDE_INTEIRAS - 1; i < QTDE_INTEIRAS; )
		vetCopia[i++] = vetInteiras[j--];
	//5 - Listar o vetCopia
	LIMPAR_TELA;
	cout << "\n\ tListagem de vetCopia com vetInteira na ordem inversa" << endl;
	ListagemDoVetor(vetCopia, QTDE_INTEIRAS, QTDE_POR_LINHA);

	//6 - Copiar o cNome em vetWork em ordem inversa
	for (i = 0, j = strlen(cNome) - 1; i <strlen(cNome); )
		vetWork[i++] = cNome[j--];
	vetWork[strlen(cNome)] = NULL;
	//7 - Exibir vetWork mostrando que está em ordem inversa
	cout << "cNome: " << cNome << endl << vetWork << endl;
	PAUSA;


}//main
//função que classifica em ordem crescente em vetor de inteiras conforme o algoritmo de D.Flores
//parâmetros :
//		ENtrada:int vetInt[] - endereço do primeiro byte da primeira inteira do vetor
//				int nQtde - quantidade de inteiras do vetor
//				flgOrdem- true - indica ordem crescente e false - indica ordem decrescente
void BubbleSort(int vetInt[], int nQtde, bool flgOrdem)
{
	int nAuxiliar,		//auxiliar para troca
		i;		//indice e contador
	bool flgHouveTroca;		// true - indice troca
	do
	{
		flgHouveTroca = false;		//não houve troca ainda
		//loop de comparação duas a duas
		for (i = 0; i < nQtde - 1; i++)
		{
			if (flgOrdem && vetInt[i] > vetInt[i + 1]|| !flgOrdem && vetInt[i] < vetInt[i + 1])		//fora de ordem
			{
				nAuxiliar = vetInt[i];		//salva elemento[1]
				vetInt[i] = vetInt[i + 1];		//troca elemento[i+1]
				vetInt[i + 1] = nAuxiliar;		//troca elemento[i]
				flgHouveTroca = true;		//indica que houve troca;
			}
		}//for i
	} while (flgHouveTroca);		//enquanto houver troca
}