#include <stdio.h>

#define MAX 50

// Definição do tipo da chave
typedef int TIPOCHAVE;

// Estrutura de um elemento da lista
typedef struct {
    TIPOCHAVE chave;
    // outros campos podem ser adicionados aqui
} ELEMENTO;

// Estrutura da lista (array de ELEMENTO + contador de elementos)
typedef struct {
    ELEMENTO A[MAX];
    int nroElem;
} LISTA;

// Inicializa a lista
void inicializarLista(LISTA *lista){
    lista->nroElem = 0;
}

// Exibe os elementos da lista
void exibirLista(LISTA *lista){
    int i;
    printf("LISTA: ");
    for(i = 0; i < lista->nroElem; i++){
        printf("%d ", lista->A[i].chave);
    }
    printf("\n");
}

// Retorna o tamanho da lista
int tamanhoLista(LISTA *lista){
    return lista->nroElem;
}

// Insere elemento no final da lista
int insereElementoFim(LISTA *lista, ELEMENTO elem){
    if(lista->nroElem >= MAX){
        return 0;
    }else{
        lista->A[lista->nroElem] = elem;
        lista->nroElem++;
        return 1;
    }
}

// Insere elemento no inicio da lista
int insereElementoInicio(LISTA *lista, ELEMENTO elem){
    int i;
    if(lista->nroElem >= MAX){
        return 0;
    }else{
        for(i = lista->nroElem; i > 0; i--){
            lista->A[i] = lista->A[i - 1];
        }
        lista->A[0] = elem;
        lista->nroElem++;
        return 1;
    }
}

// Insere elemento em uma posição específica
int insereElementoPosicao(LISTA *lista, ELEMENTO elem, int pos){
    int i;
    if(lista->nroElem >= MAX || pos < 0 || pos > lista->nroElem){
        return 0;
    }else{
        for(i = lista->nroElem; i > pos; i--){
            lista->A[i] = lista->A[i - 1];
        }
        lista->A[pos] = elem;
        lista->nroElem++;
        return 1;
    }
}

// Remove o último elemento
int removeElementoFim(LISTA *lista, ELEMENTO *elem){
    if(lista->nroElem == 0){
        return 0;
    }else{
        *elem = lista->A[lista->nroElem - 1];
        lista->nroElem--;
        return 1;
    }
}

// Remove o primeiro elemento
int removeElementoInicio(LISTA *lista, ELEMENTO *elem){
    int i;
    if(lista->nroElem == 0){
        return 0;
    }else{
        *elem = lista->A[0];
        for(i = 0; i < lista->nroElem - 1; i++){
            lista->A[i] = lista->A[i + 1];
        }
        lista->nroElem--;
        return 1;
    }
}

// Busca por chave (linear)
int buscaElemento(LISTA *lista, TIPOCHAVE ch) {
    int i;
    for(i = 0; i < lista->nroElem; i++){
        if(lista->A[i].chave == ch){
            return i;
        }
    }
    return -1;
}

// Remove elemento por chave
int removeElementoChave(LISTA *lista, TIPOCHAVE ch) {
    int pos = buscaElemento(lista, ch);
    int i;
    if(pos == -1){
        return 0;
    }
    
    for(i = pos; i < lista->nroElem - 1; i++){
        lista->A[i] = lista->A[i + 1];
    }
    lista->nroElem--;
    return 1;
}

int main(void){
    LISTA lista1;
    ELEMENTO e;

    inicializarLista(&lista1);

    // --- Teste de inserções ---
    printf("--- Testando Insercoes ---\n");
    e.chave = 10;
    insereElementoFim(&lista1, e);
    e.chave = 20;
    insereElementoInicio(&lista1, e);
    e.chave = 30;
    insereElementoFim(&lista1, e);
    
    exibirLista(&lista1); // Saída esperada: LISTA: 20 10 30
    printf("Tamanho da lista: %d\n\n", tamanhoLista(&lista1)); // Saída esperada: 3
    
    // Teste de inserção em posição específica
    printf("--- Testando insereElementoPosicao ---\n");
    e.chave = 15;
    insereElementoPosicao(&lista1, e, 1);
    exibirLista(&lista1); // Saída esperada: LISTA: 20 15 10 30
    printf("Tamanho da lista: %d\n\n", tamanhoLista(&lista1)); // Saída esperada: 4
    
    // --- Teste de buscas ---
    printf("--- Testando Busca ---\n");
    int pos = buscaElemento(&lista1, 15);
    if (pos != -1) {
        printf("Elemento com chave 15 encontrado na posicao %d.\n\n", pos); // Saída esperada: 1
    } else {
        printf("Elemento com chave 15 nao encontrado.\n\n");
    }
    
    // --- Teste de remoções ---
    printf("--- Testando Remocoes ---\n");
    
    // Removendo do fim
    removeElementoFim(&lista1, &e);
    printf("Elemento removido do fim: %d\n", e.chave); // Saída esperada: 30
    exibirLista(&lista1); // Saída esperada: LISTA: 20 15 10
    
    // Removendo do início
    removeElementoInicio(&lista1, &e);
    printf("Elemento removido do inicio: %d\n", e.chave); // Saída esperada: 20
    exibirLista(&lista1); // Saída esperada: LISTA: 15 10
    
    // Removendo por chave
    removeElementoChave(&lista1, 15);
    printf("Removendo elemento com chave 15.\n");
    exibirLista(&lista1); // Saída esperada: LISTA: 10
    
    printf("\nTeste final da lista:\n");
    exibirLista(&lista1);
    printf("Tamanho da lista final: %d\n", tamanhoLista(&lista1)); // Saída esperada: 1
    
    return 0;
}
