// Programa Ponto de Venda - Prova P1 - Linguagem de Programa��o
// FATEC - MC - AMR - 06/04/2016
#include "PontoDeVenda.h"

// Fun��o que pede um c�digo de produto v�lido ou zero para
//		cancelar a transa��o da main que est� sendo executada
//	Par�metros:
//		Entrada: char *szAcao - ponteiro para um string que indica qual
//								� a transa��o que est� sendo executada
int PedeUmProdutoValido(char *szAcao)
{
    int nCodigo = 0;                                         // para receber o c�digo do produto
	cout << "\n\tA��o: " << szAcao << endl;
    do
    {
        cout << "Informe um c�digo entre 1 e " << QTDE_PRODUTOS << endl
			<< "Ou zeros para cancelar a transa��o: ";
		cin >> nCodigo;									// pede o c�digo
        if (nCodigo == 0)                               // cancelar a transa��o?
            return 0;                                   // indica que a transa��o foi cancelada
    } while (nCodigo < 1 || nCodigo > QTDE_PRODUTOS);
    return nCodigo;                                     // devolve o c�digo que foi digitado
}

//
// Entry point do programa
//
void main(void)
{
	int i = 0,                                          // indexador e contador
		nCodigo = 0,									// para receber o c�digo do produto
		mult = 0;							// para realizar a multiplica��o
	char cOpcao,                                        // op��o de escolha do operador
		cWork[200],										// area de trabalho para o sprintf
		cNomeAluno[] = "Anderson Marin de Ramos",		// para receber o nome do aluno
		temp;											// variavel temporaria para valida��o
    SYSTEMTIME stTime;                                  // para receber a data e hora do sistema
	PRODUTO vetProdutos[QTDE_PRODUTOS];					// vetor de produtos
	setlocale(LC_ALL, "portuguese_brazil");				// acentua��o brasileira
	
    // <<<<< 0 >>>>>
	// No momento da entrega em pen drive renomeie o diret�rio
	//	PontoDeVenda_06_04_2016 para PontoDeVenda_SeuNome

    // <<<<< 1 >>>>>
	// 1. Codificar o seu nome em cNomeAluno



    // <<<<< 2 >>>>>
	// 1. Codificar um loop que inicializa o vetor indicando:
	//		Todos os produtos n�o est�o cadastrados (flgAtivo = false);
	//		nCodigoProduto = 1, 2, 3, ........QTDE_PRODUTOS
	
	for (i = 0; i < QTDE_PRODUTOS; i++) {
		vetProdutos[nCodigo].flgAtivo = false;
	}
	//
	// Loop infinito
	//
	
	while(true)
	{
		LIMPAR_TELA;
		GetLocalTime(&stTime);							// busca data e hora do sistema
		sprintf_s(cWork, 
			sizeof(cWork),"FATEC-MC - Ponto de venda em %02d/%02d/%04d �s %02d:%02d:%02d\n\tOperador: %s",
			stTime.wDay, stTime.wMonth, stTime.wYear,
			stTime.wHour, stTime.wMinute, stTime.wSecond, cNomeAluno);
		cout << "\n\t" << cWork << endl << endl;
		// exibir o menu
		cout << CADASTRAR_PRODUTO << " - Cadastrar novo produto" << endl;
		cout << EXCLUIR_PRODUTO << " - Excluir produto existente" << endl;
		cout << MOSTRAR_PRODUTO << " - Mostrar dados de um produto" << endl;
		cout << VENDER_PRODUTO << " - Vender um produto" << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do programa" << endl;
		cout << "\tSelecione: ";
		cin >> cOpcao;									// op��o escolhida pelo operador
		cOpcao = toupper(cOpcao);						// torna mai�scula

        // avaliar a op��o escolhida
        switch (cOpcao)
        {
            case CADASTRAR_PRODUTO:

                // <<<<< 3 >>>>>
                // Cadastrar o produto
                // 1. Pedir o c�digo do produto na fun��o PedeUmProdutoValido passando a
                //      a��o: "Cadastrar produto" e receber o c�digo em nC�digo.
				nCodigo = PedeUmProdutoValido("Cadastrar produto");
                // 2. Verificar se a a��o foi cancelada (retornou nCodigo == 0)
				//		Se a a��o foi cancelada voltar ao menu
				if (nCodigo == 0)
					break;
                // 3. Verificar se o produto j� est� cadastrado e se estiver, avisar
                //      ao operador, dar uma pausa e voltar ao menu.
				if (nCodigo == vetProdutos[nCodigo].nCodigoProduto)
				{
					cout << "Produto ja cadastrado" << endl;
					break;
				}
                // 3. Se n�o estiver cadastrado pedir a descri��o (n�o esquecer que tem v�rias
				//		palavras para a descri��o)
				else {
					cout << "Descricao do produto: " << endl;
					cin.ignore(1, EOF);
					cin.getline(vetProdutos[nCodigo].cDescricao, EXTENSAO_DESCRICAO,'\n');
				}
				// 4. Pedir o pre�o unit�rio 
				cout << "Pre�o unitario do produto: " << endl;
				cin >> vetProdutos[nCodigo].dPrecoUnitario;
                // 5. Indicar que o produto est� cadastrado
				cout << "Produto " << vetProdutos[nCodigo].cDescricao <<vetProdutos[nCodigo].nCodigoProduto<<" cadastrado com sucesso"<<endl;
				vetProdutos[nCodigo].nCodigoProduto = nCodigo;
				vetProdutos[nCodigo].flgAtivo = true;
				PAUSA;
                // 6. Voltar ao menu
                break;                                      // volta ao menu
            case EXCLUIR_PRODUTO:
                // <<<<< 4 >>>>>
                // Excluir o produto
                // 1. Pedir o c�digo do produto na fun��o PedeUmProdutoValido passando a
                //      a��o: "Excluir produto" e receber o c�digo em nC�digo.
				nCodigo = PedeUmProdutoValido("Excluir produto");
                // 2. Verificar se a a��o foi cancelada (retornou nCodigo == 0)
				//		Se a a��o foi cancelada voltar ao menu
				if (nCodigo == 0)
					break;
                // 3. Verificar se o produto j� est� cadastrado e se n�o estiver, avisar
                //      ao operador, dar uma pausa e voltar ao menu.
				if (nCodigo != vetProdutos[nCodigo].nCodigoProduto)
				{
					cout << "Produto n�o cadastrado" << endl;
					PAUSA;
					break;
				}
				// 4. Exibir os dados do produto e pedir uma confirma��o do operador por (S ou N)
				cout << "Produto " << vetProdutos[nCodigo].cDescricao << " de valor " << vetProdutos[nCodigo].dPrecoUnitario << " sera excluido. Confirmar?(S / N)" << endl;
				cin >> temp;
				toupper(temp);
				// 5. Se o operador responder qualquer coisa diferente de 'S' ou 's' voltar
				//		ao menu
				if (temp != 'S') {
					cout << "Opera��o cancelada" << endl;
					PAUSA;
					break;
				}
				// 6. Se o operador responder S (sim) indique na flgAtivo que o produto
				//	foi excluido
				vetProdutos[nCodigo].flgAtivo = false;
				cout << "Produto excluido com sucesso" << endl;
				PAUSA;
                break;                                      // volta ao menu
            case MOSTRAR_PRODUTO:
                // <<<<< 5 >>>>>
                // Mostrar o produto
                // 1. Pedir o c�digo do produto na fun��o PedeUmProdutoValido passando a
                //      a��o: "Mostrar produto" e receber o c�digo em nC�digo.
				nCodigo = PedeUmProdutoValido("Mostrar produto");
                // 2. Verificar se a a��o foi cancelada (retornou nCodigo == 0)
				//		Se a a��o foi cancelada voltar ao menu
				if (nCodigo == 0)
					break;
                // 3. Verificar se o produto j� est� cadastrado e se n�o estiver, avisar
                //      ao operador, dar uma pausa e voltar ao menu.
				if (nCodigo != vetProdutos[nCodigo].nCodigoProduto)
				{
					cout << "Produto n�o cadastrado" << endl;
					PAUSA;
					break;
				}
                // 4. Exibir os dados do produto inclusive o pre�o se o produto estiver 
                //      cadastrado
				cout << "Descri��o do produto: " << vetProdutos[nCodigo].cDescricao << " Codigo do Produto: " << vetProdutos[nCodigo].nCodigoProduto << " Preco do produto: " << vetProdutos[nCodigo].dPrecoUnitario<< endl;
                // 4. Dar uma pausa e voltar ao menu
				PAUSA;
                break;
            case VENDER_PRODUTO:
                // <<<<< 6 >>>>>
                // Vender um produto
                // 1. Pedir o c�digo do produto na fun��o PedeUmProdutoValido passando a
                //      a��o: "Vender produto" e receber o c�digo em nC�digo.
				nCodigo = PedeUmProdutoValido("Vender produto");
                // 2. Verificar se a a��o foi cancelada (retornou nCodigo == 0)
				//		Se a a��o foi cancelada voltar ao menu
				if (nCodigo == 0)
					break;
                // 3. Verificar se o produto j� est� cadastrado e se n�o estiver, avisar
                //      ao operador, dar uma pausa e voltar ao menu.
				if (nCodigo != vetProdutos[nCodigo].nCodigoProduto)
				{
					cout << "Produto n�o cadastrado" << endl;
					PAUSA;
					break;
				}
                // 4. Exibir os dados do produto inclusive o pre�o se o produto estiver 
                //      cadastrado
				cout << "Descri��o do produto: " << vetProdutos[nCodigo].cDescricao << " Codigo do Produto: " << vetProdutos[nCodigo].nCodigoProduto << " Preco do produto: " << vetProdutos[nCodigo].dPrecoUnitario << endl;
                // 5. Pedir a quantidade a ser vendida
				cout << "Digite a quantidade a ser vendida: " << endl;
				cin >> temp;
                // 5. Multiplicar a quantidade pelo pre�o unit�rio
				mult = mult * vetProdutos[nCodigo].dPrecoUnitario;
                // 6. Exibir o total da venda
				cout << "Total da venda foi de: " << mult<<endl;
                // 7. Dar uma pausa e voltar ao menu.
				PAUSA;
                break;
            case SAIR_DO_PROGRAMA:
                cout << "\n\tDeseja sair realmente? (S ou N): ";
				cin >> cOpcao;
				if(cOpcao == 'S' || cOpcao == 's')			 // sair realmente?
					return;									 // volta ao Sistema Operacional
                break;										 // volta ao menu
            default:
                cout << "Op��o inv�lida!" << endl;
				PAUSA;
        } // switch
	} // while
} // main