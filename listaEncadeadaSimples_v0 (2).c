#include <stdio.h>    // printf
#include <stdlib.h>   // malloc, free

/* =========================
   ESTRUTURAS BÁSICAS
   ========================= */

// Nó da lista encadeada (SLL: singly linked list)
typedef struct No {
    int valor;            // dado armazenado no nó
    struct No *prox;      // ponteiro para o próximo nó (ou NULL se for o último)
} No;

// "Cabeçalho" da lista encadeada
typedef struct {
    No *head;             // ponteiro para o primeiro nó (cabeça) ou NULL se vazia
    No *tail;             // ponteiro para o último nó (cauda) ou NULL se vazia
    int tamanho;          // quantidade atual de elementos (espelha "lista->tamanho" da versão estática)
} ListaEncadeada;

/* =========================
   OPERAÇÕES BÁSICAS
   ========================= */

// Inicializa a lista (equivalente ao "inicializarLista" da estática)
void inicializarLista(ListaEncadeada *lista) {

}

// Insere um elemento NO FIM da lista (O(1) usando 'tail')
void inserirNoFinal(ListaEncadeada *lista, int elemento) {
    // 1) Aloca um novo nó

}

// Insere um elemento NO INÍCIO da lista (O(1))
void inserirNoInicio(ListaEncadeada *lista, int valor) {

}

// Atualiza (modifica) o valor de um nó por ÍNDICE existente (0..tamanho-1)
void atualizarElemento(ListaEncadeada *lista, int index, int valor) {

}

// Remove um elemento por ÍNDICE (desalocando o nó)
void removerElemento(ListaEncadeada *lista, int index) {

}

// Busca um valor na lista e retorna seu índice (ou -1 se não encontrado)
int buscarElemento(const ListaEncadeada *lista, int valor) {

}

// Retorna o número atual de elementos (O(1))
int tamanhoLista(const ListaEncadeada *lista) {

}

// Exibe os elementos no formato "a -> b -> c -> NULL"
void exibirLista(const ListaEncadeada *lista) {

}

// Libera TODOS os nós da lista (boa prática para evitar vazamento de memória)
void liberarLista(ListaEncadeada *lista) {

}

/* =========================
   PROGRAMA DE TESTE (main)
   ========================= */

int main(void) {
    ListaEncadeada lista;                // declara a lista
    inicializarLista(&lista);            // zera head/tail/tamanho

    // Teste: inserções no final e no início (espelhando a estática)
    inserirNoFinal(&lista, 1);           // [1]
    inserirNoFinal(&lista, 20);          // [1, 20]
    inserirNoInicio(&lista, 100);        // [100, 1, 20]

    // Teste: atualizações por índice
    atualizarElemento(&lista, 0, 10);    // [10, 1, 20]
    atualizarElemento(&lista, 1, 30);    // [10, 30, 20]
    atualizarElemento(&lista, 2, 40);    // [10, 30, 40]

    // Exibe lista após modificações
    exibirLista(&lista);                 // esperado: 10 -> 30 -> 40 -> NULL

    // Remoção por índice
    removerElemento(&lista, 1);          // remove o elemento na posição 1 (30)
    exibirLista(&lista);                 // esperado: 10 -> 40 -> NULL

    // Busca de elemento
    int indice = buscarElemento(&lista, 40);
    if (indice != -1) {
        printf("Elemento 40 encontrado no índice %d\n", indice);
    } else {
        printf("Elemento 40 não encontrado.\n");
    }

    // Tamanho atual da lista
    printf("Tamanho da lista: %d\n", tamanhoLista(&lista));

    // Libera toda a memória alocada
    liberarLista(&lista);

    return 0;
}
