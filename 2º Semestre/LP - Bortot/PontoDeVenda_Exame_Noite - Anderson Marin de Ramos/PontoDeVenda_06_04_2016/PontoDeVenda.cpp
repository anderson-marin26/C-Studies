// Programa Ponto de Venda - Prova P1 - Linguagem de Programação
// FATEC - MC - JCB - 06/04/2016
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
		nCodigo = 0;                                    // para receber o código do produto
	int nPosicional;
	int nQtde;
	char cOpcao,                                        // opção de escolha do operador
		cWork[200],										// area de trabalho para o sprintf
		szNomeAluno[] = "Anderson Marin de Ramos";				// para receber o nome do aluno
    SYSTEMTIME stTime;                                  // para receber a data e hora do sistema
	PRODUTO stProduto;									// struct para conter os dados de um produto
	FILE *fdProduto;									// file descriptor do produto
	setlocale(LC_ALL, "portuguese_brazil");				// acentuação brasileira
	
    // <<<<< 0 >>>>>
	// No momento da entrega em pen drive renomeie o diretório
	//	PontoDeVenda_06_04_2016 para PontoDeVenda_SeuNome

    // <<<<< 1 >>>>>
	// 1. Codificar o seu nome em szNomeAluno



    // <<<<< 2 >>>>>
	//	Abrir o arquivo de produtos em modo r+b.
	//	Se ele existir deixar como está
	//	Se o arquivo não existir
	//		Abrir em modo w+b e se houver erro abortar o programa
	//	Fazer um loop gravando:
	//		Todos os produtos não estão cadastrados (flgCadastrado = false);
	//		nCodigoProduto = 1, 2, 3, ........QTDE_PRODUTOS
	//		Deixar o arquivo aberto


	// Recomendações:
	//	Todos os acessos para ler e gravar serão posicional porque o código do produto é 1, 2, 3, .........
	//	Codificar funções que fazem acessos posicionais para ler e gravar no cadastro de produtos
	//	Utilizar os comandos de acesso a disco:
	//        fopen_s, fread_s, fwrite, fseek
	if (fopen_s(&fdProduto, CAMINHO_CADASTRO, "r+b") != 0)
	{
		if (fopen_s(&fdProduto, CAMINHO_CADASTRO, "w+b") != 0)
		{
			cout << "Erro ao abrir o programa" << endl;
			PAUSA;
			return;
		}

		for (i = 0; i < QTDE_PRODUTOS; i++)
		{
			nPosicional = i;
			stProduto.flgCadastrado = false;
			stProduto.nCodigoProduto = i;
			if (!GravaPosicional(nPosicional * sizeof(PRODUTO), &stProduto, &fdProduto))
			{
				cout << "Falha ao gravar produto " << i << endl;
				PAUSA;
				return;
			}
		}

		
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
			stTime.wHour, stTime.wMinute, stTime.wSecond, szNomeAluno);
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
                //      ao operador, dar uma pausa e voltar ao menu. (ler posicional)
				LerPosicional(nCodigo, &stProduto, &fdProduto);
				
                // 3. Se não estiver cadastrado pedir a descrição (não esquecer que tem várias
				//		palavras para a descrição)
				
					if (stProduto.nCodigoProduto == nCodigo) {
						cout << "Produto já cadastrado" << endl;
						PAUSA;
						return;
					}
					cout << "Descricao do produto: " << endl;
					cin.ignore(1, EOF);
					cin.getline(stProduto.cDescricao, EXTENSAO_DESCRICAO, '\n');
					cout << "Preço unitario do produto: " << endl;
					// 4. Pedir o preço unitário 
					cin >> stProduto.dPrecoUnit; 
					cout << "Produto " << stProduto.cDescricao << " cadastrado com sucesso" << endl;
					stProduto.nCodigoProduto = nCodigo;
					// 5. Indicar que o produto está cadastrado (gravar posicional)
					stProduto.flgCadastrado = true;
					if (!GravaPosicional(nCodigo * sizeof(PRODUTO), &stProduto, &fdProduto))
					{
						cout << "Falha ao gravar produto " << stProduto.cDescricao << endl;
						PAUSA;
						return;
					}
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
                //      ao operador, dar uma pausa e voltar ao menu. (ler posicional)
				LerPosicional(nCodigo, &stProduto, &fdProduto);
				if (stProduto.nCodigoProduto != nCodigo)
				{
					cout << "Produto não cadastrado" << endl;
					PAUSA;
					break;
				}
				// 4. Exibir os dados do produto e pedir uma confirmação do operador por (S ou N)
				cout << "Produto " << stProduto.cDescricao << " de valor " << stProduto.dPrecoUnit << " sera excluido. Confirmar?(S / N)" << endl;
				cin >> cOpcao;
				toupper(cOpcao);
				// 5. Se o operador responder qualquer coisa diferente de 'S' ou 's' voltar
				//		ao menu
				if (cOpcao != 'S') {
					cout << "Operação cancelada" << endl;
					PAUSA;
					break;
				}
				// 6. Se o operador responder S (sim) indique na flgCadastrado que o produto
				//	foi excluido e gravar posicional.
				stProduto.flgCadastrado = false;
				if (!GravaPosicional(nCodigo * sizeof(PRODUTO), &stProduto, &fdProduto))
				{
					cout << "Falha ao gravar produto " << stProduto.cDescricao << endl;
					PAUSA;
					return;
				}
				cout << "Produto excluido com sucesso" << endl;
				PAUSA;
				break;                                    // volta ao menu
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
                //      ao operador, dar uma pausa e voltar ao menu. (ler posicional).
				LerPosicional(nCodigo, &stProduto, &fdProduto);
				if (stProduto.nCodigoProduto != nCodigo)
				{
					cout << "Produto não cadastrado" << endl;
					PAUSA;
					break;
				}
                // 4. Exibir os dados do produto inclusive o preço se o produto estiver 
                //      cadastrado
				cout << "Descrição do produto: " <<stProduto.cDescricao << " Codigo do Produto: " << stProduto.nCodigoProduto << " Preco do produto: " << stProduto.dPrecoUnit << endl;
                // 4. Dar uma pausa e voltar ao menu
				PAUSA;
                break;
            case VENDER_PRODUTO:
                // <<<<< 6 >>>>>
                // Vender um produto
				nCodigo = PedeUmProdutoValido("Vender produto");
				// 2. Verificar se a ação foi cancelada (retornou nCodigo == 0)
				//		Se a ação foi cancelada voltar ao menu
				if (nCodigo == 0)
					break;
                // 3. Verificar se o produto já está cadastrado e se não estiver, avisar
                //      ao operador, dar uma pausa e voltar ao menu. (ler posicional)
				LerPosicional(nCodigo, &stProduto, &fdProduto);
				if (nCodigo != stProduto.nCodigoProduto)
				{
					cout << "Produto não cadastrado" << endl;
					PAUSA;
					break;
				}
				//		Se o produto não estiver cadastrado avisar ao operador e voltar ao menu
                // 4. Exibir os dados do produto inclusive o preço se o produto estiver 
                //      cadastrado
				cout << "Descrição do produto: " << stProduto.cDescricao << " Codigo do Produto: " << stProduto.nCodigoProduto << " Preco do produto: " << stProduto.dPrecoUnit << endl;
                // 5. Pedir a quantidade a ser vendida
				cout << "Digite a quantidade a ser vendida: " << endl;
				cin >> nQtde;
                // 5. Multiplicar a quantidade pelo preço unitário
				nQtde = nQtde * stProduto.dPrecoUnit;
                // 6. Exibir o total da venda
				cout << "Total da venda foi de: " << nQtde << endl;
                // 7. Dar uma pausa e voltar ao menu.
				PAUSA;
                break;
            case SAIR_DO_PROGRAMA:
                cout << "\n\tDeseja sair realmente? (S ou N): ";
				cin >> cOpcao;
				if(cOpcao == 'S' || cOpcao == 's')			 // sair realmente?
				{
					// ativar o comando abaixo quando o programa estiver sendo testado
					fclose(fdProduto);						 // fechar o arquivo de produtos
					return;									 // volta ao Sistema Operacional
				}
                break;										 // volta ao menu
            default:
                cout << "Opção inválida!" << endl;
				PAUSA;
        } // switch
	} // while
} // main

bool GravaPosicional(int nPosicional, PRODUTO *ptrStProduto, FILE **fdProduto)
{
	if (fseek(*(fdProduto), nPosicional, SEEK_SET) != 0)	//erro de procura?
	{
		cout << "erro na procura de posição no arquivo." << endl;
		PAUSA;
		return false;
	}
	if (fwrite(ptrStProduto, sizeof(PRODUTO), 1, *fdProduto) == 0)	//erro de gravação?
	{
		cout << "Erro ao gravar arquivos em disco." << endl;
		PAUSA;
		return false;
	}
	return true;								// para não dar erro de compilação ????????????
}
bool LerPosicional(int nPosicional, PRODUTO *ptrStProduto, FILE **fdProduto)
{
	if (fseek(*(fdProduto), nPosicional, SEEK_SET) != 0)	//erro de procura?
	{
		cout << "erro na procura de posição no arquivo." << endl;
		PAUSA;
		return false;
	}
	if (fread_s(ptrStProduto, sizeof(PRODUTO), 1, 1, *fdProduto) == 0)	//erro de leitura?
	{
		cout << "Erro ao ler arquivo." << endl;
		PAUSA;
		return false;
	}
	return true;								// para não dar erro de compilação ????????????
}