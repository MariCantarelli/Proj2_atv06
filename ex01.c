#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Função de comparação para qsort, para ordenar em ordem decrescente
int comparar_decrescente(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}


bool podeFormarQuadradoRecursivo(int* palitos, int tamanho, int indice, int lados[], int lado_alvo) {
    // Caso base: Se todos os palitos foram alocados, encontramos uma solução!
    if (indice == tamanho) {
        return true;
    }

    // Para o palito atual (palitos[indice]), tentamos colocá-lo em cada um dos 4 lados.
    for (int i = 0; i < 4; i++) {
        // Se colocar este palito no lado 'i' não ultrapassar o alvo...
        if (lados[i] + palitos[indice] <= lado_alvo) {
            // --- FAZ A ESCOLHA ---
            lados[i] += palitos[indice];

            if (podeFormarQuadradoRecursivo(palitos, tamanho, indice + 1, lados, lado_alvo)) {
                return true; // Se a exploração deu certo, propaga o sucesso
            }

            lados[i] -= palitos[indice];
        }
    }

    // Se o palito atual não pôde ser encaixado em nenhum lado que leve a uma solução, retorna false.
    return false;
}


bool podeFormarQuadrado(int* palitos_de_fosforos, int tamanho) {
    // --- Verificações Iniciais ---
    if (tamanho < 4) {
        return false;
    }

    long soma_total = 0;
    for (int i = 0; i < tamanho; i++) {
        soma_total += palitos_de_fosforos[i];
    }

    if (soma_total % 4 != 0) {
        return false;
    }

    int lado_alvo = soma_total / 4;

    // --- Otimização: Ordenar em ordem decrescente ---
    qsort(palitos_de_fosforos, tamanho, sizeof(int), comparar_decrescente);

    // Se o maior palito já for maior que o lado, é impossível.
    if (palitos_de_fosforos[0] > lado_alvo) {
        return false;
    }

    // Vetor para armazenar a soma de cada lado que estamos construindo.
    int lados[4] = {0, 0, 0, 0};

    // Inicia o processo de backtracking a partir do primeiro palito (índice 0).
    return podeFormarQuadradoRecursivo(palitos_de_fosforos, tamanho, 0, lados, lado_alvo);
}

// Função main para testar o código
int main() {
    int palitos1[] = {1, 1, 2, 2, 2};
    int tam1 = sizeof(palitos1) / sizeof(palitos1[0]);
    // Soma = 8, Lado Alvo = 2. Possível: {2}, {2}, {1,1}, {2}
    bool resultado1 = podeFormarQuadrado(palitos1, tam1);
    printf("Teste 1 ({1,1,2,2,2}): %s\n", resultado1 ? "true" : "false"); // Saída esperada: true

    int palitos2[] = {3, 3, 3, 3, 4};
    int tam2 = sizeof(palitos2) / sizeof(palitos2[0]);
    // Soma = 16, Lado Alvo = 4. Impossível: não dá pra usar os 3s pra somar 4
    bool resultado2 = podeFormarQuadrado(palitos2, tam2);
    printf("Teste 2 ({3,3,3,3,4}): %s\n", resultado2 ? "true" : "false"); // Saída esperada: false

    int palitos3[] = {5, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3, 3};
    int tam3 = sizeof(palitos3) / sizeof(palitos3[0]);
    // Soma = 48, Lado Alvo = 12. Possível: {5,4,3}, {5,4,3}, {5,4,3}, {5,4,3}
    bool resultado3 = podeFormarQuadrado(palitos3, tam3);
    printf("Teste 3 ({5,5,5,5,4,4,4,4,3,3,3,3}): %s\n", resultado3 ? "true" : "false"); // Saída esperada: true

    return 0;
}