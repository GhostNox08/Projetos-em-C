#include <stdio.h>

int main() {
	int vet[10];
	int i;
	int x;
	
	printf("Digite 10 n�meros: \n");
	for (i =0; i<10; i++)
		scanf("%d", &vet[i]);
		
	printf("Digite o n�mero a buscar: ");
	scanf("%d", &x);
	
	for(i=0; i<10; i++) {
		if (vet[i] == x) {
			printf("Encontrado na posi��o %d\n");
			return 0;
		}
	}
	
	printf("Valor n�o encontrado.\n");
	return 0; 
}
