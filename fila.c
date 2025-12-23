/*
    ESTRUTURAS LINEARES DIDÁTICAS EM C: PILHA (STACK) E FILA (QUEUE)

    Objetivo:
    - Implementar, de forma didática, uma Fila (FIFO) usando
      listas encadeadas simples, com funções para as operações básicas.
    - Reforçar conceitos de alocação dinâmica (malloc/free), ponteiros e
      atualização coerente de contadores (tamanho).

    Decisões de projeto:
    - A Fila mantém ponteiros para o primeiro elemento (head) e último (tail), permitindo
      enfileirar em O(1) e desenfileirar em O(1).
    - As funções de remoção retornam o valor via parâmetro de saída (int *out)
      e um "código de status" (1 = sucesso, 0 = erro, ex.: estrutura vazia ou malloc falhou).
    - Mantemos um campo `tamanho` para cada estrutura, permitindo consultar o
      número de elementos em O(1).

    Operações contempladas:
    - Fila:  init, is_empty, enqueue, dequeue, front/peek, size, clear.

    Boas práticas:
    - Verificar retorno de malloc (pode ser NULL).
    - Sempre desalocar nós removidos (free) e atualizar os ponteiros de cabeça/cauda/topo.
    - Evitar "uso após free" (não usar ponteiro após liberá-lo).
*/


/* =========================================================
   DEFINIÇÃO DA FILA (QUEUE) — USANDO LISTA ENCADEADA SIMPLES
   ========================================================= */
#include <stdio.h>   // printf
#include <stdlib.h>  // malloc, free
// Define o nó da fila, armazenando um inteiro e ponteiro para o próximo nó
typedef struct NoFila {
    int valor;                 // valor armazenado no nó
    struct NoFila *prox;       // ponteiro para o próximo nó (mais antigo -> mais novo)
} NoFila;

// Estrutura "Fila": guarda ponteiros para a frente (head) e trás (tail), e o tamanho
typedef struct {
    NoFila *frente;            // primeiro elemento (a ser removido no dequeue)
    NoFila *tras;              // último elemento (o mais recém-chegado)
    int tamanho;               // quantidade de elementos
} Fila;

// Inicializa a fila vazia
void fila_init(Fila *q) {
    q->frente = NULL;          // sem nós na frente
    q->tras   = NULL;          // sem nós atrás
    q->tamanho = 0;            // tamanho zero
}

// Retorna 1 se a fila está vazia; 0 caso contrário
int fila_is_empty(const Fila *q) {
    return (q->frente == NULL); // vazia quando frente é NULL (tras também deve ser NULL)
}

// Enfileira (enqueue) um novo valor no FINAL da fila
// Retorna 1 em sucesso; 0 se malloc falhar
int fila_enqueue(Fila *q, int valor) {
    NoFila *novo = (NoFila*)malloc(sizeof(NoFila)); // aloca nó
    if (!novo) {                                    // verifica alocação
        printf("Erro: sem memória ao enfileirar.\n");
        return 0;                                   // falha
    }
    novo->valor = valor;                            // grava valor no nó
    novo->prox  = NULL;                             // novo último sempre aponta para NULL

    if (q->tras) {                                  // se já havia pelo menos um nó
        q->tras->prox = novo;                       // antigo último aponta para o novo
        q->tras = novo;                             // atualiza ponteiro 'tras' para o novo
    } else {                                        // fila estava vazia
        q->frente = novo;                           // frente e trás passam a apontar para 'novo'
        q->tras = novo;                             // frente e trás passam a apontar para 'novo'
    }
    q->tamanho++;                                   // incrementa contador
    return 1;                                       // sucesso
}

// Desenfileira (dequeue) o valor da FRENTE e o retorna via *out
// Retorna 1 em sucesso; 0 se a fila estiver vazia
int fila_dequeue(Fila *q, int *out) {
    if (fila_is_empty(q)) {                         // não há o que remover
        printf("Erro: fila vazia ao desenfileirar.\n");
        return 0;                                   // falha
    }
    NoFila *rem = q->frente;                        // nó a remover (na frente)
    if (out) *out = rem->valor;                     // copia valor removido para *out
    q->frente = rem->prox;                          // avança a frente para o próximo
    if (q->frente == NULL) {                        // se a fila ficou vazia
        q->tras = NULL;                             // 'tras' também deve virar NULL
    }
    free(rem);                                      // libera nó removido
    q->tamanho--;                                   // decrementa contador
    return 1;                                       // sucesso
}

// Espia o valor da frente sem remover
// Retorna 1 em sucesso; 0 se a fila estiver vazia
int fila_front(const Fila *q, int *out) {
    if (fila_is_empty(q)) {                         // fila vazia não tem frente
        printf("Aviso: fila vazia ao consultar frente.\n");
        return 0;                                   // falha
    }
    if (out) *out = q->frente->valor;               // retorna valor do nó da frente
    return 1;                                       // sucesso
}

// Retorna o número de elementos na fila
int fila_size(const Fila *q) {
    return q->tamanho;                              // O(1)
}

// Remove todos os nós da fila, deixando-a vazia
void fila_clear(Fila *q) {
    NoFila *atual = q->frente;                      // começa pela frente
    while (atual) {                                 // percorre até NULL
        NoFila *prox = atual->prox;                 // guarda próximo
        free(atual);                                // libera nó atual
        atual = prox;                               // avança
    }
    q->frente = q->tras = NULL;                     // zera ponteiros
    q->tamanho = 0;                                 // zera tamanho
}

/* =========================
   PROGRAMA DE TESTE (main)
   ========================= */

int main(void) {
    Fila fila;                        // declara uma fila
    fila_init(&fila);                 // inicializa (vazia)

    // Enfileira alguns valores
    fila_enqueue(&fila, 100);         // frente=100, tras=100
    fila_enqueue(&fila, 200);         // frente=100, tras=200
    fila_enqueue(&fila, 300);         // frente=100, tras=300

    // Mostra tamanho e frente
    printf("[FILA] tamanho = %d\n", fila_size(&fila)); // esperado: 3
    int valor;
    if (fila_front(&fila, &valor)) {                   // consulta frente sem remover
        printf("[FILA] frente = %d\n", valor);         // esperado: 100
    }

    // Desenfileira tudo
    while (!fila_is_empty(&fila)) {                    // enquanto houver elementos
        fila_dequeue(&fila, &valor);                   // remove da frente
        printf("[FILA] dequeue -> %d\n", valor);       // imprime valor removido
    }

    // Limpa (idempotente: já está vazia)
    fila_clear(&fila);

    return 0;                                          // fim do programa
}
