#include "avl_tree.h"

void prefixado(NoAvl *raiz) {
    if (raiz == nullptr) return;
    cout << raiz->info << " ";
    prefixado(raiz->esq);
    prefixado(raiz->dir);
}

void infixado(NoAvl *raiz) {
    if (raiz == nullptr) return;
    infixado(raiz->esq);
    cout << raiz->info << " ";
    infixado(raiz->dir);
}

void posfixado(NoAvl *raiz) {
    if (raiz == nullptr) return;
    posfixado(raiz->esq);
    posfixado(raiz->dir);
    cout << raiz->info << " ";
}

void liberar(NoAvl *raiz) {
    if (raiz == nullptr) return;
    liberar(raiz->esq);
    liberar(raiz->dir);
    delete raiz;
}

int getAltura(NoAvl *raiz) {
    return (raiz == nullptr) ? 0 : raiz->altura;
}

int calcularAltura(NoAvl *raiz) {
    int altE = getAltura(raiz->esq);
    int altD = getAltura(raiz->dir);
    return (altE > altD) ? altE + 1 : altD + 1;
}

NoAvl *rotacaoSimplesDireita(NoAvl *k) {
    NoAvl *x = k->esq;
    NoAvl *t2 = x->dir;

    k->esq = t2;
    x->dir = k;
    k->altura = calcularAltura(k);
    x->altura = calcularAltura(x);
    return x;
}

NoAvl *rotacaoSimplesEsquerda(NoAvl *k) {
    NoAvl *y = k->dir;
    NoAvl *t2 = y->esq;

    k->dir = t2;
    y->esq = k;
    k->altura = calcularAltura(k);
    y->altura = calcularAltura(y);
    return y;
}

NoAvl *rotacaoDuplaDireita(NoAvl *k) {
    k->esq = rotacaoSimplesEsquerda(k->esq);
    return rotacaoSimplesDireita(k);
}

NoAvl *rotacaoDuplaEsquerda(NoAvl *k) {
    k->dir = rotacaoSimplesDireita(k->dir);
    return rotacaoSimplesEsquerda(k);
}

NoAvl *rotacaoAVL(NoAvl *k) {
    if (getAltura(k->esq) > getAltura(k->dir)) {
        NoAvl *x = k->esq;
        if (getAltura(x->esq) >= getAltura(x->dir))
            return rotacaoSimplesDireita(k);
        else
            return rotacaoDuplaDireita(k);
    } else {
        NoAvl *y = k->dir;
        if (getAltura(y->dir) >= getAltura(y->esq))
            return rotacaoSimplesEsquerda(k);
        else
            return rotacaoDuplaEsquerda(k);
    }
}

NoAvl *inserir(NoAvl *raiz, char valor) {
    if (raiz == nullptr) {
        raiz = new NoAvl;
        if (raiz == nullptr) return nullptr;
        raiz->info = valor;
        raiz->altura = 1;
        return raiz;
    }
    if (valor < raiz->info)
        raiz->esq = inserir(raiz->esq, valor);
    else
        raiz->dir = inserir(raiz->dir, valor);

    raiz->altura = calcularAltura(raiz);
    int altE = getAltura(raiz->esq);
    int altD = getAltura(raiz->dir);
    if (abs(altE - altD) == 2)
        raiz = rotacaoAVL(raiz);
    return raiz;
}

char buscar_maior(NoAvl *raiz) {
    if (raiz->dir == nullptr)
        return raiz->info;
    else
        return buscar_maior(raiz->dir);
}

NoAvl *retirar(NoAvl *raiz, char valor) {
    if (raiz == nullptr) return nullptr;
    if (raiz->info == valor) {
        NoAvl *aux = raiz;
        if (raiz->esq == nullptr && raiz->dir == nullptr) { // Nó folha
            delete raiz;
            return nullptr;
        }
        if (raiz->esq != nullptr && raiz->dir == nullptr) { // Tem um filho à esquerda
            NoAvl *temp = raiz->esq;
            delete aux;
            return temp;
        }
        if (raiz->esq == nullptr && raiz->dir != nullptr) { // Tem um filho à direita
            NoAvl *temp = raiz->dir;
            delete aux;
            return temp;
        }
        raiz->info = buscar_maior(raiz->esq);
        raiz->esq = retirar(raiz->esq, raiz->info);
    } else if (valor < raiz->info)
        raiz->esq = retirar(raiz->esq, valor);
    else
        raiz->dir = retirar(raiz->dir, valor);

    raiz->altura = calcularAltura(raiz);
    int altE = getAltura(raiz->esq);
    int altD = getAltura(raiz->dir);
    if (abs(altE - altD) == 2)
        raiz = rotacaoAVL(raiz);
    return raiz;
}

bool buscar(NoAvl *raiz, char valor) {
    if (raiz == nullptr) return false;
    if (raiz->info == valor) return true;
    if (valor < raiz->info)
        return buscar(raiz->esq, valor);
    else
        return buscar(raiz->dir, valor);
}

void mostrar_arvore(NoAvl *raiz, int tab) {
    cout << endl;
    for (int i = 0; i < tab; i++) cout << " ";
    if (raiz == nullptr) {
        cout << "*";
        return;
    }
    cout << raiz->info;
    mostrar_arvore(raiz->esq, tab + 3);
    mostrar_arvore(raiz->dir, tab + 3);
}
