#include "Hotel.h"
//---[PedirAndarQuarto]--------------------------------------------------------------------
// Fun��o para pedir o andar e o n�mero do quarto no andar
//		
//	Par�metros:
//		Entrada: 
//			int *ptrAndar - ponteiro para receber o n�mero do andar de 1 a nQtAndares ou
//							zero para cancelar a transa��o
//			int *ptrQuarto - ponteiro para receber o n�mero do quarto por andar de 1 a
//							  nQtQuartos ou zero para cancelar a transa��o
//			int nQtAndares - quantidade de andares que foi configurada no in�cio do programa
//			int nQtQuartos - idem quantidade de quartos por andar
//			char *ptrTransacao - ponteiro da transa��o que est� sendo realizada
//		Retorno: bool = true - indica que o andar e quarto foram informados
//				 bool = false - indica que a transa��o foi cancelada porque foi informado
//								andar zero ou quarto zero
//								e n�o foi liberado por um check-out anterior
bool	PedirAndarQuarto(int *ptrAndar, int *ptrQuarto, int nQtAndares, int nQtQuartos, char *ptrTransacao)
{
	// <<<< 08 >>>>
	// 1 - Ficar em loop pedindo o n�mero do andar ou zero para cancelar a transa��o.
	//		O n�mero do andar tem que ser de 1 a nQtAndares
	// 2 - Ficar em loop pedindo o n�mero do quarto ou zeros para cancelar a transa��o
	//		O n�mero do quarto tem que ser de 1 a nQtQuartos
	cout << "\t" << ptrTransacao << endl;
	// loop para pedir o andar ou zero para cancelar a transa��o
	do
	{
		cout << "Andar entre 1 e " << nQtAndares << " ou zero para cancelar a transa��o: ";
		cin >> *ptrAndar;							// recebe o andar atrav�s do ponteiro
		if(*ptrAndar <= 0)							// cancelar a transa��o?
			return false;							// cancelou a transa��o
	} while(*ptrAndar < 1 || *ptrAndar > nQtAndares);
	// loop para pedir o quarto dentro do andar
	do
	{
		cout << "Quarto entre 1 e " << nQtQuartos << " ou zero para cancelar a transa��o: ";
		cin >> *ptrQuarto;							// recebe o quarto atrav�s do ponteiro
		if(*ptrQuarto <= 0)							// cancelar a transa��o?
			return false;							// cancelou a transa��o
	} while(*ptrQuarto < 1 || *ptrQuarto > nQtQuartos);
	return true;									// indica que foram indicados andar e quarto no andar
} 
// Fun��o que calcula o �ndice do quarto dentro do vetor de quartos
//	Par�metros:
//		Entrada: int nAndar - andar do hotel
//				 int nQuarto - quarto dentro do andar
//				 int nQtQuartoPorAndar - quantidade de quartos por andar
//		Retorno: int - indice calculado
int CalcularIndice(int nAndar, int nQuarto, int nQtQuartoPorAndar)
{
	return ((nAndar - 1) * nQtQuartoPorAndar) + (nQuarto - 1);	// devolve o �ndice
}

