#include <stdio.h>

int main()
{
	
	int media;
	int frequencia;
	
	printf("Digite a frequ�ncia: ");
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
		
		printf("O Aluno est� de Exame!!!");	
	}
	return 0;
	
}
