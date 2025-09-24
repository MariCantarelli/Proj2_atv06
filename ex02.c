#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h> // Para INT_MAX
#include <math.h>   // Para abs() em algumas C compilers

// Variáveis globais para armazenar a melhor solução encontrada
long min_diferenca_global;
bool* melhor_solucao_global;

void encontrarSubconjuntos(int* arr, int n, int indice_atual, bool* solucao_atual, long soma_atual, int elementos_atuais, long soma_total) {
    if (indice_atual == n) {
        // A lógica para o caso ímpar é um pouco diferente, ajustamos para o tamanho do primeiro conjunto
        int tamanho_conjunto1 = (n % 2 == 0) ? (n / 2) : ((n + 1) / 2);
        if (elementos_atuais == tamanho_conjunto1) {
            long diferenca_atual = labs((soma_total - soma_atual) - soma_atual); // Usando labs para long
            if (diferenca_atual < min_diferenca_global) {
                min_diferenca_global = diferenca_atual;
                for (int i = 0; i < n; i++) {
                    melhor_solucao_global[i] = solucao_atual[i];
                }
            }
        }
        return;
    }

    int tamanho_conjunto1 = (n % 2 == 0) ? (n / 2) : ((n + 1) / 2);

    // ESCOLHA 1: Excluir o elemento atual
    if ((n - (indice_atual + 1)) >= (tamanho_conjunto1 - elementos_atuais)) {
        solucao_atual[indice_atual] = false;
        encontrarSubconjuntos(arr, n, indice_atual + 1, solucao_atual, soma_atual, elementos_atuais, soma_total);
    }

    // ESCOLHA 2: Incluir o elemento atual
    if (elementos_atuais < tamanho_conjunto1) {
        solucao_atual[indice_atual] = true;
        encontrarSubconjuntos(arr, n, indice_atual + 1, solucao_atual, soma_atual + arr[indice_atual], elementos_atuais + 1, soma_total);
    }
}

void caboDeGuerra(int* arr, int n) {
    bool* solucao_atual = (bool*)calloc(n, sizeof(bool));
    melhor_solucao_global = (bool*)calloc(n, sizeof(bool));
    min_diferenca_global = LONG_MAX;

    long soma_total = 0;
    for (int i = 0; i < n; i++) {
        soma_total += arr[i];
    }

    encontrarSubconjuntos(arr, n, 0, solucao_atual, 0, 0, soma_total);

    // --- SEÇÃO DE IMPRESSÃO MODIFICADA ---
    
    // Imprime o primeiro conjunto
    bool primeiro_item = true;
    for (int i = 0; i < n; i++) {
        if (melhor_solucao_global[i]) {
            if (!primeiro_item) {
                printf(", ");
            }
            printf("%d", arr[i]);
            primeiro_item = false;
        }
    }
    printf("\n");

    // Imprime o segundo conjunto
    primeiro_item = true;
    for (int i = 0; i < n; i++) {
        if (!melhor_solucao_global[i]) {
            if (!primeiro_item) {
                printf(", ");
            }
            printf("%d", arr[i]);
            primeiro_item = false;
        }
    }
    printf("\n");
}

int main() {
    printf("entrada: arr[] = [3, 4, 5, -3, 100, 1, 89, 54, 23, 20]\nsaída:\n");
    int arr1[] = {3, 4, 5, -3, 100, 1, 89, 54, 23, 20};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    caboDeGuerra(arr1, n1);
    printf("\n");

    // Também generalizei a lógica para funcionar com N ímpar, como no segundo exemplo.
    printf("entrada: arr[] = [23, 45, -34, 12, 0, 98, -99, 4, 189, -1, 4]\nsaída:\n");
    int arr2[] = {23, 45, -34, 12, 0, 98, -99, 4, 189, -1, 4};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    caboDeGuerra(arr2, n2);

    return 0;
}