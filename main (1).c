#include <stdio.h>    // Inclui a biblioteca padrC#o de entrada e saC-da (para printf, etc.)
#include <stdlib.h>   // Inclui a biblioteca padrC#o (para funC'C5es como system se necessC!rio, embora nC#o usada aqui)

#define MAX 50        // Define uma constante para o tamanho mC!ximo do vetor da Heap

typedef struct {      // InC-cio da definiC'C#o da estrutura (struct) para representar o Heap
	int vetor[MAX]; // Array de inteiros para armazenar os elementos do Heap
	int tamanho;    // VariC!vel para armazenar o nC:mero atual de elementos no Heap
} Heap; // Nome da estrutura C) 'Heap'

/* Retorna C-ndices do pai e dos filhos */
int pai(int i) {
	return (i - 1) / 2;    // C
ndice do pai
}
int esq(int i) {
	return 2 * i + 1;    // C
ndice do filho C  esquerda
}
int dir(int i) {
	return 2 * i + 2;    // C
ndice do filho C  direita
}

/* Troca dois valores do vetor */
void trocar(int *a, int *b) { // FunC'C#o auxiliar para trocar os valores de duas variC!veis inteiras
	int temp = *a; // Armazena o valor apontado por 'a' em uma variC!vel temporC!ria
	*a = *b; // Atribui o valor apontado por 'b' ao endereC'o de 'a'
	*b = temp; // Atribui o valor temporC!rio (original de 'a') ao endereC'o de 'b'
}

/* Desce o elemento para restaurar a propriedade do heap (Min-Heapify) */
void descer(Heap *h, int i) { // FunC'ao para reorganizar o Heap descendo um elemento
	int menor = i; // Inicializa 'menor' como o C-ndice atual
	int e = esq(i); // C
ndice do filho C  esquerda
	int d = dir(i); // C
ndice do filho C  direita

	// Verifica se o filho esquerdo existe e se ele C) menor que o valor no C-ndice 'menor'
	if (e < h->tamanho && h->vetor[e] < h->vetor[menor])
		menor = e;
	// Verifica se o filho direito existe e se ele C) menor que o valor no C-ndice 'menor'
	if (d < h->tamanho && h->vetor[d] < h->vetor[menor])
		menor = d;

	if (menor != i) { // Se o menor elemento nC#o for o prC3prio C-ndice 'i'
		trocar(&h->vetor[i], &h->vetor[menor]); // Troca o elemento
		descer(h, menor); // Chama 'descer' recursivamente no novo C-ndice
	}
}

/* Imprime a heap */
void imprimir(Heap *h) { // FunC'C#o para imprimir todos os elementos do Heap
	printf("ConteC:do do Heap (Tamanho %d): ", h->tamanho); // Imprime um rC3tulo
	for (int i = 0; i < h->tamanho; i++) // Loop para iterar sobre todos os elementos atuais
		printf("%d ", h->vetor[i]); // Imprime o valor de cada elemento
	printf("\n"); // Imprime uma nova linha
}

/* Converte um array desordenado em um Min-Heap */
void construirHeap(Heap *h) {
	// Calcula o C-ndice do C:ltimo nC3 interno (o primeiro nC3 com filhos)
	int ultimo_no_interno = (h->tamanho / 2) - 1;

	// Percorre todos os nC3s internos de trC!s para frente
	for (int i = ultimo_no_interno; i >= 0; i--) {
		// Usa a funC'C#o 'descer' (Min-Heapify) para corrigir a subC!rvore
		descer(h, i);
	}
}

/* Remove o menor elemento (raiz) */
int removerMin(Heap *h) { // FunC'C#o para remover e retornar o menor elemento do Heap
	// 1. Verifica se o Heap estC! vazio
	if (h->tamanho <= 0) {
		printf("--- ERRO: Heap vazio. NC#o C) possC-vel remover o mC-nimo. ---\n");
		return -1;
	}

	// 2. Armazena o valor da raiz (o menor elemento)
	int min = h->vetor[0];

	// 3. Move o C:ltimo elemento do vetor para a raiz (posiC'C#o 0)
	// O C:ltimo elemento estC! em h->vetor[h->tamanho - 1]
	h->vetor[0] = h->vetor[h->tamanho - 1];

	// 4. Decrementa o tamanho do Heap (o C:ltimo elemento foi removido logicamente)
	h->tamanho--;

	// 5. Chama 'descer' na nova raiz para restaurar a propriedade do Heap, se o Heap ainda tiver elementos
	if (h->tamanho > 0) {
		descer(h, 0);
	}

	// 6. Retorna o menor valor que foi removido
	return min;
}

/* FunC'C#o auxiliar para testar a construC'C#o e remoC'C#o em um array */
void testarArray(int *arr, int n, const char *label) {
	Heap h;
	if (n > MAX) {
		printf("Erro: Array '%s' C) maior que o tamanho mC!ximo do Heap (%d). Ignorando teste.\n", label, MAX);
		return;
	}

	// Inicializa o Heap com o array
	for (int i = 0; i < n; i++) {
		h.vetor[i] = arr[i];
	}
	h.tamanho = n;

	printf("\n\n======================================================\n");
	printf("--- Teste com Array %s ---\n", label);
	printf("======================================================\n");
	printf("Array inicial (desordenado):\n");
	imprimir(&h);

	// Converte para Min-Heap
	construirHeap(&h);
	printf("Heap construC-do (Min-Heap):\n");
	imprimir(&h);

	// Primeira remoC'C#o
	if (h.tamanho > 0) {
		int min1 = removerMin(&h);
		printf("\n1B* RemoC'C#o: O menor elemento removido foi %d.\n", min1);
		printf("Heap apC3s a 1B* remoC'C#o e reorganizaC'C#o:\n");
		imprimir(&h);
	}

	// Segunda remoC'C#o
	if (h.tamanho > 0) {
		int min2 = removerMin(&h);
		printf("\n2B* RemoC'C#o: O prC3ximo menor elemento removido foi %d.\n", min2);
		printf("Heap apC3s a 2B* remoC'C#o e reorganizaC'C#o:\n");
		imprimir(&h);
	}
}


int main() {

	printf("SimulaC'C#o de ConstruC'C#o e RemoC'C#o em Min-Heap\n");
	printf("--------------------------------------------\n");
	printf("Para visualizar a conversC#o dos arrays em Min-Heap passo a passo, use o simulador:\n");
	printf("https://heapsortvisualizer.web.app/\n\n");

	// Array 1: {89, 17, 12, 15, 2, 5, 9, 100}
	int array1[] = {89, 17, 12, 15, 2, 5, 9, 100};
	int n1 = 8;
	testarArray(array1, n1, "1: {89, 17, 12, 15, 2, 5, 9, 100}");

	// Array 2: {10,50,90,5,8,4,100,40,20,25}
	int array2[] = {10, 50, 90, 5, 8, 4, 100, 40, 20, 25};
	int n2 = 10;
	testarArray(array2, n2, "2: {10, 50, 90, 5, 8, 4, 100, 40, 20, 25}");

	// Array 3: {15, 60, 100, 500 ,8, 2, 1, 5, 70, 32, 45, 60}
	int array3[] = {15, 60, 100, 500,8, 2, 1, 5, 70, 32, 45, 60};
	int n3 = 12;
	testarArray(array3, n3, "3: {15, 60, 100, 500 ,8, 2, 1, 5, 70, 32, 45, 60}");

	return 0;
}
