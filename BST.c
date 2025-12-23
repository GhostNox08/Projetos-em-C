#include <stdio.h> 
#include <stdlib.h>   
#include <time.h>
// -------------------------------
// Definicao do no da BST
// -------------------------------
typedef struct No {
    int valor;
    struct No *esq;
    struct No *dir;
} No;

No* criarNo(int value) {
    No* n = (No*)malloc(sizeof(No));
    if (!n) {
        fprintf(stderr, "Erro: sem memoria\n");
        exit(1);
    }
    n->valor = value;
    n->esq = NULL;
    n->dir = NULL;
    return n;
}

// -------------------------------
// Insercao na BST
// -------------------------------
No* inserirNo(No* root, int value) {
    if (root == NULL) return criarNo(value);
    if (value < root->valor)
        root->esq = inserirNo(root->esq, value);
    else if (value > root->valor)
        root->dir = inserirNo(root->dir, value);
        
    return root;
}

// -------------------------------
// Busca na BST (retorna ponteiro ou NULL)
// -------------------------------
No* buscarNo(No* root, int key) {
    if (root == NULL) return NULL;
    if (key == root->valor) return root;
    if (key < root->valor)
        return buscarNo(root->esq, key);
    else
        return buscarNo(root->dir, key);
}

// -------------------------------
// Mínimo e Maximo da BST
// -------------------------------
No* acharMin(No* root) {
    if (root == NULL) return NULL;
    while (root->esq) root = root->esq;
    return root;
}
No* acharMax(No* root) {
    if (root == NULL) return NULL;
    while (root->dir) root = root->dir;
    return root;
}

// -------------------------------
// Altura da BST
// -------------------------------
int altura(No* raiz) {
    if (raiz == NULL)
        return -1;

    int altEsq = altura(raiz->esq);
    int altDir = altura(raiz->dir);

    if (altEsq > altDir)
        return altEsq + 1;
    else
        return altDir + 1;
}

// -------------------------------
// Remocao na BST
// -------------------------------
No* excluirNo(No* root, int key) {
    if (root == NULL) return NULL;

    if (key < root->valor) {
        root->esq = excluirNo(root->esq, key);
    } else if (key > root->valor) {
        root->dir = excluirNo(root->dir, key);
    } else {
        if (root->esq == NULL && root->dir == NULL) {
            free(root);
            return NULL;
        } else if (root->esq == NULL) {
            No* temp = root->dir;
            free(root);
            return temp;
        } else if (root->dir == NULL) {
            No* temp = root->esq;
            free(root);
            return temp;
        } else {
            No* succ = acharMin(root->dir);
            root->valor = succ->valor;
            root->dir = excluirNo(root->dir, succ->valor);
        }
    }
    return root;
}

// -------------------------------
// Percursos (traversals)
// -------------------------------

void preOrdem(No* root) {
    if (root != NULL) {
        printf("%d ", root->valor);
        preOrdem(root->esq);
        preOrdem(root->dir);
    }
}

// In-order: esquerda -> no -> direita (imprime em ordem crescente)
void emOrdem(No* root) {
    if (root != NULL) {
        emOrdem(root->esq);
        printf("%d ", root->valor);
        emOrdem(root->dir);
    }
}

// Pos-ordem: esquerda -> direita -> no
void posOrdem(No* root) {
    if (root != NULL) {
        posOrdem(root->esq);
        posOrdem(root->dir);
        printf("%d ", root->valor);
    }
}

// -------------------------------
// Liberacao (free) de toda a arvore
// -------------------------------
void liberaArvore(No* root) {
    if (root == NULL) return;
    liberaArvore(root->esq);
    liberaArvore(root->dir);
    free(root);
}

// -------------------------------
// Funcao principal
// -------------------------------
#define N 15 // número de elementos

void gerarAleatorios(int vetor[], int n) {
	
	int i = 0;
	while(i<n){
		int num = rand()%100;
		int repetido = 0;
		for(int j = 0; j < i; j++){
			
			if(num==vetor[j]){
				repetido =1;
				break;
			}
			
		}
		
		if(!repetido){
			vetor[i] = num;
			i++;
		}
		
	}
	
}

// -------------------------------
// Funcao FALTANTE: Ordenar (necessário para o requisito 4)
// -------------------------------
void ordenarVetor(int vetor[], int n) {
    // Usando Bubble Sort simples para ordenar
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

void imprimirVetor(int v[], int n) {
    for(int i = 0; i<n; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main(void) {
	
    srand(time(NULL));
    
    int valoresAleatorios[N];
    int valoresOrdenados[N];
    No* raizAleatoria = NULL;
    No* raizOrdenada = NULL;

    gerarAleatorios(valoresAleatorios, N);
    
    for (int i = 0; i < N; i++) {
        valoresOrdenados[i] = valoresAleatorios[i];
    }
    ordenarVetor(valoresOrdenados, N);
    
    printf("--- Experimento com BST ---\n");
    
    // ======================================================
    // PARTE 1: ARVORE COM INSERÇÃO ALEATÓRIA (Melhor caso)
    // ======================================================
    for(int i = 0; i < N; i++){
        raizAleatoria = inserirNo(raizAleatoria, valoresAleatorios[i]);
    }
    
    printf("\n*** 1. Arvore com insercao ALEATORIA ***\n");
    printf("Valores inseridos: ");
    imprimirVetor(valoresAleatorios, N);

    // 3. Mostrar: 3.1, 3.2, 3.4
    printf("3.1 Percurso In-order (Ordenado): ");
    emOrdem(raizAleatoria);
    printf("\n3.2 Percurso Pre-order:           ");
    preOrdem(raizAleatoria);
    printf("\n3.4 Altura da Arvore: %d\n", altura(raizAleatoria));


    // ======================================================
    // PARTE 2: ARVORE COM INSERÇÃO ORDENADA (Pior caso)
    // ======================================================
    // 4. Repetir o processo com uma sequência ordenada
    for(int i = 0; i < N; i++){
        raizOrdenada = inserirNo(raizOrdenada, valoresOrdenados[i]);
    }

    printf("\n*** 2. Arvore com insercao ORDENADA ***\n");
    printf("Valores inseridos (ordenados): ");
    imprimirVetor(valoresOrdenados, N);
    
    // Mostrar percursos e altura para a árvore ordenada
    printf("3.1 Percurso In-order (Ordenado): ");
    emOrdem(raizOrdenada);
    printf("\n3.2 Percurso Pre-order:           ");
    preOrdem(raizOrdenada);
    printf("\n3.4 Altura da Arvore: %d\n", altura(raizOrdenada)); // Deve ser n-1 = 14

    // Liberação de memória (boa prática)
    liberaArvore(raizAleatoria);
    liberaArvore(raizOrdenada);

    return 0;
}
