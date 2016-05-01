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
	//		O número do andar tem que ser de 1 a nQtAndares
	
	//Pedindo o quarto
	do
	{
		cout << "\n\t" << ptrTransacao << endl;

		cout << "Informe o número do quarto do hotel entre 1 e " 
			<< nQtQuartos << endl << "Ou zero para cancelar: ";
		cin >> *ptrQuarto;

		if(*ptrQuarto == 0)
			return false;

	}while(*ptrQuarto < 1 || *ptrQuarto > nQtQuartos);
	//		O número do quarto tem que ser de 1 a nQtQuartos
	
	return true;									// !!!!!!!!!!!! para nao acusar erro de compilação
}//Fim da função