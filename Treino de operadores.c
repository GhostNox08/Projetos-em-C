#include <stdio.h>

int main(){
	
	int a;
	int b;
	int c;
	int d;
	int soma;
	
	printf("Digite o valor de a: ");
	scanf("%d", &a);
	
	printf("Digite o valor de b: ");
	scanf("%d", &b);
	
	printf("Digite o valor de c: ");
	scanf("%d", &c);
	
	printf("Digite o valor de d: ");
	scanf("%d", &d);
	
	soma = a+b+c+d;
	
	if(a>=0)
	{
		
		printf("O valor de a � inv�lido!!!\n");
		
	}
	
	else
	{
		
		printf("O valor de a � v�lido.\n");
		
	}
	
	printf("O valor da soma � = \n", soma);
	
	
	return 0;
}
