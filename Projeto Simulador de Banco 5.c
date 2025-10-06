#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

// Definindo a estrutura de uma conta bancária
struct Conta {
    char username[20];
    char pin[5];
    float saldo;
};

// Estrutura para representar a transação
struct Transacao {
    char remetente[20];
    char destinatario[20];
    float valor;
};

//Função para realizar login
bool login(struct Conta contas[], int numContas, char username[], char pin[]) {
    int i; // Declaração movida para o início da função
    for (i = 0; i < numContas; i++) {
        if (strcmp(contas[i].username, username) == 0 && strcmp(contas[i].pin, pin) == 0) {
            return true;
        }
    }
    return false;
}

//Função para consultar o saldo
void consultarSaldo(struct Conta contas[], int numContas, char username[]) {
    int i; // Declaração movida para o início da função
    for (i = 0; i < numContas; i++) {
        if (strcmp(contas[i].username, username) == 0) {
            printf("\e[1;34mSaldo atual: %.2f\n\e[0m", contas[i].saldo);
            return;
        }
    }
    printf("Conta não encontrada\n");
}

// Função para realizar o saque
void sacar(struct Conta contas[], int numContas, char username[], float valor) {
    int i; // Declaração movida para o início da função
    for (i = 0; i < numContas; i++) {
        if (strcmp(contas[i].username, username) == 0) {
            if (contas[i].saldo >= valor) {
                contas[i].saldo -= valor;
                printf("\e[1;31mSaque de %.2f realizado com sucesso.\n\e[0m", valor);
                printf("\e[1;34mSaldo atual: %.2f\n\e[0m", contas[i].saldo);
            } else {
                printf("\e[1;31mSaldo insuficiente. \n\e[0m");
            }
            return;
        }
    }
    printf("Conta não encontrada. \n");
}

// Função para realizar depósito
void depositar(struct Conta contas[], int numContas, char username[], float valor) {
    int i; // Declaração movida para o início da função
    for (i = 0; i < numContas; i++) {
        if (strcmp(contas[i].username, username) == 0) {
            contas[i].saldo += valor;
            printf("\e[1;32mDepósito de %.2f realizado com sucesso.\n\e[0m", valor);
            printf("\e[1;34mSaldo atual: %.2f\n\e[0m", contas[i].saldo);
            return;
        }
    }
    printf("Conta não encontrada.\n");
}

// Função para realizar transferências entre contas
void transferir(struct Conta contas[], int numContas, struct Transacao transacao) {
    int i; // Declaração movida para o início da função
    int indiceRemetente = -1;
    int indiceDestinatario = -1;

    for (i = 0; i < numContas; i++) {
        if (strcmp(contas[i].username, transacao.remetente) == 0) {
            indiceRemetente = i;
        }
        if (strcmp(contas[i].username, transacao.destinatario) == 0) {
            indiceDestinatario = i;
        }
    }

    if (indiceRemetente != -1 && indiceDestinatario != -1) {
        if (contas[indiceRemetente].saldo >= transacao.valor) {
            contas[indiceRemetente].saldo -= transacao.valor;
            contas[indiceDestinatario].saldo += transacao.valor;
            printf("\e[1;32mTransferencia de %.2f realizada com sucesso de %s para %s.\n\e[0m",
                   transacao.valor, contas[indiceRemetente].username, contas[indiceDestinatario].username);
        } else {
            printf("\e[1;31mSaldo insuficiente para a transferência.\n\e[0m");
        }
    } else {
        printf("\e[1;31mConta de remetente ou destinatario não encontrada.\n\e[0m");
    }
}

// Função para limpar a tela do console
void limparTela() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

// Função para ler o PIN sem eco
void lerPin(char pin[], int tamanho) {
    #ifdef _WIN32
    int i = 0;
    char ch;
    while ((ch = getch()) != '\r' && i < tamanho - 1) {
        if (ch == '\b' && i > 0) {
            printf("\b \b");
            i--;
            continue;
        }
        if (ch == '\b' && i == 0) {
            continue;
        }
        pin[i++] = ch;
        printf("*");
    }
    pin[i] = '\0';
    printf("\n");
    #else
    struct termios oldt, newt;
    int i = 0;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while ((ch = getchar()) != '\n' && i < tamanho - 1) {
        if (ch == 127 || ch == '\b') {
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        } else {
            pin[i++] = ch;
            printf("*");
        }
    }
    pin[i] = '\0';
    printf("\n");

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    #endif
}

void desenharPare() {
    printf("\n");
    printf("    /--\\\n");
    printf("   | STOP |\n");
    printf("    \\--/\n");
    printf("\n");
    printf("    \e[1;31mACESSO NEGADO\e[0m\n");
    printf("    \e[1;31mSISTEMA ENCERRADO\e[0m\n");
}

int main() {
    struct Conta contas[3] = {{"user1", "1234", 1000.0},
                              {"user2", "5678", 500.0},
                              {"user3", "9012", 500.0}};
    
    int numContas = 3;
    int opcao;
    float valor;
    struct Transacao transacao;
    char username[20];
    char pin[5];
    int c;
    int tentativas = 0;

    while (true) {
        printf("Digite o nome de usuário: ");
        scanf("%s", username);

        printf("Digite o PIN (4 digitos): ");
        lerPin(pin, 5);

        if (strlen(pin) != 4) {
            printf("PIN deve ter exatamente 4 digitos.\n");
            limparTela();
            continue;
        }

        if (login(contas, numContas, username, pin)) {
            printf("Login bem-sucedido!\n");
            limparTela();
            tentativas = 0; // Reseta o contador de tentativas
            do {
                printf("\nMenu:\n");
                printf("1. Consultar Saldo\n");
                printf("2. Sacar\n");
                printf("3. Depositar\n");
                printf("4. Transferir\n");
                printf("5. Sair\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &opcao);

                while ((c = getchar()) != '\n' && c != EOF);

                switch (opcao) {
                    case 1:
                        consultarSaldo(contas, numContas, username);
                        break;
                    case 2:
                        printf("Digite o valor a ser sacado: ");
                        scanf("%f", &valor);
                        sacar(contas, numContas, username, valor);
                        break;
                    case 3:
                        printf("Digite o valor a ser depositado: ");
                        scanf("%f", &valor);
                        depositar(contas, numContas, username, valor);
                        break;
                    case 4:
                        printf("Digite o nome de usuário do destinatário: ");
                        scanf("%s", transacao.destinatario);
                        printf("Digite o valor a ser transferido: ");
                        scanf("%f", &transacao.valor);
                        strcpy(transacao.remetente, username);
                        transferir(contas, numContas, transacao);
                        break;
                    case 5:
                        printf("Saindo...\n");
                        break;
                    default:
                        printf("Opção inválida. Tente novamente. \n");
                }
            } while (opcao != 5);
            limparTela();
        } else {
            tentativas++; // Incrementa o contador de tentativas
            if (tentativas >= 3) {
                desenharPare();
                printf("\n\n\e[1;31mPressione qualquer tecla para sair...\e[0m");
                
                #ifdef _WIN32
                getch();
                #else
                getchar();
                #endif

                return 1; // Encerra o programa
            }
            printf("Nome de usuário ou PIN incorretos. Tentativas restantes: %d\n", 3 - tentativas);
            limparTela();
        }
    }

    return 0;
}
