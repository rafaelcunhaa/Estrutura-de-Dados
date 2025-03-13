#include "produtos.hpp"
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

// FUNCIONANDO
void inicializarLueProdutos(LUE &lista) {
  lista.inicio = nullptr; // Deixa o início da lista como nulo
  lista.fim = nullptr;    // Deixa o final da lista como nulo
}

// FUNCIONANDO  
ifstream lerArquivoProdutos() {

  string nome_arquivo = "produtos.txt";

  ifstream arquivo(nome_arquivo);

  if (!arquivo.is_open()) {
    throw runtime_error("ERRO: Não foi possível abrir o arquivo de senhas.");
  }

  return arquivo; // Retorna o arquivo pronto para ser lido
}

// FUNCIONANDO
ofstream escreverArquivoProdutos() {

  string nome_arquivo = "produtos.txt";

  ofstream arquivo(nome_arquivo, ios::app);

  if (!arquivo.is_open()) {
    throw runtime_error("ERRO: Não foi possível abrir o arquivo de senhas.");
  }

  return arquivo; // Retorna o arquivo pronto para ser editado
}

// FUNCIONANDO
void limparLueProdutos(LUE &lista) {
  PRODUTO *aux1 =
      lista.inicio; // Cria um ponteiro auxiliar para o início da lista

  while (aux1 != nullptr) {
    PRODUTO *aux2 = aux1; // Fica criando um segundo poteiro auxiliar toda vez
                          // que o laço é executado
    aux1 = aux1->elo;     // Passa o primeiro ponteiro para o seguinte
    delete aux2;          // Exclui o conteúdo do segundo ponteiro
  }
}

// FUNCIONANDO
bool listaVaziaProdutos(LUE lista) {
  return (lista.inicio == nullptr && lista.fim == nullptr)
             ? true
             : false; // Retorna verdadeiro se a lista estiver vazia e falso se
                      // a lista conter algo
}

// FUNCIONANDO
void atribuirLueProdutos(LUE &lista) {
  ifstream arquivo = lerArquivoProdutos(); // Abre o arquivo para leitura
  if (!listaVaziaProdutos(lista))
    limparLueProdutos(lista); // Se a lista não estiver vazia, ela será limpa
  inicializarLueProdutos(lista); // Inicializa a lista

  string linha, nome, departamento;
  double valor;
  int quantidade;

  while (getline(arquivo, linha)) { // Separa o arquivo em linhas
    char *palavra =
        strtok(&linha[0], ":"); // Separa as palavras pelo caracter ":"
    nome = palavra;             // Atribuição para a devida variável

    palavra = strtok(nullptr, ":"); // Passa para a próxima palavra
    departamento = palavra;         // Atribuição para a devida variável

    palavra = strtok(nullptr, ":"); // Passa para a próxima palavra
    valor = stod(palavra);          // Atribuição para a devida variável

    palavra = strtok(nullptr, ":"); // Passa para a próxima palavra
    quantidade = stoi(palavra);     // Atribuição para a devida variável

    inserirFinalLueProdutos(
        lista, nome, departamento, valor,
        quantidade); // Insere o produto na lista(mandando os devidos atributos
                     // extraídos do arquivo)
  }

  arquivo.close();
}

// FUNCIONANDO
bool inserirFinalLueProdutos(LUE &lista, string nome, string departamento,
                             double valor, int quantidade) {
  PRODUTO *novoProduto = new PRODUTO; // Cria um produto

  if (novoProduto == nullptr)
    return false; // Se o produto for nulo, retorna falso

  // Atribuição de valores para o produto
  novoProduto->nome = nome;
  novoProduto->departamento = departamento;
  novoProduto->valor = valor;
  novoProduto->quantidade = quantidade;
  novoProduto->elo = nullptr;

  // Se a lista estiver vazia, o novo produto será o início e o fim da lista
  if (lista.inicio == nullptr) {
    lista.inicio = novoProduto;
    lista.fim = novoProduto;
  }
  // Se a lista não estiver vazia, o antigo fim da lista apontará para o novo
  // produto e o novo produto será o novo fim da lista
  else {
    lista.fim->elo = novoProduto;
    lista.fim = novoProduto;
  }
  return true;
}

// FUNCIONANDO
bool inserirFinalLueProdutos2(LUE **lista, string nome, string departamento,
                              double valor, int quantidade) {
  PRODUTO *novoProduto = new PRODUTO; // Cria um produto

  if (novoProduto == nullptr)
    return false; // Se o produto for nulo, retorna falso

  // Atribuição de valores para o produto
  novoProduto->nome = nome;
  novoProduto->departamento = departamento;
  novoProduto->valor = valor;
  novoProduto->quantidade = quantidade;
  novoProduto->elo = nullptr;

  // Se a lista estiver vazia, o novo produto será o início e o fim da lista
  if ((*lista)->inicio == nullptr) {
    (*lista)->inicio = novoProduto;
    (*lista)->fim = novoProduto;
  }
  // Se a lista não estiver vazia, o antigo fim da lista apontará para o novo
  // produto e o novo produto será o novo fim da lista
  else {
    (*lista)->fim->elo = novoProduto;
    (*lista)->fim = novoProduto;
  }
  return true;
}

// FUNCIONANDO
bool retirarLueProdutos(LUE &lista, string nomeProduto) {
  PRODUTO *aux, *aux2; // Criação de variáveis auxiliares

  if (lista.inicio == nullptr)
    return false; // Se a lista estiver vazia, retorna falso

  // Se o produto a ser retirado for o primeiro da lista
  if (lista.inicio->nome == nomeProduto) {
    aux = lista.inicio;
    if (lista.inicio == lista.fim) {
      lista.inicio = nullptr;
      lista.fim = nullptr;
    } else {
      lista.inicio = aux->elo;// Se não for o primeiro, o início da lista será o próximo produto
    }
    delete aux;
    return true;
  }
  // Se o produto a ser retirado for o último da lista
  aux = lista.inicio;
  aux2 = nullptr;
  while (aux != nullptr) {
    if (aux->nome == nomeProduto) {
      if (aux == lista.fim) {
        aux2->elo = nullptr;
        lista.fim = aux2;
      } else { // Se o produto a ser retirado não for o primeiro nem o último da
               // lista
        aux2->elo = aux->elo;
      }
      delete aux;
      return true;
    }
    aux2 = aux;
    aux = aux->elo;
  }
  return false;
}

// FUNCIONANDO
void mostrarLueProdutos(LUE lista) {

  PRODUTO *aux = lista.inicio; // Cria variável auxiliar

  if (listaVaziaProdutos(lista))
    cout << "Lista vazia."
         << endl; // Caso a lista esteja vazia, avisa o usuário

  // Enquanto o ponteiro auxiliar não for nulo, ele irá mostrar os valores de
  // cada produto
  cout << "-------------------" << endl;
  while (aux != nullptr) {
    cout << "PRODUTO: " << aux->nome << endl;
    cout << "DEPARTAMENTO: " << aux->departamento << endl;
    cout << "VALOR: R$" << aux->valor << endl;
    cout << "QUANTIDADE: " << aux->quantidade << endl;
    cout << "-------------------" << endl;
    aux = aux->elo;
  }
}

// FUNCIONANDO
bool buscarLueProdutos(LUE lista, string nomeProduto) {
  PRODUTO *aux = lista.inicio; // Criação de variável auxiliar

  // Varre toda a lista
  while (aux != nullptr) {
    if (aux->nome == nomeProduto) {
      return true; // Se encontrar o produto, retorna verdadeiro
    }
    aux = aux->elo;
  }
  return false; // Se varrer a lista e não encontrar o produto, retorna falso
}

// FUNCIONANDO
double retornaValorProduto(LUE lista, string nomeProduto) {
  PRODUTO *aux = lista.inicio;

  // Varre toda a lista
  while (aux != nullptr) {
    if (aux->nome == nomeProduto) {
      return aux->valor; // Se encontrar o produto, retorna o valor dele
    }
    aux = aux->elo;
  }
  return -1; // Se varrer toda a lista e não encuntra o produto, retorna -1
}

// FUNCIONANDO         
bool alterarValorProduto(LUE &lista, string nomeProduto, double novoValor) {

  ifstream arquivo = lerArquivoProdutos(); // Abre para leitura o arquivo origem

  string nome_arquivo = "produtos.txt";

  ofstream arq_temp_escrita(
      "temp.txt"); // Abre para escrita o arquivo temporário

  if (!arq_temp_escrita.is_open()) {
    cout << "Erro ao abrir o arquivo temporário!" << endl;
    return false;
  }

  bool verificacao = false;
  string linha;
  string _linha;

  while (getline(arquivo, linha)) { // Varre cada linha do arquivo origem
    if (!linha.find(nomeProduto)) { // Se encontrar o produto a ser alterado
      // Escreve no arquivo temporário a linha com as alterações
        verificacao = true;
      char *palavra = strtok(&linha[0], ":");
      _linha = palavra;
      palavra = strtok(nullptr, ":");
      _linha = _linha + ":" + palavra;
      palavra = strtok(nullptr, ":");
      arq_temp_escrita << _linha + ":" << fixed << setprecision(2) << novoValor;
      palavra = strtok(nullptr, ":");
      arq_temp_escrita << ":" << palavra << endl;
    } else {
      arq_temp_escrita
          << linha
          << endl; // Se não encontrar o produto, escreve a linha sem alterações
    }
  }

  // Fecha os arquivos
  arquivo.close();
  arq_temp_escrita.close();

  if(!verificacao){
    cout << endl;
    cout << "Produto não encontrado!" ;
    cout << endl;
  }

  remove("produtos.txt"); // Remove o arquivo origem
  rename("temp.txt",
         "produtos.txt"); // Renomeia o arquivo temporário para o arquivo origem

  // Inicializa a lista novamente(para renovar a lista ao alterar o preço de
  // algum produto)
  inicializarLueProdutos(lista);
  atribuirLueProdutos(lista);

  return true;
}

// FUNCIONANDO
bool removerProduto(LUE &lista, string nomeProduto) {
  // PRODUTO *aux = lista.inicio; // Cria variável auxiliar

  ifstream arquivo = lerArquivoProdutos(); // Abre para leitura o arquivo origem

  string nome_arquivo = "produtos.txt";

  ofstream arq_temp_escrita(
      "temp.txt"); // Abre para escrita o arquivo temporário

  if (!arq_temp_escrita.is_open()) {
    cout << "Erro ao abrir o arquivo temporário!" << endl;
    return false;
  }

  bool verificacao = false;

  string linha;
  string _linha;

  while (getline(arquivo, linha)) { // Varre cada linha do arquivo origem
    char *palavra = strtok(&linha[0], ":");
    if (palavra == nomeProduto) {
      verificacao = true;
      // Não faz nada, pois o produto a ser removido já foi encontrado
    } else { // Se não encontrar o produto, escreve a linha sem alterações
      arq_temp_escrita << palavra << ":";
      palavra = strtok(nullptr, ":");
      arq_temp_escrita << palavra << ":";
      palavra = strtok(nullptr, ":");
      arq_temp_escrita << palavra << ":";
      palavra = strtok(nullptr, ":");
      arq_temp_escrita << palavra << endl;
    }
  }

  // Fecha os arquivos
  arquivo.close();
  arq_temp_escrita.close();

  if(!verificacao){
    cout << endl;
    cout << "Produto não encontrado!" ;
    cout << endl;
  }

  remove("produtos.txt"); // Remove o arquivo origem
  rename("temp.txt",
         "produtos.txt"); // Renomeia o arquivo temporário para o arquivo origem

  // Inicializa a lista novamente(para renovar a lista ao alterar o preço de
  // algum produto)
  inicializarLueProdutos(lista);
  atribuirLueProdutos(lista);

  return true;
}

// FUNCIONANDO
bool adicionarProdutoEstoque(LUE &lista, string nomeProduto, string dept, double valor, int qtd){

  ifstream arquivo = lerArquivoProdutos(); // Abre para leitura o arquivo origem

  string nome_arquivo = "produtos.txt";

  ofstream arq_temp_escrita(
      "temp.txt"); // Abre para escrita o arquivo temporário

  if (!arq_temp_escrita.is_open()) {
    cout << "Erro ao abrir o arquivo temporário!" << endl;
    return false;
  }

  string linha;

  // Escreve todos os produtos no arquivo temporario
  while (getline(arquivo, linha)){
    char *palavra = strtok(&linha[0], ":");
    arq_temp_escrita << palavra << ":";
    palavra = strtok(nullptr, ":");
    arq_temp_escrita << palavra << ":";
    palavra = strtok(nullptr, ":");
    arq_temp_escrita << palavra << ":";
    palavra = strtok(nullptr, ":");
    arq_temp_escrita << palavra << endl;
  }
  // Adiciona o novo produto ao arquivo temporario
  arq_temp_escrita << nomeProduto << ":" << dept << ":" << fixed << setprecision(2) << valor << ":" << qtd << endl;

  // Fecha os arquivos
  arquivo.close();
  arq_temp_escrita.close();

  remove("produtos.txt"); // Remove o arquivo origem
  rename("temp.txt",
         "produtos.txt"); // Renomeia o arquivo temporário para o arquivo origem

  // Inicializa a lista novamente(para renovar a lista ao alterar o preço de
  // algum produto)
  inicializarLueProdutos(lista);
  atribuirLueProdutos(lista);

  return true;
}

// FUNCIONANDO
bool adicionarProdutoCarrinho(LUE &listaCompra, LUE listaProdutos,
                              string nomeProduto, int quantidade) {
  PRODUTO *aux = listaProdutos.inicio; // Criação de variável auxiliar

  while (aux != nullptr) {          // Varre a lista de produtos
    if (aux->nome == nomeProduto) { // Nome for igual ao desejado
      if (aux->quantidade >=
          quantidade) { // Quantidade em estoque for maior ou igual a desejada
        inserirFinalLueProdutos(listaCompra, aux->nome, aux->departamento,
                                aux->valor,
                                quantidade); // Adiciona o produto ao carrinho
        return true;
      }
    }
    aux = aux->elo;
  }
  return false;
}