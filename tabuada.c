#include<stdio.h>

void exibirTabuada(int n){
	printf("Tabuada de %d: \n", n);
	for (int i=1; i<10; i++){
		printf("%d x %d =%d\n", n,i, n*i);
	}
}

int main(){
	
	int N;
	
	printf("Digite um número positivo inteiro: ");
	scanf("%d", &N);
	
	if(N > 0){
		exibirTabuada(N);
	}else{
		printf("O valor não é válido!!!");
	}
	
	printf("\n\nFIM\n\n");
	return 0;
}
