//* ATIVIDADE 1 - SIMPLES: DIVIDIR UM ARRANJO EM 3 PARTES IGUAIS, 
//* JOGANDO UM PARA O SELECION, OUTRA PARA O INSERCTION E A ULTIMA PARA O BUBBLE.
//* AO RETORNAR OS ARRANJOS ORDENADOS, FAZER UM MERGE.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void trocar(int *x, int *y) {
    int aux = *x;
    *x = *y;
    *y = aux;
}

int* criarArranjoSemRepeticao(int n) {
    int* arranjo = (int*)malloc(n * sizeof(int));
    if (arranjo == NULL) {
        printf("Problema na alocacao de Memoria\n");
        exit(1);
    }

    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        int novoNumero, repetido;
        do {
            repetido = 0;
            novoNumero = rand() % (n * 5);
            for (int j = 0; j < i; j++) {
                if (arranjo[j] == novoNumero) {
                    repetido = 1;
                    break;
                }
            }
        } while (repetido);

        arranjo[i] = novoNumero;
    }

    return arranjo;
}


void ordenacao_por_selecao(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int posmenor = i;
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[posmenor]) {
                posmenor = j;
            }
        }
        if (posmenor != i) {
            trocar(&A[i], &A[posmenor]);
        }
    }
}


void ordenacao_por_insercao(int A[], int n) {
    for (int j = 1; j < n; j++) {
        int chave = A[j];
        int i = j - 1;

        while (i >= 0 && A[i] > chave) {
            A[i + 1] = A[i];
            i--;
        }
        A[i + 1] = chave;
    }
}


void ordenacao_bubble(int A[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n - i; j++) {
            if (A[j - 1] > A[j]) {
                trocar(&A[j - 1], &A[j]);
            }
        }
    }
}


void mostrar(int A[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}


void merge_tres_partes(int A[], int tam, int n) {
    int i = 0;        
    int j = tam;      
    int k = 2 * tam;  

    int *resultado = (int*)malloc(n * sizeof(int));
    int r = 0;

    while (i < tam || j < 2 * tam || k < 3 * tam) {

        if (i < tam &&
           (j >= 2 * tam || A[i] <= A[j]) &&
           (k >= 3 * tam || A[i] <= A[k])) {

            resultado[r++] = A[i++];
        }
        else if (j < 2 * tam &&
                (k >= 3 * tam || A[j] <= A[k])) {

            resultado[r++] = A[j++];
        }
        else {
            resultado[r++] = A[k++];
        }
    }

   
    for (int x = 0; x < n; x++) {
        A[x] = resultado[x];
    }

    free(resultado);
}

int main() {
    int n = 15;
    int tam = n / 3;

    int* A = criarArranjoSemRepeticao(n);

    printf("1. ARRAY ORIGINAL:\n");
    mostrar(A, n);
    printf("--------------------------------------------\n");

    printf("2. DIVIDINDO E ORDENANDO AS 3 PARTES:\n");

 
    ordenacao_por_selecao(&A[0], tam);
    printf("Parte 1 (Selection): ");
    mostrar(&A[0], tam);

  
    ordenacao_por_insercao(&A[tam], tam);
    printf("Parte 2 (Insertion): ");
    mostrar(&A[tam], tam);

 
    ordenacao_bubble(&A[2 * tam], tam);
    printf("Parte 3 (Bubble):    ");
    mostrar(&A[2 * tam], tam);

    printf("--------------------------------------------\n");

  
    merge_tres_partes(A, tam, n);

    printf("3. ARRAY FINAL ORDENADO (MERGE CORRETO):\n");
    mostrar(A, n);

    free(A);
    return 0;
}
