// Fun��es da Oficina Mecanica
#include <iostream>
#include <windows.h>
#include "Hotel.h"
using namespace std;

//---[PedirAndar]--------------------------------------------------------------------
// Fun��o para pedir um andar v�lido ou zeros para cancelar a transa��o
//
//	Par�metros:
//		Entrada:
//			int nQtAndares - quantidade de andares do hotel	
//			char *ptrTransacao - ponteiro para um string que cont�m a transa��o
//								sendo executada.
//		Retorno:
//			int - um andar v�lido (1 a nQtAndares) ou zero para cancelar a transa��o
int	PedirAndar(int nQtAndares, char *ptrTransacao)
{
	int nAndar;							// para receber o andar
	cout << "\t" << ptrTransacao << endl;
	do
	{
		cout << "Andar entre 1 e " << nQtAndares << endl
			<< "Ou zeros para cancelar: ";
		cin >> nAndar;					// recebe o andar
		if(nAndar == 0)					// cancelar?
			return 0;					// indica que deve cancelar
	} while(nAndar < 1 || nAndar > nQtAndares); // loop at� andar v�lido
	return nAndar;						// retorna o n�mero do andar
}

//---[PedirQuarto]--------------------------------------------------------------------
// Fun��o para pedir um quarto v�lido ou zeros para cancelar a transa��o
//
//	Par�metros:
//		Entrada:
//			int nQtQuartos - quantidade de quartos por andar do hotel	
//			char *ptrTransacao - ponteiro para um string que cont�m a transa��o
//								sendo executada.
//		Retorno:
//			int - um quarto v�lido (1 a nQtQuartos) ou zero para cancelar a transa��o
int	PedirQuarto(int nQtQuartos, char *ptrTransacao)
{
	int nQuarto;							// para receber o quarto
	cout << "\t" << ptrTransacao << endl;
	do
	{
		cout << "Quarto entre 1 e " << nQtQuartos << endl
			<< "Ou zeros para cancelar: ";
		cin >> nQuarto;							// recebe o quarto
		if(nQuarto == 0)						// cancelar?
			return 0;							// indica que deve cancelar
	} while(nQuarto < 1 || nQuarto > nQtQuartos); // loop at� quarto v�lido
	return nQuarto;								// retorna o n�mero do quarto
}

//---[LerQuarto]--------------------------------------------------------------------
// Fun��o que l� um quarto dentro do arquivo de quartos
//
//	Par�metros:
//		Entrada:
//			int nAndar - andar desejado
//			int nQuarto - n�mero do quarto dentro do andar
//			int nQtQuartoPorAndar - quantidade de quartos por andar
//			FILE *fdQuarto - file descriptor do quarto
//			QUARTO *ptrStQuarto - ponteiro da struct que ir� receber os dados do quarto
//		Retorno:
//			bool - true - indica que a leitura foi realizada e o conte�do do quarto
//							foi armazenado em ptrStQuarto.
//				   false - indica que houve erro ou no posicionamento ou na leitura
bool LerQuarto(int nAndar, int nQuarto, int nQtQuartoPorAndar, FILE *fdQuarto, QUARTO *ptrStQuarto)
{
	int nIndice = ((nAndar - 1) * nQtQuartoPorAndar) + (nQuarto - 1);
	// fazer o posicionamento no arquivo
	if(fseek(fdQuarto, nIndice * sizeof(QUARTO), SEEK_SET) != 0)	// fseek com erro?
		return false;								// indica que houve erro
	// vai ler o registro do quarto
	if(fread_s(ptrStQuarto, sizeof(QUARTO), 1, 1,fdQuarto) == 0)		// erro de leitura?
		return false;
	return true;
}
//---[GravarQuarto]--------------------------------------------------------------------
// Fun��o que grava um quarto dentro do arquivo de quartos
//
//	Par�metros:
//		Entrada:
//			int nAndar - andar desejado
//			int nQuarto - n�mero do quarto dentro do andar
//			int nQtQuartoPorAndar - quantidade de quartos por andar
//			FILE *fdQuarto - file descriptor do quarto
//			QUARTO *ptrStQuarto - ponteiro da struct que contem os dados do quarto a serem gravados
//		Retorno:
//			bool - true - indica que a grava��o foi realizada OK
//				   false - indica que houve erro ou no posicionamento ou na grava��o
bool GravarQuarto(int nAndar, int nQuarto, int nQtQuartoPorAndar, FILE *fdQuarto, QUARTO *ptrStQuarto)
{
	int nIndice = ((nAndar - 1) * nQtQuartoPorAndar) + (nQuarto - 1);
	// fazer o posicionamento no arquivo
	if(fseek(fdQuarto, nIndice * sizeof(QUARTO), SEEK_SET) != 0)	// fseek com erro?
		return false;								// indica que houve erro
	// vai vai gravar o registro do quarto
	if(fwrite(ptrStQuarto, sizeof(QUARTO), 1, fdQuarto) == 0)		// erro de grava��o?
		return false;
	return true;
}
double PedirValorServi�o() 
{
	double valor;
	bool flgValorValido = false;
	do
	{
		cout << "Digite o valor do servi�o: ";
		cin >> valor;
		if (cin.fail() || valor <= 0)
		{
			cout << "Digite um valor v�lido!" << endl;
			PAUSA;
		}
		else
		{
			flgValorValido = true;
		}
	} while (!flgValorValido);
	return valor;
}
