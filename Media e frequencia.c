#include <stdio.h>

int main()
{
	
	int media;
	int frequencia;
	
	printf("Digite a frequência: ");
	scanf("%d", &frequencia);
	
	printf("Digite a media: ");
	scanf("%d", &media);
	
	if (frequencia<75)
	{
		printf("O aluno foi Reprovado!!!");
	}
	if (frequencia>=75 && media >=7.5){
		
		printf("O aluno foi Aprovado!!!");
	}
	else{
		
		printf("O Aluno está de Exame!!!");	
	}
	return 0;
	
}
