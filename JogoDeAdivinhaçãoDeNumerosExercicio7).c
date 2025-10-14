#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Função principal do jogo de adivinhação
int jogar_partida(int numero_secreto) {
    // Declaração das variáveis
    int total_de_tentativas = 0;
    int pontos = 1000;
    int nivel;
    int chute;
    int rodada;
    int acertou = 0; // Inicializado como 0 (Falso)
    int pontos_perdidos;
    int continuar_jogando = 1; // 1 para Sim (Continua), 0 para Não (Pára)
    char opcao_parar;

    printf("*********************************\n");
    printf("Bem vindo ao jogo de adivinhacao!\n");
    printf("*********************************\n");

    printf("Qual o nivel de dificuldade?\n");
    printf("(1) Facil (2) Medio (3) Dificil\n");

    printf("Defina um nivel: ");
    // Verifica se a leitura do nível foi bem-sucedida, caso contrário, usa o padrão.
    if (scanf("%d", &nivel) != 1) {
        nivel = 3; // Padrão Difícil se a entrada for inválida
        // Limpa o buffer de entrada
        while (getchar() != '\n'); 
    }

    // Define o total de tentativas com base no nível
    if (nivel == 1) {
        total_de_tentativas = 20;
    } else if (nivel == 2) {
        total_de_tentativas = 10;
    } else {
        total_de_tentativas = 5;
    }

    // Loop das tentativas
    for (rodada = 1; rodada <= total_de_tentativas; rodada++) {
        printf("\nTentativa %d de %d\n", rodada, total_de_tentativas);

        printf("Digite um numero entre 1 e 100 (ou 0 para parar): ");
        if (scanf("%d", &chute) != 1) {
             chute = 101; // Valor que causa erro de entrada
             while (getchar() != '\n');
        }

        // Nova lógica: Parar o jogo
        if (chute == 0) {
            printf("\nVoce escolheu parar o jogo.\n");
            acertou = 0; // Garante que a mensagem de "fim do jogo" seja exibida corretamente
            break;
        }

        printf("Voce digitou %d\n", chute);

        // Tratamento de erro de entrada (1 a 100)
        if (chute < 1 || chute > 100) {
            printf("Voce deve digitar um numero entre 1 e 100!\n");
            rodada--; // Decrementa a rodada para que esta tentativa não conte
            continue;
        }

        // Condicionais
        acertou = (chute == numero_secreto);
        int maior = (chute > numero_secreto);
        int menor = (chute < numero_secreto);

        if (acertou) {
            printf("\nPARABENS! Voce acertou e fez %d pontos!\n", pontos);
            break; // Sai do loop de tentativas
        } else {
            if (maior) {
                printf("Voce errou! O seu chute foi maior do que o numero secreto.\n");
            } else if (menor) {
                printf("Voce errou! O seu chute foi menor do que o numero secreto.\n");
            }
            
            // Cálculo dos pontos perdidos: abs(numero_secreto - chute)
            pontos_perdidos = (int)fabs(numero_secreto - chute);
            pontos = pontos - pontos_perdidos;
            
            if (pontos < 0) {
                pontos = 0;
            }
            printf("Pontos atuais: %d\n", pontos);
        }
    }

    printf("\n---------- FIM DA PARTIDA ----------\n");
    // Nova função: Revelar o número secreto
    if (!acertou) {
        printf("O numero secreto era %d.\n", numero_secreto);
    }
    printf("Sua pontuacao final foi de %d pontos.\n", pontos);

    // Retorna um valor (0 ou 1) para ser usado no loop principal
    return 1; // Indica que a partida terminou e o loop principal deve continuar (pedir novo jogo)
}

// Função principal que contém o loop de repetição
int main() {
    int jogar_novamente = 1;

    // Inicializa a semente para a geração de números aleatórios
    srand(time(0));

    // Loop principal (do-while) para jogar múltiplas vezes
    do {
        // Gera um novo número secreto a cada novo jogo
        int novo_numero_secreto = rand() % 100 + 1;

        // Chama a função da partida
        jogar_partida(novo_numero_secreto);

        // Pergunta se o usuário quer jogar novamente
        printf("\nQuer jogar novamente? (1 para Sim / 0 para Nao): ");
        if (scanf("%d", &jogar_novamente) != 1) {
            jogar_novamente = 0; // Pára se a entrada for inválida
            while (getchar() != '\n'); 
        }

    } while (jogar_novamente == 1);

    printf("\nObrigado por jogar! Ate mais.\n");
    return 0;
}

//fabs é uma função que calcula o valor absoluto de um número de ponto flutuante (do tipo double ou float).
//srand é função usada para inicializar o gerador de números pseudoaleatórios;
