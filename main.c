/* 
O programa lê o nome do aluno, lê 5 notas (array de int), 
calcula a média e informa se aprovado ou reprovado. 
*/

#include <stdio.h>   // printf, scanf, fgets
#include <string.h>  // strlen

// ------------------------------------------------------------
// Exemplo simples: média de 5 notas
// - Leitura do nome (string) com fgets (aceita espaços)
// - Array unidimensional de int para guardar as notas
// - Repetição (for) para ler as notas e somar
// - Condicional (if/else) para decidir aprovação
// ------------------------------------------------------------
int main(void) {
    // -----------------------------
    // Declaração de variáveis
    // -----------------------------
    char nome[50];        // string para guardar o nome do aluno (até 49 chars + '\0')
    int  notas[5];        // array unidimensional com 5 notas (inteiros)
    int  i;               // índice para o laço
    int  soma = 0;        // acumulador para somar as notas
    double media;         // média das notas

    // -----------------------------
    // Leitura do nome do aluno
    // Usamos fgets para permitir espaços no nome.
    // fgets inclui o '\n' no final se couber no buffer.
    // -----------------------------
    printf("Digite o nome do aluno: ");
    //scanf("%*[^\n]",&nome);
    // fgets tenta ler até 49 caracteres (size-1) OU até '\n'
    // Se der erro/EOF sem ler nada, retorna NULL
    if (fgets(nome, sizeof(nome), stdin) == NULL) {
        // Se der erro/EOF, encerramos com uma mensagem simples.
        printf("Erro na leitura do nome.\n");
        return 1;
    }

    // -----------------------------
    // Leitura das 5 notas (0 a 10)
    // O "for" é a repetição usada para preencher o array.
    // -----------------------------
    for (i = 0; i < 5; i++) {
        printf("Digite a nota %d (0 a 10): ", i + 1);
        // Em scanf, usamos &notas[i] para informar o endereço da variável.
        // Isso é necessário para que scanf consiga escrever o valor lido.
        scanf("%d", &notas[i]);

        // Validação simples (opcional): força o intervalo 0..10
        if (notas[i] < 0)  notas[i] = 0;
        if (notas[i] > 10) notas[i] = 10;

        // Soma parcial das notas para depois calcular a média
        soma += notas[i];
    }

    // -----------------------------
    // Cálculo da média (conversão para double para não perder casas decimais)
    // -----------------------------
    media = soma / 5.0;

    // -----------------------------
    // Saída de resultados
    // -----------------------------
    printf("\nAluno: %s\n", nome);
    printf("Media: %.2f\n", media);

    // -----------------------------
    // Condicional: aprovado (>= 6.0) ou reprovado
    // -----------------------------
    if (media >= 6.0) {
        printf("Situacao: APROVADO\n");
    } else {
        printf("Situacao: REPROVADO\n");
    }

    // Fim do programa
    return 0;
}