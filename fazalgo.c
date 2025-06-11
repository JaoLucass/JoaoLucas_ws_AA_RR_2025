#include <stdio.h>
#include <time.h>

void FazAlgo(int n) {
    int i, j, k;
    volatile int dummy = 0; // Evita otimização dos loops
    
    for (i = 1; i < n - 1; i++) {
        for (j = i + 1; j <= n; j++) {
            for (k = 1; k <= j; k++) {
                dummy = i + j + k; // Operação O(1) que não será otimizada
            }
        }
    }
}

int main() {
    // Diferentes tamanhos de entrada para teste
    int tamanhos[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1200, 1500};
    int num_testes = sizeof(tamanhos) / sizeof(tamanhos[0]);
    
    printf("n\tTempo (segundos)\n");
    printf("--------------------------------\n");
    
    for (int i = 0; i < num_testes; i++) {
        int n = tamanhos[i];
        clock_t inicio, fim;
        double tempo_gasto;
        
        inicio = clock();
        FazAlgo(n);
        fim = clock();
        
        tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        
        printf("%d\t%f\n", n, tempo_gasto);
    }
    
    return 0;
}