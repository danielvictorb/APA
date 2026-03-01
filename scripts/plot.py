import pandas as pd
import matplotlib.pyplot as plt
import os

CSV_PATH = "results/results.csv"
OUT_DIR = "results"

def print_table(df):
    pivot = df.pivot_table(index=["input_type", "size"], columns="algorithm", values="time_ms")
    pivot = pivot.reset_index()
    print("\n" + "=" * 90)
    print("TABELA DE RESULTADOS (tempo em ms)")
    print("=" * 90)
    print(pivot.to_string(index=False, float_format="%.2f"))
    print("=" * 90 + "\n")

def plot_by_input_type(df):
    input_types = df["input_type"].unique()

    for itype in input_types:
        subset = df[df["input_type"] == itype]
        fig, ax = plt.subplots(figsize=(10, 6))

        for algo in subset["algorithm"].unique():
            data = subset[subset["algorithm"] == algo]
            ax.plot(data["size"], data["time_ms"], marker="o", label=algo)

        ax.set_title(f"Tempo de execução — {itype}")
        ax.set_xlabel("Tamanho do array")
        ax.set_ylabel("Tempo (ms)")
        ax.legend()
        ax.grid(True, alpha=0.3)
        ax.set_xscale("log")
        ax.set_yscale("log")

        path = os.path.join(OUT_DIR, f"graph_{itype}.png")
        fig.savefig(path, dpi=150, bbox_inches="tight")
        plt.close(fig)
        print(f"Gráfico salvo: {path}")

def plot_combined(df):
    input_types = df["input_type"].unique()
    fig, axes = plt.subplots(2, 2, figsize=(16, 12))
    axes = axes.flatten()

    for i, itype in enumerate(input_types):
        ax = axes[i]
        subset = df[df["input_type"] == itype]

        for algo in subset["algorithm"].unique():
            data = subset[subset["algorithm"] == algo]
            ax.plot(data["size"], data["time_ms"], marker="o", label=algo)

        ax.set_title(itype)
        ax.set_xlabel("Tamanho")
        ax.set_ylabel("Tempo (ms)")
        ax.legend(fontsize=8)
        ax.grid(True, alpha=0.3)
        ax.set_xscale("log")
        ax.set_yscale("log")

    fig.suptitle("Comparação de Algoritmos de Ordenação", fontsize=14)
    fig.tight_layout()
    path = os.path.join(OUT_DIR, "graph_combined.png")
    fig.savefig(path, dpi=150, bbox_inches="tight")
    plt.close(fig)
    print(f"Gráfico combinado salvo: {path}")

def plot_linear(df):
    input_types = df["input_type"].unique()
    fig, axes = plt.subplots(2, 2, figsize=(16, 12))
    axes = axes.flatten()

    for i, itype in enumerate(input_types):
        ax = axes[i]
        subset = df[df["input_type"] == itype]

        for algo in subset["algorithm"].unique():
            data = subset[subset["algorithm"] == algo]
            ax.plot(data["size"], data["time_ms"], marker="o", linewidth=2, label=algo)

        ax.set_title(itype, fontsize=13)
        ax.set_xlabel("Tamanho do array")
        ax.set_ylabel("Tempo (ms)")
        ax.legend(fontsize=9)
        ax.grid(True, alpha=0.3)

    fig.suptitle("Comparação de Algoritmos — Escala Linear", fontsize=14)
    fig.tight_layout()
    path = os.path.join(OUT_DIR, "graph_linear.png")
    fig.savefig(path, dpi=150, bbox_inches="tight")
    plt.close(fig)
    print(f"Gráfico linear salvo: {path}")

if __name__ == "__main__":
    df = pd.read_csv(CSV_PATH)
    print_table(df)
    plot_by_input_type(df)
    plot_combined(df)
    plot_linear(df)
