// Primeiro programa de LP
// FATEC - Mogi das Cruzes - Anderson Marin de Ramos - Copyright 2016
#include "Primo.h"
// Entry point do programa
void main(void) {
	char cTexto[80];	//para receber um texto
	cout << "Digite um texto: ";
	cin.getline(cTexto, sizeof(cTexto) - 1, '\n');		// recebe um texto
	cout << "O texto digitado foi: " << cTexto << endl;
	PAUSA;
}