#ifndef PRODUTOS_HPP
#define PRODUTOS_HPP

#include <iostream>
#include <fstream>

using namespace std;

struct PRODUTO {
    string nome;
    string departamento; // adega - higiene - doces - padaria - frios
    double valor; // valor unitário
    int quantidade; // qtd em estoque
    PRODUTO* elo; // Ponteiro para o próximo produto
};

struct LUE {
    PRODUTO* inicio; // Ponteiro para o primeiro produto da lista
    PRODUTO* fim; // Ponteiro para o último produto da lista
};

void inicializarLueProdutos(LUE &lista); // Função para inicializar lista

ifstream lerArquivoProdutos(); // Abrir arquivo de texto dos produtos para leitura

ofstream escreverArquivoProdutos(); // Abrir arquivo de texto dos produtos para escritura

void limparLueProdutos(LUE &lista); // Função para limpar todos os produtos da lista (será usada para renovar a lista ao alterar o preço de algum produto)

bool listaVaziaProdutos(LUE lista); // Função para verificar se a lista está vazia

void atribuirLueProdutos(LUE &lista); // Função para atribuir todos os produtos do arquivo de texto para a lista (é iniciada junto com a main)

bool inserirFinalLueProdutos(LUE &lista, string nome, string departamento, double valor, int quantidade); // Função para adicionar produto na lista geral

bool inserirFinalLueProdutos2(LUE **, string , string ,double , int ); // Função para adicionar produto no carrinho

bool retirarLueProdutos(LUE &lista, string nomeProduto); // Função para remover produto da lista

void mostrarLueProdutos(LUE lista); // Função para mostrar a lista de produtos

bool buscarLueProdutos(LUE lista, string nomeProduto); // Função para buscar produto na lista

double retornaValorProduto(LUE lista, string nomeProduto); // Função que retorna o valor de um produto(retorna -1 se não encontrar)

bool alterarValorProduto(LUE &lista, string nomeProduto, double novoValor); // Função para alterar o valor de um produto

bool removerProduto(LUE &lista, string nomeProduto); // Função para remover um produto tanto da lista, quanto do arquivo de texto

bool adicionarProdutoEstoque(LUE &lista, string nomeProduto, string dept, double valor, int qtd); // Adicionar produto no estoque e lue

#endif
