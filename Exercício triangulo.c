#include <stdio.h>

int main(){
	
	int a;
	int b;
	int c;
	int perimetro;
	
	printf("Digite o valor de a: ");
	scanf("%d", &a);
	
	printf("Digite o valor de b: ");
	scanf("%d", &b);
	
	printf("Digite o valor de c: ");
	scanf("%d", &c);
	
	perimetro = a+b+c;
	
	if (a<b+c && b<a+c && c<a+b){
		
		printf("O Triangulo existe!!!");
	}
	else{
		
		printf("O Triângulo não existe!!!");
	
	}
	
	printf("A soma dos lados do triangulo é= \n", perimetro);
	
	return 0;
}
