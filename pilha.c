/*
    ESTRUTURAS LINEARES DIDÁTICAS EM C: PILHA (STACK) E FILA (QUEUE)

    Objetivo:
    - Implementar, de forma didática, uma Pilha (LIFO) usando
      listas encadeadas simples, com funções para as operações básicas.
    - Reforçar conceitos de alocação dinâmica (malloc/free), ponteiros e
      atualização coerente de contadores (tamanho).

    Decisões de projeto:
    - Tanto Pilha quanto Fila usam nós encadeados simples (apenas ponteiro para o próximo).
    - A Pilha mantém ponteiro para o TOPO (push/pop no topo em O(1)).
    - As funções de remoção retornam o valor via parâmetro de saída (int *out)
      e um "código de status" (1 = sucesso, 0 = erro, ex.: estrutura vazia ou malloc falhou).
    - Mantemos um campo `tamanho` para cada estrutura, permitindo consultar o
      número de elementos em O(1).

    Operações contempladas:
    - Pilha: init, is_empty, push, pop, top/peek, size, clear.

    Boas práticas:
    - Verificar retorno de malloc (pode ser NULL).
    - Sempre desalocar nós removidos (free) e atualizar os ponteiros de cabeça/cauda/topo.
    - Evitar "uso após free" (não usar ponteiro após liberá-lo).
*/

#include <stdio.h>   // printf
#include <stdlib.h>  // malloc, free

/* =========================================================
   DEFINIÇÃO DA PILHA (STACK) — USANDO LISTA ENCADEADA SIMPLES
   ========================================================= */

// Define o nó da pilha, armazenando um inteiro e o ponteiro para o próximo nó
typedef struct NoPilha {
    int valor;                 // valor armazenado no nó
    struct NoPilha *prox;      // ponteiro para o próximo nó (logo abaixo no "stack")
} NoPilha;

// Estrutura "Pilha": guarda o ponteiro para o topo e o tamanho atual
typedef struct {
    NoPilha *topo;             // topo da pilha (último inserido)
    int tamanho;               // quantidade de elementos
} Pilha;

// Inicializa a pilha deixando-a vazia
void pilha_init(Pilha *p) {
    p->topo = NULL;            // sem nós, topo é NULL
    p->tamanho = 0;            // tamanho começa em 0
}

// Retorna 1 se a pilha está vazia; 0 caso contrário
int pilha_is_empty(const Pilha *p) {
    if(p->topo == NULL){
        return 1; // vazia quando topo é NULL
    }
    return 0;
}

// Empilha (push) um novo valor no topo
// Retorna 1 em sucesso; 0 se malloc falhar
int pilha_push(Pilha *p, int valor) {
    NoPilha *novo = (NoPilha*)malloc(sizeof(NoPilha)); // aloca nó
    if (!novo) {                                       // verifica falha de alocação
        printf("Erro: sem memória ao empilhar.\n");
        return 0;                                      // sinaliza erro
    }
    novo->valor = valor;                               // armazena o valor no nó
    novo->prox  = p->topo;                             // encadeia: novo aponta para antigo topo
    p->topo     = novo;                                // atualiza topo para o novo nó
    p->tamanho++;                                      // incrementa contador
    return 1;                                          // sucesso
}

// Desempilha (pop) removendo o elemento do topo e retornando-o via *out
// Retorna 1 em sucesso; 0 se a pilha estiver vazia
int pilha_pop(Pilha *p, int *out) {
    if (pilha_is_empty(p)) {                           // não há o que remover
        printf("Erro: pilha vazia ao desempilhar.\n");
        return 0;                                      // falha
    }
    NoPilha *rem = p->topo;                            // nó a remover (topo atual)
    if (out!=NULL){
        *out = rem->valor;                             // escreve o valor removido em *out (se out != NULL)
    }                                                   
    p->topo = rem->prox;                               // atualiza topo para o próximo nó
    free(rem);                                         // libera nó removido
    p->tamanho--;                                      // decrementa tamanho
    return 1;                                          // sucesso
}

// Espia (peek/top) o valor do topo sem remover
// Retorna 1 em sucesso; 0 se a pilha estiver vazia
int pilha_top(const Pilha *p, int *out) {
    if (pilha_is_empty(p)) {                           // pilha vazia não tem topo
        printf("Aviso: pilha vazia ao consultar topo.\n");
        return 0;                                      // falha
    }
    if (out!=NULL){
        *out = p->topo->valor;                         // retorna o valor do topo
    }
    return 1;                                          // sucesso
}

// Retorna o número de elementos da pilha
int pilha_size(const Pilha *p) {
    return p->tamanho;                                 // O(1), já mantemos o contador
}

// Remove todos os nós da pilha, deixando-a vazia
void pilha_clear(Pilha *p) {
    NoPilha *atual = p->topo;                          // começa pelo topo
    while (atual) {                                    // percorre até NULL
        NoPilha *prox = atual->prox;                   // guarda próximo nó
        free(atual);                                   // libera nó atual
        atual = prox;                                  // avança
    }
    p->topo = NULL;                                    // topo volta a NULL
    p->tamanho = 0;                                    // tamanho zera
}

/* =========================
   PROGRAMA DE TESTE (main)
   ========================= */

int main(void) {
    Pilha pilha;                    // declara uma pilha
    pilha_init(&pilha);             // inicializa (vazia)

    // Empilha alguns valores
    pilha_push(&pilha, 10);         // topo: 10
    pilha_push(&pilha, 20);         // topo: 20, abaixo: 10
    pilha_push(&pilha, 30);         // topo: 30, abaixo: 20 -> 10

    // Mostra tamanho e topo
    printf("[PILHA] tamanho = %d\n", pilha_size(&pilha)); // esperado: 3
    int valor;
    if (pilha_top(&pilha, &valor)) {                      // consulta topo sem remover
        printf("[PILHA] topo = %d\n", valor);             // esperado: 30
    }

    
    // Desempilha tudo
    while (!pilha_is_empty(&pilha)) {                     // enquanto houver elementos
        pilha_pop(&pilha, &valor);                        // remove topo
        printf("[PILHA] pop -> %d\n", valor);             // imprime valor removido
    }

    // Limpa (idempotente: já está vazia)
    pilha_clear(&pilha);
    return 0;                                          // fim do programa
}
