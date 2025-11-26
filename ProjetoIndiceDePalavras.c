/* 
Projeto Final – Índice de Palavras 
Aluno(s): Adrian Pereira da Silva Lemes
Estrutura escolhida: Árvore Binária de Busca (ABB) não balanceada

Justificativa (resumo):
A ABB foi escolhida porque é simples de implementar e já organiza as palavras 
em ordem lexicográfica pela própria estrutura (esquerda < raiz < direita). 
Ela permite busca e inserção eficiente na média, sem necessidade de estruturas 
mais complexas como AVL ou Red-Black Tree. Isso facilita a implementação do 
índice e das operações de listagem alfabeticamente.

Complexidades (Big-O):
insert_token: O(h)   → O(log n) na média, O(n) no pior caso  
search_token: O(h)   → O(log n) na média, O(n) no pior caso  
list_sorted:  O(n)   
(estratégia: travessia in-order da ABB, que já produz ordem alfabética)

topK:
O(n log n)
(estratégia usada no código: copiar todos os nós para um vetor e usar qsort 
ordenando por frequência de forma decrescente)

Observações adicionais:
- Tokens são normalizados: minúsculas, remoção de pontuação e descarte de 
  palavras com menos de 2 caracteres.  
- Frequência das palavras é incrementada diretamente nos nós.  
- A ABB não é balanceada, então a performance pode degradar se o texto tiver 
  muitas palavras em ordem similar.  
  
Obs: Ordem lexicográfica é a disciplina que estuda e organiza o léxico de uma língua.
Obs2: é uma estrutura de dados em forma de árvore binária de busca balanceada. Essa estrutura é utilizada em algoritmos de busca e ordenação, sendo uma alternativa eficiente para garantir um bom desempenho em operações de inserção, remoção e busca de elementos. 
  
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// =========================================================================
// ESTRUTURA DE DADOS: ÁRVORE BINÁRIA DE BUSCA (ABB)
// =========================================================================

typedef struct NoPalavra {
    char *token;
    int frequencia;
    struct NoPalavra *esquerda;
    struct NoPalavra *direita;
} NoPalavra;

typedef struct {
    char *palavra;
    int frequencia;
} ItemFrequencia;

// =========================================================================
// PROTÓTIPOS DAS FUNÇÕES
// =========================================================================
NoPalavra* criar_no(const char *token);
NoPalavra* inserir_token(NoPalavra *raiz, const char *token);
NoPalavra* buscar_token(NoPalavra *raiz, const char *token);
void liberar_memoria(NoPalavra *raiz);
char *normalizar_token(char *token);
int processar_arquivo(const char *nome_arquivo, NoPalavra **raiz);

void carregar_texto_e_montar_indice(NoPalavra **raiz);
void buscar_palavra_menu(NoPalavra *raiz);
void listar_palavras(NoPalavra *raiz);
void exibir_top_n(NoPalavra *raiz);

void travessia_inorder_alfabetica(NoPalavra *raiz);
int contar_nos(NoPalavra *raiz);
void popular_vetor_com_dados(NoPalavra *raiz, ItemFrequencia **vetor, int *indice);
int comparar_frequencia(const void *a, const void *b);

// =========================================================================
// IMPLEMENTAÇÃO DAS FUNÇÕES
// =========================================================================

NoPalavra* criar_no(const char *token) {
    NoPalavra *novo_no = (NoPalavra *)malloc(sizeof(NoPalavra));
    if (novo_no == NULL) return NULL;

    novo_no->token = (char *)malloc(strlen(token) + 1);
    if (novo_no->token == NULL) {
        free(novo_no);
        return NULL;
    }
    strcpy(novo_no->token, token);

    novo_no->frequencia = 1;
    novo_no->esquerda = NULL;
    novo_no->direita = NULL;
    return novo_no;
}

NoPalavra* inserir_token(NoPalavra *raiz, const char *token) {
    if (raiz == NULL) {
        return criar_no(token);
    }

    int comparacao = strcmp(token, raiz->token);

    if (comparacao < 0) {
        raiz->esquerda = inserir_token(raiz->esquerda, token);
    } else if (comparacao > 0) {
        raiz->direita = inserir_token(raiz->direita, token);
    } else {
        raiz->frequencia++;
    }
    return raiz;
}

NoPalavra* buscar_token(NoPalavra *raiz, const char *token) {
    if (raiz == NULL) return NULL;

    int comparacao = strcmp(token, raiz->token);
    if (comparacao == 0) return raiz;
    else if (comparacao < 0) return buscar_token(raiz->esquerda, token);
    else return buscar_token(raiz->direita, token);
}

void liberar_memoria(NoPalavra *raiz) {
    if (raiz != NULL) {
        liberar_memoria(raiz->esquerda);
        liberar_memoria(raiz->direita);
        free(raiz->token);
        free(raiz);
    }
}

// =========================================================================
// TOKENIZAÇÃO E PROCESSAMENTO
// =========================================================================

char *normalizar_token(char *token) {
    if (!token || token[0] == '\0') return NULL;

    // 1. Converter para minúsculas
    int i;
    for (i = 0; token[i]; i++) {
        token[i] = tolower((unsigned char)token[i]);
    }

    // 2. Remover pontuações (ficar só com letras/dígitos)
    int j;
    for (i = 0, j = 0; token[i] != '\0'; i++) {
        if (isalnum((unsigned char)token[i])) {
            token[j++] = token[i];
        }
    }
    token[j] = '\0';

    // 3. Descartar tokens muito curtos (ex: 1 letra)
    if (strlen(token) < 2) return NULL;

    return token;
}

int processar_arquivo(const char *nome_arquivo, NoPalavra **raiz) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) return -1;

    char linha[1024];
    const char *delimitadores = " \t\n.,!?;:\"()[]{}<>@#$%^&*-+=/\\|~`";

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *token = strtok(linha, delimitadores);
        while (token != NULL) {
            char temp[1024];
            strcpy(temp, token);
            char *token_normalizado = normalizar_token(temp);

            if (token_normalizado != NULL) {
                *raiz = inserir_token(*raiz, token_normalizado);
            }

            token = strtok(NULL, delimitadores);
        }
    }

    fclose(arquivo);
    return 0;
}

// =========================================================================
// FUNÇÕES AUXILIARES PARA LISTAGEM E TOPK
// =========================================================================

int contar_nos(NoPalavra *raiz) {
    if (raiz == NULL) return 0;
    return 1 + contar_nos(raiz->esquerda) + contar_nos(raiz->direita);
}

void popular_vetor_com_dados(NoPalavra *raiz, ItemFrequencia **vetor, int *indice) {
    if (raiz == NULL) return;
    popular_vetor_com_dados(raiz->esquerda, vetor, indice);
    (*vetor)[*indice].palavra = raiz->token;
    (*vetor)[*indice].frequencia = raiz->frequencia;
    (*indice)++;
    popular_vetor_com_dados(raiz->direita, vetor, indice);
}

int comparar_frequencia(const void *a, const void *b) {
    ItemFrequencia *A = (ItemFrequencia *)a;
    ItemFrequencia *B = (ItemFrequencia *)b;
    return B->frequencia - A->frequencia;
}

void travessia_inorder_alfabetica(NoPalavra *raiz) {
    if (raiz != NULL) {
        travessia_inorder_alfabetica(raiz->esquerda);
        printf("  %s (%d)\n", raiz->token, raiz->frequencia);
        travessia_inorder_alfabetica(raiz->direita);
    }
}

// =========================================================================
// MENU E OPERAÇÕES
// =========================================================================

void carregar_texto_e_montar_indice(NoPalavra **raiz) {
    char nome_arquivo[100];
    printf("Digite o nome do arquivo .txt do professor: ");
    scanf("%s", nome_arquivo);

    if (*raiz != NULL) {
        liberar_memoria(*raiz);
        *raiz = NULL;
    }

    if (processar_arquivo(nome_arquivo, raiz) == 0) {
        printf("Arquivo '%s' carregado e índice montado com sucesso.\n", nome_arquivo);
    } else {
        printf("ERRO: Não foi possível abrir o arquivo '%s'.\n", nome_arquivo);
    }
}

void buscar_palavra_menu(NoPalavra *raiz) {
    if (raiz == NULL) {
        printf("Índice vazio. Carregue um arquivo primeiro.\n");
        return;
    }

    char palavra[100];
    printf("Digite a palavra a buscar: ");
    scanf("%s", palavra);

    char *normalizada = normalizar_token(palavra);
    if (normalizada == NULL) {
        printf("Palavra inválida.\n");
        return;
    }

    NoPalavra *res = buscar_token(raiz, normalizada);
    if (res != NULL) {
        printf("PALAVRA ENCONTRADA: '%s' | Frequência: %d\n", res->token, res->frequencia);
    } else {
        printf("Palavra '%s' não encontrada.\n", normalizada);
    }
}

void listar_palavras(NoPalavra *raiz) {
    if (raiz == NULL) {
        printf("Índice vazio.\n");
        return;
    }

    int escolha;
    printf("\nListagem:\n");
    printf("1) Ordem Alfabética\n");
    printf("2) Ordem de Frequência\n");
    printf("Escolha: ");
    scanf("%d", &escolha);

    if (escolha == 1) {
        printf("\n--- Palavras em Ordem Alfabética ---\n");
        travessia_inorder_alfabetica(raiz);
    } else if (escolha == 2) {
        int total = contar_nos(raiz);
        ItemFrequencia *vetor = malloc(total * sizeof(ItemFrequencia));
        if (!vetor) return;
        int idx = 0;
        popular_vetor_com_dados(raiz, &vetor, &idx);
        qsort(vetor, total, sizeof(ItemFrequencia), comparar_frequencia);
        printf("\n--- Palavras em Ordem de Frequência ---\n");
        for (int i = 0; i < total; i++) {
            printf("  %s (%d)\n", vetor[i].palavra, vetor[i].frequencia);
        }
        free(vetor);
    } else {
        printf("Opção inválida.\n");
    }
}

void exibir_top_n(NoPalavra *raiz) {
    if (raiz == NULL) {
        printf("Índice vazio.\n");
        return;
    }

    int total = contar_nos(raiz);
    if (total == 0) return;

    int n;
    printf("Digite o valor de N: ");
    scanf("%d", &n);
    if (n <= 0) return;

    ItemFrequencia *vetor = malloc(total * sizeof(ItemFrequencia));
    if (!vetor) return;

    int idx = 0;
    popular_vetor_com_dados(raiz, &vetor, &idx);
    qsort(vetor, total, sizeof(ItemFrequencia), comparar_frequencia);

    if (n > total) n = total;

    printf("\n--- Top %d Palavras ---\n", n);
    for (int i = 0; i < n; i++) {
        printf("  %s (%d)\n", vetor[i].palavra, vetor[i].frequencia);
    }

    free(vetor);
}

// =========================================================================
// MAIN
// =========================================================================

int main() {
    NoPalavra *raiz = NULL;
    int opcao;

    do {
        printf("\n========== MENU ==========\n");
        printf("1) Carregar texto e montar índice\n");
        printf("2) Buscar palavra\n");
        printf("3) Listar todas as palavras\n");
        printf("4) Exibir Top N palavras mais frequentes\n");
        printf("0) Sair\n");
        printf("==========================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            carregar_texto_e_montar_indice(&raiz);
            break;
        case 2:
            buscar_palavra_menu(raiz);
            break;
        case 3:
            listar_palavras(raiz);
            break;
        case 4:
            exibir_top_n(raiz);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    liberar_memoria(raiz);
    return 0;
}
