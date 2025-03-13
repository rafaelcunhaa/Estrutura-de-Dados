#include <iostream>
#include <string>
#include "lue.h"
#include "avl_tree.h"

using namespace std;

bool removerPrimeiroItemLueAvl(Lue &lista, NoAvl &primeiroItem){
    if(lista.comeco == nullptr) return false;

    NoLue *aux = lista.comeco;
    primeiroItem = lista.comeco->info;
    primeiroItem.qtdOcorrencias = lista.comeco->info.qtdOcorrencias;
    lista.comeco = aux->elo;
    if (lista.comeco == nullptr) {
        lista.fim = nullptr;
    }
    delete aux;
    return true;
}

void ordenarPorMenorOcorrenciaLueAvl(Lue &lista) {
    if (lista.comeco == nullptr || lista.comeco->elo == nullptr) {
        return;
    }

    NoLue *ordenada = nullptr;

    NoLue *atual = lista.comeco;
    while (atual != nullptr) {
        NoLue *proximo = atual->elo;

        if (ordenada == nullptr || ordenada->info.qtdOcorrencias > atual->info.qtdOcorrencias) {
            atual->elo = ordenada;
            ordenada = atual;
        } else {
            NoLue *atualOrdenada = ordenada;
            while (atualOrdenada->elo != nullptr && atualOrdenada->elo->info.qtdOcorrencias <= atual->info.qtdOcorrencias) {
                atualOrdenada = atualOrdenada->elo;
            }
            atual->elo = atualOrdenada->elo;
            atualOrdenada->elo = atual;
        }

        atual = proximo;
    }

    lista.comeco = ordenada;

    NoLue *aux = lista.comeco;
    while (aux->elo != nullptr) {
        aux = aux->elo;
    }
    lista.fim = aux;
}

void adicionarOcorrenciaAvl(Lue &lista, NoAvl novo){
  NoLue *aux = lista.comeco;
  while(aux != nullptr){
    if(aux->info.info == novo.info){
      aux->info.qtdOcorrencias++;    
    }

    aux = aux->elo;
  }  
}

void preencherLueAvl(Lue &lista, string frase){
  for(int i = 0; i < frase.size(); i++){
    NoAvl novo;
    novo.info = frase[i];
    novo.qtdOcorrencias = 0;
    if(!buscarLue(lista, novo)){
      inserirLue(lista, novo);
    }else{
      adicionarOcorrenciaAvl(lista, novo);
    }
  }
  ordenarPorMenorOcorrenciaLueAvl(lista);
}

void mostrarTodosItensComOcorrenciasLueAvl(Lue lista){
  NoLue *aux = lista.comeco;
  while(aux != nullptr){
      if(aux->info.info == '\0') cout << aux->info.qtdOcorrencias << ": NULO" << endl;
      else cout << aux->info.qtdOcorrencias << ": " << aux->info.info << endl;
      aux = aux->elo;
  }
}

void removerDoisPrimeirosECriarNovoNo(Lue &lista){
    NoAvl primeiro;
    NoAvl segundo;

    if (removerPrimeiroItemLueAvl(lista, primeiro) && removerPrimeiroItemLueAvl(lista, segundo)) {
        NoAvl novaArvore;
        novaArvore.info = '\0';


        // Criar nós para esquerda e direita
        novaArvore.esq = new NoAvl;
        novaArvore.esq->info = primeiro.info;
        novaArvore.esq->qtdOcorrencias = primeiro.qtdOcorrencias;
        novaArvore.esq->esq = primeiro.esq;
        novaArvore.esq->dir = primeiro.dir;

        novaArvore.dir = new NoAvl;
        novaArvore.dir->info = segundo.info;
        novaArvore.dir->qtdOcorrencias = segundo.qtdOcorrencias;
        novaArvore.dir->esq = segundo.esq;
        novaArvore.dir->dir = segundo.dir;

        novaArvore.qtdOcorrencias = novaArvore.esq->qtdOcorrencias + novaArvore.dir->qtdOcorrencias;

        inserirLue(lista, novaArvore);
        cout << "OCORRENCIAS: " << novaArvore.qtdOcorrencias << endl;
        if(novaArvore.esq->info == '\0' && novaArvore.dir->info == '\0') cout << "ESQUERDA -> NULO : " << novaArvore.esq->qtdOcorrencias << " / DIREITA -> NULO : " << novaArvore.dir->qtdOcorrencias << endl << endl;
        else if(novaArvore.esq->info == '\0') cout << "ESQUERDA -> NULO : " << novaArvore.esq->qtdOcorrencias << " / DIREITA -> " << novaArvore.dir->info << " : " << novaArvore.dir->qtdOcorrencias << endl << endl;
        else if(novaArvore.dir->info == '\0') cout << "ESQUERDA -> " << novaArvore.esq->info << " : " << novaArvore.esq->qtdOcorrencias << " / DIREITA -> NULO : " << novaArvore.dir->qtdOcorrencias << endl << endl;
        else cout << "ESQUERDA -> " << novaArvore.esq->info << " : " << novaArvore.esq->qtdOcorrencias << " / DIREITA -> " << novaArvore.dir->info << " : " << novaArvore.dir->qtdOcorrencias << endl << endl;
    }
    ordenarPorMenorOcorrenciaLueAvl(lista);
}

bool imprimirCodificado(NoAvl *raiz, char valor, string &codigo) {
    if (raiz == nullptr) return false;
    if (raiz->info == valor) return true;

    if (imprimirCodificado(raiz->esq, valor, codigo)) {
        codigo = "0" + codigo;
        return true;
    }
    if (imprimirCodificado(raiz->dir, valor, codigo)) {
        codigo = "1" + codigo;
        return true;
    }
    return false;
}

/*
void imprimirTabelaComStringCodificada(Lue lista, string frase) {
    if (lista.comeco == nullptr) return;
    NoAvl *arvore = &lista.comeco->info;

    for (int i=0; i < frase.size(); i++) {
        string codigo;
        cout << "[ " << frase[i] << " ]: ";
        if (imprimirCodificado(arvore, frase[i], codigo)) {
            cout << codigo;
        }
        cout << endl;
    }
}*/

bool verificarExistenciaDeCaracter(string frase, char caracter){
    for(int i=0; i < frase.size(); i++){
        if(frase[i] == caracter) return true;
    }
    return false;
}

void imprimirTabelaComStringCodificada(Lue lista, string frase){
    string fraseTemp = "";

    for(int i=0; i < frase.size(); i++){
        if(!verificarExistenciaDeCaracter(fraseTemp, frase[i])) fraseTemp += frase[i];
    }

    for(int i=0; i < fraseTemp.size(); i++){
        NoAvl *arvore = &lista.comeco->info;
        string codigo;
        cout << "[ " << fraseTemp[i] << " ]: ";
        if (imprimirCodificado(arvore, fraseTemp[i], codigo)){
            cout << codigo;
        }
        cout << endl;
    }
}

int main() {
  Lue listaArvores;
  inicializarLue(listaArvores);
  string frase;

  cout << "Digite uma frase: ";
  getline(cin, frase);

  cout << endl;

  preencherLueAvl(listaArvores, frase);
  mostrarTodosItensComOcorrenciasLueAvl(listaArvores);

  while(contarLue(listaArvores) > 1){
    cout << endl << endl;

    removerDoisPrimeirosECriarNovoNo(listaArvores);
    mostrarTodosItensComOcorrenciasLueAvl(listaArvores);
  }

  cout << endl << endl;

  imprimirTabelaComStringCodificada(listaArvores, frase);

  //mostrar_arvore(&listaArvores.comeco->info, 0);

  return 0;
}
