#include <stdio.h>
#include <stdlib.h>

// Função auxiliar para encontrar o máximo entre dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

/* ===== Struct do nó ===== */
typedef struct no {
    int valor;
    struct no *esq;
    struct no *dir;
} No;

/* ===== cria e retorna um novo nó ===== */
No* criarNo(int valor) {
    No* n = (No*)malloc(sizeof(No));
    if (!n) {
        printf("Falha ao alocar memoria.\n");
        exit(1);
    }
    n->valor = valor;
    n->esq = NULL;
    n->dir = NULL;
    return n;
}

/* ===== constroi recursivamente uma ARVORE BINARIA COMPLETA a partir de um vetor ===== */
No* construirCompleta(int arr[], int n, int i) {
    if (i >= n) return NULL;
    No* raiz = criarNo(arr[i]);
    raiz->esq = construirCompleta(arr, n, 2*i + 1);
    raiz->dir = construirCompleta(arr, n, 2*i + 2);
    return raiz;
}

/* ===== impressao pre-ordem (No, Esq, Dir) ===== */
void imprimirPreOrdem(No* r) {
    if (r == NULL) return;
    printf("%d ", r->valor);
    imprimirPreOrdem(r->esq);
    imprimirPreOrdem(r->dir);
}

/* ===== impressao in-order (Esq, Nó, Dir) ===== */
void imprimirInOrdem(No* r) {
    if (r == NULL) return;
    imprimirInOrdem(r->esq);
    printf("%d ", r->valor);
    imprimirInOrdem(r->dir);
}

/* ===== impressao pos-ordem (Esq, Dir, Nó) ===== */
void imprimirPosOrdem(No* r) {
    if (r == NULL) return;
    imprimirPosOrdem(r->esq);
    imprimirPosOrdem(r->dir);
    printf("%d ", r->valor);
}

/* ===== liberar memoria ===== */
void liberar(No* r) {
    if (!r) return;
    liberar(r->esq);
    liberar(r->dir);
    free(r);
}

/* ===== ATIVIDADE 1: calcular altura da arvore ===== */
int altura(No* r) {
    if (r == NULL) {
        return -1; // Árvore vazia tem altura -1
    }
    // Retorna 1 (pelo nó atual) + o máximo entre as alturas das subárvores
    return 1 + max(altura(r->esq), altura(r->dir));
}

/* ===== ATIVIDADE 2: contar nós da arvore ===== */
int contarNos(No* r) {
    if (r == NULL) {
        return 0; // Árvore vazia tem 0 nós
    }
    // Retorna 1 (pelo nó atual) + a soma dos nós da esquerda e direita
    return 1 + contarNos(r->esq) + contarNos(r->dir);
}

/* ===== ATIVIDADE 3: buscar um valor ===== */
No* buscar(No* r, int chave) {
    if (r == NULL) {
        return NULL; // Valor não encontrado neste caminho
    }
    
    // 1. Verifica se o valor está no nó atual
    if (r->valor == chave) {
        return r; // Valor encontrado
    }

    // 2. Tenta buscar na esquerda
    No* achou = buscar(r->esq, chave);
    if (achou != NULL) {
        return achou; // Retorna se encontrou na esquerda
    }

    // 3. Tenta buscar na direita (se não encontrou na esquerda)
    return buscar(r->dir, chave);
}

int main(void) {
    int dados[] = {10, 5, 20, 25, 30, 7};
    int n = (int)(sizeof(dados) / sizeof(dados[0]));

    No* raiz = construirCompleta(dados, n, 0);
/*
         10
       /    \
      5      20
     / \    /
   25  30  7
*/

    printf("Pre-order: ");
    imprimirPreOrdem(raiz);
    printf("\n"); // Esperado: 10 5 25 30 20 7

    printf("In-order: ");
    imprimirInOrdem(raiz);
    printf("\n"); // Esperado: 25 5 30 10 7 20

    printf("Pos-order: ");
    imprimirPosOrdem(raiz);
    printf("\n"); // Esperado: 25 30 5 7 20 10

    // Atividade 1
    printf("\n--- Atividade 1 ---\n");
    printf("Altura da arvore = %d\n", altura(raiz)); // Esperado: 2

    // Atividade 2
    printf("\n--- Atividade 2 ---\n");
    printf("Total de nos = %d\n", contarNos(raiz)); // Esperado: 6

    // Atividade 3
    printf("\n--- Atividade 3 ---\n");
    int chave = 30;
    No* achou = buscar(raiz, chave);
    if (achou)
        printf("Valor %d encontrado!\n", chave);
    else
        printf("Valor %d nao encontrado.\n", chave); // Encontrado

    chave = 99;
    achou = buscar(raiz, chave);
    if (achou)
        printf("Valor %d encontrado!\n", chave);
    else
        printf("Valor %d nao encontrado.\n", chave); // Não encontrado

    liberar(raiz);
    return 0;
}
