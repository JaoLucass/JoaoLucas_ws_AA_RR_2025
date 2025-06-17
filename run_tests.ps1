# Configurações
$tamanhos = 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1500
$repeticoes = 5
$resultadosDir = "resultados"
$relatoriosDir = "relatorios"

# Criar diretórios se não existirem
New-Item -ItemType Directory -Path $resultadosDir -Force | Out-Null
New-Item -ItemType Directory -Path $relatoriosDir -Force | Out-Null

# Compilar o código
gcc -O0 -o algoritmo.exe fazalgo.c
if (-not $?) {
    Write-Host "Erro na compilação!" -ForegroundColor Red
    exit 1
}

# Arquivo de resultados
$outputFile = "$resultadosDir\resultados.csv"
"n,tempo_medio_ms" | Out-File $outputFile -Encoding UTF8

# Executar testes
foreach ($n in $tamanhos) {
    Write-Host "Testando n = $n"
    $tempoTotal = 0.0
    
    for ($i = 1; $i -le $repeticoes; $i++) {
        $output = .\algoritmo.exe $n
        $tempo = [double]$output
        $tempoTotal += $tempo   # <-- Adicione esta linha
        Write-Host "  Execução $i`: $output ms"
    }
    
    $tempoMedio = $tempoTotal / $repeticoes
    Write-Host "Tempo médio: $tempoMedio ms`n"
    "$n,$tempoMedio" | Out-File $outputFile -Append -Encoding UTF8
}

# Gerar relatório
python analyze_results.py

Write-Host "Testes concluídos! Verifique as pastas $resultadosDir e $relatoriosDir"