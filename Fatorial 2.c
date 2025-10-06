#include <stdio.h>

int fatorial(int n){
	if(n<0){
		printf("Não existe fatorial negativo");
		return -1;
		
	}else if (n ==0){
		return 1;
	}else{
		return n*fatorial(n-1);
	}
}

int main() {
	
	int N;
	int resultadoFatorial;
	
	printf("Digite um número inteiro positivo: ");
	scanf("%d", N);
	
	resultadoFatorial = fatorial(N);
	
	if (resultadoFatorial == -1) {
		printf("Digite um numero positivo!!!");
	}else{
		
		printf("O valor do fatorial %d é %d", N, resultadoFatorial);
	}
	return 0;
}
