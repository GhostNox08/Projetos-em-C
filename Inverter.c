#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída

int main() {
    int v[6], temp; // Declara um vetor 'v' de 6 inteiros e uma variável 'temp' para trocas
    int i;

    printf("Digite 6 números:\n"); // Pede ao usuário para digitar 6 números
    for (i = 0; i < 6; i++) { // Loop para ler os 6 números e armazená-los no vetor
        scanf("%d", &v[i]);
    }

    // Loop principal para inverter o vetor
    for (i = 0; i < 3; i++) { // Este loop executa 3 vezes (para i = 0, 1, 2)
        temp = v[i];           // 1. Salva o valor do elemento na posição 'i' em 'temp'
        v[i] = v[5 - i];       // 2. Copia o valor do elemento "oposto" (5 - i) para a posição 'i'
        v[5 - i] = temp;       // 3. Coloca o valor original de 'v[i]' (salvo em 'temp') na posição "oposta"
    }

    printf("Vetor invertido:\n"); // Imprime uma mensagem
    for (i = 0; i < 6; i++) { // Loop para imprimir todos os elementos do vetor invertido
        printf("%d ", v[i]);
    }

    printf("\n"); // Imprime uma nova linha para melhor formatação
    return 0;     // Retorna 0 indicando que o programa executou com sucesso
}
