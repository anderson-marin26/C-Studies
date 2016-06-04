//Funcoes do programa de agencia bancaria
#include "Agencia.h"

int PedirCodigoCliente(char *ptrAcao) {
	int nCodigo;			// para receber o codigo
	cout << "\n\t" << ptrAcao << endl;
	do
	{
		// validando campo de codigo para somente numeros
		int error;
		do
		{
			error = 0;
			cout << "Código do cliente entre 1 e " << QTDE_CLIENTES << endl << "Ou zero para cancelar a transaçao: ";
			cin >> nCodigo;
			if (cin.fail())
			{
				cout << "Entre um codigo valido" << endl;
				error = 1;
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (error == 1);
		if (nCodigo == 0) {
			return 0;
		}
	} while (nCodigo < 1 || nCodigo > QTDE_CLIENTES);
	return nCodigo;
}

bool LerClientePosicional(int nCodigo, CLIENTE *ptrCliente, FILE *fdArquivo) {
	if (fseek(fdArquivo, (nCodigo - 1) * sizeof(CLIENTE), SEEK_SET) != 0) {
		return false;
	}
	if (fread_s(ptrCliente, sizeof(CLIENTE), sizeof(CLIENTE), 1, fdArquivo) == 0) {
		return false;
	}
	return true;
}

bool GravarClientePosicional(int nCodigo, CLIENTE *ptrCliente, FILE *fdArquivo) {
	if (fseek(fdArquivo, (nCodigo - 1) * sizeof(CLIENTE), SEEK_SET) != 0) {
		return false;
	}
	if (fwrite(ptrCliente, sizeof(CLIENTE), 1, fdArquivo) == 0) {
		return false;
	}
	return true;
}

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