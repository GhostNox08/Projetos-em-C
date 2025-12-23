/* =========================================================
   DEFINIÇÃO DA FILA COM PRIORIDADE - USANDO LISTA ENCADEADA SIMPLES
   ========================================================= */
#include <stdio.h>    // printf
#include <stdlib.h>   // malloc, free

// Define o nó da fila, armazenando valor, prioridade e ponteiro para o próximo nó
typedef struct NoFila {
    int valor;                    // valor armazenado no nó
    int prioridade;               // prioridade do nó (menor valor = maior prioridade)
    struct NoFila *prox;          // ponteiro para o próximo nó
} NoFila;

// Estrutura "FilaPrioridade": guarda ponteiros para a frente (head) e trás (tail), e o tamanho
typedef struct {
    NoFila *frente;               // primeiro elemento (a ser removido no dequeue)
    int tamanho;                  // quantidade de elementos
} FilaPrioridade;

// Inicializa a fila de prioridade vazia
void fila_init(FilaPrioridade *q) {
    q->frente = NULL;
    q->tamanho = 0;
}

// Retorna 1 se a fila está vazia; 0 caso contrário
int fila_is_empty(const FilaPrioridade *q) {
    return (q->frente == NULL);
}

// Enfileira (enqueue) um novo valor na posição correta de prioridade
// Retorna 1 em sucesso; 0 se malloc falhar
int fila_enqueue(FilaPrioridade *q, int valor, int prioridade) {
    NoFila *novo = (NoFila*)malloc(sizeof(NoFila)); // aloca nó
    if (!novo) {
        printf("Erro: sem memória ao enfileirar.\n");
        return 0;
    }
    novo->valor = valor;
    novo->prioridade = prioridade;
    novo->prox = NULL;

    // Se a fila estiver vazia ou o novo nó tiver a maior prioridade
    if (fila_is_empty(q) || prioridade < q->frente->prioridade) {
        novo->prox = q->frente;
        q->frente = novo;
    } else {
        // Encontra a posição correta para inserir o novo nó
        NoFila *atual = q->frente;
        while (atual->prox != NULL && atual->prox->prioridade <= prioridade) {
            atual = atual->prox;
        }
        novo->prox = atual->prox;
        atual->prox = novo;
    }
    
    q->tamanho++;
    return 1;
}

// Desenfileira (dequeue) o valor da FRENTE e o retorna via *out
// Retorna 1 em sucesso; 0 se a fila estiver vazia
int fila_dequeue(FilaPrioridade *q, int *out) {
    if (fila_is_empty(q)) {
        printf("Erro: fila vazia ao desenfileirar.\n");
        return 0;
    }
    NoFila *rem = q->frente;
    if (out) *out = rem->valor;
    q->frente = rem->prox;
    
    free(rem);
    q->tamanho--;
    return 1;
}

// Espia o valor da frente (o de maior prioridade) sem remover
// Retorna 1 em sucesso; 0 se a fila estiver vazia
int fila_front(const FilaPrioridade *q, int *out) {
    if (fila_is_empty(q)) {
        printf("Aviso: fila vazia ao consultar frente.\n");
        return 0;
    }
    if (out) *out = q->frente->valor;
    return 1;
}

// Retorna o número de elementos na fila
int fila_size(const FilaPrioridade *q) {
    return q->tamanho;
}

// Remove todos os nós da fila, deixando-a vazia
void fila_clear(FilaPrioridade *q) {
    NoFila *atual = q->frente;
    while (atual) {
        NoFila *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    q->frente = NULL;
    q->tamanho = 0;
}

/* =========================
   PROGRAMA DE TESTE
   ========================= */
int main(void) {
    FilaPrioridade fila;
    fila_init(&fila);

    fila_enqueue(&fila, 10, 3); // Valor 10, Prioridade 3
    fila_enqueue(&fila, 20, 1); // Valor 20, Prioridade 1 (maior prioridade)
    fila_enqueue(&fila, 30, 2); // Valor 30, Prioridade 2
    fila_enqueue(&fila, 40, 1); // Valor 40, Prioridade 1 (mesma do 20)
    fila_enqueue(&fila, 50, 2); // Valor 50, Prioridade 2

    printf("Fila de Prioridade (valores enfileirados):\n");
    NoFila *atual = fila.frente;
    while(atual != NULL) {
        printf("Valor: %d (Prioridade: %d)\n", atual->valor, atual->prioridade);
        atual = atual->prox;
    }
    
    printf("\n[FILA] tamanho = %d\n", fila_size(&fila));
    int valor;
    if (fila_front(&fila, &valor)) {
        printf("[FILA] frente = %d (maior prioridade)\n", valor);
    }

    printf("\nDesenfileirando na ordem de prioridade:\n");
    while (!fila_is_empty(&fila)) {
        fila_dequeue(&fila, &valor);
        printf("[FILA] dequeue -> %d\n", valor);
    }
    
    fila_clear(&fila);

    return 0;
}