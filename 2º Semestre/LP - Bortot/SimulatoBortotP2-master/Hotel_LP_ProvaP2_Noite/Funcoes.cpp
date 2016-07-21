// Funções da Oficina Mecanica
#include <iostream>
#include <windows.h>
#include "Hotel.h"
using namespace std;

//---[PedirAndar]--------------------------------------------------------------------
// Função para pedir um andar válido ou zeros para cancelar a transação
//
//	Parâmetros:
//		Entrada:
//			int nQtAndares - quantidade de andares do hotel	
//			char *ptrTransacao - ponteiro para um string que contém a transação
//								sendo executada.
//		Retorno:
//			int - um andar válido (1 a nQtAndares) ou zero para cancelar a transação
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
	} while(nAndar < 1 || nAndar > nQtAndares); // loop até andar válido
	return nAndar;						// retorna o número do andar
}

//---[PedirQuarto]--------------------------------------------------------------------
// Função para pedir um quarto válido ou zeros para cancelar a transação
//
//	Parâmetros:
//		Entrada:
//			int nQtQuartos - quantidade de quartos por andar do hotel	
//			char *ptrTransacao - ponteiro para um string que contém a transação
//								sendo executada.
//		Retorno:
//			int - um quarto válido (1 a nQtQuartos) ou zero para cancelar a transação
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
	} while(nQuarto < 1 || nQuarto > nQtQuartos); // loop até quarto válido
	return nQuarto;								// retorna o número do quarto
}

//---[LerQuarto]--------------------------------------------------------------------
// Função que lê um quarto dentro do arquivo de quartos
//
//	Parâmetros:
//		Entrada:
//			int nAndar - andar desejado
//			int nQuarto - número do quarto dentro do andar
//			int nQtQuartoPorAndar - quantidade de quartos por andar
//			FILE *fdQuarto - file descriptor do quarto
//			QUARTO *ptrStQuarto - ponteiro da struct que irá receber os dados do quarto
//		Retorno:
//			bool - true - indica que a leitura foi realizada e o conteúdo do quarto
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
// Função que grava um quarto dentro do arquivo de quartos
//
//	Parâmetros:
//		Entrada:
//			int nAndar - andar desejado
//			int nQuarto - número do quarto dentro do andar
//			int nQtQuartoPorAndar - quantidade de quartos por andar
//			FILE *fdQuarto - file descriptor do quarto
//			QUARTO *ptrStQuarto - ponteiro da struct que contem os dados do quarto a serem gravados
//		Retorno:
//			bool - true - indica que a gravação foi realizada OK
//				   false - indica que houve erro ou no posicionamento ou na gravação
bool GravarQuarto(int nAndar, int nQuarto, int nQtQuartoPorAndar, FILE *fdQuarto, QUARTO *ptrStQuarto)
{
	int nIndice = ((nAndar - 1) * nQtQuartoPorAndar) + (nQuarto - 1);
	// fazer o posicionamento no arquivo
	if(fseek(fdQuarto, nIndice * sizeof(QUARTO), SEEK_SET) != 0)	// fseek com erro?
		return false;								// indica que houve erro
	// vai vai gravar o registro do quarto
	if(fwrite(ptrStQuarto, sizeof(QUARTO), 1, fdQuarto) == 0)		// erro de gravação?
		return false;
	return true;
}
double PedirValorServiço() 
{
	double valor;
	bool flgValorValido = false;
	do
	{
		cout << "Digite o valor do serviço: ";
		cin >> valor;
		if (cin.fail() || valor <= 0)
		{
			cout << "Digite um valor válido!" << endl;
			PAUSA;
		}
		else
		{
			flgValorValido = true;
		}
	} while (!flgValorValido);
	return valor;
}
