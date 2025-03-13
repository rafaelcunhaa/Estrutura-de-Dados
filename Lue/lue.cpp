#include "lue.h"
#include <iostream>
using namespace std;

void inicializarLue(Lue &lista) {
    lista.comeco = nullptr;
    lista.fim = nullptr;
}

bool inserirFinalLue(Lue &lista, NoAvl valor) {
    NoLue *novo = new NoLue;
    if (novo == nullptr) return false;
    novo->info = valor;
    novo->elo = nullptr;
    if (lista.comeco == nullptr) { // Lista vazia
        lista.comeco = novo;
        lista.fim = novo;
    } else {
        lista.fim->elo = novo;
        lista.fim = novo;
    }
    return true;
}

bool inserirLue(Lue &lista, NoAvl valor) {
    NoLue *novo = new NoLue;
    novo->info = valor;
    if(novo->info.info != '\0') novo->info.qtdOcorrencias = 1;
    novo->info.altura = 1;
    if (novo == nullptr) return false;
    novo->elo = nullptr;
    if (lista.comeco == nullptr) { // Caso 1 - Lista vazia
        lista.comeco = novo;
        lista.fim = novo;
        return true;
    }
    if (valor.info <= lista.comeco->info.info) { // Caso 2 - Inserir no começo
        novo->elo = lista.comeco;
        lista.comeco = novo;
        return true;
    }
    if (valor.info >= lista.fim->info.info) { // Caso 3 - Inserir no final
        lista.fim->elo = novo;
        lista.fim = novo;
        return true;
    }
    // Caso 4 - Inserir no meio
    NoLue *anterior = lista.comeco;
    NoLue *atual = lista.comeco->elo;
    while (atual != nullptr && valor.info > atual->info.info) {
        anterior = atual;
        atual = atual->elo;
    }
    novo->elo = atual;
    anterior->elo = novo;
    return true;
}


void mostrarLue(Lue lista) {
    NoLue *aux = lista.comeco;
    while (aux != nullptr) {
        cout << aux->info.info << " ";
        aux = aux->elo;
    }
}

bool buscarLue(Lue lista, NoAvl valor) {
    NoLue *aux = lista.comeco;
    while (aux != nullptr) {
        if (aux->info.info == valor.info) return true;
        aux = aux->elo;
    }
    return false;
}

void liberarLue(Lue &lista) {
    NoLue *aux = lista.comeco;
    NoLue *aux2;
    while (aux != nullptr) {
        aux2 = aux->elo;
        delete aux;
        aux = aux2;
    }
}

bool retirarLue(Lue &lista, NoAvl valor) {
    NoLue *aux, *aux2;
    if (lista.comeco == nullptr) return false;
    // Caso 1 e 2
    if (lista.comeco->info.info == valor.info) {
        aux = lista.comeco;
        if (lista.comeco == lista.fim) {
            lista.comeco = nullptr;
            lista.fim = nullptr;
        } else {
            lista.comeco = aux->elo;
        }
        delete aux;
        return true;
    }
    // Caso 3 e 4
    aux = lista.comeco;
    aux2 = nullptr;
    while (aux != nullptr) {
        if (aux->info.info == valor.info) {
            if (aux == lista.fim) { // caso 3
                aux2->elo = nullptr;
                lista.fim = aux2;
            } else { // caso 4
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

int contarLue(Lue lista) {
    NoLue *aux = lista.comeco;
    int cont = 0;
    while (aux != nullptr) {
        cont++;
        aux = aux->elo;
    }
    return cont;
}

bool iguaisLue(Lue lista1, Lue lista2) {
    NoLue *aux1 = lista1.comeco;
    if (contarLue(lista1) != contarLue(lista2)) return false;
    while (aux1 != nullptr) {
        if (!buscarLue(lista2, aux1->info)) return false;
        aux1 = aux1->elo;
    }
    return true;
}

Lue diferencaLue(Lue lista1, Lue lista2) {
    Lue resposta;
    inicializarLue(resposta);
    NoLue *aux1 = lista1.comeco;
    while (aux1 != nullptr) {
        if (!buscarLue(lista2, aux1->info))
            inserirFinalLue(resposta, aux1->info);
        aux1 = aux1->elo;
    }
    return resposta;
}

int comunsLue(Lue lista1, Lue lista2) {
    int cont = 0;
    NoLue *aux1 = lista1.comeco;
    while (aux1 != nullptr) {
        if (buscarLue(lista2, aux1->info)) cont++;
        aux1 = aux1->elo;
    }
    return cont;
}
