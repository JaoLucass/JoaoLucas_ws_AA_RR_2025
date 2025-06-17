import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

# Configurações
resultados_dir = 'resultados'
relatorios_dir = 'relatorios'
csv_path = os.path.join(resultados_dir, 'resultados.csv')
relatorio_path = os.path.join(relatorios_dir, 'relatorio.txt')
grafico_path = os.path.join(relatorios_dir, 'desempenho.png')

# Processar dados
df = pd.read_csv(csv_path)
df['log(tempo)'] = np.log(df['tempo_medio_ms'])

# Calcular regressão linear para verificar complexidade
coef = np.polyfit(np.log(df['n']), np.log(df['tempo_medio_ms']), 1)
expoente = coef[0]

# Criar gráfico
plt.figure(figsize=(10, 6))

# Gráfico 1: Tempo vs n
plt.subplot(1, 2, 1)
plt.plot(df['n'], df['tempo_medio_ms'], 'bo-')
plt.title('Tempo de Execução vs Tamanho da Entrada')
plt.xlabel('n')
plt.ylabel('Tempo (ms)')
plt.grid(True)

plt.tight_layout()
plt.savefig(grafico_path)
plt.close()

# Gerar relatório textual
with open(relatorio_path, 'w') as f:
    f.write("Relatório de Desempenho - Algoritmo FazAlgo\n")
    f.write("===========================================\n\n")
    f.write(f"Testes realizados: {len(df)} tamanhos diferentes\n")
    f.write(f"Repetições por teste: 5\n")
    f.write(f"Expoente calculado: {expoente:.4f} (esperado ~3 para O(n³))\n\n")
    
    f.write("Resultados Detalhados:\n")
    f.write("n\tTempo Médio (ms)\n")
    f.write("-------------------\n")
    for _, row in df.iterrows():
        f.write(f"{row['n']}\t{row['tempo_medio_ms']:.3f}\n")
    
    f.write("\nConclusão:\n")
    if 2.9 <= expoente <= 3.1:
        f.write("O algoritmo demonstra comportamento O(n³) como esperado.")
    else:
        f.write(f"Possível anomalia: expoente calculado ({expoente:.4f}) difere significativamente de 3.")

print(f"Relatório gerado em: {relatorio_path}")
print(f"Gráfico salvo em: {grafico_path}")