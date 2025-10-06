#include <stdio.h>

void maior(int *a, int *b, int *maiorValor) {
	
	if(*a>*b) {
		*maiorValor= *a;
	}else{
		*maiorValor= *b;
	}
}

int main() {
	int x,y, maiorResultado;
	printf("Digite dois números");
	scanf("%d %d", &x,&y);
	
	maior(&x, &y, maiorResultado);
	
	printf("Maior valor é %d\n", maiorResultado);
	return 0;
}
