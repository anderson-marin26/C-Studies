// Programa que exibe a maior inteira com sinal que digitarem
// FATEC Mogi das Cruzes - Anderson Marin de Ramos - 24/02/2016 - Vers�o 0.0
#include "Trono.h"

//entry point

void main(void) {
	int i,			// contador
		nTrono,		// para receber a maior inteira	
		nInteira;	// para receber as inteiras digitadas

					// loop do programa
	for (i = 0; i < QTDE_INTEIRAS; i++) {
		cout << "Digite a inteira de ordem " << i + 1 << " de " << QTDE_INTEIRAS << ": ";
		cin >> nInteira;	// recebe a inteira
		if (i == 0 || nInteira > nTrono)			// Vai para o trono?
			nTrono = nInteira;	//Copia a inteira no trono
	}

	cout << "A maior inteira digitada foi: " << nTrono << endl;
	PAUSA;
}
