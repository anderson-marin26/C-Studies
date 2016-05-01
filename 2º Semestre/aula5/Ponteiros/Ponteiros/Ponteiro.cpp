// Programa que demostra o uso de ponteiros
// FATEC MC - Anderson Marin de Ramos - 16/03/2016
#include "Ponteiro.h"

//funcao que lista o vetor de inteiras com 8 por linha
//parametros:
//		Entrada: int *ptrVet - endereco da primeira inteira do vetor
//				 int nQtInteiras - quantidade de inteiras do vetor
//				 char *ptrCabecalho - ponteiro de um string que contem o cabeçalho da listagem
void ListarVetorInteiras(int *ptrVet, int nQtInteiras, char *ptrCabecalho) {
	int i,j;									//indices e contadores
	LIMPAR_TELA;
	cout << "\n\t" << ptrCabecalho << endl;		//imprimi o cabecalho
	for (i = 0; i < nQtInteiras;) {				//lista todas
		for (j = 0; j < 8; j++, i++) {			//lista 8 por linha
			if (i == nQtInteiras)				//listou todas?
				break;							//cai fora do for j
			cout << *ptrVet++ << "\t";			//exibe o que aponta e incrementa para o proximo
		}//for j
		cout << endl;
	}//for i
	PAUSA;
}

//funcao que lista o vetor de inteiras com 8 por linha utilizando a aritmetica de ponteiros
//parametros:
//		Entrada: int *ptrVet - endereco da primeira inteira do vetor
//				 int nQtInteiras - quantidade de inteiras do vetor
//				 char *ptrCabecalho - ponteiro de um string que contem o cabeçalho da listagem
void ListarVetorInt(int *ptrVet, int nQtInteiras, char *ptrCabecalho) {
	int i, j;									//indices e contadores
	LIMPAR_TELA;
	cout << "\n\t" << ptrCabecalho << endl;		//imprimi o cabecalho
	for (i = 0; i < nQtInteiras;) {				//lista todas
		for (j = 0; j < 8; j++, i++) {			//lista 8 por linha
			if (i == nQtInteiras)				//listou todas?
				break;							//cai fora do for j
			cout << *(ptrVet + i) << "\t";		//exibe o que esta apontado pelo endereco obtido pelo calculo:
												// [ptrVet] + i * sizeof(int)
		}//for j
		cout << endl;
	}//for i
	PAUSA;
}

//funcao que lista o vetor de inteiras com 8 por linha
//parametros:
//		Entrada: int *ptrVet - endereco da primeira inteira do vetor
//				 int nQtInteiras - quantidade de inteiras do vetor
//				 char *ptrCabecalho - ponteiro de um string que contem o cabeçalho da listagem
void ListarVetorVetor(int *ptrVet, int nQtInteiras, char *ptrCabecalho) {
	int i, j;									//indices e contadores
	LIMPAR_TELA;
	cout << "\n\t" << ptrCabecalho << endl;		//imprimi o cabecalho
	for (i = 0; i < nQtInteiras;) {				//lista todas
		for (j = 0; j < 8; j++, i++) {			//lista 8 por linha
			if (i == nQtInteiras)				//listou todas?
				break;							//cai fora do for j
			cout << *&ptrVet[i] << "\t";			//exibe o que aponta e incrementa para o proximo
		}//for j
		cout << endl;
	}//for i
	PAUSA;
}


//Funcao que lista um vetor de strings
//Parametros
//	Entrada: char *ptrVet - ponteiro para o primeiro string do vetor
//			 int NQtStrings - quantidade de strings do vetor
//			 char *ptrCabec - ponteiro para um string que contem o cabecalho da listagem
void ListarVetorString(char *ptrVet, int NQtStrings, char *ptrCabec) {
	int i;			//indice e contador
	LIMPAR_TELA;
	cout << "\n\t" << ptrCabec << endl;		//imprime o cabecalho
	for (i = 0; i < NQtStrings; i++,ptrVet +=EXTENSAO_NOME + 1) {		//loop da listagem
		cout << ptrVet << endl;
	}
	PAUSA;
}

//funcao que lista o vetor de clientes utilizando o ponteiro direto
//parametros
//	Entrada:CLIENTE *ptrVetCliente - endereco do primeiro cliente do vetor
//					 int nQtClientes - quantidade de clientes no vetor
//					 char *ptrCabec - cabecalho da listagem
void ListarClientes(CLIENTE *ptrVetCliente, int nQtClientes, char *ptrCabec) {
	int i;				//indice e contador
	LIMPAR_TELA;
	cout << "\n\t" << ptrCabec << endl;
	//loop de listagem
	for (i = 0; i < nQtClientes; i++,ptrVetCliente++) {
		cout << "Nome: " << ptrVetCliente->cNome << " Codigo: " << ptrVetCliente->nCodigo << " Saldo: " << ptrVetCliente->dSaldo << endl;
	}
	PAUSA;
}

//funcao que lista o vetor de clientes utilizando aritmetica de ponteiros
//parametros
//	Entrada:CLIENTE *ptrVetCliente - endereco do primeiro cliente do vetor
//					 int nQtClientes - quantidade de clientes no vetor
//					 char *ptrCabec - cabecalho da listagem
void ListarClienteAritmetica(CLIENTE *ptrVetCliente, int nQtClientes, char *ptrCabec) {
	int i;				//indice e contador
	LIMPAR_TELA;
	cout << "\n\t" << ptrCabec << endl;
	//loop de listagem
	for (i = 0; i < nQtClientes; i++) {
		cout << "Nome: " << (ptrVetCliente+ i)->cNome << " Codigo: " << (ptrVetCliente + i)->nCodigo << " Saldo: " << (ptrVetCliente + i)->dSaldo << endl;
	}
	PAUSA;
}

//funcao que lista o vetor de clientes utilizando aritmetica de ponteiros
//parametros
//	Entrada:CLIENTE *ptrVetCliente - endereco do primeiro cliente do vetor
//					 int nQtClientes - quantidade de clientes no vetor
//					 char *ptrCabec - cabecalho da listagem
void ListarClienteSprintf(CLIENTE *ptrVetCliente, int nQtClientes, char *ptrCabec) {
	int i;				//indice e contador
	char cWork[150];	//para trabalho do scanf
	LIMPAR_TELA;
	cout << "\n\t" << ptrCabec << endl;
	cout << "Codigo          Nome                     Saldo" << endl;
	//loop de listagem
	for (i = 0; i < nQtClientes; i++) {
		sprintf_s(cWork, sizeof(cWork), " %5d %-31s %8.2f", (ptrVetCliente + i)->nCodigo, (ptrVetCliente + i)->cNome, (ptrVetCliente + i)->dSaldo);
		cout << cWork << endl;
	}//for i
	PAUSA;
}

//entry point
void main(void) {
	int i, j,										//contadores e indexadores
		nValor = 100,								//inteira com valor inicial
		nValor1 = 500,								//idem
		nResultado,									//idem sem valor inicial
		vetInteiras[QTDE_INTEIRAS],					//vetor de inteiras sem valor inicial
		vetInt[] = { 30,50,101,201,55,78,99,204 },  //vetor com valores
		*ptrA,										//ponteiro de inteira sem valor inicial
		*ptrB = &nValor1,							//ponteiro apontando para nValor1
		*ptrC = &nResultado,						//ponteiro apontando para nResultado
		**ptrX = &ptrA;								//ponteiro que aponta para outro ponteiro
	char cNome[] = "Anderson Marin de Ramos",
		vetNomes[][EXTENSAO_NOME + 1] = {
		"Bianca Sayuri Futikami",
		"Charlie Brown",
		"Spike",
		"Cachalote" },
		*ptrChar;									//ponteiro do tipo char
	char cWork[200];								//vetor de char para trabalho

	CLIENTE stCliente,								//struct para conter os dados de um cliente
		*ptrSt = &stCliente,						//ptrSt aponta para a struct stCliente
		vetClientes[10];							//vetor de clientes


	ACENTUACAO_BRASILEIRA;

	//vamos trabalhar com struct
	stCliente.nCodigo = 100;			//codigo do cliente
	strcpy_s(stCliente.cNome, sizeof(stCliente.cNome), "Pedro da Silva");
	stCliente.dSaldo = 1234.45;			//saldo
	cout << "Codigo: " << ptrSt->nCodigo << " Nome: " << ptrSt->cNome << " Saldo: " << ptrSt->dSaldo << endl;
	PAUSA;

	for (i = 0; i < 10; i++) {
		vetClientes[i].nCodigo = i + 1;			//codigo do cliente
		strcpy_s(vetClientes[i].cNome, sizeof(stCliente.cNome), "Cliente de ordem ");
		_itoa_s(i + 1, cWork, sizeof(cWork), 10);
		strcat_s(vetClientes[i].cNome, sizeof(stCliente.cNome), cWork);
		vetClientes[i].dSaldo = (i + 1) * 12000.456;
	}

	ListarClientes(vetClientes, 10, "Listagem de clientes");
	ListarClienteAritmetica(vetClientes, 10, "Listagem de clientes com aritmetica de ponteiros");
	ListarClienteSprintf(vetClientes, 10, "Listagem de clientes com sprintf_s");

	nResultado = nValor + nValor1;	//soma de conteudos
	ptrA = &nValor;
	cout << "Endereço de nResultado" << &nResultado << "nResultado =" << nResultado << " &nValor ="<<&nValor << " nValor=" << nValor<<endl <<"&nValor1 = " << &nValor1 <<" nValor1 =" << nValor1 << endl;
	**ptrX = 55;				//nValor = 55
	*ptrC = *ptrA * *ptrB;		//multiplica atravez de ponteiros.
	cout << "Endereço de nResultado" << &nResultado << "nResultado =" << nResultado << " &nValor =" << &nValor << " nValor=" << nValor << endl << "&nValor1 = " << &nValor1 << " nValor1 =" << nValor1 << endl;
	PAUSA;

	ListarVetorInteiras(vetInt, sizeof(vetInt)/sizeof(int), "Listagem do VetInt");
	ListarVetorInt(vetInt, sizeof(vetInt) / sizeof(int), "Listagem do VetInt com Aritmetica de ponteiros");

	// preencher o vetInteiras com valores
	for (i = 0,ptrA=vetInteiras; i < QTDE_INTEIRAS; i++, ptrA++) {
		*ptrA = i * 13;
	}
	//restaurar o ptrA
	ptrA = vetInteiras;					//volta a apontar para a primeira inteira
	ListarVetorInteiras(ptrA, QTDE_INTEIRAS, "Listagem do vetInteiras");
	ListarVetorVetor(ptrA, QTDE_INTEIRAS, "Listagem do vetInteiras como vetor");
	ptrChar = &vetNomes[0][0];
	ListarVetorString(ptrChar, 4, "Listagem de cNomes");
	

	PAUSA;

}// main