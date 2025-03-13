#include <iostream>
#include <cmath>
#include <ctime>
#include <chrono>

using namespace std;

class Cronometro {// Classe para cornometrar o tempo de execução das ordenações
private:
    chrono::time_point<chrono::high_resolution_clock> inicio, fim;
    bool rodando;

public:
    Cronometro() : rodando(false) {}

    void iniciar() {
        inicio = chrono::high_resolution_clock::now();
        rodando = true;
    }

    void parar() {
        fim = chrono::high_resolution_clock::now();
        rodando = false;
    }

    double tempoDecorrido() {
        if (rodando) {
            fim = chrono::high_resolution_clock::now();
        }
        return chrono::duration<double>(fim - inicio).count();
    }
};


// Função para mostrar os elementos
void mostrarVetor(int vetor[], int tamanho){
  for(int i = 0; i < tamanho; i++){
    cout << i << " - " << vetor[i] << endl;
  }
}


void shell(int vetor[], int inicio, int inc, int tamanho){
  int i, j, k, chave;
  bool achou;

  for(i = inicio + inc; i < tamanho; i += inc){
    j = inicio;
    achou = false;
    while(j < i && !achou){//achou = false
      if(vetor[i] < vetor[j]) achou = true;
      else j += inc;
    }
    if(achou){//achou = true
      chave = vetor[i];
      k = i - inc;
      while(k > j - inc){
        vetor[k + inc] = vetor[k];
        k = k - inc;
      }
      vetor[j] = chave;
    }
  }
}

// ordenação Shell
void ordenacaoShell(int vetor[], int tamanho, int numeroDePassos){
  for(int i = numeroDePassos; i >= 0; i--){
    int inc = pow(2, i);
    for(int j = 0; j <= inc; j++){
      shell(vetor, j, inc, tamanho);
    }
  }
}

// ordenação Inserção 
void ordenacaoInsercao(int vetor[], int tamanho){
  for(int j = 0; j < tamanho - 1; j++){
    int chave = vetor[j];
    int i = j - 1;
    while( i >= 0 && vetor[i] > chave){
      vetor[i + 1] = vetor[i];
      i--;
    }
    vetor[i + 1] = chave;
  }
}

// ordenação Bolha
void ordenacaoBolha(int vetor[], int tamanho){
  bool troca = true;
  int limite = tamanho - 1;
  int k;

  while(troca){
    troca = false;
    for(int i = 0; i <= limite - 1; i++){
      if(vetor[i] > vetor[i+1]){
        int temp = vetor[i];
        vetor[i] = vetor[i+1];
        vetor[i+1] = temp;
        k = i;
        troca = true;
      }
    }
    limite = k;
  }
}

// ordenação Quick
void ordenacaoQuick(int vetor[], int esq, int dir){
  int i = esq, j = dir, x = vetor[(i + j) / 2], aux;

  do{
    while(x > vetor[i]) i++;
    while(x < vetor[j]) j--;
    if(i <= j){
      aux = vetor[i];
      vetor[i] = vetor[j];
      vetor[j] = aux;
      i++;
      j--;
    }
  }while(i <= j);
  if(esq < j) ordenacaoQuick(vetor, esq, j);
  if(dir > i) ordenacaoQuick(vetor, i, dir);
}

// ordenação seleçao direta
void ordenacaoSelecaoDireta(int vetor[], int tamanho){
  for(int i = 0; i < tamanho - 1; i++){
    int pos_menor = i;
    for(int j = i + 1; j < tamanho; j++){
      if(vetor[j] < vetor[pos_menor]) pos_menor = j;
    }
    int temp = vetor[i];
    vetor[i] = vetor[pos_menor];
    vetor[pos_menor] = temp;
  }
}

// mesclar vetores
void mesclar(int vetor[], int comeco, int meio, int fim){
  int com1 = comeco;
  int com2 = meio + 1;
  int tam = fim - comeco + 1;
  int comAux = 0;
  int *vetAux = new int[tam];
  while(com1 <= meio && com2 <= fim){//enquanto não chegar no final de um dos vetores
    if(vetor[com1] < vetor[com2]){
      vetAux[comAux] = vetor[com1];
      com1++;
    }else{//se o elemento do vetor 1 for maior que o do vetor 2
      vetAux[comAux] = vetor[com2];
      com2++;
    }
    comAux++;
  }
  while(com1 <= meio){//se ainda tiver elementos no vetor 1
    vetAux[comAux] = vetor[com1];
    comAux++;
    com1++;
  }
  while(com2 <= fim){//se ainda tiver elementos no vetor 2
    vetAux[comAux] = vetor[com2];
    comAux++;
    com2++;
  }
  for(comAux = comeco; comAux <= fim; comAux++){//copiar o vetor auxiliar para o vetor original
    vetor[comAux] = vetAux[comAux - comeco];
  }
  delete []vetAux;
}

// ordenação Merge
void ordenacaoMergeSort(int vetor[], int comeco, int fim){
  int meio;
  if(comeco == fim) return;
  meio = (comeco + fim) / 2;
  ordenacaoMergeSort(vetor, comeco, meio);
  ordenacaoMergeSort(vetor, meio + 1, fim);
  mesclar(vetor, comeco, meio, fim);
}

// Função para preencher o vetor com valores aleatórios
void preencherVetorAleatoriamente(int vetor[], int tamanho){
  unsigned seed = time(0);
  srand(seed);
  for(int i = 0; i < tamanho; i++){
    vetor[i] = rand()%101;
  }
}

// Função para preencher o vetor com valores ordenados
void preencherVetorCrescente(int vetor[], int tamanho){
  for(int i = 0; i < tamanho; i++){
    vetor[i] = i;
  }
}

// Função para preencher o vetor com valores decrescentes
void preencherVetorDecrescente(int vetor[], int tamanho){
  for(int i = 0; i < tamanho; i++){
    vetor[i] = tamanho - i;
  }
}

// Função para copiar o vetor
void copiarVetorAuxiliar(int origem[], int destino[], int tamanhoVetores){
  for(int k = 0; k < tamanhoVetores; k++){
    destino[k] = origem[k];
  }
}

int main() {

  int qtdVetores, tamanhoVetores, vezesDeExecucaoDosMetodos;
  Cronometro cronometro;

  do{//pedir a quantidade de vetores
    cout << "Digite o numero de vetores a serem criados (minimo 2): ";
    cin >> qtdVetores;
  }while(qtdVetores < 2);

  do{//pedir o tamanho dos vetores
    cout << "Digite o tamanho dos vetores: ";
    cin >> tamanhoVetores;
  }while(tamanhoVetores < 1);

  int vetor[qtdVetores][tamanhoVetores];//vetor de vetores
  int vetAux[tamanhoVetores];//vetor auxiliar para copiar o vetor

  preencherVetorCrescente(vetor[0], tamanhoVetores);//preencher o vetor com valores crescentes
  preencherVetorDecrescente(vetor[1], tamanhoVetores);//preencher o vetor com valores decrescentes

  for(int i = 2; i < qtdVetores; i++){//preencher os demais vetores com valores aleatórios
    preencherVetorAleatoriamente(vetor[i], tamanhoVetores);
  }

  do{//pedir a quantidade de vezes de execução dos métodos
    cout << "Digite a quantidade de vezes que os metodos serao executados: ";
    cin >> vezesDeExecucaoDosMetodos;
  }while(vezesDeExecucaoDosMetodos < 1);

  cout << endl;

  /*for(int i = 0; i < vezesDeExecucaoDosMetodos; i++){
    cronometro.iniciar();
    copiarVetorAuxiliar(vetor[i], vetAux, tamanhoVetores);
    ordenacaoInsercao(vetAux, tamanhoVetores);
    cronometro.parar();
    cout << "Tempo de execucao InsertionSort - Vetor " << i + 1 << ": " << cronometro.tempoDecorrido() << " segundo(s)." << endl;
  }

  cout << endl;

  for(int i = 0; i < vezesDeExecucaoDosMetodos; i++){
    cronometro.iniciar();
    copiarVetorAuxiliar(vetor[i], vetAux, tamanhoVetores);
    ordenacaoShell(vetAux, tamanhoVetores, 2);
    cout << "Tempo de execucao ShellSort - Vetor " << i + 1 << ": " << cronometro.tempoDecorrido() << " segundo(s)." << endl;
  }

  cout << endl;

  for(int i = 0; i < vezesDeExecucaoDosMetodos; i++){
    cronometro.iniciar();
    copiarVetorAuxiliar(vetor[i], vetAux, tamanhoVetores);
    ordenacaoBolha(vetAux, tamanhoVetores);
    cout << "Tempo de execucao BubbleSort - Vetor " << i + 1 << ": " << cronometro.tempoDecorrido() << " segundo(s)." << endl;
  }

  cout << endl;

  for(int i = 0; i < vezesDeExecucaoDosMetodos; i++){
    cronometro.iniciar();
    copiarVetorAuxiliar(vetor[i], vetAux, tamanhoVetores);
    ordenacaoQuick(vetAux, 0, tamanhoVetores - 1);
    cout << "Tempo de execucao QuickSort - Vetor " << i + 1 << ": " << cronometro.tempoDecorrido() << " segundo(s)." << endl;
  }

  cout << endl;

  for(int i = 0; i < vezesDeExecucaoDosMetodos; i++){
    cronometro.iniciar();
    copiarVetorAuxiliar(vetor[i], vetAux, tamanhoVetores);
    ordenacaoSelecaoDireta(vetAux, tamanhoVetores);
    cout << "Tempo de execucao DirectSelectionSort - Vetor " << i + 1 << ": " << cronometro.tempoDecorrido() << " segundo(s)." << endl;
  }

  cout << endl;

  for(int i = 0; i < vezesDeExecucaoDosMetodos; i++){
    cronometro.iniciar();
    copiarVetorAuxiliar(vetor[i], vetAux, tamanhoVetores);
    ordenacaoMergeSort(vetAux, 0, tamanhoVetores - 1);
    cout << "Tempo de execucao MergeSort - Vetor " << i + 1 << ": " << cronometro.tempoDecorrido() << " segundo(s)." << endl;
  }

  cout << endl << "Fim da execucao." << endl;*/

  
  for(int j = 0; j < vezesDeExecucaoDosMetodos; j++){
    //INSERT SORT
    for(int i = 0; i < qtdVetores; i++){
        cronometro.iniciar();
        copiarVetorAuxiliar(vetor[i], vetAux, tamanhoVetores);
        ordenacaoInsercao(vetAux, tamanhoVetores);
        cronometro.parar();
        cout << "Tempo de execucao InsertionSort - Vetor " << i + 1 << " - Execução " << j + 1 << ": " << cronometro.tempoDecorrido() << " segundo(s)." << endl;
    }
    cout << endl;

    //SHELL SORT
    for(int i = 0; i < qtdVetores; i++){//preencher o vetor com valores crescentes
        cronometro.iniciar();
        copiarVetorAuxiliar(vetor[i], vetAux, tamanhoVetores);
        ordenacaoShell(vetAux, tamanhoVetores, 2);
        cronometro.parar();
        cout << "Tempo de execucao ShellSort - Vetor " << i + 1 << " - Execução " << j + 1 << ": " << cronometro.tempoDecorrido() << " segundo(s)." << endl;
    }
    cout << endl;
    
    //BUBBLE SORT
    for(int i = 0; i < qtdVetores; i++){//preencher o vetor com valores decrescentes
        cronometro.iniciar();
        copiarVetorAuxiliar(vetor[i], vetAux, tamanhoVetores);
        ordenacaoBolha(vetAux, tamanhoVetores);
        cronometro.parar();
        cout << "Tempo de execucao BubbleSort - Vetor " << i + 1 << " - Execução " << j + 1 << ": " << cronometro.tempoDecorrido() << " segundo(s)." << endl;
    }
    cout << endl;

    //QUICK SORT
    for(int i = 0; i < qtdVetores; i++){//preencher o vetor com valores aleatórios  
        cronometro.iniciar();
        copiarVetorAuxiliar(vetor[i], vetAux, tamanhoVetores);
        ordenacaoQuick(vetAux, 0, tamanhoVetores - 1);
        cronometro.parar();
        cout << "Tempo de execucao QuickSort - Vetor " << i + 1 << " - Execução " << j + 1 << ": " << cronometro.tempoDecorrido() << " segundo(s)." << endl;
    }
    cout << endl;

    //DIRECT SELECTION SORT
    for(int i = 0; i < qtdVetores; i++){//preencher o vetor com valores aleatórios
        cronometro.iniciar();
        copiarVetorAuxiliar(vetor[i], vetAux, tamanhoVetores);
        ordenacaoSelecaoDireta(vetAux, tamanhoVetores);
        cronometro.parar();
        cout << "Tempo de execucao DirectSelectionSort - Vetor " << i + 1 << " - Execução " << j + 1 << ": " << cronometro.tempoDecorrido() << " segundo(s)." << endl;
    }
    cout << endl;

    //MERGE SORT
    for(int i = 0; i < qtdVetores; i++){
        cronometro.iniciar();
        copiarVetorAuxiliar(vetor[i], vetAux, tamanhoVetores);
        ordenacaoMergeSort(vetAux, 0, tamanhoVetores - 1);
        cronometro.parar();
        cout << "Tempo de execucao MergeSort - Vetor " << i + 1 << " - Execução " << j + 1 << ": " << cronometro.tempoDecorrido() << " segundo(s)." << endl;
    }
    cout << endl;
  }

  cout << endl << "Fim da execucao." << endl;
}
