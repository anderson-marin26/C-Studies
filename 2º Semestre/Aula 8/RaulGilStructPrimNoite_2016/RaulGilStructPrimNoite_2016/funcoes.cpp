//Funcoes do programa Raul Gil
#include "RaulGil.h"

//Funcao que inclui um calouro no vetor de calouros atravez de ponteiros
//Parametros:
//			CALOURO *ptrStCalouro - ponteiro de uma struct que contem os dados do calouro a ser inserido no vetor
//			CALOURO *ptrVetCalouros - ponteiro do primeiro calouro fo vetor
//			int *ptrProx - ponteiro do indice do proximo a ser inserido
//			int *ptrTrono - ponteiro da nota do trono
//			int *ptrVenc - ponteiro do melhor calouro ate o momento
//	Retorno:
//		int - indice do proximo calouro
int InserirCalouro(CALOURO *ptrStCalouro, CALOURO *ptrVetCalouros, int *ptrProx, int *ptrTrono, int *ptrVenc) {
	//copiar a struct no seu lugar do vetor
	memcpy_s((ptrVetCalouros + *ptrProx), sizeof(CALOURO), ptrStCalouro, sizeof(CALOURO));
	
	//verificar se o calouro vai para o trono
	if (ptrStCalouro->nNota > *ptrTrono) {
		*ptrTrono = ptrStCalouro->nNota;		//nota do trono
		*ptrVenc = *ptrProx;					//indice do calouro é o do vencedor
	}
	//devolver o indice no vetor para o proximo calouro
	return(*ptrProx += 1);						//indice do prox
}//Inserir calouro


//funcao que exibe o vencedor
// Parametros:
//			Entrada:
//					CALOURO *ptrVetCalouros - ponteiro do primeiro calouro do vetor
//					int *ptrVencedor - ponteiro para o indice do vencedor
void ExibeVencedor(CALOURO *ptrVetCalouros, int *ptrVencedor) {
	LIMPAR_TELA;
	
	cout << "/t/n Calouro vencedor de indice: " << *ptrVencedor;

}//exibe vencedor

//funcao que lista os calouros que cantaram até o momento
// parametros:
//		Entrada:
//			CALOURO *ptrvetCalouros - ponteiro para o vetor de calouros
//			int *ptrProximo	- ponteiro do indice para o proximo calouro que vai indicar quantos calouros cantaram
//			SYSTEMTIME *ptrTime - ponteiro para a data e hora do sistema obtidas na main para formatar um cabeçalho simpatico

void ListarCalouros(CALOURO *ptrvetCalouros, int *ptrProximo, SYSTEMTIME *ptrTime) {

	LIMPAR_TELA;
	
}//Listar calouros