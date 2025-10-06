#include <stdio.h>

void intercala(int arr[], int esq[], int n_esq, int dir[], int n_dir) {
	int i = 0, j = 0, k = 0;
	
	while (i < n_esq && j < n_dir){
		if (esq[i <= dir[j]){
			arr[k] = esq[i];
			i++;
		}
		else{
			arr[k] = di[j];
			j++;
		}
		k++;
	}
	
	while ( i < n_esq) {
		arr´[k] = esq[i];
		i++;
		k++;
	}
	
	while (j < n_dir) {
		arr[k] = dir[j];
		k++;
		j++;
	}
}

void mergeSort(int arr[], int tamanho) {
    if (tamanho <= 1) {
        return; // Caso base: o array j? est? ordenado.
    }

    int meio = tamanho / 2;

    int esquerda[meio];
    int direita[tamanho - meio];

    for (int i = 0; i < meio; i++) {
        esquerda[i] = arr[i];
    }

    for (int i = meio; i < tamanho; i++) {
        direita[i - meio] = arr[i];
    }

    mergeSort(esquerda, meio);
    mergeSort(direita, tamanho - meio);
    intercala(arr, esquerda, meio, direita, tamanho - meio);
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int tamanho = sizeof(arr) / sizeof(arr[0]);

    printf("Array original: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    mergeSort(arr, tamanho);

    printf("Array ordenado: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

