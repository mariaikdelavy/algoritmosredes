#include <stdio.h>
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

int main() {
    int n, raiz;

    printf("Digite o número de nós: ");
    scanf("%d", &n);

    // Aloca dinamicamente a matriz de adjacência
    int **grafo = (int **)malloc(n * sizeof(int *));
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

    dijkstra(grafo, n, raiz);

    // Libera a memória alocada
    for (int i = 0; i < n; i++) {
        free(grafo[i]);
    }
    free(grafo);

    return 0;
}
