#ifndef COMPRA_HPP
#define COMPRA_HPP

#include "produtos.hpp"

using namespace std;

struct COMPRA{
  string nome;
  string data;
  string formaPagamento;
  double valorTotal;
  bool finalizada;
  LUE *listaProdutos;
  COMPRA *elo;
};

struct COMPRASLUE{
  COMPRA *inicio;
  COMPRA *fim;
};

void inicializarLueCompras(COMPRASLUE &lista); // Inicializa a lista de compras efetuadas

void limparLueCompras(COMPRASLUE &lista); // Limpa a lista de compras efetuadas

bool criarNovaCompra(COMPRASLUE &lista, string nome, string data); // Função para iniciar uma nova compra

COMPRA *buscarCompraAtual(COMPRASLUE lista); // Encontra a última compra(a atual)

bool adicionarProdutoCompra(COMPRASLUE &lista, LUE listaProdutos, string nomeProduto, int quantidade); // Adiciona um produto ao carrinho

bool removerProdutoCompra(COMPRASLUE &lista, LUE listaProdutos, string nomeProduto); // Remove produto do carrinho

double calcularTotal(COMPRASLUE lista);

double finalizarVenda(COMPRASLUE &lista, LUE &listaProdutos, string formaPagamento, double valorPago);

bool gerarEstatisticas(COMPRASLUE lista);

#endif