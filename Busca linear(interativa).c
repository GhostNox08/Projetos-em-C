#include <stdio.h>

int main() {
	int vet[10];
	int i;
	int x;
	
	printf("Digite 10 números: \n");
	for (i =0; i<10; i++)
		scanf("%d", &vet[i]);
		
	printf("Digite o número a buscar: ");
	scanf("%d", &x);
	
	for(i=0; i<10; i++) {
		if (vet[i] == x) {
			printf("Encontrado na posição %d\n");
			return 0;
		}
	}
	
	printf("Valor não encontrado.\n");
	return 0; 
}
