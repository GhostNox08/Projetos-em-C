#include <stdio.h>

int busca(int vet[], int tamanho, int x, int i) {
	if(i >= tamanho) return -1;
	if (vet[i] ==  x) return i;
	return busca(vet, tamanho, x, i + 1);
	
}

int main() {
	int v[6] ={10, 20, 30, 40, 50, 60}, valor;
	
	printf("Digite o valor a buscar: ");
	scanf("%d", &valor);
	
	int pos = busca(v, 6, valor, 0);
	
	if (pos != -1)
		printf("Encontrado na posiçãp %d\n", pos);
	else
		printf("Não encontrado\n");
		
	return 0;
	
}
