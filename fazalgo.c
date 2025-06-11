#include <stdio.h>
#include <windows.h>

void FazAlgo(int n) {
    int i, j, k;
    volatile int dummy = 0;
    
    for (i = 1; i < n - 1; i++) {
        for (j = i + 1; j <= n; j++) {
            for (k = 1; k <= j; k++) {
                dummy += i * j - k;
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
    int repeticoes = 10000;  // Número de repetições para aumentar precisão
    double tempo_total_us = 0.0;
    
    QueryPerformanceFrequency(&freq);
    
    // Medição com repetições para melhor precisão
    for (int r = 0; r < repeticoes; r++) {
        QueryPerformanceCounter(&inicio);
        FazAlgo(n);
        QueryPerformanceCounter(&fim);
        
        double tempo_us = (double)(fim.QuadPart - inicio.QuadPart) * 1000000.0 / freq.QuadPart;
        tempo_total_us += tempo_us;
    }
    
    double tempo_medio_us = tempo_total_us / repeticoes;
    printf("%.3f", tempo_medio_us);  // Tempo médio em microssegundos
    
    return 0;
}