#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

/* Função que recebe por VALOR: trabalha com uma cópia */
int alteraValor(int n){
    return n * 2;
}

/* Função que recebe por REFERÊNCIA (via ponteiro): altera o original */
void alteraValorRef(int *n){
    *n = *n * 2;
}

/* Dobra cada elemento de um array (vetor) IN-PLACE.
   Observação: em C, “passar um array” equivale a passar um ponteiro
   para o primeiro elemento; logo, a função altera o original. */
void dobrarElementos(int v[], int tamanho){
    for (int i = 0; i < tamanho; i++){
        v[i] = v[i] * 2;
    }
}

/* Struct simples para demonstrar acesso via ponteiro (->) */
typedef struct {
    char nome[20];
    int  idade;
} Pessoa;

/* Recebe ponteiro para struct e altera um campo */
void alteraReferencia(Pessoa *p) {
    p->idade = 99;  /* p->idade == (*p).idade */
}

int main(void){
    /* Se quiser testar acentuação no Windows:
       - descomente setlocale abaixo
       - no terminal: chcp 65001
    */
    // setlocale(LC_ALL, "Portuguese");

    /* -----------------------------------------------------------
       1. Declaração de variável e impressão do endereço
       ----------------------------------------------------------- */
    int x;

    printf("Entre com um numero inteiro: ");
    scanf("%d", &x);                  // &x = endereço de x

    printf("O valor de x e: %d\n", x);
    /* %p imprime endereços; a norma pede elencar como (void*), mas no windows funciona sem */
    printf("O endereco da variavel x e: %p\n", (void*)&x);

    /* Ponteiro para x: armazena o ENDEREÇO de x */
    int *ptx = &x;

    printf("ptx armazena o endereco de x: %p\n", (void*)ptx);
    /* *ptx = conteudo no endereco apontado (valor de x) */
    printf("conteudo apontado por ptx (*ptx): %d\n", *ptx);

    /* Demonstra que alterar via variável ou via *ponteiro muda o MESMO valor */
    x++;              // incrementa x
    printf("apos x++: x = %d\n", x);

    (*ptx)++;         // incrementa o valor apontado (x)
    printf("apos (*ptx)++: x = %d\n", x);

    /* -----------------------------------------------------------
       2. Strings (char[]) e aritmética de ponteiros
       ----------------------------------------------------------- */
    /* Dica importante: o tamanho do array deve incluir o '\0'
       em alguns compiladores nome[4] pode dar errou ou imprimir sujeira: 'J' 'o' 'a' 'o' '\0'          */
    char nome[5] = "Joao";

    printf("nome: %s\n", nome);
    printf("endereco de nome (nome == &nome[0]): %p\n", (void*)nome);

    char *ptnome = nome;  // ptnome aponta para o primeiro caractere

    printf("ptnome (endereco atual): %p\n", (void*)ptnome);
    printf("conteudo em *ptnome (primeira letra): %c\n", *ptnome);

    /* Percorrendo a string com ponteiro:
       - Pare em '\0' (fim da string)
       - Evite usar sizeof(nome) para percorrer “conteúdo lógico” de strings;
         sizeof(nome) conta a capacidade do buffer (inclui '\0'). */
    printf("Percorrendo cada letra: ");
    for(int i=0;i<5;i++){
        printf("%c ",*ptnome);
        *ptnome++;
    }
    printf("/n");
    //outra opção para imprimir Joao caracter a caracter sem precisar
    //do tamanho da string (5)
    for (char *p = nome; *p != '\0'; p++) {
        printf("%c ", *p);
    }
    printf("\n");

    /* -----------------------------------------------------------
       3. Passagem por valor vs. por referência
       ----------------------------------------------------------- */
    int n = 20;

    /* Por valor: função recebe uma CÓPIA; n não muda */
    printf("alteraValor(n) (por valor) = %d\n", alteraValor(n));
    printf("n apos chamada por valor = %d\n", n);

    /* Por referência: função recebe ENDEREÇO; n muda */
    alteraValorRef(&n);
    printf("n apos alteraValorRef(&n) (por referencia) = %d\n", n);

    /* -----------------------------------------------------------
       4. Arrays em funções (dobrar elementos)
       ----------------------------------------------------------- */
    int numeros[5] = {1, 2, 3, 4, 5};

    /* Aqui “numeros” decai para int*, logo a função altera o original */
    dobrarElementos(numeros, 5);

    printf("vetor apos dobrarElementos: ");
    for (int i = 0; i < 5; i++){
        printf("%d ", numeros[i]);
    }
    printf("\n");

    /* -----------------------------------------------------------
       5. Struct + ponteiro (operador ->)
       ----------------------------------------------------------- */
    Pessoa pessoa = {"Joao", 30};

    /* Passa o ENDERECO da struct, altera o original */
    alteraReferencia(&pessoa);

    printf("Idade de %s apos alteraReferencia: %d\n",
           pessoa.nome, pessoa.idade);  // esperado: 99

    return 0;
}
