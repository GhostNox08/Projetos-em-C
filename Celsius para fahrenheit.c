#include <stdio.h>

int main(){
	
	int c;
	int f;
	
	printf("Digite o valor em Celsius: ");
	scanf("%d", &c);
	
	f = c*1.8 + 32;
	
	printf("O valor em Fahrenheit é = \n", f);
	
	return 0;
	
}
