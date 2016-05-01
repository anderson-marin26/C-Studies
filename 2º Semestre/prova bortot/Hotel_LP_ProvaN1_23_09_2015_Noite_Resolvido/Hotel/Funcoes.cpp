#include "Hotel.h"
//---[PedirAndarQuarto]--------------------------------------------------------------------
// Função para pedir o andar e o número do quarto no andar
//		
//	Parâmetros:
//		Entrada: 
//			int *ptrAndar - ponteiro para receber o número do andar de 1 a nQtAndares ou
//							zero para cancelar a transação
//			int *ptrQuarto - ponteiro para receber o número do quarto por andar de 1 a
//							  nQtQuartos ou zero para cancelar a transação
//			int nQtAndares - quantidade de andares que foi configurada no início do programa
//			int nQtQuartos - idem quantidade de quartos por andar
//			char *ptrTransacao - ponteiro da transação que está sendo realizada
//		Retorno: bool = true - indica que o andar e quarto foram informados
//				 bool = false - indica que a transação foi cancelada porque foi informado
//								andar zero ou quarto zero
//								e não foi liberado por um check-out anterior
bool	PedirAndarQuarto(int *ptrAndar, int *ptrQuarto, int nQtAndares, int nQtQuartos, char *ptrTransacao)
{
	// <<<< 08 >>>>
	// 1 - Ficar em loop pedindo o número do andar ou zero para cancelar a transação.
	//		O número do andar tem que ser de 1 a nQtAndares
	// 2 - Ficar em loop pedindo o número do quarto ou zeros para cancelar a transação
	//		O número do quarto tem que ser de 1 a nQtQuartos
	cout << "\t" << ptrTransacao << endl;
	// loop para pedir o andar ou zero para cancelar a transação
	do
	{
		cout << "Andar entre 1 e " << nQtAndares << " ou zero para cancelar a transação: ";
		cin >> *ptrAndar;							// recebe o andar através do ponteiro
		if(*ptrAndar <= 0)							// cancelar a transação?
			return false;							// cancelou a transação
	} while(*ptrAndar < 1 || *ptrAndar > nQtAndares);
	// loop para pedir o quarto dentro do andar
	do
	{
		cout << "Quarto entre 1 e " << nQtQuartos << " ou zero para cancelar a transação: ";
		cin >> *ptrQuarto;							// recebe o quarto através do ponteiro
		if(*ptrQuarto <= 0)							// cancelar a transação?
			return false;							// cancelou a transação
	} while(*ptrQuarto < 1 || *ptrQuarto > nQtQuartos);
	return true;									// indica que foram indicados andar e quarto no andar
} 
// Função que calcula o índice do quarto dentro do vetor de quartos
//	Parâmetros:
//		Entrada: int nAndar - andar do hotel
//				 int nQuarto - quarto dentro do andar
//				 int nQtQuartoPorAndar - quantidade de quartos por andar
//		Retorno: int - indice calculado
int CalcularIndice(int nAndar, int nQuarto, int nQtQuartoPorAndar)
{
	return ((nAndar - 1) * nQtQuartoPorAndar) + (nQuarto - 1);	// devolve o índice
}

