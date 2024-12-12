#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void inicializarTabela(int *distancia, int *proximo, int n, int id) {
    for (int i = 0; i < n; i++) {
        if (i == id) {
            distancia[i] = 0; 
            proximo[i] = id;  
        } else {
            distancia[i] = INT_MAX; 
            proximo[i] = -1;        
        }
    }
}

void imprimirTabela(int *distancia, int *proximo, int n, int id) {
    printf("Tabela de roteamento do nó %d:\n", id);
    printf("Nó Destino | Distância | Próximo Nó\n");
    for (int i = 0; i < n; i++) {
        if (distancia[i] == INT_MAX) {
            printf("     %d     |   INFINITO   |    -\n", i);
        } else {
            printf("     %d     |     %d       |    %d\n", i, distancia[i], proximo[i]);
        }
    }
    printf("\n");
}

void atualizarTabela(int *minhaDistancia, int *meuProximo, int *vizinhoDistancia, int **grafo, int n, int meuId, int vizinhoId) {
    for (int i = 0; i < n; i++) {
        if (i == meuId) continue; 

        if (vizinhoDistancia[i] != INT_MAX && grafo[meuId][vizinhoId] != INT_MAX) {
            int novaDistancia = grafo[meuId][vizinhoId] + vizinhoDistancia[i];
            if (novaDistancia < minhaDistancia[i]) {
                minhaDistancia[i] = novaDistancia;
                meuProximo[i] = vizinhoId;
            }
        }
    }
}

int main() {
    int n; 

    printf("Digite o número de nós na rede: ");
    scanf("%d", &n);

    int **grafo = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        grafo[i] = (int *)malloc(n * sizeof(int));
    }

    printf("Digite a matriz de adjacência (use um valor muito alto para representar INFINITO):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grafo[i][j]);
            if (i == j) grafo[i][j] = 0; 
        }
    }

    int **distancia = (int **)malloc(n * sizeof(int *));
    int **proximo = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        distancia[i] = (int *)malloc(n * sizeof(int));
        proximo[i] = (int *)malloc(n * sizeof(int));
        inicializarTabela(distancia[i], proximo[i], n, i);
    }

    int convergiu = 0; 
    int iteracao = 0;

    while (!convergiu) {
        printf("\nIteração %d:\n", ++iteracao);
        convergiu = 1;

        int **distanciaAntiga = (int **)malloc(n * sizeof(int *));
        for (int i = 0; i < n; i++) {
            distanciaAntiga[i] = (int *)malloc(n * sizeof(int));
            memcpy(distanciaAntiga[i], distancia[i], n * sizeof(int));
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grafo[i][j] != INT_MAX && i != j) {
                    atualizarTabela(distancia[i], proximo[i], distancia[j], grafo, n, i, j);
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (distancia[i][j] != distanciaAntiga[i][j]) {
                    convergiu = 0;
                    break;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            free(distanciaAntiga[i]);
        }
        free(distanciaAntiga);

        for (int i = 0; i < n; i++) {
            imprimirTabela(distancia[i], proximo[i], n, i);
        }
    }

    printf("\nAs tabelas de roteamento convergiram!\n");

    for (int i = 0; i < n; i++) {
        free(grafo[i]);
        free(distancia[i]);
        free(proximo[i]);
    }
    free(grafo);
    free(distancia);
    free(proximo);

    return 0;
}
