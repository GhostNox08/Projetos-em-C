#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 100
#define M 127  // tamanho da tabela (nC:mero primo prC3ximo de 100)

// --------------------- Estruturas ---------------------
typedef struct Node {
	char *word;
	struct Node *next;
} Node;

typedef struct {
	Node *buckets[M];
} HashTable;

// --------------------- FunC'C5es Hash ---------------------

// hash1: soma dos cC3digos ASCII
int hash1(const char *s) {
	int sum = 0;
	while (*s) sum += *s++;
	return sum % M;
}

// hash2: mC)todo multiplicativo
int hash2(const char *s) {
	unsigned long k = 0;
	while (*s) k = k * 31 + *s++;
	double A = 0.618033;
	double frac = k * A - (long)(k * A);
	return (int)(M * frac);
}

// --------------------- GeraC'C#o de Palavras ---------------------
void generate_words(char *words[], int n) {
	const char charset[] = "abcdefghijklmnopqrstuvwxyz";
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		int len = 4 + rand() % 7; // entre 4 e 10 caracteres
		words[i] = malloc(len + 1);
		for (int j = 0; j < len; j++) {
			words[i][j] = charset[rand() % 26];
		}
		words[i][len] = '\0';
	}
}

// --------------------- InserC'C#o e Contagem ---------------------
int insert(HashTable *ht, const char *word, int (*hash_func)(const char *)) {
	int index = hash_func(word);
	Node *newNode = malloc(sizeof(Node));
	newNode->word = strdup(word);
	newNode->next = NULL;

	if (ht->buckets[index] == NULL) {
		ht->buckets[index] = newNode;
		return 0;  // sem colisC#o
	} else {
		newNode->next = ht->buckets[index];
		ht->buckets[index] = newNode;
		return 1;  // colisC#o
	}
}

void init_table(HashTable *ht) {
	for (int i = 0; i < M; i++) {
		ht->buckets[i] = NULL;
	}
}

// --------------------- EstatC-sticas ---------------------
void print_stats(HashTable *ht, const char *nome_hash, int total_colisoes) {
	int vazios = 0, um = 0, dois_ou_mais = 0;
	for (int i = 0; i < M; i++) {
		int count = 0;
		Node *curr = ht->buckets[i];
		while (curr) {
			count++;
			curr = curr->next;
		}
		if (count == 0) vazios++;
		else if (count == 1) um++;
		else dois_ou_mais++;
	}

	printf("\n===== %s =====\n", nome_hash);
	printf("Total de colisC5es: %d\n", total_colisoes);
	printf("Buckets vazios: %d\n", vazios);
	printf("Buckets com 1 elemento: %d\n", um);
	printf("Buckets com >=2 elementos: %d\n", dois_ou_mais);
}

// --------------------- FunC'C#o Principal ---------------------
int main() {
	char *words[N];
	generate_words(words, N);

	HashTable ht1, ht2;
	init_table(&ht1);
	init_table(&ht2);

	int colisoes1 = 0, colisoes2 = 0;

	for (int i = 0; i < N; i++) {
		colisoes1 += insert(&ht1, words[i], hash1);
		colisoes2 += insert(&ht2, words[i], hash2);
	}

	print_stats(&ht1, "HASH 1 (soma ASCII)", colisoes1);
	print_stats(&ht2, "HASH 2 (mC)todo multiplicativo)", colisoes2);

	// Libera memC3ria
	for (int i = 0; i < N; i++) free(words[i]);
	for (int i = 0; i < M; i++) {
		Node *curr = ht1.buckets[i];
		while (curr) {
			Node *tmp = curr;
			curr = curr->next;
			free(tmp->word);
			free(tmp);
		}
		curr = ht2.buckets[i];
		while (curr) {
			Node *tmp = curr;
			curr = curr->next;
			free(tmp->word);
			free(tmp);
		}
	}

	return 0;
}
