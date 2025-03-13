#include "compra.hpp"
#include "produtos.hpp"
#include <cstring>
#include <iostream>

using namespace std;

// FUNCIONANDO
void inicializarLueCompras(COMPRASLUE &lista) {
  lista.inicio = nullptr; // Deixa o início da lista como nulo
  lista.fim = nullptr;    // Deixa o final da lista como nulo
}

// FUNCIONANDO
void limparLueCompras(COMPRASLUE &lista) {
  COMPRA *aux1 =
      lista.inicio; // Cria um ponteiro auxiliar para o início da lista

  while (aux1 != nullptr) {
    COMPRA *aux2 = aux1; // Fica criando um segundo poteiro auxiliar toda vez
                         // que o laço é executado
    aux1 = aux1->elo;    // Passa o primeiro ponteiro para o seguinte
    delete aux2;         // Exclui o conteúdo do segundo ponteiro
  }
}

// FUNCIONANDO
bool criarNovaCompra(COMPRASLUE &lista, string nome, string data) {
  COMPRA *novaCompra = new COMPRA; // Cria uma compra
  LUE *listaProdutos = new LUE;

  inicializarLueProdutos(*listaProdutos);

  if (novaCompra == nullptr)
    return false; // Se o produto for nulo, retorna falso

  // Atribuição de valores para o produto
  novaCompra->nome = nome;
  novaCompra->data = data;
  novaCompra->listaProdutos = listaProdutos;
  novaCompra->elo = nullptr;

  // Se a lista estiver vazia, o novo produto será o início e o fim da lista
  if (lista.inicio == nullptr) {
    lista.inicio = novaCompra;
    lista.fim = novaCompra;
  }
  // Se a lista não estiver vazia, o antigo fim da lista apontará para o novo
  // produto e o novo produto será o novo fim da lista
  else {
    lista.fim->elo = novaCompra;
    lista.fim = novaCompra;
  }
  return true;
}

// FUNCIONANDO
COMPRA *buscarCompraAtual(COMPRASLUE lista) {
  COMPRA *aux = lista.inicio;

  while (aux != nullptr) {
    if (aux->elo == nullptr) {
      return aux; // Retorna o último item da lista
    }
    aux = aux->elo;
  }
  return aux;
}

// FUNCIONANDO
bool adicionarProdutoCompra(COMPRASLUE &lista, LUE listaProdutos,
                            string nomeProduto, int quantidade) {
  COMPRA *atual = lista.fim;

  if (atual == nullptr)
    return false;

  PRODUTO *aux = listaProdutos.inicio;

  while (aux != nullptr) {
    if (aux->nome == nomeProduto) { // Se o nome for igual ao do produto atual
      if (aux->quantidade >= quantidade) { // Verifica se possui em estoque
        inserirFinalLueProdutos2(&atual->listaProdutos, aux->nome, // Coloca o produto no carrinho
           aux->departamento, aux->valor, quantidade);
        return true;
      }
    }
    aux = aux->elo;
  }
  return false;
}

// FUNCIONANDO
bool removerProdutoCompra(COMPRASLUE &lista, LUE listaProdutos,
                          string nomeProduto) {
  COMPRA *atual = buscarCompraAtual(lista);

  if (atual == nullptr)
    return false;

  PRODUTO *aux = listaProdutos.inicio;

  while (aux != nullptr) {
    if (aux->nome == nomeProduto) {
      retirarLueProdutos(*atual->listaProdutos, nomeProduto); // Encontra o produto e chama a função para remover da lista
      return true;
    }
    aux = aux->elo;
  }
  return false;
}

// FUNCIONANDO
double calcularTotal(COMPRASLUE lista) {
  COMPRA *atual = buscarCompraAtual(lista);
  PRODUTO *aux = atual->listaProdutos->inicio;
  double total = 0;

  // Laço para varrer todos os produtos do carrinho e multiplicar o preço unitário pela quantidade
  while (aux != nullptr) {
    total += aux->valor * aux->quantidade;
    aux = aux->elo;
  }
  return total;
}

// FUNCIONANDO
double finalizarVenda(COMPRASLUE &lista, LUE &listaProdutos,
                      string formaPagamento, double valorPago) {
  COMPRA *atual = lista.fim;
  PRODUTO *aux = atual->listaProdutos->inicio;
  double total = 0;

  while (aux != nullptr) {
    ifstream arquivo =
        lerArquivoProdutos(); // Abre para leitura o arquivo origem

    string nome_arquivo = "produtos.txt";

    ofstream arq_temp_escrita(
        "temp.txt"); // Abre para escrita o arquivo temporário

    if (!arq_temp_escrita.is_open()) {
      cout << "Erro ao abrir o arquivo temporário!" << endl;
      return false;
    }

    string linha;
    int novaQuantidade;

    while (getline(arquivo, linha)) { // Varre cada linha do arquivo origem
      char *palavra = strtok(&linha[0], ":");
      if (aux->nome == palavra) {
        // Escreve no arquivo temporário a linha com as alterações
        arq_temp_escrita << palavra << ":";
        palavra = strtok(nullptr, ":");
        arq_temp_escrita << palavra << ":";
        palavra = strtok(nullptr, ":");
        arq_temp_escrita << palavra << ":";
        palavra = strtok(nullptr, ":");
        novaQuantidade = stoi(palavra) - aux->quantidade;
        arq_temp_escrita << novaQuantidade << endl;
      } else {
        arq_temp_escrita << palavra << ":";
        palavra = strtok(nullptr, ":");
        arq_temp_escrita << palavra << ":";
        palavra = strtok(nullptr, ":");
        arq_temp_escrita << palavra << ":";
        palavra = strtok(nullptr, ":");
        arq_temp_escrita << palavra << endl;
      }
    }

    total += aux->valor * aux->quantidade;

    // Fecha os arquivos
    arquivo.close();
    arq_temp_escrita.close();

    remove("produtos.txt"); // Remove o arquivo origem
    rename(
        "temp.txt",
        "produtos.txt"); // Renomeia o arquivo temporário para o arquivo origem

    aux = aux->elo;
  }

  atual->formaPagamento = formaPagamento;
  atual->valorTotal = total;

  // Inicializa a lista novamente
  inicializarLueProdutos(listaProdutos);
  atribuirLueProdutos(listaProdutos);

  return total - valorPago;
}

// FUNCIONANDO
bool gerarEstatisticas(COMPRASLUE lista) {
  COMPRA *atual = lista.inicio;
  int qtdDinheiro = 0, qtdCartao = 0, qtdOutros = 0;
  double totalDinheiro = 0, totalCartao = 0, totalOutros = 0;

  if (atual == nullptr)
    return false;

  while (atual != nullptr) {
    if (atual->formaPagamento == "dinheiro") {
      qtdDinheiro++; // Adiciona 1 para o total de vendas no dinheiro
      totalDinheiro += atual->valorTotal; // Soma o valor total da venda ao total em dinheiro
    } else if (atual->formaPagamento == "cartão") {
      qtdCartao++; // Adiciona 1 para o total de vendas no cartão
      totalCartao += atual->valorTotal; // Soma o valor total da venda ao total em cartão
    } else if (atual->formaPagamento == "outro") {
      qtdOutros++; // Adiciona 1 para o total de vendas em outros
      totalOutros += atual->valorTotal; // Soma o valor total da venda ao total em outros
    }
    atual = atual->elo;
  }

  // Escreve na tela os resultados das estatísticas
  cout << "\nESTATÍSTICAS" << endl;
  cout << "DINHEIRO\nNúmero de vendas: " << qtdDinheiro << "\nValor total: R$"
       << totalDinheiro << endl;
  cout << "\nCARTÃO\nNúmero de vendas: " << qtdCartao << "\nValor total: R$"
       << totalCartao << endl;
  cout << "\nOUTROS\nNúmero de vendas: " << qtdOutros << "\nValor total: R$"
       << totalOutros << endl;

  return true;
}
