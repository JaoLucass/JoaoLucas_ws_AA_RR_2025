#include <stdio.h>
#include <windows.h>

void FazAlgo(int n) {
    int i, j, k;
    volatile int dummy = 0; // Previne otimização
    
    for (i = 1; i < n - 1; i++) {
        for (j = i + 1; j <= n; j++) {
            for (k = 1; k <= j; k++) {
                dummy += i * j - k; // Operação não trivial
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <n>\n", argv[0]);
        return 1;
    }
    
    int n = atoi(argv[1]);
    LARGE_INTEGER inicio, fim, freq;
    
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&inicio);
    
    FazAlgo(n);
    
    QueryPerformanceCounter(&fim);
    double tempo_ms = (double)(fim.QuadPart - inicio.QuadPart) * 1000.0 / freq.QuadPart;
    
    printf("%.3f", tempo_ms); // Saída apenas do tempo
    return 0;
}