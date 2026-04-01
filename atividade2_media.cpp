//*ATIVIDADE 2 - MEDIA - CRIAR UM ARRANJO COM 10,100,1000,10000,50000,100000,200000,300000,400000,500000.
//*CRIAR 4 COPIAS . INSERCTION, SELECTION,BUBBLE,MERGE , QUICK

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


int* criarArranjo(int n) {
    int *v = (int*) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        v[i] = rand() % (n * 10);
    }
    return v;
}


void copiar(int *orig, int *dest, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = orig[i];
    }
}


void selection(int v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[min]) min = j;
        }
        trocar(&v[i], &v[min]);
    }
}


void insertion(int v[], int n) {
    for (int j = 1; j < n; j++) {
        int chave = v[j];
        int i = j - 1;

        while (i >= 0 && v[i] > chave) {
            v[i + 1] = v[i];
            i--;
        }
        v[i + 1] = chave;
    }
}


void bubble(int v[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n - i; j++) {
            if (v[j - 1] > v[j]) {
                trocar(&v[j - 1], &v[j]);
            }
        }
    }
}


void merge(int v[], int inicio, int meio, int fim) {
    int i = inicio, j = meio + 1, k = 0;
    int *temp = (int*) malloc((fim - inicio + 1) * sizeof(int));

    while (i <= meio && j <= fim) {
        if (v[i] < v[j]) temp[k++] = v[i++];
        else temp[k++] = v[j++];
    }

    while (i <= meio) temp[k++] = v[i++];
    while (j <= fim) temp[k++] = v[j++];

    for (i = inicio, k = 0; i <= fim; i++, k++) {
        v[i] = temp[k];
    }

    free(temp);
}

void mergeSort(int v[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        mergeSort(v, inicio, meio);
        mergeSort(v, meio + 1, fim);
        merge(v, inicio, meio, fim);
    }
}


int particionar(int v[], int inicio, int fim) {
    int pivo = v[fim];
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        if (v[j] < pivo) {
            i++;
            trocar(&v[i], &v[j]);
        }
    }

    trocar(&v[i + 1], &v[fim]);
    return i + 1;
}

void quickSort(int v[], int inicio, int fim) {
    if (inicio < fim) {
        int p = particionar(v, inicio, fim);
        quickSort(v, inicio, p - 1);
        quickSort(v, p + 1, fim);
    }
}


int main() {
    srand(time(NULL));

    int tamanhos[] = {10, 100, 1000, 10000, 50000, 100000, 200000, 300000, 400000, 500000};

    printf("N\tInsertion\tSelection\tBubble\tMerge\tQuick\n");

    for (int t = 0; t < 10; t++) {
        int n = tamanhos[t];

        int *original = criarArranjo(n);

		int *v1 = (int*) malloc(n * sizeof(int));
		int *v2 = (int*) malloc(n * sizeof(int));
		int *v3 = (int*) malloc(n * sizeof(int));
		int *v4 = (int*) malloc(n * sizeof(int));
		int *v5 = (int*) malloc(n * sizeof(int));
		
        copiar(original, v1, n);
        copiar(original, v2, n);
        copiar(original, v3, n);
        copiar(original, v4, n);
        copiar(original, v5, n);

        clock_t ini, fim;
        double t1, t2, t3, t4, t5;

 
        ini = clock();
        insertion(v1, n);
        fim = clock();
        t1 = (double)(fim - ini) / CLOCKS_PER_SEC;

 
        ini = clock();
        selection(v2, n);
        fim = clock();
        t2 = (double)(fim - ini) / CLOCKS_PER_SEC;


        ini = clock();
        bubble(v3, n);
        fim = clock();
        t3 = (double)(fim - ini) / CLOCKS_PER_SEC;

       
        ini = clock();
        mergeSort(v4, 0, n - 1);
        fim = clock();
        t4 = (double)(fim - ini) / CLOCKS_PER_SEC;

    
        ini = clock();
        quickSort(v5, 0, n - 1);
        fim = clock();
        t5 = (double)(fim - ini) / CLOCKS_PER_SEC;

        printf("%d\t%f\t%f\t%f\t%f\t%f\n", n, t1, t2, t3, t4, t5);

        free(original);
        free(v1); free(v2); free(v3); free(v4); free(v5);
    }

    return 0;
}
