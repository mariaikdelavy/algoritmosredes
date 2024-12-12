#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void dijkstra(int **grafo, int n, int raiz) {
    int dist[n];       
    int visitado[n];   
    
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX; 
        visitado[i] = 0;
    }

    dist[raiz] = 0; 

    for (int i = 0; i < n - 1; i++) {
        int minDist = INT_MAX, u = -1;

        for (int j = 0; j < n; j++) {
            if (!visitado[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        if (u == -1) break; 

        visitado[u] = 1;

        for (int v = 0; v < n; v++) {
            if (grafo[u][v] && !visitado[v] && dist[u] != INT_MAX &&
                dist[u] + grafo[u][v] < dist[v]) {
                dist[v] = dist[u] + grafo[u][v];
            }
        }
    }

    printf("Menores distâncias a partir do nó %d:\n", raiz);
    for (int i = 0; i < n; i++) {
        if (dist[i] == INT_MAX) {
            printf("Nó %d: INFINITO\n", i);
        } else {
            printf("Nó %d: %d\n", i, dist[i]);
        }
    }
}

void adicionarNo(int ***grafo, int *n) {
    int novoTamanho = *n + 1;

    *grafo = realloc(*grafo, novoTamanho * sizeof(int *));
    for (int i = 0; i < novoTamanho; i++) {
        (*grafo)[i] = realloc((*grafo)[i], novoTamanho * sizeof(int));
    }

    for (int i = 0; i < novoTamanho; i++) {
        (*grafo)[i][novoTamanho - 1] = 0;
        (*grafo)[novoTamanho - 1][i] = 0;
    }

    *n = novoTamanho;
    printf("Novo nó %d adicionado.\n", *n - 1);
}

void removerNo(int ***grafo, int *n, int no) {
    int novoTamanho = *n - 1;

    for (int i = 0; i < *n; i++) {
        (*grafo)[i][no] = 0;
        (*grafo)[no][i] = 0;
    }

    printf("Nó %d removido (marcado como desconectado).\n", no);
}

int main() {
    int **grafo, n, raiz, escolha, no;

    printf("Digite o número inicial de nós: ");
    scanf("%d", &n);

    grafo = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        grafo[i] = (int *)malloc(n * sizeof(int));
    }

    printf("Digite a matriz de adjacência do grafo (use 0 para ausência de aresta):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grafo[i][j]);
        }
    }

    printf("Digite o nó raiz (0 a %d): ", n - 1);
    scanf("%d", &raiz);

    while (1) {
        printf("\nEscolha uma opção:\n");
        printf("1. Executar Dijkstra\n");
        printf("2. Adicionar nó\n");
        printf("3. Remover nó\n");
        printf("4. Sair\n");
        printf("Opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                dijkstra(grafo, n, raiz);
                break;
            case 2:
                adicionarNo(&grafo, &n);
                break;
            case 3:
                printf("Digite o nó a ser removido (0 a %d): ", n - 1);
                scanf("%d", &no);
                if (no >= 0 && no < n) {
                    removerNo(&grafo, &n, no);
                } else {
                    printf("Nó inválido!\n");
                }
                break;
            case 4:
                printf("Encerrando...\n");
                for (int i = 0; i < n; i++) {
                    free(grafo[i]);
                }
                free(grafo);
                return 0;
            default:
                printf("Opção inválida!\n");
        }
    }
}
