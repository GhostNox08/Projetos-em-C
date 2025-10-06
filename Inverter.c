#include <stdio.h> // Inclui a biblioteca padr�o de entrada e sa�da

int main() {
    int v[6], temp; // Declara um vetor 'v' de 6 inteiros e uma vari�vel 'temp' para trocas
    int i;

    printf("Digite 6 n�meros:\n"); // Pede ao usu�rio para digitar 6 n�meros
    for (i = 0; i < 6; i++) { // Loop para ler os 6 n�meros e armazen�-los no vetor
        scanf("%d", &v[i]);
    }

    // Loop principal para inverter o vetor
    for (i = 0; i < 3; i++) { // Este loop executa 3 vezes (para i = 0, 1, 2)
        temp = v[i];           // 1. Salva o valor do elemento na posi��o 'i' em 'temp'
        v[i] = v[5 - i];       // 2. Copia o valor do elemento "oposto" (5 - i) para a posi��o 'i'
        v[5 - i] = temp;       // 3. Coloca o valor original de 'v[i]' (salvo em 'temp') na posi��o "oposta"
    }

    printf("Vetor invertido:\n"); // Imprime uma mensagem
    for (i = 0; i < 6; i++) { // Loop para imprimir todos os elementos do vetor invertido
        printf("%d ", v[i]);
    }

    printf("\n"); // Imprime uma nova linha para melhor formata��o
    return 0;     // Retorna 0 indicando que o programa executou com sucesso
}
