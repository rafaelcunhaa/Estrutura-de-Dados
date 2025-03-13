#include <iostream>
#include "produtos.hpp"
#include "compra.hpp"

LUE listaGeralProdutos;
COMPRASLUE listaGeralCompras;

//TESTADO
void menuGerente(){
  int opcao_gerente;
  string nome, departamento;
  double valor;
  int quantidade;
  

  do{
    cout << "\nEscolha a opção desejada:\n1-Adicionar produto ao estoque \n2-Retirar Produto \n3-Mostrar Produtos \n4-Buscar Produto \n5-Valor do Produto \n6-Alterar Valor do Produto \n7-Sair\n " << endl;
    cin >> opcao_gerente;
    

    if(opcao_gerente == 1){
      cout << "\nDigite o nome do produto: " << endl;
      cin >> nome;
      cout << "\nDigite o departamento do produto: " << endl;
      cin >> departamento;
      cout << "\nDigite o valor do produto: " << endl;
      cin >> valor;
      cout << "\nDigite a quantidade do produto: " << endl;
      cin >> quantidade;
       adicionarProdutoEstoque(listaGeralProdutos, nome, departamento, valor,quantidade);  
      cout << "\nItem adicionado com sucesso" << endl;
    }
    

    if(opcao_gerente == 2){
      cout << "\nDigite o nome do produto que deseja remover: " << endl;
      cin >> nome;
      removerProduto(listaGeralProdutos, nome);
    }
    

    if(opcao_gerente == 3){
      mostrarLueProdutos(listaGeralProdutos);
    }
    

    if(opcao_gerente == 4){
      cout << "\nDigite o nome do produto que deseja buscar: " << endl;
      cin >> nome;
      buscarLueProdutos(listaGeralProdutos, nome);
      if(!buscarLueProdutos(listaGeralProdutos, nome)){
        cout << "\nProduto não encontrado." << endl;
      }else{
        cout << "\nProduto encontrado." << endl;
      }
    }

    if(opcao_gerente == 5){
      cout << "\nDigite o nome do produto que deseja saber o valor: " << endl;
      cin >> nome;
      retornaValorProduto(listaGeralProdutos, nome);
      if(retornaValorProduto(listaGeralProdutos, nome) == -1){
        cout << "\nIten não encontrado" << endl;
      }else{
        cout << "\nValor do produto: " << retornaValorProduto(listaGeralProdutos, nome) << endl;
      }
    }

    if(opcao_gerente == 6){
      cout << "\nDigite o nome do produto que deseja alterar o valor: " << endl;
      cin >> nome;
      cout << "\nDigite o novo valor do produto: " << endl;
      cin >> valor;
      alterarValorProduto(listaGeralProdutos, nome, valor);
    }
    
    }
  while(opcao_gerente != 7);
  
}

// FINALIZADA
void menuCompraAberta(){
  
  int opcao_compraAberta;
  string nomeProduto;
  int quantidade;
  string finalizadora;
  int op_finalizadora;
  double valorPago;

  do{
  cout << "\nDigite qual é a operação que você quer fazer: \n1. Mostrar lista de produtos\n2. Adicionar produto ao carrinho\n3. Remover produto do carrinho\n4. Mostrar carrinho\n5. Finalizar compra\nSelecionado:\n ";
  cin >> opcao_compraAberta;
  
  if(opcao_compraAberta == 2){
    cout << "\nDigite o nome do produto a ser adicionado: ";
    cin >> nomeProduto;
    cout << "\nDigite a quantidade a ser adicionada: ";
    cin >> quantidade;
    adicionarProdutoCompra(listaGeralCompras, listaGeralProdutos, nomeProduto, quantidade);
    cin.ignore();
  }
  
  else if(opcao_compraAberta == 3){
    cout << "\nDigite o nome do produto a ser removido: ";
    cin >> nomeProduto;
    removerProdutoCompra(listaGeralCompras, listaGeralProdutos, nomeProduto);
    if(!removerProdutoCompra(listaGeralCompras, listaGeralProdutos, nomeProduto)){
    cout << "\nProduto não encontrado." << endl;
    }
    cin.ignore();
  }
  
  else if(opcao_compraAberta == 1){
    mostrarLueProdutos(listaGeralProdutos);
    cin.ignore();
  }
  else if(opcao_compraAberta == 4){
    COMPRA *atual = buscarCompraAtual(listaGeralCompras);
    mostrarLueProdutos(*atual->listaProdutos);
    cin.ignore();
  }
  }while(opcao_compraAberta != 5);

  cout << "\nTotal: R$" << calcularTotal(listaGeralCompras) << endl;
  
  cout << "\nQual é a forma de pagamento?\n1. Dinheiro\n2. Cartão\n3. Outros\nSelecionado: ";
  cin >> op_finalizadora;
  if(op_finalizadora == 1) finalizadora = "dinheiro";
  else if(op_finalizadora == 2) finalizadora = "cartão";
  else finalizadora = "outros";
  
  cout << "\nQuanto foi pago? ";
  cin >> valorPago;

  cout << "\nTroco: R$" << finalizarVenda(listaGeralCompras, listaGeralProdutos, finalizadora, valorPago) * -1 << endl;
  cin.ignore();
}

// VERIFICAAAAAAAAAAAAAAAAAAAAAAAAR
void menuCompra(){
  string nome, data;
  
  cout << "\nDigite o nome do cliente:\n ";
  cin >> nome;
  cout << "\nDigite a data da compra:\n ";
  cin >> data;
  criarNovaCompra(listaGeralCompras, nome, data);
  
  menuCompraAberta();
}


void menuVendedor(){
  int op_menuVendedor = 0;
  
  cin.ignore();
  
  do{
    cout << "\nMENU VENDEDOR\nEscolha a operação a ser realizada\n1. Iniciar nova compra\n2. Verificar estatísticas\n3. Sair\nSelecionado: ";
    cin >> op_menuVendedor;
    if(op_menuVendedor == 1) menuCompra();
    if(op_menuVendedor == 2) gerarEstatisticas(listaGeralCompras);
  }while(op_menuVendedor != 3);
}

void menuInicial(){

  inicializarLueProdutos(listaGeralProdutos);
  atribuirLueProdutos(listaGeralProdutos);

  inicializarLueCompras(listaGeralCompras);
  
  int op_menu;

  cout << "BEM VINDO AO MERCADO!" << endl;
  cout << "O que deseja fazer?\n[1] Menu Gerente\n[2] Menu Vendedor\n[0] Sair\nSelecionado: ";
  cin >> op_menu;

  if(op_menu == 1) menuGerente();

  if(op_menu == 2) menuVendedor();
}