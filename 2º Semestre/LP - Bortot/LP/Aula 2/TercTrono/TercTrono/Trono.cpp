// Programa que exibe a maior inteira com sinal que digitarem
// FATEC Mogi das Cruzes - Anderson Marin de Ramos - 24/02/2016 - Versão 0.0
#include "Trono.h"

//entry point

void main(void) {
	int i,						// contador
		nTrono = INT_MIN,		// para receber a maior inteira digitada
		nInteira;				// para receber as inteiras digitadas
	for (i = 0; i < QTDE_INTEIRAS; i++) {
		cout << "Digite uma inteira: " << endl;
		cin >> nInteira;
		if (nInteira > nTrono) {
			nTrono = nInteira;
		}
	}
	cout << "A maior inteira digitada foi " << nTrono << endl;
	PAUSA;
}// main
