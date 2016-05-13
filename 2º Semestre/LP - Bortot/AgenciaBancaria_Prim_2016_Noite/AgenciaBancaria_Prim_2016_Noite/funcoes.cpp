//Funcoes do programa de agencia bancaria
#include "Agencia.h"

int PedirCodigoCliente(char *ptrAcao) {
	int nCodigo;			// para receber o codigo
	cout << "\n\t" << ptrAcao << endl;
	do
	{
		cout << "Código do cliente entre 1 e " << QTDE_CLIENTES << endl << "Ou zero para cancelar a transaçao: ";
		cin >> nCodigo;
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