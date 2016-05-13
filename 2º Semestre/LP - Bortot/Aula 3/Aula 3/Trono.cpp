// programa que exibe a maior e a menor inteira com sinal digitada
// FATEC-MC - RVC - 02-03-2016 - Versão 0.0
#include "Trono.h"
//
// Entry point do programa
//

void main(void) {
	int i,						// contador
		nTronoMax = INT_MIN,		// para receber a maior inteira digitada
		nTronoMin = INT_MAX,
		nInteira,				// para receber as inteiras digitadas
		nQtdInteiras;
	setlocale(LC_ALL, "portuguese_brazil"); // para acentuação no video
	//loop para receber uma quantidade valida ou zeros para cancelar o programa
	do {
		cout << "digite a quantidade de inteiras entre " << QTDE_MINIMA << " e " << QTDE_MAXIMA << endl
			<< " ou digite 0 para sair do programa" << endl;
		cin >> nQtdInteiras;

		if (nQtdInteiras == 0) {
			return;
		}
	} while (nQtdInteiras < QTDE_MINIMA || nQtdInteiras > QTDE_MAXIMA);

	for (i = 0; i < nQtdInteiras; i++) {
		cout << "Digite a inteira " << i + 1<< " de " << nQtdInteiras << " : " << endl;
		cin >> nInteira;
		if (nInteira > nTronoMax) {
				nTronoMax = nInteira;
		}
		if (nInteira < nTronoMin) {
			nTronoMin = nInteira;
		}
	}
	cout << "A maior inteira digitada foi: " << nTronoMax << endl;
	cout << "A menor inteira digitada foi: " << nTronoMin << endl;
	PAUSA;
}// main
