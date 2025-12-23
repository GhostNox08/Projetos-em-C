/*
    Objetivo do exercício:
    - Demonstrar a diferença entre alocação estática (variáveis/arrays normais)
      e alocação dinâmica (malloc/free) em C.
    - Exibir valores e também os ENDEREÇOS de memória (ponteiros),
      praticando aritmética de ponteiros e o acesso a elementos.
*/

#include <stdio.h>   // printf
#include <stdlib.h>  // malloc, free

int main(void){
    // ===== Parte 1: variável inteira "a" alocada estaticamente (na stack) =====
    int a;           // declara uma variável inteira chamada 'a'
    a = 10;          // atribui o valor 10 à variável 'a'
    printf("a = %d \n", a);  // imprime o valor contido em 'a'

    // ===== Parte 2: alocação dinâmica de UM inteiro =====
    // int *ptr = (int*) malloc(sizeof(*ptr));
    // Observação: o cast (int*) não é necessário em C (é comum em C++),
    // mas aqui foi mantido para fins didáticos.
    int *ptr = (int*) malloc(sizeof(*ptr));  // aloca espaço para 1 int e retorna o endereço
    *ptr = 10;                               // armazena 10 na região apontada por 'ptr'
    printf("ptr = %p \n", (void*)ptr);       // imprime o ENDEREÇO armazenado em 'ptr'
    printf("*ptr = %d \n", *ptr);            // imprime o VALOR armazenado nesse endereço
    free(ptr);                               // libera a memória alocada dinamicamente para 'ptr'
    // (boa prática: após free(ptr); pode-se fazer ptr = NULL; para evitar ponteiro danificado)

    // Separador visual para a saída
    printf("****************\n");

    // ===== Parte 3: array estático =====
    int arr[5] = {1,2,3,4,5};                // declara e inicializa um array de 5 inteiros
    for(int i = 0; i < 5; i++){              // percorre os índices 0..4
        printf("arr[%d]=%d \n", i, arr[i]);  // imprime cada elemento do array estático
    }

    // Outro separador visual
    printf("****************\n");

    // ===== Parte 4: vetor (array) alocado dinamicamente =====
    // Aloca espaço para 5 inteiros de uma vez. sizeof(*ptx) é equivalente a sizeof(int) aqui.
    int *ptx = malloc(5 * sizeof(*ptx));     // retorna o endereço do primeiro elemento (base do bloco)
    int *cabeca = ptx;                       // guarda a "cabeça" (endereço base) para poder voltar depois

    // Imprimir o ENDEREÇO (não o valor). Use %p e converta para (void*).
    printf("ptx = %p\n", (void*)ptx);        // mostra o endereço para o qual 'ptx' está apontando

    // Preenche o bloco dinâmico com os valores 10,11,12,13,14 usando aritmética de ponteiros
    for(int i = 0; i < 5; i++){
        *ptx = 10 + i;   // escreve (10+i) NO ENDEREÇO apontado por 'ptx'
        ptx++;           // avança o ponteiro para o PRÓXIMO int do bloco (somando 1 "posição" = +sizeof(int))
    }

    // Após o loop acima, 'ptx' ficou 5 posições à frente (ou seja, 1 além do último elemento válido)
    printf("ptx (apos loop) = %p\n", (void*)ptx);  // imprime o endereço ATUAL (um após o fim do bloco)

    ptx = cabeca;  // "reset": volta o ponteiro para o endereço base do bloco dinâmico

    // Lê/imprime os valores como se fosse um array comum (indexação em ponteiros)
    for(int i = 0; i < 5; i++){
        printf("ptx[%d]=%d \n", i, (void*)ptx[i]);  // ptx[i] é açúcar sintático para *(ptx + i)
    }

    free(ptx);     // libera a memória do bloco dinâmico (precisa ser a "cabeça", que restauramos acima)
    // (boa prática: ptx = NULL; cabeca = NULL;)

    return 0;      // indica término bem-sucedido do programa
}
/*
observações:
Para imprimir endereços de ponteiro use sempre %p e passe (void*)ponteiro.
Depois de um free(ptr);, evite usar o ponteiro; se precisar, redefina-o para NULL para prevenir uso acidental.
Sempre que imprimir um ponteiro, para garantir conformidade, utilize (void*)ptr, por exemplo, em:
printf("ptx[%d]=%d \n", i, (void*)ptx[i]);
*/