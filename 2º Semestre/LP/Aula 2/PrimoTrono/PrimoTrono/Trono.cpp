// Programa que exibe a maior inteira com sinal que digitarem
// FATEC Mogi das Cruzes - Anderson Marin de Ramos - 24/02/2016 - Versão 0.0
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
		if (i == 0)			// é a primeira inteira digitada?
			nTrono = nInteira;	//Copia a inteira no trono
		
		if (nInteira > nTrono)
			nTrono = nInteira; // copia inteira no trono
	}

	cout << "A maior inteira digitada foi: " << nTrono << endl;
	PAUSA;
}
