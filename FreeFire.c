// ===========================================
//  SISTEMA MESTRE – TORRE DE RESGATE
//  Ordenação e Busca Binária com Análise
// ===========================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_COMPONENTES 20

// Estrutura principal dos componentes da torre
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade; // 1 a 10
} Componente;

// Funções utilitárias

// Remove quebra de linha capturada pelo fgets
tvoid limparEnter(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

// Exibe todos os componentes cadastrados
void mostrarComponentes(Componente lista[], int n) {
    printf("\n=== LISTA DE COMPONENTES ===\n");
    for (int i = 0; i < n; i++) {
        printf("[%d] Nome: %s | Tipo: %s | Prioridade: %d\n",
               i + 1, lista[i].nome, lista[i].tipo, lista[i].prioridade);
    }
    printf("================================\n");
}

// ALGORITMOS DE ORDENAÇÃO

// Bubble Sort – Ordena por NOME
int bubbleSortNome(Componente lista[], int n) {
    int comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(lista[j].nome, lista[j + 1].nome) > 0) {
                Componente temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }
    return comparacoes;
}

// Insertion Sort – Ordena por TIPO
int insertionSortTipo(Componente lista[], int n) {
    int comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = lista[i];
        int j = i - 1;

        while (j >= 0 && strcmp(lista[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            lista[j + 1] = lista[j];
            j--;
        }
        lista[j + 1] = chave;
    }
    return comparacoes;
}

// Selection Sort – Ordena por PRIORIDADE
int selectionSortPrioridade(Componente lista[], int n) {
    int comparacoes = 0;

    for (int i = 0; i < n - 1; i++) {
        int menor = i;

        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (lista[j].prioridade < lista[menor].prioridade) {
                menor = j;
            }
        }

        if (menor != i) {
            Componente temp = lista[i];
            lista[i] = lista[menor];
            lista[menor] = temp;
        }
    }
    return comparacoes;
}

// BUSCA BINÁRIA

int buscaBinariaPorNome(Componente lista[], int n, char alvo[]) {
    int inicio = 0, fim = n - 1, meio;
    int comparacoes = 0;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        comparacoes++;

        int cmp = strcmp(lista[meio].nome, alvo);

        if (cmp == 0) {
            printf("Comparações na busca binária: %d\n", comparacoes);
            return meio;
        }
        else if (cmp < 0) {
            inicio = meio + 1;
        }
        else {
            fim = meio - 1;
        }
    }

    printf("Comparações na busca binária: %d\n", comparacoes);
    return -1;
}

//  MENU PRINCIPAL

int main() {
    Componente lista[MAX_COMPONENTES];
    int qtd = 0;
    int opcao;
    bool ordenadoPorNome = false;

    do {
        printf("\n===== MENU TORRE DE RESGATE =====\n");
        printf("1. Adicionar componente\n");
        printf("2. Mostrar componentes\n");
        printf("3. Ordenar por nome (Bubble Sort)\n");
        printf("4. Ordenar por tipo (Insertion Sort)\n");
        printf("5. Ordenar por prioridade (Selection Sort)\n");
        printf("6. Buscar componente por nome (Binária)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {

        case 1: // Cadastro
            if (qtd >= MAX_COMPONENTES) {
                printf("Limite máximo atingido!\n");
                break;
            }

            printf("Nome do componente: ");
            fgets(lista[qtd].nome, 30, stdin);
            limparEnter(lista[qtd].nome);

            printf("Tipo do componente: ");
            fgets(lista[qtd].tipo, 20, stdin);
            limparEnter(lista[qtd].tipo);

            printf("Prioridade (1 a 10): ");
            scanf("%d", &lista[qtd].prioridade);
            getchar();

            qtd++;
            printf("Componente adicionado!\n");
            ordenadoPorNome = false;
            break;

        case 2:
            mostrarComponentes(lista, qtd);
            break;

        case 3: {
            clock_t inicio = clock();
            int comps = bubbleSortNome(lista, qtd);
            clock_t fim = clock();

            ordenadoPorNome = true;

            printf("\nOrdenado por nome usando Bubble Sort.\n");
            printf("Comparações: %d\n", comps);
            printf("Tempo: %.6f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
        } break;

        case 4: {
            clock_t inicio = clock();
            int comps = insertionSortTipo(lista, qtd);
            clock_t fim = clock();

            ordenadoPorNome = false;

            printf("\nOrdenado por tipo usando Insertion Sort.\n");
            printf("Comparações: %d\n", comps);
            printf("Tempo: %.6f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
        } break;

        case 5: {
            clock_t inicio = clock();
            int comps = selectionSortPrioridade(lista, qtd);
            clock_t fim = clock();

            ordenadoPorNome = false;

            printf("\nOrdenado por prioridade usando Selection Sort.\n");
            printf("Comparações: %d\n", comps);
            printf("Tempo: %.6f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
        } break;

        case 6: {
            if (!ordenadoPorNome) {
                printf("Para usar busca binária, primeiro ordene por nome!\n");
                break;
            }

            char alvo[30];
            printf("Nome a buscar: ");
            fgets(alvo, 30, stdin);
            limparEnter(alvo);

            int pos = buscaBinariaPorNome(lista, qtd, alvo);

            if (pos >= 0) {
                printf("\nComponente encontrado!\nNome: %s\nTipo: %s\nPrioridade: %d\n",
                       lista[pos].nome, lista[pos].tipo, lista[pos].prioridade);
            } else {
                printf("Componente NÃO encontrado.\n");
            }
        } break;

        }

    } while (opcao != 0);

    printf("Encerrando sistema... Boa sorte na missão final!\n");
    return 0;
}