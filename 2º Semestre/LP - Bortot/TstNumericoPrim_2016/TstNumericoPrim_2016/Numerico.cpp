// Numeric test program
// FATEC-MC - AMR - 18/05/2016 - Version 0.0
#include "Meu.h"

// entry point
void main(void) {
	int nValor;
	while (true) {
		cout << "Digite uma inteira: ";
		nValor = TestNumerico(6);
		if (nValor == 999999) {
			return;
		}
		cout << endl << "Foi digitado: " << nValor<<endl;
	}
}// main

// function that test each caracter for non numeric caracter and warns with a BEEL when the test returns false
int TestNumerico(int nExtenMax) {
	int iIndProximo = 0,
		nCaractere;
	char cBufferTeclado[20];

	// infinity loop for receive each caracter
	for (iIndProximo = 0; ;) {
		nCaractere = _getch();				// get a caracter without echoing
		switch (nCaractere) {
			case BACK_SPACE:
				if (iIndProximo == 0) {		// doesnt type anything
					_putch(BELL);
					continue;
				}
				_putch(BACK_SPACE);
				_putch(SPACE);
				_putch(BACK_SPACE);
				iIndProximo--;
				break;
			case ENTER:
				if (iIndProximo == 0) {
					return 0;
				}
				return atoi(cBufferTeclado);				
			case '-':
				if (iIndProximo != 0) {
					_putch(BELL);
					continue;
				}
				cBufferTeclado[iIndProximo++] = nCaractere;
				cBufferTeclado[iIndProximo] = NULL;
				_putch(nCaractere);
				break;
			case '+':
				if (iIndProximo != 0) {
					_putch(BELL);
					continue;
				}
				cBufferTeclado[iIndProximo++] = nCaractere;
				cBufferTeclado[iIndProximo] = NULL;
				_putch(nCaractere);
				break;
			default:
				if (iIndProximo == nExtenMax) {
					_putch(BELL);
					break;
				}
				if (nCaractere<'0' || nCaractere>'9') {
					_putch(BELL);
					break;
				}
				// valid caracter
				cBufferTeclado[iIndProximo++] = nCaractere;
				cBufferTeclado[iIndProximo] = NULL;
				_putch(nCaractere);				
		}// infinity loop
	}// for iIndProximo
}