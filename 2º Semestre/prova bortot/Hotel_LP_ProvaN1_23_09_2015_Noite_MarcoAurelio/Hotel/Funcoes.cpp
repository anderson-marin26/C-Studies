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
	//Pedindo o Andar
	do
	{
		cout << "\n\t" << ptrTransacao << endl;

		cout << "Informe o andar do hotel entre 1 e " 
			<< nQtAndares << endl << "Ou zero para cancelar: ";
		cin >> *ptrAndar;

		if(*ptrAndar == 0)
			return false;

	}while(*ptrAndar < 1 || *ptrAndar > nQtAndares);
	//		O n�mero do andar tem que ser de 1 a nQtAndares
	
	//Pedindo o quarto
	do
	{
		cout << "\n\t" << ptrTransacao << endl;

		cout << "Informe o n�mero do quarto do hotel entre 1 e " 
			<< nQtQuartos << endl << "Ou zero para cancelar: ";
		cin >> *ptrQuarto;

		if(*ptrQuarto == 0)
			return false;

	}while(*ptrQuarto < 1 || *ptrQuarto > nQtQuartos);
	//		O n�mero do quarto tem que ser de 1 a nQtQuartos
	
	return true;									// !!!!!!!!!!!! para nao acusar erro de compila��o
}//Fim da fun��o