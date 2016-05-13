// Programa Ponto de Venda - Prova P1 - Linguagem de Programação
// FATEC - MC - AMR - 06/04/2016
#include "PontoDeVenda.h"

// Função que pede um código de produto válido ou zero para
//		cancelar a transação da main que está sendo executada
//	Parâmetros:
//		Entrada: char *szAcao - ponteiro para um string que indica qual
//								é a transação que está sendo executada
int PedeUmProdutoValido(char *szAcao)
{
    int nCodigo = 0;                                         // para receber o código do produto
	cout << "\n\tAção: " << szAcao << endl;
    do
    {
        cout << "Informe um código entre 1 e " << QTDE_PRODUTOS << endl
			<< "Ou zeros para cancelar a transação: ";
		cin >> nCodigo;									// pede o código
        if (nCodigo == 0)                               // cancelar a transação?
            return 0;                                   // indica que a transação foi cancelada
    } while (nCodigo < 1 || nCodigo > QTDE_PRODUTOS);
    return nCodigo;                                     // devolve o código que foi digitado
}

//
// Entry point do programa
//
void main(void)
{
	int i = 0,                                          // indexador e contador
		nCodigo = 0,									// para receber o código do produto
		mult = 0;							// para realizar a multiplicação
	char cOpcao,                                        // opção de escolha do operador
		cWork[200],										// area de trabalho para o sprintf
		cNomeAluno[] = "Anderson Marin de Ramos",		// para receber o nome do aluno
		temp;											// variavel temporaria para validação
    SYSTEMTIME stTime;                                  // para receber a data e hora do sistema
	PRODUTO vetProdutos[QTDE_PRODUTOS];					// vetor de produtos
	setlocale(LC_ALL, "portuguese_brazil");				// acentuação brasileira
	
    // <<<<< 0 >>>>>
	// No momento da entrega em pen drive renomeie o diretório
	//	PontoDeVenda_06_04_2016 para PontoDeVenda_SeuNome

    // <<<<< 1 >>>>>
	// 1. Codificar o seu nome em cNomeAluno



    // <<<<< 2 >>>>>
	// 1. Codificar um loop que inicializa o vetor indicando:
	//		Todos os produtos não estão cadastrados (flgAtivo = false);
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
			sizeof(cWork),"FATEC-MC - Ponto de venda em %02d/%02d/%04d às %02d:%02d:%02d\n\tOperador: %s",
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
		cin >> cOpcao;									// opção escolhida pelo operador
		cOpcao = toupper(cOpcao);						// torna maiúscula

        // avaliar a opção escolhida
        switch (cOpcao)
        {
            case CADASTRAR_PRODUTO:

                // <<<<< 3 >>>>>
                // Cadastrar o produto
                // 1. Pedir o código do produto na função PedeUmProdutoValido passando a
                //      ação: "Cadastrar produto" e receber o código em nCódigo.
				nCodigo = PedeUmProdutoValido("Cadastrar produto");
                // 2. Verificar se a ação foi cancelada (retornou nCodigo == 0)
				//		Se a ação foi cancelada voltar ao menu
				if (nCodigo == 0)
					break;
                // 3. Verificar se o produto já está cadastrado e se estiver, avisar
                //      ao operador, dar uma pausa e voltar ao menu.
				if (nCodigo == vetProdutos[nCodigo].nCodigoProduto)
				{
					cout << "Produto ja cadastrado" << endl;
					break;
				}
                // 3. Se não estiver cadastrado pedir a descrição (não esquecer que tem várias
				//		palavras para a descrição)
				else {
					cout << "Descricao do produto: " << endl;
					cin.ignore(1, EOF);
					cin.getline(vetProdutos[nCodigo].cDescricao, EXTENSAO_DESCRICAO,'\n');
				}
				// 4. Pedir o preço unitário 
				cout << "Preço unitario do produto: " << endl;
				cin >> vetProdutos[nCodigo].dPrecoUnitario;
                // 5. Indicar que o produto está cadastrado
				cout << "Produto " << vetProdutos[nCodigo].cDescricao <<vetProdutos[nCodigo].nCodigoProduto<<" cadastrado com sucesso"<<endl;
				vetProdutos[nCodigo].nCodigoProduto = nCodigo;
				vetProdutos[nCodigo].flgAtivo = true;
				PAUSA;
                // 6. Voltar ao menu
                break;                                      // volta ao menu
            case EXCLUIR_PRODUTO:
                // <<<<< 4 >>>>>
                // Excluir o produto
                // 1. Pedir o código do produto na função PedeUmProdutoValido passando a
                //      ação: "Excluir produto" e receber o código em nCódigo.
				nCodigo = PedeUmProdutoValido("Excluir produto");
                // 2. Verificar se a ação foi cancelada (retornou nCodigo == 0)
				//		Se a ação foi cancelada voltar ao menu
				if (nCodigo == 0)
					break;
                // 3. Verificar se o produto já está cadastrado e se não estiver, avisar
                //      ao operador, dar uma pausa e voltar ao menu.
				if (nCodigo != vetProdutos[nCodigo].nCodigoProduto)
				{
					cout << "Produto não cadastrado" << endl;
					PAUSA;
					break;
				}
				// 4. Exibir os dados do produto e pedir uma confirmação do operador por (S ou N)
				cout << "Produto " << vetProdutos[nCodigo].cDescricao << " de valor " << vetProdutos[nCodigo].dPrecoUnitario << " sera excluido. Confirmar?(S / N)" << endl;
				cin >> temp;
				toupper(temp);
				// 5. Se o operador responder qualquer coisa diferente de 'S' ou 's' voltar
				//		ao menu
				if (temp != 'S') {
					cout << "Operação cancelada" << endl;
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
                // 1. Pedir o código do produto na função PedeUmProdutoValido passando a
                //      ação: "Mostrar produto" e receber o código em nCódigo.
				nCodigo = PedeUmProdutoValido("Mostrar produto");
                // 2. Verificar se a ação foi cancelada (retornou nCodigo == 0)
				//		Se a ação foi cancelada voltar ao menu
				if (nCodigo == 0)
					break;
                // 3. Verificar se o produto já está cadastrado e se não estiver, avisar
                //      ao operador, dar uma pausa e voltar ao menu.
				if (nCodigo != vetProdutos[nCodigo].nCodigoProduto)
				{
					cout << "Produto não cadastrado" << endl;
					PAUSA;
					break;
				}
                // 4. Exibir os dados do produto inclusive o preço se o produto estiver 
                //      cadastrado
				cout << "Descrição do produto: " << vetProdutos[nCodigo].cDescricao << " Codigo do Produto: " << vetProdutos[nCodigo].nCodigoProduto << " Preco do produto: " << vetProdutos[nCodigo].dPrecoUnitario<< endl;
                // 4. Dar uma pausa e voltar ao menu
				PAUSA;
                break;
            case VENDER_PRODUTO:
                // <<<<< 6 >>>>>
                // Vender um produto
                // 1. Pedir o código do produto na função PedeUmProdutoValido passando a
                //      ação: "Vender produto" e receber o código em nCódigo.
				nCodigo = PedeUmProdutoValido("Vender produto");
                // 2. Verificar se a ação foi cancelada (retornou nCodigo == 0)
				//		Se a ação foi cancelada voltar ao menu
				if (nCodigo == 0)
					break;
                // 3. Verificar se o produto já está cadastrado e se não estiver, avisar
                //      ao operador, dar uma pausa e voltar ao menu.
				if (nCodigo != vetProdutos[nCodigo].nCodigoProduto)
				{
					cout << "Produto não cadastrado" << endl;
					PAUSA;
					break;
				}
                // 4. Exibir os dados do produto inclusive o preço se o produto estiver 
                //      cadastrado
				cout << "Descrição do produto: " << vetProdutos[nCodigo].cDescricao << " Codigo do Produto: " << vetProdutos[nCodigo].nCodigoProduto << " Preco do produto: " << vetProdutos[nCodigo].dPrecoUnitario << endl;
                // 5. Pedir a quantidade a ser vendida
				cout << "Digite a quantidade a ser vendida: " << endl;
				cin >> temp;
                // 5. Multiplicar a quantidade pelo preço unitário
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
                cout << "Opção inválida!" << endl;
				PAUSA;
        } // switch
	} // while
} // main