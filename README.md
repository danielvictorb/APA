# APA — Benchmark de Algoritmos de Ordenação

Compara o desempenho de **Insertion Sort**, **Selection Sort**, **Quick Sort** (partição de Hoare) e **Merge Sort** em diferentes cenários de entrada, medindo o tempo de execução para arrays de 1.000 a 100.000 elementos e gerando gráficos com os resultados.

## Cenários de entrada

| Tipo | Descrição |
|------|-----------|
| `random` | Valores aleatórios entre 0 e n |
| `few_unique` | Apenas 11 valores distintos (0–10) |
| `sorted` | Array já ordenado (0, 1, 2, …) |
| `reversed` | Array em ordem decrescente |

## Estrutura do projeto

```
src/
  main.cpp        — ponto de entrada; configura algoritmos, tamanhos e tipos de entrada
  sorts.h/.cpp    — implementação dos 4 algoritmos de ordenação
  generator.h/.cpp — geração dos arrays de teste para cada cenário
  benchmark.h/.cpp — medição de tempo (chrono) e escrita do CSV de resultados
scripts/
  plot.py          — lê o CSV e gera gráficos (por tipo, combinado e escala linear)
results/           — CSV com os tempos e gráficos PNG (gerados automaticamente)
Makefile           — comandos de compilação, execução e plotagem
```

## Requisitos

- **g++** com suporte a C++17
- **Python 3** com `pandas` e `matplotlib`

## Passo a passo

### 1. Clonar o repositório

```bash
git clone <url-do-repo>
cd APA
```

### 2. Instalar dependências Python (com uv)

```bash
uv venv
source .venv/bin/activate
uv pip install pandas matplotlib
```

> Sem uv, use `pip install pandas matplotlib` direto.

### 3. Compilar e rodar tudo

```bash
make
```

Isso compila o benchmark, executa todos os cenários e gera os gráficos em `results/`.

### 4. (Opcional) Rodar etapas separadas

```bash
make run    # compila e roda o benchmark (gera results/results.csv)
make plot   # gera os gráficos a partir do CSV
```

## Comandos do Makefile

| Comando | O que faz |
|---------|-----------|
| `make` | Compila, roda o benchmark e gera os gráficos |
| `make run` | Compila e executa o benchmark (todos os cenários) |
| `make plot` | Gera os gráficos PNG a partir de `results/results.csv` |
| `make test-random` | Roda apenas com entrada aleatória |
| `make test-few-unique` | Roda apenas com poucos valores únicos |
| `make test-sorted` | Roda apenas com entrada ordenada |
| `make test-reversed` | Roda apenas com entrada invertida |
| `make clean` | Remove o binário e tudo em `results/` |
| `make clean-results` | Remove apenas o CSV de resultados |

## Saída

Após rodar, a pasta `results/` conterá:

- `results.csv` — tempos de cada algoritmo por cenário e tamanho
- `graph_random.png`, `graph_sorted.png`, etc. — gráfico individual por cenário (escala log-log)
- `graph_combined.png` — todos os cenários em um só gráfico (escala log-log)
- `graph_linear.png` — todos os cenários em escala linear
