#include <stdio.h>

int main() {
	
	int b;
	int B;
	int h;
	int Area;
	
	printf("Digite o valor da base menor: ");
	scanf("%d", &b);
	
	printf("Digite o valor da base maior: ");
	scanf("%d", &B);
	
	printf("Digite o valor da altura: ");
	scanf("%d", &h);
	
	Area = ((b+B)*h)/2;
	
	printf("O valor da Area é: %d", Area);
	
	printf("\n");
	
	printf("FIM!!!");
	
	return 0;
}
