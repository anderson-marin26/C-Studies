// Program for test Assembler fragment within c++
// FATEC - MC - AMR - 18/05/2016 - Version 0.0
#include "Meu.h"

// entry point
void main(void) {
	int nValorA = 1200,
		nValorB = 500,
		nValorC = 50,
		i = 0,
		nResultado = 0;
	i++;
	nResultado = nValorA + nValorB;
	nResultado *= nValorC;
	cout << "nResultado = " << nResultado << endl;
	PAUSA;
	_asm {
		mov nValorC, 10;				// [nValorC] = 10
		mov eax, nValorB;				// [eax] = [nValorB]
		imul eax, nValorC;				// [eax] = [eax] * [nValorC]
		mov nResultado, eax			// [nResultado] = [eax]
	}
	cout << "nResultado asm = " << nResultado << endl;
	PAUSA;
}// main